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

    while (window.isOpen())
    {
    	controller.handleInputs();
        window.clear();
        window.display();
    }
	return 0;
}