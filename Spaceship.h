#pragma once
#include "Amo.h"

class Spaceship
{
public:
	const float _acceleration = 7.0;// m/s
	const float _deceleration = 5.0;// m/s

	float horizontalVector, verticalVector;
	float horizontalPosition, verticalPosition;
	float w, h;
	float angle;
	int totalAmo;
	int availableAmo = totalAmo;
	float speed;
	Amo amos[100];

	bool live;

	Spaceship() : horizontalVector(0), verticalVector(0), horizontalPosition(+0.5), verticalPosition(0), angle(0), totalAmo(100), live(true), speed(0.05), w(0.05), h(0.06) {};
	Spaceship(float horizontalVector, float verticalVector, float horizontalPosition, float verticalPosition, int amo, bool live) : horizontalVector(horizontalVector), verticalVector(verticalVector), horizontalPosition(horizontalPosition), verticalPosition(verticalPosition), totalAmo(totalAmo), live(true), w(0.05), h(0.06) {};
	void fire();
};

