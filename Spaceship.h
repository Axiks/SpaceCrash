#pragma once
#include "Amo.h"
#include <GL\glew.h>
#include "Vars.h"
#include "GameObj.h"


class Spaceship
{
public:
	const float _acceleration = 7.0;// m/s
	const float _deceleration = 5.0;// m/s

	bool live;
	float w, h;
	float horizontalPosition, verticalPosition;
	float angle;
	float speed;
	bool horizontalVector, verticalVector;
	int totalAmo;
	int availableAmo = totalAmo;
	Amo *amos = new Amo[totalAmo];
	GameObj gameObj = GameObj(0, 0, new GLfloat[16]);

	Spaceship() : horizontalVector(0), verticalVector(0), horizontalPosition(0.5), verticalPosition(0), angle(0), totalAmo(400), live(true), speed(0.05), w(0.05), h(0.06) {
		gameObj.weight = w;
		gameObj.height = h;
	};
	void fire();
};

