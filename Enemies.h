#pragma once
#include <cstdlib>

class Enemies
{
public:
	float horizontalPosition, verticalPosition;
	float w, h;
	float speed;
	bool live;
	Enemies(float hor, float ver) : horizontalPosition(hor), verticalPosition(ver), w(0.1), h(0.1), live(true){};
	Enemies() : horizontalPosition(0), verticalPosition(0), w(0.1), h(0.1), live(true) {};
};


