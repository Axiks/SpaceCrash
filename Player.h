#pragma once
#include <string>
#include "Spaceship.h"
using namespace std;
class Player
{
public: 
	string name;
	int lives;
	Spaceship spaceship;

	Player() : name("Neko"), lives(3) {};
	Player(string name, int lives) : name(name), lives(lives) {};
};

