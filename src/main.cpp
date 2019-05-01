#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "const.hpp"
#include "view.hpp"
#include "input.hpp"
#include "controller.hpp"

int main(int argc, char *argv[])
{
	View window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LittleWorld");
	Controller controller(&window);
	window.loadMap();
    while (window.isOpen())
    {
    	controller.handleInputs();
    	window.clear();
        window.drawMap(2);
        window.drawMap(1);
        window.drawMap(3);
        window.display();
    }
	return 0;
}