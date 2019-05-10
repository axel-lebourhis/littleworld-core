#ifndef MODEL_HPP
#define MODEL_HPP

#include <SFML/Graphics.hpp>
#include "observer.hpp"
#include "view.hpp"

class Model : public Observable<stateInfo> {
private:
	stateInfo info;
	int testScroll_;

public:
	Model();

	void loadMap();
	void testScroll();
	void updateView();
	void moveDown(int);
	void moveUp(int);
	void moveLeft(int);
	void moveRight(int);
};


#endif