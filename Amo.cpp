#include "Amo.h"
#include "Spaceship.h"

//bool Amo::fire(Spaceship spaceship)
//{
//	live = true;
//	//cout << "SpaceSheap horyzontal: " << spaceship.horizontalPosition << "	"<< "SpaceSheap vertical: " << spaceship.verticalPosition << endl;
//	angle = spaceship.angle;
//
//	horizontalFirePosition = spaceship.horizontalPosition;
//	verticalFirePosition = spaceship.verticalPosition;
//
//	horizontalPosition = 0;
//	verticalPosition = 0;
//
//	cout << "Amo vertical position: " << verticalPosition << endl;
//	return(true);
//}

void Amo::set(Amo amoSecond) {
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

void Amo::destroy() {
	live = false;
	angle = 0;
	horizontalFirePosition = 0;
	verticalFirePosition = 0;
	horizontalPosition = 0;
	verticalPosition = 0;
}

void Amo::colaider() {
	//cout << "AMO Position x:" << amo.horizontalPosition << " y:" << amo.verticalPosition << endl;
	if (x >= 1.0 || x <= -1.0 ||
		y >= 1.0 || y <= -1.0) {
		destroy();
		cout << "Amo live false";
	}
}
