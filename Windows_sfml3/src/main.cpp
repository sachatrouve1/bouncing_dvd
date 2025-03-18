#include <SFML/System/Angle.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "../header/main.hpp"

using namespace std;

#define ANTIALIASING 8
#define VSYNC true

int main(int argc, char const *argv[])
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = ANTIALIASING;
    sf::RenderWindow window(sf::VideoMode({(unsigned)SCREEN.x, (unsigned)SCREEN.y}), "Bouncing DVD logo", sf::State::Fullscreen, settings);
    window.setVerticalSyncEnabled(true);

    string logoFilename = "../ressources/DVD_logo.png";
    string fluteFilename = "../ressources/flute.png";
    string ouhSoundFilename = "../ressources/ouh.wav";
    string plazaMusicFilename = "../ressources/plaza_music.ogg";
    string tomfMusicFilename = "../ressources/take_on_me_flute.ogg";
    
    sf::Texture textureDVD;
    if (!textureDVD.loadFromFile(logoFilename))
    {
        cout << "Cannot load " << logoFilename << endl;
    }
    textureDVD.setSmooth(true);

    sf::Texture textureFlute;
    if (!textureFlute.loadFromFile(fluteFilename))
    {
        cout << "Cannot load " << fluteFilename << endl;
    }
    textureFlute.setSmooth(true);

    sf::Vector2i position =
    {
        rand() % (SCREEN.x+1 - (int)textureDVD.getSize().x),
        rand() % (SCREEN.y+1 - (int)textureDVD.getSize().y)
    };

    sf::Sprite sprite(textureDVD);
    sprite.setOrigin({(float)textureDVD.getSize().x / 2, (float)textureDVD.getSize().y / 2});
    sprite.setPosition({(float)position.x, (float)position.y});
    sprite.setColor(color());

    sf::Vector2i speed = {4, 4};
    sf::Vector2i spriteSize = {(int)(textureDVD.getSize().x), (int)(textureDVD.getSize().y)};
    
    sf::SoundBuffer bufferNoise;
    if (!bufferNoise.loadFromFile(ouhSoundFilename))
    {
        cout << "cannot load" << ouhSoundFilename << endl;
    }
    sf::Sound noise(bufferNoise);

    sf::Music music1;
    if (!music1.openFromFile(plazaMusicFilename))
    {
        cout << "cannot load" << plazaMusicFilename << endl;
    }
    sf::Music music2;
    if (!music2.openFromFile(tomfMusicFilename))
    {
        cout << "cannot load" << tomfMusicFilename << endl;
    }

    bool escapePressed = false;
    bool F1Pressed = false;
    bool F2Pressed = false;
    sf::Angle rotation = sf::degrees(1.0);
    bool isFlute = false;

    while (window.isOpen())
    {
        position = {position.x + speed.x, position.y + speed.y};

        if (position.x + spriteSize.x >= SCREEN.x)
        {
            speed.x = -speed.x;
            position.x = SCREEN.x - spriteSize.x;
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
        else if (position.y + spriteSize.y >= SCREEN.y)
        {
            speed.y = -speed.y;
            position.y = SCREEN.y - spriteSize.y;
            
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
        
        sprite.setPosition({(float)(position.x + speed.x), (float)(position.y + speed.y)});
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyPressed->scancode)
                {
                case sf::Keyboard::Scancode::Delete:
                    window.close();
                    exit(0);
                    break;

                case sf::Keyboard::Scancode::Escape:
                    escapePressed = !escapePressed;
                    break;

                case sf::Keyboard::Scancode::F1:
                    F1Pressed = !F1Pressed;
                    
                    if (F1Pressed)
                    {
                        music1.play();
                        music1.setLooping(true);
                        speed *= 5;
                    }
                    else
                    {
                        music1.stop();
                        speed /= 5;
                    }
                    break;
                
                case sf::Keyboard::Scancode::F2:
                    F2Pressed = !F2Pressed;

                    if (F2Pressed)
                    {
                        music2.play();
                        music2.setLooping(true);
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
                    break;
                
                default:
                    break;
                }
            }
        }

        if (isFlute)
        {
            rotation += sf::degrees(5);
            sprite.setRotation(rotation);
        }
        else
        {
            sprite.setOrigin({0, 0});
            sprite.setRotation(sf::degrees(0));
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
        (uint8_t)(100 + (rand() % 256)),
        (uint8_t)(100 + (rand() % 256)),
        (uint8_t)(100 + (rand() % 256))
    };

    return color;
}
