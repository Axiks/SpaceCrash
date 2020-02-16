#pragma once
#include <GL\glew.h>
#include "GameObj.h"
class Debug
{
private:
	int frame;
public:
	Debug(): frame(0) {};
	void drawMatrix(GameObj gameObj);
	void drawCollision(GameObj gameObj);
	bool collisionCheck(GameObj A, GameObj B);
};

