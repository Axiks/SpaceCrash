﻿#pragma once
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
//#pragma comment(lib, "irrKlang.lib")
//#include <irrKlang.h>
#include <cstdlib>
#include <ctime>  
#include <random>
#include <windows.h>

//using namespace irrklang;
using namespace std;

//ISoundEngine* BackgroundMusic = createIrrKlangDevice();
//ISoundEngine* fireEfect = createIrrKlangDevice();
Spaceship spaceship;
Amo amo;

mt19937 gen;
uniform_real_distribution<> tandH(-0.9, 0.9);
uniform_real_distribution<> tandV(0, 0.9);


Enemies enem(0.0, 0.0);

void amoColaider() {
	//cout << "AMO Position x:" << amo.horizontalPosition << " y:" << amo.verticalPosition << endl;
	if (amo.verticalPosition >= 1.0) {
		amo.live = false;
		cout << "Amo live false";
	}
}

void eminemNew() {
	enem.live = true;
	gen.seed(time(0));
	enem.horizontalPosition = (float)tandH(gen);
	enem.verticalPosition = (float)tandV(gen);
}

void eminemCrash() {
	cout << "Enem horyzontal position: " << enem.horizontalPosition << endl;
	cout << "Amo hor position: " << amo.horizontalPosition << endl;
	if (
			amo.verticalPosition >= enem.verticalPosition - enem.h && ( (amo.horizontalPosition > enem.horizontalPosition) && (amo.horizontalPosition <= enem.horizontalPosition + (enem.h + 0.01)))
		) {
		amo.live = false;
		enem.live = false;
		eminemNew();
	}
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(spaceship.verticalPosition, -spaceship.horizontalPosition, 0.0);
	glRotated(spaceship.angle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(spaceship.verticalPosition, spaceship.horizontalPosition, 1.0);
	glVertex2f(-0.05, -0.06);
	glVertex2f(0.05, -0.06);
	glVertex2f(0, 0.06);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	if (amo.live) {
		amoColaider();
		//glTranslatef(amo.verticalPosition, -amo.horizontalPosition, 0.0);
		//glRotated(amo.angle, 0, 0, 1);
		glRotated(amo.angle, 0, 0, 1);
		glTranslated(amo.horizontalPosition, amo.verticalPosition += amo._speed, 0);
		//glTranslatef(amo.horizontalPosition += amo._speed, amo.verticalPosition += sqrt(pow(abs(amo.horizontalPosition - amo.horizontalFirePosition) / cos(amo.angle),2) - pow(amo.horizontalFirePosition - amo.horizontalFirePosition, 2)) - amo.verticalFirePosition, 0.0);
		glBegin(GL_LINES);
		glColor3f(spaceship.horizontalPosition, spaceship.verticalPosition + amo._speed, 0.9);
		glVertex2f(0.0, 0.1);
		glVertex2f(0, 0.0);
		glEnd();
	}
	glPopMatrix();



	//Enemies
	glPushMatrix();

	if (enem.live) {
		eminemCrash();
		glTranslatef(enem.horizontalPosition, enem.verticalPosition, 0.0);
		glBegin(GL_QUADS);
		glColor3f(spaceship.verticalPosition, spaceship.horizontalPosition, 1.0);
		glVertex2f(0.0, enem.h);
		glVertex2f(enem.w, enem.h);
		glVertex2f(enem.w, 0.0);
		glVertex2f(0.0, 0.0);
		glEnd();
	}


	glPopMatrix();


	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) {

	if (key == _GLFW_KEY_SPACE) {
		cout << "Space press";
;		if (amo.live == false) {
			amo.live = true;
			amo.angle = spaceship.angle;

			amo.horizontalFirePosition = spaceship.verticalPosition;
			amo.verticalFirePosition = -spaceship.horizontalPosition;

			amo.horizontalPosition = amo.horizontalFirePosition;
			amo.verticalPosition = amo.verticalFirePosition;

			cout << "Angle: " << amo.angle << endl;
			cout << "AMO horizontalPosition: " << amo.horizontalPosition << endl;
			cout << "AMO verticalPosition: " << amo.verticalPosition << endl;

			//fireEfect->play2D("audio/fire.mp3", false);
		}
		else {
			amo.live = false;
			amo.angle = 0;
			amo.horizontalFirePosition = 0;
			amo.verticalFirePosition = 0;
			amo.horizontalPosition = 0;
			amo.verticalPosition = 0;
			//fireEfect->removeAllSoundSources();
		}
	}

}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if(spaceship.verticalPosition - spaceship.speed < 1.0 && spaceship.verticalPosition - spaceship.speed > -1.0)
			spaceship.verticalPosition -= spaceship.speed;
		break;
	case GLUT_KEY_RIGHT:
		if (spaceship.verticalPosition + spaceship.speed < 1.0 && spaceship.verticalPosition + spaceship.speed > -1.0)
			spaceship.verticalPosition += spaceship.speed;
		break;
	case GLUT_KEY_UP:
		if (spaceship.horizontalPosition - spaceship.speed < 1.0 && spaceship.horizontalPosition - spaceship.speed > -1.0)
			spaceship.horizontalPosition -= spaceship.speed;
		break;
	case GLUT_KEY_DOWN:
		if (spaceship.horizontalPosition + spaceship.speed < 1.0 && spaceship.horizontalPosition + spaceship.speed > -1.0)
			spaceship.horizontalPosition += spaceship.speed;
		break;
	}
}

void Mouse(int ax, int ay)
{
	float XPosition = (ax / (float)(_DisplayWidth - (_DisplayWidth / 2))) - 1.0;
	float YPosition = (ay / (float)(_DisplayHeight - (_DisplayHeight / 2))) - 1.0;
	cout << fixed;
	cout << " x:" << XPosition << " y:" << YPosition << endl;

	spaceship.verticalPosition = XPosition;
	spaceship.horizontalPosition = YPosition;
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
		cout << "Space press";
		;		if (amo.live == false) {
			amo.live = true;
			amo.angle = spaceship.angle;

			amo.horizontalFirePosition = spaceship.verticalPosition;
			amo.verticalFirePosition = -spaceship.horizontalPosition;

			amo.horizontalPosition = amo.horizontalFirePosition;
			amo.verticalPosition = amo.verticalFirePosition;

			cout << "Angle: " << amo.angle << endl;
			cout << "AMO horizontalPosition: " << amo.horizontalPosition << endl;
			cout << "AMO verticalPosition: " << amo.verticalPosition << endl;

			//fireEfect->play2D("audio/fire.mp3", false);
		}
		else {
			amo.live = false;
			amo.angle = 0;
			amo.horizontalFirePosition = 0;
			amo.verticalFirePosition = 0;
			amo.horizontalPosition = 0;
			amo.verticalPosition = 0;
			//fireEfect->removeAllSoundSources();
		}
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

