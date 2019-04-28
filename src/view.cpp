#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "const.hpp"
#include "view.hpp"

View::View(sf::VideoMode mode, const sf::String &title) :
sf::RenderWindow(mode, title) 
{
	std::cout << "View constructor" << std::endl;
}