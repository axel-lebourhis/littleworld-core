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
	View window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LW Unit Test App");
	Model model;
	Controller controller(&window, &model);
	model.addObserver(&window);

	/* model unit test */
	std::cout << "START MODEL UNIT TEST" << std::endl;
	model.runUnitTest();
	std::cout << "MODEL UNIT TEST PASSED" << std::endl;

	/* controller unit test */
	std::cout << "START CONTROLLER UNIT TEST" << std::endl;
	controller.runUnitTest();
	std::cout << "CONTROLLER UNIT TEST PASSED" << std::endl;

	/* view unit test */
	std::cout << "START VIEW UNIT TEST" << std::endl;
	window.runUnitTest();
	std::cout << "VIEW UNIT TEST PASSED" << std::endl;

	return 0;
}