#pragma once
#include <stdio.h>
#include <iostream>
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

	void set (Amo amoSecond) {
		cout << "amoSecond x: " << amoSecond.x << endl;
		horizontalPosition = amoSecond.horizontalPosition;
		verticalPosition = amoSecond.verticalPosition; 
		verticalVector = amoSecond.verticalVector;
		angle = amoSecond.angle;
		live = amoSecond.live,
		horizontalFirePosition = amoSecond.horizontalFirePosition;
		verticalFirePosition = amoSecond.verticalFirePosition;
		x = amoSecond.x;
		y = amoSecond.y;
		//Amo(amoSecond.horizontalPosition, amoSecond.verticalPosition, amoSecond.verticalVector, amoSecond.angle, amoSecond.live, amoSecond.horizontalFirePosition, amoSecond.verticalFirePosition, amoSecond.x, amoSecond.y);
		cout << "Work x: " << x << endl;
	}
};

