#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "const.hpp"

int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LittleWorld");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
	return 0;
}