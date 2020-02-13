#include <stdio.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <windows.h>
#include <cmath>
#include "Vars.h"
#include "Player.h"
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
Player player;

mt19937 gen;
uniform_real_distribution<> tandH(-0.9, 0.9);
uniform_real_distribution<> tandV(0, 0.9);

uniform_real_distribution<> starH(-1.25, 1.25);
uniform_real_distribution<> starV(-1.25, 1.25);

Enemies enem(0.0, 0.0);

float StarCoord[_DrawStar * 2];
float StarBrightness = 0;
bool Brightness = true;


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

void createStar() {
	int c = 0;
	gen.seed(time(0));
	for (int i = 0; i < (_DrawStar * 2) - 2; i = i + 2, c++) {
		float x = (float)starH(gen);
		float y = (float)starV(gen);
		StarCoord[i] = x;
		StarCoord[i + 1] = y;
		cout << "Star "<< c <<" cord: x)" << x << " y)" << y << endl;
	}
}

void eminemAngleSet() {
	float enemX = enem.spaceship.horizontalPosition;
	float enemY = enem.spaceship.verticalPosition;
	float a = fabs(enemY - player.spaceship.verticalPosition);
	float b = fabs(player.spaceship.horizontalPosition - enemX);
	float c = sqrt(pow(a, 2) + pow(b, 2));
	float angle = sin(a/c);
	enem.spaceship.angle = angle * 360;
	cout << "Angle: " << enem.spaceship.angle << endl;
}

void eminemNew() {
	enem.spaceship.live = true;
	gen.seed(time(0));
	enem.spaceship.horizontalPosition = (float)tandH(gen);
	enem.spaceship.verticalPosition = (float)tandV(gen);
	enem.spaceship.horizontalVector = enem.random();
	enem.spaceship.verticalVector = enem.random();
}

void eminemCrash(Amo amo) {
	//cout << "Enem horyzontal position: " << enem.horizontalPosition << endl;
	//cout << "Amo hor position: " << amo.horizontalPosition << endl;

	/*Calculate position Qwadrat*/
	bool crash = CheckCollision(enem.spaceship.horizontalPosition, enem.spaceship.verticalPosition, enem.spaceship.w, enem.spaceship.h, amo.x, amo.y, 0.1, 0.01);
	if (crash) {
		cout << "amo destroy" << endl;
		amo.destroy();
		enem.spaceship.live = false;
		eminemNew();
	}
}

void Physics() {

}

void Draw()
{
	if (Brightness && StarBrightness < 1.5) {
		StarBrightness += 1.5 / (15 * _DisplayFPS);
	}
	else
	{
		Brightness = false;
		StarBrightness -= 1.5 / (15 * _DisplayFPS);
		if (StarBrightness < 0) Brightness = true;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(player.spaceship.horizontalPosition, player.spaceship.verticalPosition, 0.0);
	glRotated(player.spaceship.angle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
		glColor3f(player.spaceship.verticalPosition, player.spaceship.horizontalPosition, 1.0);
		glVertex2f(-player.spaceship.w, -player.spaceship.h);
		glVertex2f(player.spaceship.w, -player.spaceship.h);
		glVertex2f(0, player.spaceship.h);
	glEnd();
	glPopMatrix();

	//Amo
	for (int i = 0; i < player.spaceship.totalAmo; i++) {
		if (player.spaceship.amos[i].live) {
			//cout << "Amo "<< i <<" live: " << spaceship.amos[i].live << "; y: " << spaceship.amos[i].y << endl;
			glPushMatrix();
			glTranslatef(player.spaceship.amos[i].horizontalFirePosition, player.spaceship.amos[i].verticalFirePosition, 0.0);
			glRotated(player.spaceship.amos[i].angle, 0, 0, 1);
			glTranslated(player.spaceship.amos[i].horizontalPosition, player.spaceship.amos[i].verticalPosition += player.spaceship.amos[i]._speed, 0);
			glBegin(GL_LINES);
			glColor3f(player.spaceship.horizontalPosition, player.spaceship.verticalPosition, 0.9);
			glVertex2f(0.0, 0.1);
			glVertex2f(0, 0.0);
			glEnd();
			GLfloat matrixf[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
			player.spaceship.amos[i].x = matrixf[12];
			player.spaceship.amos[i].y = matrixf[13];
			player.spaceship.amos[i].colaider();
			eminemCrash(player.spaceship.amos[i]);
			glPopMatrix();
		}
	}


	//Enemies
	if (enem.spaceship.live) {
		//eminemAngleSet();
		enem.run();
		glPushMatrix();
		glTranslatef(enem.spaceship.horizontalPosition, enem.spaceship.verticalPosition, 0.0);
		glRotated(enem.spaceship.angle, 0, 0, 1);
		glBegin(GL_QUADS);
		glColor3f(player.spaceship.verticalPosition, player.spaceship.horizontalPosition, 1.0);
		glVertex2f(0.0, enem.spaceship.h);
		glVertex2f(enem.spaceship.w, enem.spaceship.h);
		glVertex2f(enem.spaceship.w, 0.0);
		glVertex2f(0.0, 0.0);
		glEnd();
		glPopMatrix();
	}

	//Amo
	for (int i = 0; i < enem.spaceship.totalAmo; i++) {
		if (enem.spaceship.amos[i].live) {
			//cout << "Amo "<< i <<" live: " << spaceship.amos[i].live << "; y: " << spaceship.amos[i].y << endl;
			glPushMatrix();
			glTranslatef(enem.spaceship.amos[i].horizontalFirePosition, enem.spaceship.amos[i].verticalFirePosition, 0.0);
			glRotated(enem.spaceship.amos[i].angle, 0, 0, 1);
			glTranslated(enem.spaceship.amos[i].horizontalPosition, enem.spaceship.amos[i].verticalPosition += enem.spaceship.amos[i]._speed, 0);
			glBegin(GL_LINES);
			glColor3f(enem.spaceship.horizontalPosition, enem.spaceship.verticalPosition, 0.9);
			glVertex2f(0.0, 0.1);
			glVertex2f(0, 0.0);
			glEnd();
			GLfloat matrixf[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
			enem.spaceship.amos[i].x = matrixf[12];
			enem.spaceship.amos[i].y = matrixf[13];
			//enem.spaceship.amos[i].colaider();
			//eminemCrash(enem.spaceship.amos[i]);
			glPopMatrix();
		}
	}


	//Space
	for (int i = 0; i < ((_DrawStar * 2) - 2) / 2; i = i + 2) {
		glPushMatrix();
		glTranslatef(-player.spaceship.horizontalPosition / 20, -player.spaceship.verticalPosition / 20, 0.0);
		glBegin(GL_POINTS);
		glColor3f(player.spaceship.verticalPosition + StarBrightness, player.spaceship.horizontalPosition + StarBrightness, 1.0);
		glVertex2f(StarCoord[i], StarCoord[i+1]);
		glEnd();
		glPopMatrix();
	}

	for (int i = _DrawStar / 2; i < (_DrawStar * 2) - 2; i = i + 2) {
		glPushMatrix();
		glTranslatef(-player.spaceship.horizontalPosition / 10, -player.spaceship.verticalPosition / 10, 0.0);
		glBegin(GL_POINTS);
		glColor3f(player.spaceship.verticalPosition + 1.5, player.spaceship.horizontalPosition + 1.5, 1.0);
		glVertex2f(StarCoord[i], StarCoord[i + 1]);
		glEnd();
		glPopMatrix();
	}

	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) {

	if (key == _GLFW_KEY_SPACE) {
		cout << "Space press";
		player.spaceship.fire();
		//enem.spaceship.fire();
		fireEfect->play2D("audio/lasser.wav", false);
	}

}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if (player.spaceship.horizontalPosition - player.spaceship.speed < 1.0 && player.spaceship.horizontalPosition - player.spaceship.speed > -1.0)
			player.spaceship.horizontalPosition -= player.spaceship.speed;
		break;
	case GLUT_KEY_RIGHT:
		if (player.spaceship.horizontalPosition + player.spaceship.speed < 1.0 && player.spaceship.horizontalPosition + player.spaceship.speed > -1.0)
			player.spaceship.horizontalPosition += player.spaceship.speed;
		break;
	case GLUT_KEY_UP:
		if (player.spaceship.verticalPosition + player.spaceship.speed < 1.0 && player.spaceship.verticalPosition + player.spaceship.speed > -1.0)
			player.spaceship.verticalPosition += player.spaceship.speed;
		break;
	case GLUT_KEY_DOWN:
		if (player.spaceship.verticalPosition - player.spaceship.speed < 1.0 && player.spaceship.verticalPosition - player.spaceship.speed > -1.0)
			player.spaceship.verticalPosition -= player.spaceship.speed;
		break;
	}
}

void Mouse(int ax, int ay)
{
	float XPosition = (ax / (float)(_DisplayWidth - (_DisplayWidth / 2))) - 1.0;
	float YPosition = (ay / (float)(_DisplayHeight - (_DisplayHeight / 2))) - 1.0;
	//cout << fixed;
	//cout << " x:" << XPosition << " y:" << -YPosition << endl;

	player.spaceship.horizontalPosition = XPosition;
	player.spaceship.verticalPosition = -YPosition;
}

void MouseFunc(int button, int state, int x, int y)
{
	if (button == 3) {
		player.spaceship.angle += 5;
	}

	if (button == 4) {
		player.spaceship.angle -= 5;
	}

	if (button == GLUT_MIDDLE_BUTTON) {
		player.spaceship.angle = 0;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		cout << "Mouse Left press";
		player.spaceship.fire();
		fireEfect->play2D("audio/lasser.wav", false);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		cout << "Mouse Right press";
		eminemAngleSet();
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 0.0f, 0.0f, 1.0f);
	createStar();
	eminemNew();
	BackgroundMusic->play2D("audio/bg.mp3", true);
}

int main(int argc, char** argv)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, _DisplayWidth, _DisplayHeight, TRUE);

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