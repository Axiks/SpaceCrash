#pragma once
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

	Amo() : horizontalPosition(0), verticalPosition(0), verticalVector(0),angle(0), live(false), horizontalFirePosition(0), verticalFirePosition(0){};
};

