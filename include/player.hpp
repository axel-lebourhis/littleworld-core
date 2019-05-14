#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player 
{
private:
	double hp;
	double mana;
	double stamina;
	int map_pos_x;
	int map_pos_y;
	int screen_pos_x;
	int screen_pos_y;
	int direction;
	bool moving;
public:
	Player();
	Player(const Player& copy_player);

	int getMapPosX() const;
	int getMapPosY() const;
	int getScreenPosX() const;
	int getScreenPosY() const;
	int getDirection() const;
	bool isMoving() const;
	double getHp() const;
	double getMana() const;
	double getStamina() const;

	void setMapPosX(int pos_x);
	void setMapPosY(int pos_y);
	void setScreenPosX(int pos_x);
	void setScreenPosY(int pos_y);
	void setDirection(int dir);
	void setMoving(bool state);
	void setHp(double val);
	void setMana(double val);
	void setStamina(double val);
};

#endif