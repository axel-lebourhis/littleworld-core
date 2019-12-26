#ifndef MONSTER_HPP
#define MONSTER_HPP

typedef enum {
	MONSTER1,
	MONSTER2,
	MONSTER3
} monster_t;

class Monster
{
private:
	double hp;
	monster_t type;
	int map_pos_x;
	int map_pos_y;
	int screen_pos_x;
	int screen_pos_y;
	int direction;
	bool moving;
public:
	Monster();
	Monster(const Monster& copy_monster);

	int getMapPosX() const;
	int getMapPosY() const;
	int getScreenPosX() const;
	int getScreenPosY() const;
	int getDirection() const;
	bool isMoving() const;
	double getHp() const;
	monster_t getType() const;

	void setMapPosX(int pos_x);
	void setMapPosY(int pos_y);
	void setScreenPosX(int pos_x);
	void setScreenPosY(int pos_y);
	void setDirection(int dir);
	void setMoving(bool state);
	void setHp(double val);
	void setType(monster_t t);
};

#endif