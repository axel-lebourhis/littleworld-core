#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "const.hpp"
#include "observer.hpp"

class View : public sf::RenderWindow , public Observer<int>
{
private:
	// textures
	sf::Texture tileSet1Texture;
	sf::Texture tileSet1bTexture;
	sf::Texture HUDTexture;
	sf::Texture HUDManaTexture;
	sf::Texture HUDLifeTexture;
	// sprites
	sf::Sprite tileSet1;
	sf::Sprite tileSet1b;
	sf::Sprite HUD;
	sf::Sprite HUDMana;
	sf::Sprite HUDLife;
	// misc
	int charBeginX_, charBeginY_;
	int mapStartX_, mapStartY_;
	int mapMaxX_, mapMaxY_;
	int tilesetDisplayed_;

	int layer1_[80][80];
	int layer2_[80][80];
	int layer3_[80][80];
	int layer4_[80][80];

public:
	View(sf::VideoMode mode, const sf::String &title);

	void update(int info) override;

	void loadMap();
	void drawMap(int layer);
};

#endif