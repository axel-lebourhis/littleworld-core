#ifndef MODEL_HPP
#define MODEL_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "observer.hpp"
#include "view.hpp"
#include "player.hpp"

class Model : public Observable<stateInfo> {
private:
	stateInfo info;
	int testScroll_;
	int mapUp;
	int mapDown;
	int mapLeft;
	int mapRight;
	int level;

public:
	Model();

	void setPlayerMoving(bool);
	void setLevel(int);

	bool getPlayerMoving() const;;
	int getLevel() const;

	void loadMap(std::string);
	void testScroll();
	void updateView();
	void moveDown(int);
	void moveUp(int);
	void moveLeft(int);
	void moveRight(int);
	void moveCameraDown(int);
	void moveCameraUp(int);
	void moveCameraLeft(int);
	void moveCameraRight(int);
	void setCameraOnPlayer();
	void changeLevel();
	bool isCollision(int);
};


#endif