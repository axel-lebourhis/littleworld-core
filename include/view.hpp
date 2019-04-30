#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "const.hpp"
#include "observer.hpp"

class View : public sf::RenderWindow , public Observer<int>
{
//private:

public:
	View(sf::VideoMode mode, const sf::String &title);

	void update(int info) override;
};

#endif