#include "Enemies.h"

Enemies::Enemies(float hor, float ver)
{
	createSpaceship();
	spaceship.w = 0.1;
	spaceship.h = 0.1;
	spaceship.speed = 0.01;
}

void Enemies::run()
{
	if (spaceship.horizontalVector) {
		spaceship.horizontalPosition += spaceship.speed;
	}
	else spaceship.horizontalPosition -= spaceship.speed;
	if (spaceship.horizontalPosition >= 1) spaceship.horizontalVector = false;
	if (spaceship.horizontalPosition <= -1) spaceship.horizontalVector = true;

	if (spaceship.verticalVector) {
		spaceship.verticalPosition += spaceship.speed;
	}
	else spaceship.verticalPosition -= spaceship.speed;
	if (spaceship.verticalPosition >= 1) spaceship.verticalVector = false;
	if (spaceship.verticalPosition <= 0) spaceship.verticalVector = true;
}

bool Enemies::random() {
	if (rand() % 2 == 0)
		return true;
	else return false;
}

void Enemies::createSpaceship()
{
	mt19937 gen;
	uniform_real_distribution<> randX(-0.9, 0.9);
	uniform_real_distribution<> randY(0, 0.9);
	spaceship.live = true;
	gen.seed(time(0));
	spaceship.horizontalPosition = (float)randX(gen);
	spaceship.verticalPosition = (float)randY(gen);
	spaceship.horizontalVector = random();
	spaceship.verticalVector = random();
}
