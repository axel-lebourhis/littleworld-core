#include "const.hpp"
#include "monster.hpp"

Monster::Monster() {
	type = MONSTER1;
	screen_pos_x = 0;
	screen_pos_y = 0;
	map_pos_x = 0;
	map_pos_y = 0;
	hp = 100.0;
	direction = HERO_ORIENTED_DOWN;
	moving = false;
}

Monster::Monster(const Monster& copy_monster) {
	setHp(copy_monster.getHp());
	setMapPosX(copy_monster.getMapPosX());
	setMapPosY(copy_monster.getMapPosY());
	setDirection(copy_monster.getDirection());
	setScreenPosX(copy_monster.getScreenPosX());
	setScreenPosY(copy_monster.getScreenPosY());
	setType(copy_monster.getType());
}

int Monster::getMapPosX() const {
	return map_pos_x;
}

int Monster::getMapPosY() const {
	return map_pos_y;
}

int Monster::getScreenPosX() const {
	return screen_pos_x;
}

int Monster::getScreenPosY() const {
	return screen_pos_y;
}

int Monster::getDirection() const {
	return direction;
}

bool Monster::isMoving() const {
	return moving;
}

double Monster::getHp() const {
	return hp;
}

monster_t Monster::getType() const {
	return type;
}

void Monster::setMapPosX(int pos_x) {
	map_pos_x = pos_x;
}

void Monster::setMapPosY(int pos_y) {
	map_pos_y = pos_y;
}

void Monster::setScreenPosX(int pos_x) {
	screen_pos_x = pos_x;
}

void Monster::setScreenPosY(int pos_y) {
	screen_pos_y = pos_y;
}

void Monster::setDirection(int dir) {
	direction = dir;
}

void Monster::setMoving(bool state) {
	moving = state;
}

void Monster::setHp(double val) {
	hp = val;
}

void Monster::setType(monster_t t) {
	type = t;
}