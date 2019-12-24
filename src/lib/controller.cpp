#include <SFML/Graphics.hpp>
#ifdef TEST
#include <assert.h>
#endif
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

#ifdef TEST
bool Controller::runUnitTest()
{
	return true;
}
#endif