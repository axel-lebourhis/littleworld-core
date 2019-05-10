#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include "observer.hpp"
#include "view.hpp"
#include "model.hpp"

class Input
{
private:
	sf::Event event_;
	int moveOffset_;

public:
	Input();

	void handleInputs(View* window, Model* model);
};

#endif