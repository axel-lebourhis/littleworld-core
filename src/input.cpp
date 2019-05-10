#include <SFML/Graphics.hpp>

#include "input.hpp"
#include "view.hpp"
#include "model.hpp"
#include "const.hpp"

Input::Input() :
event_()
{
	std::cout << "Input constructor" << std::endl;
	moveOffset_ = MOVE_SPEED;
}

void Input::handleInputs(View* window, Model* model) {
	window->pollEvent(event_);
	if(event_.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window->close();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		model->moveDown(moveOffset_);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		model->moveUp(moveOffset_);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		model->moveLeft(moveOffset_);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		model->moveRight(moveOffset_);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		moveOffset_ = RUN_MOVE_SPEED;
	}
	else {
		moveOffset_ = MOVE_SPEED;
	}
}
