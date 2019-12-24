#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#ifdef TEST
#include <assert.h>
#endif
#include "const.hpp"
#include "view.hpp"

View::View(sf::VideoMode mode, const sf::String &title) :
sf::RenderWindow(mode, title) 
{
	std::cout << "View constructor" << std::endl;

	if(!tileSet1Texture.loadFromFile("graphics/tileset1.png")){
		std::cout << "Error loading tileset 1." << std::endl;
	}
	else {
		tileSet1.setTexture(tileSet1Texture);
	}

	if(!tileSet1bTexture.loadFromFile("graphics/tileset1b.png")){
		std::cout << "Error loading tileset 1b." << std::endl;
	}
	else {
		tileSet1b.setTexture(tileSet1bTexture);
	}

	if(!HUDTexture.loadFromFile("graphics/HUD.png")){
		std::cout << "Error loading HUD texture." << std::endl;
	}
	else {
		HUD.setTexture(HUDTexture);
	}

	if(!HUDManaTexture.loadFromFile("graphics/energy.png")){
		std::cout << "Error loading Mana texture." << std::endl;
	}
	else {
		HUDMana.setTexture(HUDManaTexture);
	}

	if(!HUDLifeTexture.loadFromFile("graphics/life.png")){
		std::cout << "Error loading Life texture." << std::endl;
	}
	else {
		HUDLife.setTexture(HUDLifeTexture);
	}

	if(!heroTexture.loadFromFile("graphics/hero.png")){
		std::cout << "Error loading Hero texture." << std::endl;
	}
	else {
		hero.setTexture(heroTexture);
	}

	tilesetDisplayed_ = 1;
	tileSetTimer_ = TIME_BETWEEN_FRAME * 3;
	testScroll_ = 0;
	heroTileTimer_ = TIME_BETWEEN_HERO_FRAME;
	heroTileDisplayed_ = 0;
}

void View::update(stateInfo updated_info) {
	info = updated_info;
    clear();
    drawMap(2);
    drawMap(1);
    drawPlayer();
    drawMap(3);
}

void View::resetHeroTileDisplayed() {
	heroTileDisplayed_ = 0;
	heroTileTimer_ = 0;
}

void View::drawPlayer() {
	hero.setPosition(sf::Vector2f(info.player.getScreenPosX(),info.player.getScreenPosY()));
	switch(info.player.getDirection()) {
		case HERO_ORIENTED_LEFT :
			if(info.player.isMoving()) {
				hero.setTextureRect(sf::IntRect(heroTileDisplayed_*HERO_TILE_SIZE_X, (HERO_ORIENTED_LEFT+3)*HERO_TILE_SIZE_Y, HERO_TILE_SIZE_X, HERO_TILE_SIZE_Y));
			}
			else {
				hero.setTextureRect(sf::IntRect(heroTileDisplayed_*HERO_TILE_SIZE_X, HERO_ORIENTED_LEFT*HERO_TILE_SIZE_Y, HERO_TILE_SIZE_X, HERO_TILE_SIZE_Y));
			}
			break;
		case HERO_ORIENTED_RIGHT :
			if(info.player.isMoving()) {
				hero.setTextureRect(sf::IntRect((heroTileDisplayed_+1)*HERO_TILE_SIZE_X, (HERO_ORIENTED_LEFT+3)*HERO_TILE_SIZE_Y, (-1)*HERO_TILE_SIZE_X, HERO_TILE_SIZE_Y));
			}
			else {
				hero.setTextureRect(sf::IntRect((heroTileDisplayed_+1)*HERO_TILE_SIZE_X, HERO_ORIENTED_LEFT*HERO_TILE_SIZE_Y, (-1)*HERO_TILE_SIZE_X, HERO_TILE_SIZE_Y));
			}
			break;
		case HERO_ORIENTED_UP :
			if(info.player.isMoving()) {
				hero.setTextureRect(sf::IntRect(heroTileDisplayed_*HERO_TILE_SIZE_X, (HERO_ORIENTED_UP+3)*HERO_TILE_SIZE_Y, HERO_TILE_SIZE_X, HERO_TILE_SIZE_Y));
			}
			else {
				hero.setTextureRect(sf::IntRect(heroTileDisplayed_*HERO_TILE_SIZE_X, HERO_ORIENTED_UP*HERO_TILE_SIZE_Y, HERO_TILE_SIZE_X, HERO_TILE_SIZE_Y));
			}
			break;
		case HERO_ORIENTED_DOWN :
			if(info.player.isMoving()) {
				hero.setTextureRect(sf::IntRect(heroTileDisplayed_*HERO_TILE_SIZE_X, (HERO_ORIENTED_DOWN+3)*HERO_TILE_SIZE_Y, HERO_TILE_SIZE_X, HERO_TILE_SIZE_Y));
			}
			else {
				hero.setTextureRect(sf::IntRect(heroTileDisplayed_*HERO_TILE_SIZE_X, HERO_ORIENTED_DOWN*HERO_TILE_SIZE_Y, HERO_TILE_SIZE_X, HERO_TILE_SIZE_Y));
			}
			break;
		default :
			break;		
	}
	if(heroTileTimer_ <= 0) {
		heroTileDisplayed_++;
		if(heroTileDisplayed_ == 7) {
			heroTileDisplayed_ = 0;
		}
		heroTileTimer_ = TIME_BETWEEN_HERO_FRAME;
	}
	else {
		heroTileTimer_--;
	}
	draw(hero);
}

void View::drawMap(int layer) {
	int tile_screen_x = info.map_start_p_x / TILE_SIZE;
	int start_blit_x = (info.map_start_p_x % TILE_SIZE)*-1;
	int end_blit_x = start_blit_x + WINDOW_WIDTH + (start_blit_x == 0 ? 0 : TILE_SIZE);

	int tile_screen_y = info.map_start_p_y / TILE_SIZE;
	int start_blit_y = (info.map_start_p_y % TILE_SIZE)*-1;
	int end_blit_y = start_blit_y + WINDOW_HEIGHT + (start_blit_y == 0 ? 0 : TILE_SIZE);
	int tile;
	int tile_tileset_x, tile_tileset_y;

	if(tileSetTimer_ <= 0) {
		if(tilesetDisplayed_) {
			tilesetDisplayed_ = 0;
		}
		else {
			tilesetDisplayed_ = 1;
		}
		tileSetTimer_ = TIME_BETWEEN_FRAME * 3;
	}
	else {
		tileSetTimer_--;
	}

	if(layer == 1) {
		for(int y = start_blit_y; y < end_blit_y; y += TILE_SIZE) {
			tile_screen_x = info.map_start_p_x / TILE_SIZE;
			for(int x = start_blit_x; x < end_blit_x; x += TILE_SIZE) {
				tile = info.layer1[tile_screen_y][tile_screen_x];
				tile_tileset_y = tile / TILES_PER_LINE * TILE_SIZE;
				tile_tileset_x = tile % TILES_PER_LINE * TILE_SIZE;
				if(tilesetDisplayed_) {
					tileSet1.setPosition(sf::Vector2f(x,y));
					tileSet1.setTextureRect(sf::IntRect(tile_tileset_x, tile_tileset_y, TILE_SIZE, TILE_SIZE));
					draw(tileSet1);
				}
				else {
					tileSet1b.setPosition(sf::Vector2f(x,y));
					tileSet1b.setTextureRect(sf::IntRect(tile_tileset_x, tile_tileset_y, TILE_SIZE, TILE_SIZE));
					draw(tileSet1b);
				}
				tile_screen_x++;
			}
			tile_screen_y++;
		}
	}
	else if(layer == 2) {
		for(int y = start_blit_y; y < end_blit_y; y += TILE_SIZE) {
			tile_screen_x = info.map_start_p_x / TILE_SIZE;
			for(int x = start_blit_x; x < end_blit_x; x += TILE_SIZE) {
				tile = info.layer2[tile_screen_y][tile_screen_x];
				tile_tileset_y = tile / TILES_PER_LINE * TILE_SIZE;
				tile_tileset_x = tile % TILES_PER_LINE * TILE_SIZE;
				if(tilesetDisplayed_) {
					tileSet1.setPosition(sf::Vector2f(x,y));
					tileSet1.setTextureRect(sf::IntRect(tile_tileset_x, tile_tileset_y, TILE_SIZE, TILE_SIZE));
					draw(tileSet1);
				}
				else {
					tileSet1b.setPosition(sf::Vector2f(x,y));
					tileSet1b.setTextureRect(sf::IntRect(tile_tileset_x, tile_tileset_y, TILE_SIZE, TILE_SIZE));
					draw(tileSet1b);
				}
				tile_screen_x++;
			}
			tile_screen_y++;
		}
	}
	else if(layer == 3) {
		for(int y = start_blit_y; y < end_blit_y; y += TILE_SIZE) {
			tile_screen_x = info.map_start_p_x / TILE_SIZE;
			for(int x = start_blit_x; x < end_blit_x; x += TILE_SIZE) {
				tile = info.layer3[tile_screen_y][tile_screen_x];
				tile_tileset_y = tile / TILES_PER_LINE * TILE_SIZE;
				tile_tileset_x = tile % TILES_PER_LINE * TILE_SIZE;
				if(tilesetDisplayed_) {
					tileSet1.setPosition(sf::Vector2f(x,y));
					tileSet1.setTextureRect(sf::IntRect(tile_tileset_x, tile_tileset_y, TILE_SIZE, TILE_SIZE));
					draw(tileSet1);
				}
				else {
					tileSet1b.setPosition(sf::Vector2f(x,y));
					tileSet1b.setTextureRect(sf::IntRect(tile_tileset_x, tile_tileset_y, TILE_SIZE, TILE_SIZE));
					draw(tileSet1b);
				}
				tile_screen_x++;
			}
			tile_screen_y++;
		}
	}
}

#ifdef TEST
bool View::runUnitTest()
{
	return true;
}
#endif