#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../header/main.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Bouncing DVD logo", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    sf::Texture textureDVD;
    textureDVD.loadFromFile("../ressources/DVD_logo.png");
    textureDVD.setSmooth(true);
    sf::Texture textureFlute;
    textureFlute.loadFromFile("../ressources/flute.png");
    textureFlute.setSmooth(true);

    sf::Vector2i position =
    {
        rand() % (SCREEN_X+1 - (int)textureDVD.getSize().x),
        rand() % (SCREEN_Y+1 - (int)textureDVD.getSize().y)
    };

    sf::Sprite sprite;
    sprite.setTexture(textureDVD);
    sprite.setOrigin(textureDVD.getSize().x / 2, textureDVD.getSize().y / 2);
    sprite.setPosition(position.x, position.y);
    sprite.setColor(color());

    sf::Vector2i speed = {4, 4};
    sf::Vector2i spriteSize = {(int)(textureDVD.getSize().x), (int)(textureDVD.getSize().y)};
    
    sf::SoundBuffer bufferNoise;
    bufferNoise.loadFromFile("../ressources/ouh.wav");
    sf::Sound noise;
    noise.setBuffer(bufferNoise);
   
    sf::Music music1;
    music1.openFromFile("../ressources/plaza_music.ogg");
    sf::Music music2;
    music2.openFromFile("../ressources/take_on_me_flute.ogg");

    bool escapePressed = false;
    bool F1Pressed = false;
    bool F2Pressed = false;
    float rotation = 1.0;
    bool isFlute = false;

    while (window.isOpen())
    {
        sf::Event event;

        position = {position.x + speed.x, position.y + speed.y};

        if (position.x + spriteSize.x >= SCREEN_X)
        {
            speed.x = -speed.x;
            position.x = SCREEN_X - spriteSize.x;
            if (!isFlute)
            {
                sprite.setColor(color());
            }
            if (escapePressed)
            {
                noise.play();
            }
        }
        else if (position.x <= 0)
        {
            speed.x = -speed.x;
            position.x = 0;
            if (!isFlute)
            {
                sprite.setColor(color());
            }
            if (escapePressed)
            {
                noise.play();
            }
        }
        else if (position.y + spriteSize.y >= SCREEN_Y)
        {
            speed.y = -speed.y;
            position.y = SCREEN_Y - spriteSize.y;
            
            if (!isFlute)
            {
                sprite.setColor(color());
            }

            if (escapePressed)
            {
                noise.play();
            }
        }
        else if (position.y <= 0)
        {
            speed.y = -speed.y;
            position.y = 0;
            if (!isFlute)
            {
                sprite.setColor(color());
            }
            if (escapePressed)
            {
                noise.play();
            }
        }
        
        sprite.setPosition(position.x + speed.x, position.y + speed.y);
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    escapePressed = !escapePressed;
                }
                else if(event.key.code == sf::Keyboard::F1)
                {
                    F1Pressed = !F1Pressed;
                    if (F1Pressed)
                    {
                        music1.play();
                        music1.setLoop(true);
                        speed *= 5;
                    }
                    else
                    {
                        music1.stop();
                        speed /= 5;
                    }
                }
                else if(event.key.code == sf::Keyboard::F2)
                {
                    F2Pressed = !F2Pressed;
                    if (F2Pressed)
                    {
                        music2.play();
                        music2.setLoop(true);
                        speed *= 5;
                        sprite.setTexture(textureFlute);
                        sprite.setColor(sf::Color::White);
                        isFlute = true;
                    }
                    else
                    {
                        music2.stop();
                        speed /= 5;
                        sprite.setTexture(textureDVD);
                        isFlute = false;
                    }
                }
            }
        }

        if (isFlute)
        {
            rotation += 5;
            sprite.setRotation(rotation);
        }
        else
        {
            sprite.setOrigin(0, 0);
            sprite.setRotation(0);
        }

        window.setPosition(sf::Vector2i(0, 0));
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

sf::Color color()
{
    sf::Color color =
    {
        (sf::Uint8)(100 + (rand() % 256)),
        (sf::Uint8)(100 + (rand() % 256)),
        (sf::Uint8)(100 + (rand() % 256))
    };

    return color;
}
