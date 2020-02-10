#pragma once
#include "Amo.h"
#include <list>

class Spaceship
{
public:
	const float _acceleration = 7.0;// m/s
	const float _deceleration = 5.0;// m/s

	float horizontalVector, verticalVector;
	float horizontalPosition, verticalPosition;
	float w, h;
	float angle;
	int amo;
	float speed;
	//list<Amo> amos;

	bool live;

	Spaceship(float horizontalVector, float verticalVector, float horizontalPosition, float verticalPosition, int amo, bool live) : horizontalVector(horizontalVector), verticalVector(verticalVector), horizontalPosition(horizontalPosition), verticalPosition(verticalPosition), amo(amo), live(true), w(0.05), h(0.06) {};
	Spaceship() : horizontalVector(0), verticalVector(0), horizontalPosition(+0.5), verticalPosition(0), angle(0), amo(10), live(true), speed(0.05), w(0.05), h(0.06){};

	void Fire() {
		//amos.insert();
	}
};

