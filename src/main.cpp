#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "const.hpp"
#include "view.hpp"
#include "input.hpp"
#include "controller.hpp"
#include "model.hpp"

int main(int argc, char *argv[])
{
	View window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LittleWorld");
	Controller controller(&window);
	Model model;

	model.addObserver(&window);
	model.loadMap();
	window.setVerticalSyncEnabled(true);
	//window.loadMap();
    while (window.isOpen())
    {
    	controller.handleInputs();
    	model.testScroll();
    	model.updateView();
    	//window.update(0);
        window.display();
    }
	return 0;
}