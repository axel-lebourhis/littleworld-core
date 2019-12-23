#include <SFML/Graphics.hpp>

#include "controller.hpp"

Controller::Controller(View* view, Model* model) :
input_()
{
	std::cout << "Controller constructor" << std::endl;
	view_ = view;
	model_ = model;
}

void Controller::handleInputs() {
	input_.handleInputs(view_, model_);
}