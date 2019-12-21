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
	float angle;
	int amo;
	//list<Amo> amos;

	bool live;

	Spaceship(float horizontalVector, float verticalVector, float horizontalPosition, float verticalPosition, int amo, bool live) : horizontalVector(horizontalVector), verticalVector(verticalVector), horizontalPosition(horizontalPosition), verticalPosition(verticalPosition), amo(amo), live(true){};
	Spaceship() : horizontalVector(0), verticalVector(0), horizontalPosition(0), verticalPosition(0), angle(0), amo(10), live(true){};

	void Fire() {
		//amos.insert();
	}
};

