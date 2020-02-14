#pragma once
#include <cstdlib>
#include <string>
#include "Spaceship.h"
#include <ctime>
#include <random>

class Enemies
{
public:
	string name;
	int lives;
	Spaceship spaceship;

	Enemies(float hor, float ver);
	//Enemies(float hor, float ver) : spaceship.horizontalPosition(hor), spaceship.verticalPosition(ver), spaceship.w(0.1), spaceship.h(0.1), spaceship.live(true), spaceship.speed(0.01), spaceship.angle(0){};
	//Enemies() : spaceship.horizontalPosition{(0), spaceship.verticalPosition(0), spaceship.w(0.1), spaceship.h(0.1), spaceship.live(true), spaceship.speed(0.01), spaceship.angle() {};
	void run();
	void createSpaceship();
private:
	bool random();
};


