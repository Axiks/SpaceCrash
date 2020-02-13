#include "Enemies.h"

void Enemies::run()
{
	if (horizontalVector) {
		horizontalPosition += speed;
	}
	else horizontalPosition -= speed;
	if (horizontalPosition >= 1) horizontalVector = false;
	if (horizontalPosition <= -1) horizontalVector = true;

	if (verticalVector) {
		verticalPosition += speed;
	}
	else verticalPosition -= speed;
	if (verticalPosition >= 1) verticalVector = false;
	if (verticalPosition <= 0) verticalVector = true;
}



bool Enemies::random() {
	if (rand() % 2 == 0)
		return true;
	else return false;
}


