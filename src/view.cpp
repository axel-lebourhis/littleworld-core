#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
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
}

void View::update(int info) {
	
}

void View::loadMap() {
	std::fstream file_stream;

	mapMaxX_ = 0; 
	mapMaxY_ = 0;

	std::vector<std::vector<int>> lines;
	std::vector<int> line_v;

	std::string strBuf;
	std::stringstream strStream;

	file_stream.open("map/map1.txt", std::fstream::in);

	if(!file_stream.is_open()) {
		std::cerr << "Error opening map file." << std::endl;
	}

	while(!file_stream.eof()) {
		getline(file_stream, strBuf);
		if(!strBuf.size())
			continue;

		strStream.clear();
		strStream.str(strBuf);
		line_v.clear();
		strBuf.clear();
		while(true) {
			getline(strStream, strBuf, ' ');
			line_v.push_back(atoi(strBuf.c_str()));
			if(!strStream.good())
				break;
		}
		if(line_v.size())
			lines.push_back(line_v);
	}
	file_stream.close();

	charBeginX_ = lines[0][0];
	charBeginY_ = lines[0][1];
	tilesetDisplayed_ = lines[0][2];

	for(int x = 3; x < MAX_TILES_XY + 3; x++) {
		layer1_[0][x-3] = lines[0][x];
	}

	for(int y = 1; y < MAX_TILES_XY; y++) {
		for(int x = 0; x < MAX_TILES_XY; x++) {
			layer1_[y][x] = lines[y][x];
			if(layer1_[y][x] > 0) {
				if(x > mapMaxX_)
					mapMaxX_ = x;
				if(y > mapMaxY_)
					mapMaxY_ = y;
			}
		}
	}

	for(int y = 0; y < MAX_TILES_XY; y++) {
		for(int x = 0; x < MAX_TILES_XY; x++) {
			layer2_[y][x] = lines[y+MAX_TILES_XY][x];
		}
	}

	for(int y = 0; y < MAX_TILES_XY; y++) {
		for(int x = 0; x < MAX_TILES_XY; x++) {
			layer3_[y][x] = lines[y+MAX_TILES_XY*2][x];
		}
	}

	for(int y = 0; y < MAX_TILES_XY; y++) {
		for(int x = 0; x < MAX_TILES_XY; x++) {
			layer4_[y][x] = lines[y+MAX_TILES_XY*3][x];
		}
	}
}

void View::drawMap(int layer) {
	int tile_screen_x = charBeginX_ / TILE_SIZE;
	int start_blit_x = (charBeginX_ % TILE_SIZE)*-1;
	int end_blit_x = start_blit_x + WINDOW_WIDTH + (start_blit_x == 0 ? 0 : TILE_SIZE);

	int tile_screen_y = charBeginY_ / TILE_SIZE;
	int start_blit_y = (charBeginY_ % TILE_SIZE)*-1;
	int end_blit_y = start_blit_y + WINDOW_HEIGHT + (start_blit_y == 0 ? 0 : TILE_SIZE);
	int tile;
	int tile_tileset_x, tile_tileset_y;

	if(layer == 1) {
		for(int y = start_blit_y; y < end_blit_y; y += TILE_SIZE) {
			tile_screen_x = charBeginX_ / TILE_SIZE;
			for(int x = start_blit_x; x < end_blit_x; x += TILE_SIZE) {
				tile = layer1_[tile_screen_y][tile_screen_x];
				tile_tileset_y = tile / TILES_PER_LINE * TILE_SIZE;
				tile_tileset_x = tile % TILES_PER_LINE * TILE_SIZE;
				tileSet1.setPosition(sf::Vector2f(x,y));
				tileSet1.setTextureRect(sf::IntRect(tile_tileset_x, tile_tileset_y, TILE_SIZE, TILE_SIZE));
				draw(tileSet1);
				tile_screen_x++;
			}
			tile_screen_y++;
		}
	}
	else if(layer == 2) {
		for(int y = start_blit_y; y < end_blit_y; y += TILE_SIZE) {
			tile_screen_x = charBeginX_ / TILE_SIZE;
			for(int x = start_blit_x; x < end_blit_x; x += TILE_SIZE) {
				tile = layer2_[tile_screen_y][tile_screen_x];
				tile_tileset_y = tile / TILES_PER_LINE * TILE_SIZE;
				tile_tileset_x = tile % TILES_PER_LINE * TILE_SIZE;
				tileSet1.setPosition(sf::Vector2f(x,y));
				tileSet1.setTextureRect(sf::IntRect(tile_tileset_x, tile_tileset_y, TILE_SIZE, TILE_SIZE));
				draw(tileSet1);
				tile_screen_x++;
			}
			tile_screen_y++;
		}
	}
	else if(layer == 3) {
		for(int y = start_blit_y; y < end_blit_y; y += TILE_SIZE) {
			tile_screen_x = charBeginX_ / TILE_SIZE;
			for(int x = start_blit_x; x < end_blit_x; x += TILE_SIZE) {
				tile = layer3_[tile_screen_y][tile_screen_x];
				tile_tileset_y = tile / TILES_PER_LINE * TILE_SIZE;
				tile_tileset_x = tile % TILES_PER_LINE * TILE_SIZE;
				tileSet1.setPosition(sf::Vector2f(x,y));
				tileSet1.setTextureRect(sf::IntRect(tile_tileset_x, tile_tileset_y, TILE_SIZE, TILE_SIZE));
				draw(tileSet1);
				tile_screen_x++;
			}
			tile_screen_y++;
		}
	}
}