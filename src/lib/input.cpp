#include <SFML/Graphics.hpp>

#include "input.hpp"
#include "view.hpp"
#include "model.hpp"
#include "const.hpp"
#include "player.hpp"

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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if(!model->getPlayerMoving()) {
			window->resetHeroTileDisplayed();
		}
		model->setPlayerMoving(true);
		model->moveDown(moveOffset_);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if(!model->getPlayerMoving()) {
			window->resetHeroTileDisplayed();
		}
		model->setPlayerMoving(true);
		model->moveUp(moveOffset_);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if(!model->getPlayerMoving()) {
			window->resetHeroTileDisplayed();
		}
		model->setPlayerMoving(true);
		model->moveLeft(moveOffset_);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if(!model->getPlayerMoving()) {
			window->resetHeroTileDisplayed();
		}
		model->setPlayerMoving(true);
		model->moveRight(moveOffset_);
	}
	else {
		model->setPlayerMoving(false);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		moveOffset_ = RUN_MOVE_SPEED;
	}
	else {
		moveOffset_ = MOVE_SPEED;
	}
}
