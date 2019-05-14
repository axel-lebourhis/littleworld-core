#include "const.hpp"
#include "player.hpp"

Player::Player() {
	screen_pos_x = 0;
	screen_pos_y = 0;
	map_pos_x = 0;
	map_pos_y = 0;
	hp = 100.0;
	mana = 100.0;
	stamina = 100.0;
	direction = HERO_ORIENTED_DOWN;
	moving = false;
}

Player::Player(const Player& copy_player) {
	setHp(copy_player.getHp());
	setMana(copy_player.getMana());
	setStamina(copy_player.getStamina());
	setMapPosX(copy_player.getMapPosX());
	setMapPosY(copy_player.getMapPosY());
	setDirection(copy_player.getDirection());
	setScreenPosX(copy_player.getScreenPosX());
	setScreenPosY(copy_player.getScreenPosY());
}

int Player::getMapPosX() const {
	return map_pos_x;
}

int Player::getMapPosY() const {
	return map_pos_y;
}

int Player::getScreenPosX() const {
	return screen_pos_x;
}

int Player::getScreenPosY() const {
	return screen_pos_y;
}

int Player::getDirection() const {
	return direction;
}

bool Player::isMoving() const {
	return moving;
}

double Player::getHp() const {
	return hp;
}

double Player::getMana() const {
	return mana;
}

double Player::getStamina() const {
	return stamina;
}

void Player::setMapPosX(int pos_x) {
	map_pos_x = pos_x;
}

void Player::setMapPosY(int pos_y) {
	map_pos_y = pos_y;
}

void Player::setScreenPosX(int pos_x) {
	screen_pos_x = pos_x;
}

void Player::setScreenPosY(int pos_y) {
	screen_pos_y = pos_y;
}

void Player::setDirection(int dir) {
	direction = dir;
}

void Player::setMoving(bool state) {
	moving = state;
}

void Player::setHp(double val) {
	hp = val;
}

void Player::setMana(double val) {
	mana = val;
}

void Player::setStamina(double val) {
	stamina = val;
}
