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
	Model model;
	Controller controller(&window, &model);

	model.addObserver(&window);
	model.loadMap();
	window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
    	controller.handleInputs();
    	model.updateView();
        window.display();
    }
	return 0;
}