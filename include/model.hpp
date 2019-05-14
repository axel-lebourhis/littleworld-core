#ifndef MODEL_HPP
#define MODEL_HPP

#include <SFML/Graphics.hpp>
#include "observer.hpp"
#include "view.hpp"
#include "player.hpp"

class Model : public Observable<stateInfo> {
private:
	stateInfo info;
	int testScroll_;

public:
	Model();

	void setPlayerMoving(bool);
	bool getPlayerMoving() const;;

	void loadMap();
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
	bool isCollision(int);
};


#endif