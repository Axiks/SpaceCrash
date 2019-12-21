#pragma once
class Amo
{
public: 
	const float _speed = 0.025;

	float verticalVector;
	float horizontalPosition, verticalPosition;
	float angle;

	bool live;

	Amo() : horizontalPosition(0), verticalPosition(0), verticalVector(0),angle(0), live(false) {};
};

