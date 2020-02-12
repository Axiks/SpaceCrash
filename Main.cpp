#include <stdio.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <windows.h>
#include <cmath>
#include "Vars.h"
#include "Spaceship.h"
#include "Amo.h"
#include "Enemies.h"
#pragma comment(lib, "irrKlang.lib")
#include <irrKlang.h>
#include <cstdlib>
#include <ctime>  
#include <random>
#include <windows.h>
#include <array>

using namespace std;
using namespace irrklang;

ISoundEngine* BackgroundMusic = createIrrKlangDevice();
ISoundEngine* fireEfect = createIrrKlangDevice();
Spaceship spaceship;

mt19937 gen;
uniform_real_distribution<> tandH(-0.9, 0.9);
uniform_real_distribution<> tandV(0, 0.9);

Enemies enem(0.0, 0.0);


GLboolean CheckCollision(float oneX, float oneY, float oneSizeX, float oneSizeY, float twoX, float twoY, float twoSizeX, float twoSizeY) // AABB - AABB collision
{
	// Collision x-axis?
	bool collisionX = twoX <= oneX + oneSizeX &&
					  twoX >= oneX;
	// Collision y-axis?
	bool collisionY = twoY <= oneY + oneSizeY &&
					  twoY >= oneY;
	if (false) {
		//Debug
		float a = oneSizeX;
		float b = oneSizeY;
		float c = oneSizeX;
		float d = oneSizeY;

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

	// Collision only if on both axes
	return collisionX && collisionY;
}

void drawMatrix(GLfloat matrix[16]) {
	for (int i = 0; i < 16; i++) {
		cout << "[" << i << "] " << matrix[i] << " ";
		if (i == 3 || i == 7 || i == 11 || i == 15) cout << endl;
		if (i == 15) cout << endl;
	}
}

//void amoFire() {
//	//for(int i = 0; i < ccc; i++){}
//		amo.live = true;
//		//cout << "SpaceSheap horyzontal: " << spaceship.horizontalPosition << "	"<< "SpaceSheap vertical: " << spaceship.verticalPosition << endl;
//		amo.angle = spaceship.angle;
//
//		amo.horizontalFirePosition = spaceship.horizontalPosition;
//		amo.verticalFirePosition = spaceship.verticalPosition;
//
//		amo.horizontalPosition = 0;
//		amo.verticalPosition =  0;
//
//		cout << "Amo vertical position: " << amo.verticalPosition << endl;
//
//		//cout << "availableAmo: " << spaceship.availableAmo << endl;
//
//		//cout << amo.fire();
//		//cout << "Angle: " << amo.angle << endl;
//		//cout << "AMO horizontalPosition: " << amo.horizontalPosition << endl;
//		//cout << "AMO verticalPosition: " << amo.verticalPosition << endl;
//
//		//fireEfect->play2D("audio/fire.mp3", false);		
//}

void eminemNew() {
	enem.live = true;
	gen.seed(time(0));
	enem.horizontalPosition = (float)tandH(gen);
	enem.verticalPosition = (float)tandV(gen);
}

void eminemCrash(Amo amo) {
	//cout << "Enem horyzontal position: " << enem.horizontalPosition << endl;
	//cout << "Amo hor position: " << amo.horizontalPosition << endl;
	/*if (
			amo.y >= enem.verticalPosition - enem.h && ( (amo.x > enem.horizontalPosition) && (amo.x <= enem.horizontalPosition + (enem.h + 0.01)))
		) {
		amo.live = false;
		enem.live = false;
		eminemNew();
		}*/

	/*Calculate position Qwadrat*/

	bool crash = CheckCollision(enem.horizontalPosition, enem.verticalPosition, enem.w, enem.h, amo.x, amo.y, 0.1, 0.01);

		if (crash) {
			amo.destroy();
			enem.live = false;
			eminemNew();
		}
}

void Physics() {

}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(spaceship.horizontalPosition, spaceship.verticalPosition, 0.0);
	glRotated(spaceship.angle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
		glColor3f(spaceship.verticalPosition, spaceship.horizontalPosition, 1.0);
		glVertex2f(-spaceship.w, -spaceship.h);
		glVertex2f(spaceship.w, -spaceship.h);
		glVertex2f(0, spaceship.h);
	glEnd();
	glPopMatrix();

	//glPushMatrix();
	////for (int i = 0; i < ccc; i++) {
	//int i = 0;
	//	if (amos[i].live) {
	//		amoColaider();
	//		glTranslatef(amos[i].horizontalFirePosition, amo.verticalFirePosition, 0.0);
	//		glRotated(amo.angle, 0, 0, 1);
	//		//glTranslatef(amo.verticalPosition, -amo.horizontalPosition, 0.0);
	//		//glRotated(amo.angle, 0, 0, 1);
	//		glTranslated(amo.horizontalPosition, amo.verticalPosition += amo._speed, 0);
	//		//glTranslatef(amo.horizontalPosition += amo._speed, amo.verticalPosition += sqrt(pow(abs(amo.horizontalPosition - amo.horizontalFirePosition) / cos(amo.angle),2) - pow(amo.horizontalFirePosition - amo.horizontalFirePosition, 2)) - amo.verticalFirePosition, 0.0);
	//		glBegin(GL_LINES);
	//		glColor3f(spaceship.horizontalPosition, spaceship.verticalPosition, 0.9);
	//		glVertex2f(0.0, 0.1);
	//		glVertex2f(0, 0.0);
	//		glEnd();
	//		GLfloat matrixf[16];
	//		glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
	//		//drawMatrix(matrixf);
	//		amo.x = matrixf[12];
	//		amo.y = matrixf[13];
	//	}
	////}
	//glPopMatrix();

	for (int i = 0; i < spaceship.totalAmo; i++) {
		if (spaceship.amos[i].live) {
			glPushMatrix();
			glTranslatef(spaceship.amos[i].horizontalFirePosition, spaceship.amos[i].verticalFirePosition, 0.0);
			glRotated(spaceship.amos[i].angle, 0, 0, 1);
			//glTranslatef(amo.verticalPosition, -amo.horizontalPosition, 0.0);
			//glRotated(amo.angle, 0, 0, 1);
			glTranslated(spaceship.amos[i].horizontalPosition, spaceship.amos[i].verticalPosition += spaceship.amos[i]._speed, 0);
			glBegin(GL_LINES);
			glColor3f(spaceship.horizontalPosition, spaceship.verticalPosition, 0.9);
			glVertex2f(0.0, 0.1);
			glVertex2f(0, 0.0);
			glEnd();
			GLfloat matrixf[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
			spaceship.amos[i].x = matrixf[12];
			spaceship.amos[i].y = matrixf[13];
			spaceship.amos[i].colaider();
			eminemCrash(spaceship.amos[i]);
			glPopMatrix();
		}
	}



	//Enemies
	glPushMatrix();

	if (enem.live) {
		glTranslatef(enem.horizontalPosition, enem.verticalPosition, 0.0);
		glBegin(GL_QUADS);
		glColor3f(spaceship.verticalPosition, spaceship.horizontalPosition, 1.0);
		glVertex2f(0.0, enem.h);
		glVertex2f(enem.w, enem.h);
		glVertex2f(enem.w, 0.0);
		glVertex2f(0.0, 0.0);
		glEnd();
	}

	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) {

	if (key == _GLFW_KEY_SPACE) {
		cout << "Space press";
		spaceship.fire();
	}

}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if (spaceship.horizontalPosition - spaceship.speed < 1.0 && spaceship.horizontalPosition - spaceship.speed > -1.0)
			spaceship.horizontalPosition -= spaceship.speed;
		break;
	case GLUT_KEY_RIGHT:
		if (spaceship.horizontalPosition + spaceship.speed < 1.0 && spaceship.horizontalPosition + spaceship.speed > -1.0)
			spaceship.horizontalPosition += spaceship.speed;
		break;
	case GLUT_KEY_UP:
		if (spaceship.verticalPosition + spaceship.speed < 1.0 && spaceship.verticalPosition + spaceship.speed > -1.0)
			spaceship.verticalPosition += spaceship.speed;
		break;
	case GLUT_KEY_DOWN:
		if (spaceship.verticalPosition - spaceship.speed < 1.0 && spaceship.verticalPosition - spaceship.speed > -1.0)
			spaceship.verticalPosition -= spaceship.speed;
		break;
	}
}

void Mouse(int ax, int ay)
{
	float XPosition = (ax / (float)(_DisplayWidth - (_DisplayWidth / 2))) - 1.0;
	float YPosition = (ay / (float)(_DisplayHeight - (_DisplayHeight / 2))) - 1.0;
	//cout << fixed;
	//cout << " x:" << XPosition << " y:" << -YPosition << endl;

	spaceship.horizontalPosition = XPosition;
	spaceship.verticalPosition = -YPosition;
}

void MouseFunc(int button, int state, int x, int y)
{
	if (button == 3) {
		spaceship.angle += 5;
	}

	if (button == 4) {
		spaceship.angle -= 5;
	}

	if (button == GLUT_MIDDLE_BUTTON) {
		spaceship.angle = 0;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		cout << "Mouse Left press";
		spaceship.fire();
	}

	// Wheel reports as button 3(scroll up) and button 4(scroll down)
	if ((button == 3) || (button == 4)) // It's a wheel event
	{
		if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
		printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);
	}
	else {  // normal button event
		printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
	}
}

void Timer(int)
{
	Draw();
	glutTimerFunc(_DisplayFPS, Timer, 0);
}

void Init()
{
	eminemNew();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 0.0f, 0.0f, 1.0f);
	//BackgroundMusic->play2D("audio/breakout.mp3", true);
}

int main(int argc, char** argv)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, _DisplayWidth, _DisplayHeight, TRUE);


	/*cout << "1))" << amos[0].x << endl;
	Amo z = Amo();
	z.x = 0.5;
	cout << "z))" << z.x << endl;
	amos[0].set(z);
	cout << "2))" << amos[0].x << endl;*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(_DisplayWidth, _DisplayHeight);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("SpaceY");
	glutDisplayFunc(Draw);
	glutTimerFunc(_DisplayFPS, Timer, 0);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutPassiveMotionFunc(Mouse);
	glutMouseFunc(MouseFunc);

	Init();
	glutMainLoop();
}