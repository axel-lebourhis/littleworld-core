#include <SFML/Graphics.hpp>

#include "controller.hpp"

Controller::Controller(View* view) :
input_()
{
	std::cout << "Controller constructor" << std::endl;
	view_ = view;
}

void Controller::handleInputs() {
	input_.handleInputs(view_);
}