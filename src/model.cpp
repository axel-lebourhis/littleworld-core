#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "model.hpp"

Model::Model() :
info()
{

}

void Model::updateView() {
	notifyObservers(info);
}

void Model::loadMap() {
	std::fstream file_stream;

	info.map_max_p_x = 0; 
	info.map_max_p_y = 0;
	info.map_start_p_x = 0;
	info.map_start_p_y = 0;

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

	info.player_start_x = lines[0][0];
	info.player_start_y = lines[0][1];

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

	info.map_max_p_x = (info.map_max_p_x + 1) * TILE_SIZE;
	info.map_max_p_y = (info.map_max_p_y + 1) * TILE_SIZE;
}

void Model::moveDown(int offset) {
	if(info.map_start_p_y < info.map_max_p_y - WINDOW_HEIGHT) {
		info.map_start_p_y += offset;
	}
}

void Model::moveUp(int offset) {
	if(info.map_start_p_y > 0) {
		info.map_start_p_y -= offset;
	}
}

void Model::moveLeft(int offset) {
	if(info.map_start_p_x > 0) {
		info.map_start_p_x -= offset;
	}
}

void Model::moveRight(int offset) {
	if(info.map_start_p_x < info.map_max_p_x - WINDOW_WIDTH) {
		info.map_start_p_x += offset;
	}
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