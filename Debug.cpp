#include "Debug.h"
#include <GL\glew.h>
#include <iostream>
using namespace std;

void Debug::drawMatrix(GameObj gameObj) {
	for (int i = 0; i < 16; i++) {
		cout << "[" << i << "] " << gameObj.matrix[i] << " ";
		if (i == 3 || i == 7 || i == 11 || i == 15) cout << endl;
		if (i == 15) cout << endl;
	}
}

void Debug::drawCollision(GameObj gameObj)
{
	float a = gameObj.weight;
	float b = gameObj.height;
	float c = gameObj.weight;
	float d = gameObj.height;
	float oneX = gameObj.matrix[12];
	float oneY = gameObj.matrix[13];

	cout << endl;
	cout << "        a         " << endl;
	cout << "   A---------B    " << endl;
	cout << "   |---------|    " << endl;
	cout << "d  |---------|  b " << endl;
	cout << "   |---------|    " << endl;
	cout << "   D---------C    " << endl;
	cout << "        c         " << endl;
	cout << "A)" << "x: " << oneX << " y: " << oneY + d << endl;
	cout << "B)" << "x: " << oneX + a << " y: " << oneY + d << endl;
	cout << "C)" << "x: " << oneX + a << " y: " << oneY << endl;
	cout << "(D) " << "x: " << oneX << " y: " << oneY << endl;
	cout << "a) " << a << endl;
	cout << "b) " << b << endl;
	cout << "c) " << c << endl;
	cout << "d) " << d << endl;
}

bool Debug::collisionCheck(GameObj A, GameObj B) {
	// Collision x-axis?
	bool collisionX = B.matrix[12] <= A.matrix[12] + A.weight &&
		B.matrix[12] >= A.matrix[12];
	// Collision y-axis?
	//bool collisionY = B.y <= A.y + A.height &&
	//	B.y >= A.y;

	cout << "Frame: " << frame << endl;
	cout << endl;

	cout << "Draw A" << endl;
	Debug::drawCollision(A);
	cout << endl;

	cout << "Draw B" << endl;
	Debug::drawCollision(B);

	cout << "REsult: " << (collisionX) << endl;
	cout << endl;
	cout << endl;
	frame++;
	return collisionX;
}