#pragma once
#include <stdio.h>
#include <iostream>
#include "Spaceship.h"


using namespace std;
class Amo
{
public: 
	const float _speed = 0.05;

	float verticalVector;
	float horizontalPosition, verticalPosition;
	float x, y;
	float horizontalFirePosition, verticalFirePosition;
	float angle;
	bool live;

	Amo() : horizontalPosition(0), verticalPosition(0), verticalVector(0),angle(0), live(false), horizontalFirePosition(0), verticalFirePosition(0), x(0), y(0){};
	Amo(float horizontalPosition, float verticalPosition, float verticalVector, float angle, float live, float horizontalFirePosition, float verticalFirePosition, float x, float y) : horizontalPosition(horizontalPosition), verticalPosition(verticalPosition), verticalVector(verticalVector), angle(angle), live(live), horizontalFirePosition(horizontalFirePosition), verticalFirePosition(verticalFirePosition), x(x), y(y) {};

	//void fire(Spaceship spaceship);

	bool fire(Spaceship sp);

	void set(Amo amoSecond);

	void destroy();

	void colaider();

};

