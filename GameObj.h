#pragma once
#include <GL\glew.h>
class GameObj
{
public:
	double x, y;
	double weight, height;
	GLfloat* matrix = new GLfloat[16];

	GameObj(): x(0), y(0), weight(0), height(0){};
	GameObj(double x, double y, GLfloat* matrix) : x(x), y(y), matrix(matrix) {};
};

