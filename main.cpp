
#include<iostream>

#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>



int main()
{
   sf:: RenderWindow window(sf::VideoMode(512,512), "x o game", sf:: Style::Default);
   sf::Event ev;
   sf::Sprite background;
   sf::Texture backgroundimage;
   backgroundimage.loadFromFile("background.png");
   background.setTexture(backgroundimage);

   sf::Vector2u texturesize = backgroundimage.getSize();
   sf::Vector2u windowsize = window.getSize();

   float scalex = static_cast<float>(windowsize.x) / texturesize.x;
   float scaley = static_cast<float>(windowsize.y) / texturesize.y;

   background.setScale(scalex, scaley);

   const int pos = 13;


   sf::Sprite x[5];
   sf::Texture xtexture;
   xtexture.loadFromFile("x.png");

   sf::Sprite o[5];
   sf::Texture otexture;
   otexture.loadFromFile("o.png");

   for (int i = 0; i < 5; i++) {
       x[i].setTexture(xtexture);
       x[i].setScale(scaley, scalex);
       x[i].setPosition((4 * pos * scalex + scalex), (4 * pos * scaley + scaley));
       o[i].setTexture(otexture);
       o[i].setScale(scaley, scalex);
       o[i].setPosition((4 * pos * scalex + scalex), (4 * pos * scaley + scaley));
   }
  
   sf::Sprite s;
   sf::Texture stexture;
   stexture.loadFromFile("select.png");
   s.setTexture(stexture);
   s.setScale(scalex, scaley);
   s.setPosition(0, 0);

   float bestnumber = pos * scalex;

   int state[3][3]{} ;
  
   bool ismoving = false;
   bool still = true;
   int turn = 1;

   int scorex = 0, scoreo = 0;

    while (window.isOpen())
    {
        while (window.pollEvent(ev)) 
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        sf::Vector2f spos = s.getPosition();
        int sx = spos.x / bestnumber;
        int sy = spos.y / bestnumber;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (ismoving == false && sy<2 ) {
                spos.y += bestnumber;
                ismoving = true;
            }
        }else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (ismoving == false && sy >0) {
                spos.y -= bestnumber;
                ismoving = true;
            }
        }else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (ismoving == false && sx>0) {
                spos.x -= bestnumber;
                ismoving = true;
            }
        }else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (ismoving == false && sx < 2) {
                spos.x += bestnumber;
                ismoving = true;
            }
        }
        else
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
            {
                if (ismoving == false &&still &&state[sx][sy]==0) {
                    if (turn % 2) {
                        x[turn / 2].setPosition(spos.x + pos, spos.y + pos);
                        state[sx][sy] = 1;
                        if ((state[0][0] ==1 && state[1][1] ==1 && state[2][2] ==1 ) || (state[0][0] ==1 && state[0][1] ==1 && state[0][2] ==1 ) || (state[0][0] ==1 && state[1][0] ==1 && state[2][0] ==1 ) || (state[1][0] ==1 && state[1][1] ==1 && state[1][2] ==1 ) || (state[0][1] ==1 && state[1][1] ==1 && state[2][1] ==1 ) || (state[2][0] ==1 && state[1][1] ==1 && state[0][2] ==1 ) || (state[2][0] ==1 && state[2][1] ==1 && state[2][2] ==1 ) || (state[0][2] ==1 && state[1][2] ==1 && state[2][2] ==1 ))
                        {
                            still = false;
                            scorex++;
                            std::cout << "the winner is: X \n";
                            std::cout << "scores: X: " << scorex << '\t' << "O: " << scoreo<<'\n';
                            std::cout << "press ENTER to play a new game\npress SHIFT to reset scores\n";
                        }
                        turn++;
                    }
                    else
                        if (turn % 2 == 0 &&still) {
                            o[turn / 2].setPosition(spos.x + pos, spos.y + pos);
                            state[sx][sy] = 2;
                            turn++;
                            if ((state[0][0] ==2 && state[1][1] ==2 && state[2][2] ==2 ) || (state[0][0] ==2 && state[0][1] ==2 && state[0][2] ==2 ) || (state[0][0] ==2 && state[1][0] ==2 && state[2][0] ==2 ) || (state[1][0] ==2 && state[1][1] ==2 && state[1][2] ==2 ) || (state[0][1] ==2 && state[1][1] ==2 && state[2][1] ==2 ) || (state[2][0] ==2 && state[1][1] ==2 && state[0][2] ==2 ) || (state[2][0] ==2 && state[2][1] ==2 && state[2][2] ==2 ) || (state[0][2] ==2 && state[1][2] ==2 && state[2][2] ==2 ))
                            {
                                still = false;
                                scoreo++;
                                std::cout << "the winner is: O\n";
                                std::cout << "scores: X: " << scorex << '\t' << "O: " << scoreo<<'\n';

                            }
                        }
                    ismoving = true;
                }
            }
            else 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (ismoving == false  ) {
                        for (int i = 0; i < 5; i++) {
                            x[i].setPosition((4 * pos * scalex + scalex), (4 * pos * scaley + scaley));
                            o[i].setPosition((4 * pos * scalex + scalex), (4 * pos * scaley + scaley));
                        }
                        state[0][0] = 0;
                        state[0][1] = 0;
                        state[0][2] = 0;

                        state[1][0] = 0;
                        state[1][1] = 0;
                        state[1][2] = 0;

                        state[2][0] = 0;
                        state[2][1] = 0;
                        state[2][2] = 0;

                        turn = 1;
                        ismoving = true;
                        still = true;
                    }
                }else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            if (ismoving == false ) {
                scorex = 0;
                scoreo = 0;
                std::cout << "scores: X: " << scorex << '\t' << "O: " << scoreo << '\n';
                ismoving = true;
            }

        }
                else
            {
                ismoving = false;

            }
        s.setPosition(spos.x,spos.y );
        
        window.clear();
        window.draw(background);
        for (int i = 0; i < 5; i++)
        {
            window.draw(x[i]);
            window.draw(o[i]);
        }
        window.draw(s);
        window.display();
    }
    

    return 0;
}