#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "const.hpp"
#include "observer.hpp"
#include "player.hpp"
#include "monster.hpp"

struct stateInfo {
	Player player;
	Monster monsters[MAX_MONSTERS];
	int map_start_p_x;
	int map_start_p_y;
	int map_max_p_x;
	int map_max_p_y;
	int tile_number_x;
	int tile_number_y;
	int layer1[MAX_TILES_XY][MAX_TILES_XY];
	int layer2[MAX_TILES_XY][MAX_TILES_XY];
	int layer3[MAX_TILES_XY][MAX_TILES_XY];
	int layer4[MAX_TILES_XY][MAX_TILES_XY];
	int tilesetDisplayed;
	int nbMonsters;

	stateInfo() :
	player() 
	{
		map_start_p_x = 0;
		map_start_p_y = 0;
		map_max_p_x = 0;
		map_max_p_y = 0;
		tile_number_x = 0;
		tile_number_y = 0;
		tilesetDisplayed = 0;
		for(int i = 0; i < MAX_TILES_XY; i++) {
			for(int j = 0; j < MAX_TILES_XY; j++) {
				layer1[i][j] = 0;
				layer2[i][j] = 0;
				layer3[i][j] = 0;
				layer4[i][j] = 0;
			}
		}
		for(int i = 0; i < MAX_MONSTERS; i++) {
			monsters[i] = Monster();
		}
	}

	stateInfo(const stateInfo& copy_info)
	{
		player = copy_info.player;
		map_start_p_x = copy_info.map_start_p_x;
		map_start_p_y = copy_info.map_start_p_y;
		map_max_p_x = copy_info.map_max_p_x;
		map_max_p_y = copy_info.map_max_p_y;
		tile_number_x = copy_info.tile_number_x;
		tile_number_y = copy_info.tile_number_y;
		tilesetDisplayed = copy_info.tilesetDisplayed;
		nbMonsters = copy_info.nbMonsters;
		for(int i = 0; i < nbMonsters; i++) {
			monsters[i] = copy_info.monsters[i];
		}
		for(int i = 0; i < MAX_TILES_XY; i++) {
			for(int j = 0; j < MAX_TILES_XY; j++) {
				layer1[i][j] = copy_info.layer1[i][j];
				layer2[i][j] = copy_info.layer2[i][j];
				layer3[i][j] = copy_info.layer3[i][j];
				layer4[i][j] = copy_info.layer4[i][j];
			}
		}
	}
};

class View : public sf::RenderWindow , public Observer<stateInfo>
{
private:
	// textures
	sf::Texture tileSet1Texture;
	sf::Texture tileSet1bTexture;
	sf::Texture heroTexture;
	sf::Texture monster1Texture;
	sf::Texture monster2Texture;
	sf::Texture monster3Texture;
	sf::Texture HUDTexture;
	sf::Texture HUDManaTexture;
	sf::Texture HUDLifeTexture;
	// sprites
	sf::Sprite tileSet1;
	sf::Sprite tileSet1b;
	sf::Sprite hero;
	sf::Sprite monster1;
	sf::Sprite monster2;
	sf::Sprite monster3;
	sf::Sprite HUD;
	sf::Sprite HUDMana;
	sf::Sprite HUDLife;
	// state_info
	stateInfo info;

	// misc
	int tilesetDisplayed_;
	int tileSetTimer_;
	int heroTileTimer_;
	int heroTileDisplayed_;
	int testScroll_;

public:
	View(sf::VideoMode mode, const sf::String &title);

	void update(stateInfo updated_info) override;

	void drawMap(int layer);
	void drawPlayer();
	void drawMonsters();

	void resetHeroTileDisplayed();

#ifdef TEST
	bool runUnitTest();
#endif
};

#endif