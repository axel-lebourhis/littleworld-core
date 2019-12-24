#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#ifdef TEST
#include <assert.h>
#endif
#include "model.hpp"

Model::Model() :
info()
{
	level = 1;
	loadMap("map/map"+std::to_string(level)+".txt");
}

void Model::setPlayerMoving(bool state) {
	info.player.setMoving(state);
}

void Model::setLevel(int l) {
	level = l;
	loadMap("map/map"+std::to_string(level)+".txt");
}

bool Model::getPlayerMoving() const {
	return info.player.isMoving();
}

int Model::getLevel() const {
	return level;
}

void Model::updateView() {
	notifyObservers(info);
}

void Model::changeLevel() {
	switch(info.player.getDirection()) {
		case HERO_ORIENTED_UP :
			if(mapUp != 0) {
				setLevel(mapUp);
			}
			break;
		case HERO_ORIENTED_DOWN :
			if(mapDown != 0) {
				setLevel(mapDown);
			}
			break;
		case HERO_ORIENTED_LEFT :
			if(mapLeft != 0) {
				setLevel(mapLeft);
			}
			break;
		case HERO_ORIENTED_RIGHT :
			if(mapRight != 0) {
				setLevel(mapRight);
			}
			break;
	}
}

void Model::loadMap(std::string filename) {
	std::fstream file_stream;

	info.map_max_p_x = 0; 
	info.map_max_p_y = 0;

	std::vector<std::vector<int>> lines;
	std::vector<int> line_v;

	std::string strBuf;
	std::stringstream strStream;

	file_stream.open(filename, std::fstream::in);

	if(!file_stream.is_open()) {
		std::cerr << "Error opening map file." << std::endl;
		exit(EXIT_FAILURE);
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

	for(int x = 3; x < MAX_TILES_XY + 3; x++) {
		info.layer1[0][x-3] = lines[0][x];
	}

	for(int y = 1; y < MAX_TILES_XY; y++) {
		for(int x = 0; x < MAX_TILES_XY; x++) {
			info.layer1[y][x] = lines[y][x];
			if(info.layer1[y][x] > 0) {
				if(x > info.map_max_p_x) {
					info.map_max_p_x = x;
				}
				if(y > info.map_max_p_y) {
					info.map_max_p_y = y;
				}
			}
		}
	}

	info.player.setMapPosX(lines[0][0]);
	info.player.setMapPosY(lines[0][1]);

	int part_x = WINDOW_WIDTH;
	int count_x = 0;

	while(part_x < info.player.getMapPosX()) {
		count_x++;
		part_x += WINDOW_WIDTH;
	}

	int part_y = WINDOW_HEIGHT;
	int count_y = 0;

	while(part_y < info.player.getMapPosY()) {
		count_y++;
		part_y += WINDOW_HEIGHT;
	}

	info.map_max_p_x = (info.map_max_p_x + 1) * TILE_SIZE;
	info.map_max_p_y = (info.map_max_p_y + 1) * TILE_SIZE;

	if(count_x*WINDOW_WIDTH > info.map_start_p_x) {
		info.map_start_p_x = info.map_max_p_x - WINDOW_WIDTH;		
	}
	else {
		info.map_start_p_x = count_x*WINDOW_WIDTH;
	}

	if(count_y*WINDOW_HEIGHT > info.map_start_p_y) {
		info.map_start_p_y =  info.map_max_p_y - WINDOW_HEIGHT;
	}
	else {
		info.map_start_p_y = count_y*WINDOW_HEIGHT;
	}

    info.player.setScreenPosX(lines[0][0] - info.map_start_p_x);
    info.player.setScreenPosY(lines[0][1] - info.map_start_p_y);

	for(int y = 0; y < MAX_TILES_XY; y++) {
		for(int x = 0; x < MAX_TILES_XY; x++) {
			info.layer2[y][x] = lines[y+MAX_TILES_XY][x];
		}
	}

	for(int y = 0; y < MAX_TILES_XY; y++) {
		for(int x = 0; x < MAX_TILES_XY; x++) {
			info.layer3[y][x] = lines[y+MAX_TILES_XY*2][x];
		}
	}

	for(int y = 0; y < MAX_TILES_XY; y++) {
		for(int x = 0; x < MAX_TILES_XY; x++) {
			info.layer4[y][x] = lines[y+MAX_TILES_XY*3][x];
		}
	}

	int y = MAX_TILES_XY * 4;

	mapUp = lines[y][0];
	mapDown = lines[y][1];
	mapLeft = lines[y][2];
	mapRight = lines[y][3];
}

void Model::moveCameraDown(int offset) {
	if(info.map_start_p_y < info.map_max_p_y - WINDOW_HEIGHT) {
		info.map_start_p_y += offset;
	}
}

void Model::moveCameraUp(int offset) {
	if(info.map_start_p_y > 0) {
		info.map_start_p_y -= offset;
	}
}

void Model::moveCameraLeft(int offset) {
	if(info.map_start_p_x > 0) {
		info.map_start_p_x -= offset;
	}
}

void Model::moveCameraRight(int offset) {
	if(info.map_start_p_x < info.map_max_p_x - WINDOW_WIDTH) {
		info.map_start_p_x += offset;
	}
}

void Model::setCameraOnPlayer() {
	int current_map_pos_x = info.player.getMapPosX();
	int current_map_pos_y = info.player.getMapPosY();

	int left_x = current_map_pos_x - WINDOW_WIDTH/2;
	int right_x = current_map_pos_x + WINDOW_WIDTH/2;
	int bottom_y = current_map_pos_y + WINDOW_HEIGHT/2;
	int up_y = current_map_pos_y - WINDOW_HEIGHT/2;
	
	if(left_x > 0 && right_x < info.map_max_p_x) {
		info.map_start_p_x = left_x;
		info.player.setScreenPosX(WINDOW_WIDTH/2);
	}
	else if(left_x < 0) {
		info.map_start_p_x = 0;
		info.player.setScreenPosX(0);
	}
	else if(right_x > info.map_max_p_x) {
		info.map_start_p_x = info.map_max_p_x - WINDOW_WIDTH;
		info.player.setScreenPosX(WINDOW_WIDTH - HERO_TILE_SIZE_X);
	}

	if(up_y > 0 && bottom_y < info.map_max_p_y) {
		info.map_start_p_y = up_y;
		info.player.setScreenPosY(WINDOW_HEIGHT/2);
	}
	else if(up_y < 0) {
		info.map_start_p_y = 0;
		info.player.setScreenPosY(0);
	}
	else if(bottom_y > info.map_max_p_y) {
		info.map_start_p_y = info.map_max_p_y - WINDOW_HEIGHT;
		info.player.setScreenPosY(WINDOW_HEIGHT - HERO_TILE_SIZE_Y);
	}
}

bool Model::isCollision(int direction) {
	int player_tile_x1 = 0;
	int player_tile_x2 = 0;
	int player_tile_y1 = 0;
	int player_tile_y2 = 0;
	switch(direction) {
		case HERO_ORIENTED_LEFT :
			player_tile_x1 = (info.player.getMapPosX() - 3) / TILE_SIZE;
			player_tile_y1 = info.player.getMapPosY() / TILE_SIZE;
			player_tile_y2 = (info.player.getMapPosY() + TILE_SIZE) / TILE_SIZE;
			if(info.layer4[player_tile_y1][player_tile_x1] == 1 || info.layer4[player_tile_y2][player_tile_x1] == 1) {
				return true;
			}
			break;
		case HERO_ORIENTED_RIGHT :
			player_tile_x2 = (info.player.getMapPosX() + HERO_TILE_SIZE_X + 3) / TILE_SIZE;
			player_tile_y1 = info.player.getMapPosY() / TILE_SIZE;
			player_tile_y2 = (info.player.getMapPosY() + TILE_SIZE) / TILE_SIZE;
			if(info.layer4[player_tile_y1][player_tile_x2] == 1 || info.layer4[player_tile_y2][player_tile_x2] == 1) {
				return true;
			}
			break;
		case HERO_ORIENTED_UP :
			player_tile_x1 = info.player.getMapPosX() / TILE_SIZE;
			player_tile_x2 = (info.player.getMapPosX() + TILE_SIZE) / TILE_SIZE;
			player_tile_y1 = (info.player.getMapPosY() - 3 ) / TILE_SIZE;
			if(info.layer4[player_tile_y1][player_tile_x1] == 1 || info.layer4[player_tile_y1][player_tile_x2] == 1) {
				return true;
			}
			break;
		case HERO_ORIENTED_DOWN :
			player_tile_x1 = info.player.getMapPosX() / TILE_SIZE;
			player_tile_x2 = (info.player.getMapPosX() + TILE_SIZE) / TILE_SIZE;
			player_tile_y2 = (info.player.getMapPosY() + HERO_TILE_SIZE_Y + 3) / TILE_SIZE;
			if(info.layer4[player_tile_y2][player_tile_x1] == 1 || info.layer4[player_tile_y2][player_tile_x2] == 1) {
				return true;
			}
			break;
		default :
			break;
	}
	return false;
}

void Model::moveDown(int offset) {
	if(!isCollision(HERO_ORIENTED_DOWN) && info.player.getMapPosY() < info.map_max_p_y - HERO_TILE_SIZE_Y) {
		if((info.player.getScreenPosY() > WINDOW_HEIGHT/2) && (info.map_start_p_y < info.map_max_p_y - WINDOW_HEIGHT)) {
			moveCameraDown(offset);
			info.player.setMapPosY(info.player.getMapPosY() + offset);
		}
		else {
			info.player.setScreenPosY(info.player.getScreenPosY() + offset);
			info.player.setMapPosY(info.player.getMapPosY() + offset);
		}
	}
	else if(mapDown != 0 && info.player.getMapPosY() >= info.map_max_p_y - HERO_TILE_SIZE_Y) {
		info.player.setDirection(HERO_ORIENTED_DOWN);
		int map_pos_x = info.player.getMapPosX();
		changeLevel();
		info.player.setMapPosX(map_pos_x);
		info.player.setMapPosY(0);
		setCameraOnPlayer();
	}
	else {
		info.player.setMoving(false);
	}
	info.player.setDirection(HERO_ORIENTED_DOWN);
}

void Model::moveUp(int offset) {
	if(!isCollision(HERO_ORIENTED_UP) && info.player.getMapPosY() > 0) {
		if((info.player.getScreenPosY() < WINDOW_HEIGHT/2) && (info.map_start_p_y > 0)) {
			moveCameraUp(offset);
			info.player.setMapPosY(info.player.getMapPosY() - offset);
		}
		else {
			info.player.setScreenPosY(info.player.getScreenPosY() - offset);
			info.player.setMapPosY(info.player.getMapPosY() - offset);
		}
	}
	else if(mapUp != 0 && info.player.getMapPosY() <= 0) {
		info.player.setDirection(HERO_ORIENTED_UP);
		int map_pos_x = info.player.getMapPosX();
		changeLevel();
		info.player.setMapPosX(map_pos_x);
		info.player.setMapPosY(info.map_max_p_y - HERO_TILE_SIZE_Y);
		setCameraOnPlayer();
	}
	else {
		info.player.setMoving(false);
	}
	info.player.setDirection(HERO_ORIENTED_UP);
}

void Model::moveLeft(int offset) {
	if(!isCollision(HERO_ORIENTED_LEFT) && info.player.getMapPosX() > 0) {
		if((info.player.getScreenPosX() < WINDOW_WIDTH/2) && (info.map_start_p_x > 0)) {
			moveCameraLeft(offset);
			info.player.setMapPosX(info.player.getMapPosX() - offset);
		}
		else {
			info.player.setScreenPosX(info.player.getScreenPosX() - offset);
			info.player.setMapPosX(info.player.getMapPosX() - offset);
		}
	}
	else if(mapLeft != 0 && info.player.getMapPosX() <= 0) {
		info.player.setDirection(HERO_ORIENTED_LEFT);
		int map_pos_y = info.player.getMapPosY();
		changeLevel();
		info.player.setMapPosX(info.map_max_p_x - HERO_TILE_SIZE_X);
		info.player.setMapPosY(map_pos_y);
		setCameraOnPlayer();
	}
	else {
		info.player.setMoving(false);
	}
	info.player.setDirection(HERO_ORIENTED_LEFT);
}

void Model::moveRight(int offset) {
	if(!isCollision(HERO_ORIENTED_RIGHT) && info.player.getMapPosX() < info.map_max_p_x - HERO_TILE_SIZE_X) {
		if((info.player.getScreenPosX() > WINDOW_WIDTH/2) && (info.map_start_p_x < info.map_max_p_x - WINDOW_WIDTH)) {
			moveCameraRight(offset);
			info.player.setMapPosX(info.player.getMapPosX() + offset);
		}
		else {
			info.player.setScreenPosX(info.player.getScreenPosX() + offset);
			info.player.setMapPosX(info.player.getMapPosX() + offset);
		}
	}
	else if(mapRight != 0 && info.player.getMapPosX() >= info.map_max_p_x - HERO_TILE_SIZE_X) {
		info.player.setDirection(HERO_ORIENTED_RIGHT);
		int map_pos_y = info.player.getMapPosY();
		changeLevel();
		info.player.setMapPosX(0);
		info.player.setMapPosY(map_pos_y);
		setCameraOnPlayer();
	}
	else {
		info.player.setMoving(false);
	}
	info.player.setDirection(HERO_ORIENTED_RIGHT);
}

void Model::testScroll() {
	if(testScroll_ == 0) {
		if(info.map_start_p_x <= info.map_max_p_x - WINDOW_WIDTH) {
			info.map_start_p_x += 1;
		}
		else {
			testScroll_ = 1;
		}
	}
	else if(testScroll_ == 1) {
		if(info.map_start_p_y <= info.map_max_p_y - WINDOW_HEIGHT) {
			info.map_start_p_y += 1;
		}
		else {
			testScroll_ = 2;
		}
	}
	else if(testScroll_ == 2) {
		if(info.map_start_p_x > 0) {
			info.map_start_p_x -= 1;
		}
		else {
			testScroll_ = 3;
		}
	}
	else if(testScroll_ == 3) {
		if(info.map_start_p_y > 0) {
			info.map_start_p_y -= 1;
		}
		else {
			testScroll_ = 0;
		}
	}
}

#ifdef TEST
bool Model::runUnitTest()
{
	this->setPlayerMoving(true);
	assert(this->getPlayerMoving() == true);

	this->setPlayerMoving(false);
	assert(this->getPlayerMoving() == false);

	this->setLevel(2);
	assert(this->getLevel() == 2);

	this->setLevel(1);
	assert(this->getLevel() == 1);

	return true;
}
#endif