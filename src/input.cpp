#include <SFML/Graphics.hpp>

#include "input.hpp"
#include "view.hpp"

Input::Input() :
event_(),
button_()
{
	std::cout << "Input constructor" << std::endl;
}

Button Input::getButton(void) const {
	return button_;
}

void Input::setButton(buttonType button, bool state) {
	switch(button) {
		case left:
			button_.left = state;
			break;
		case right:
			button_.right = state;
			break;
		case up:
			button_.up = state;
			break;
		case down:
			button_.down = state;
			break;
		case attack:
			button_.attack = state;
			break;
		case spell:
			button_.spell = state;
			break;
		case run:
			button_.run = state;
			break;
		case enter:
			button_.enter = state;
			break;
		default:
			break;
	}
}

void Input::handleInputs(View &window) {
	while (window.pollEvent(event_)) {
	    switch (event_.type) {
	    	case sf::Event::Closed :
	    		window.close();
	    		break;
	    	case sf::Event::KeyPressed :
	    		switch(event_.key.code) {
	    			case sf::Keyboard::Escape :
	    				window.close();
	    				break;
	    			case sf::Keyboard::LShift :
	    				button_.run = true;
	    				break;
	    			case sf::Keyboard::Q :
	    				button_.left = true;
	    				break;
	    			case sf::Keyboard::D :
	    				button_.right = true;
	    				break;
	    			case sf::Keyboard::Z :
	    				button_.up = true;
	    				break;
	    			case sf::Keyboard::S :
	    				button_.down = true;
	    				break;
	    			case sf::Keyboard::Space :
	    				button_.attack = true;
	    				break;
	    			case sf::Keyboard::LControl :
	    				button_.spell = true;
	    				break;
	    			default :
	    				break;
	    		}
	    	case sf::Event::KeyReleased :
	    		switch(event_.key.code) {
	    			case sf::Keyboard::Escape :
	    				window.close();
	    				break;
	    			case sf::Keyboard::LShift :
	    				button_.run = false;
	    				break;
	    			case sf::Keyboard::Q :
	    				button_.left = false;
	    				break;
	    			case sf::Keyboard::D :
	    				button_.right = false;
	    				break;
	    			case sf::Keyboard::Z :
	    				button_.up = false;
	    				break;
	    			case sf::Keyboard::S :
	    				button_.down = false;
	    				break;
	    			case sf::Keyboard::Space :
	    				button_.attack = false;
	    				break;
	    			case sf::Keyboard::LControl :
	    				button_.spell = false;
	    				break;
	    			default :
	    				break;
	    		}
	    	default:
	    		break;
	    }
    }
}