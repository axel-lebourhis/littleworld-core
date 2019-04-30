#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "const.hpp"
#include "view.hpp"
#include "input.hpp"

int main(int argc, char *argv[])
{
	View window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LittleWorld");
	Input input;

    while (window.isOpen())
    {
    	input.handleInputs(window);
        window.clear();
        window.display();
    }
	return 0;
}