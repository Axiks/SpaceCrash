#include "Main.h"
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <windows.h>
#include <cmath>
#include "Vars.h"
#include "Spaceship.h"
#include "Amo.h"
using namespace std;

Spaceship spaceship;
Amo amo;
float positionSpaceShipX;

void Draw()
{
	//cout << "Draw";

	GLfloat centerX = (-0.15 + 0 + 0.15) / 3;
	GLfloat centerY = (0 + 0 + 0.45) / 3;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(spaceship.verticalPosition, -spaceship.horizontalPosition, 0.0);
	glRotated(spaceship.angle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(spaceship.verticalPosition, spaceship.horizontalPosition, 1.0);
	glVertex2f(-0.1, -0.15);
	glVertex2f(0.1, -0.15);
	glVertex2f(0, 0.15);
	glEnd();

	glPopMatrix();


	glPushMatrix();

	if (amo.live) {
	glTranslatef(amo.verticalPosition, -amo.horizontalPosition, 0.0);
	glRotated(amo.angle, 0, 0, 1);
	
		glTranslatef(0.0, amo.verticalVector += amo._speed, 0.0);
		glBegin(GL_LINES);
		glColor3f(spaceship.horizontalPosition, spaceship.verticalPosition, 0.7);
		glVertex2f(0.0, 0);
		glVertex2f(0, 0.1);
		glEnd();
	}

	glPopMatrix();



	//Enemies
	glPushMatrix();

	glTranslatef(0.2, 0.85, 0.0);
	glBegin(GL_QUADS);
	glColor3f(spaceship.verticalPosition, spaceship.horizontalPosition, 1.0);
	glVertex2f(0.0, 0.1);
	glVertex2f(0.1, 0.1);
	glVertex2f(0.1, 0.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	glPopMatrix();



	glutSwapBuffers();
	//glRotated(-spaceship.angle, 0, 0, 1);
	//glTranslatef(-spaceship.verticalPosition, spaceship.horizontalPosition, 0.0);

	//glPopMatrix();

	//glFlush();

}



void Mouse(int ax, int ay)
{
	float XPosition = (ax / (float) (_DisplayWidth - (_DisplayWidth/2))) -1.0;
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
		if (amo.live == false) {
			amo.live = true;
			amo.angle = spaceship.angle;
			amo.horizontalPosition = spaceship.horizontalPosition;
			amo.verticalPosition = spaceship.verticalPosition;
		}
		else {
			amo.live = false;
			amo.horizontalPosition = 0;
			amo.verticalPosition = 0;
			amo.verticalVector = 0;
			amo.live = true;
			amo.angle = spaceship.angle;
			amo.horizontalPosition = spaceship.horizontalPosition;
			amo.verticalPosition = spaceship.verticalPosition;
		}
		cout << "Amo fire" << endl;
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
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(_DisplayWidth, _DisplayHeight);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("SpaceY");
	glutDisplayFunc(Draw);
	glutTimerFunc(_DisplayFPS, Timer, 0);
	glutPassiveMotionFunc(Mouse);
	glutMouseFunc(MouseFunc);
	Init();
	glutMainLoop();
}


///////////////////////////

//#include <iostream>
//#include "glut.h"
//
//using namespace std;
//
//int max_bullets = 5;//10;
//
//struct Bullet {
//	int x, y;
//	bool busy;
//};
//
//class Fire
//{
//private:
//	Bullet* bullets;
//
//public:
//	Fire()
//	{
//		bullets = new Bullet[max_bullets];
//		for (int i = 0; i < max_bullets; ++i)
//			bullets[i].busy = false;
//	}
//	~Fire() { delete[] bullets; }
//
//	bool AddBullet()
//	{
//		int n = -1;
//		for (int i = 0; i < max_bullets; ++i)
//			if (!bullets[i].busy) {
//				n = i;
//				break;
//			}
//		if (n < 0) return false;
//		bullets[n].busy = true;
//		bullets[n].x = 0;
//		bullets[n].y = 0;
//		return true;
//	}
//
//	void Update()
//	{
//		for (int i = 0; i < max_bullets; ++i)
//			if (bullets[i].busy) {
//				bullets[i].y += 15;
//				if (bullets[i].y > 300)
//					bullets[i].busy = false;
//			}
//	}
//
//	void Draw()
//	{
//		//      glPushMatrix();
//		//      glTranslatef(0.0,0.0,0.0);
//		glPointSize(10);
//		glEnable(GL_POINT_SMOOTH);
//		glBegin(GL_POINTS);
//		glColor3f(0.0f, 1.0f, 0.0f);
//		glVertex2f(0.0f, 0.0f);
//		glColor3f(1.0f, 0.0f, 1.0f);
//		for (int i = 0; i < max_bullets; ++i) {
//			if (bullets[i].busy) {
//				glVertex2f((float)bullets[i].x, (float)bullets[i].y);
//			}
//		}
//		glEnd();
//		glDisable(GL_POINT_SMOOTH);
//		//      glPopMatrix();
//	}
//
//} shot;
//
//void mauseClick(int button, int state, int x, int y)
//{
//	switch (button)
//	{
//	case GLUT_LEFT_BUTTON:
//		if (state == GLUT_UP) {
//			shot.AddBullet();
//		}
//		break;
//	case GLUT_MIDDLE_BUTTON:
//		if (state == GLUT_DOWN)
//			glutIdleFunc(NULL);
//		break;
//	default:
//		break;
//	}
//}
//
//void Timer(int value)
//{
//	shot.Update();
//	glutPostRedisplay();
//	glutTimerFunc(100, Timer, 0);
//}
//
//void draw()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	shot.Draw();
//
//	glFlush();
//	glutSwapBuffers();
//}
//
//void Initialization()
//{
//	glClearColor(0.1, 0.3, 0.5, 1.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-600, 600, -400, 400, -300, 300);
//}
//
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
//	glutInitWindowSize(640, 480);
//	glutInitWindowPosition(20, 20);
//	glutCreateWindow("Tanks");
//	glutDisplayFunc(draw);
//	glutTimerFunc(100, Timer, 0);
//	glutMouseFunc(mauseClick);
//	Initialization();
//	glutMainLoop();
//	system("pause >> NULL");
//	return 0;
//}