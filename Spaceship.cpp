#include "Spaceship.h"

void Spaceship::fire() {
	amos[totalAmo - availableAmo].live = true;
	amos[totalAmo - availableAmo].angle = angle;

	amos[totalAmo - availableAmo].horizontalFirePosition = horizontalPosition;
	amos[totalAmo - availableAmo].verticalFirePosition = verticalPosition;
	
	amos[totalAmo - availableAmo].horizontalPosition = 0;
	amos[totalAmo - availableAmo].verticalPosition = 0;

	cout << "Amo[" << totalAmo - availableAmo << "] vertical position: " << amos[totalAmo - availableAmo].horizontalFirePosition << endl;
	availableAmo--;
}