#include "Enemies.h"

Enemies::Enemies(float hor, float ver)
{
	spaceship.horizontalPosition = hor;
	spaceship.verticalPosition = ver;
	spaceship.w = 0.1;
	spaceship.h = 0.1;
	spaceship.live = true;
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


