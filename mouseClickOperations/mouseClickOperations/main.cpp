#include <stdlib.h>
#include <glut.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include "mario.h"

using namespace std;

int width = 640, height = 480;
int displaycount = 0;
Mario m;

struct xy {
	int x, y;
};
vector<xy> p;

void setWindow(int left, int right, int top, int bottom)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, top, bottom);
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	setWindow(0, width, 0, height);
}

void myDisplay(void)
{
	
}

void displayPoints(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	for (int i = 0; i < p.size(); i++)
	{
		cout << p.at(i).x << " " << p.at(i).y;
		glVertex2d(p.at(i).x, p.at(i).y);
	}
	glEnd();
	glFlush();
}

void displayGameCharacter()
{
	glClear(GL_COLOR_BUFFER_BIT);
	m.render();
	glFlush();
}

float gettime()
{
	static __int64 i64Frequency = 0;
	static __int64 i64BeginCount = 0;
	if (i64Frequency == 0)
	{	// do this only for the first time
		QueryPerformanceFrequency((LARGE_INTEGER*)&i64Frequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&i64BeginCount); //retrieve the number of
																 //ticks since system start (64bit int).
	}
	__int64 i64CurrentCount;
	QueryPerformanceCounter((LARGE_INTEGER*)&i64CurrentCount);
	return  (float)(i64CurrentCount - i64BeginCount) / i64Frequency;
}

void displayObject(int x, int y)
{
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x+5, y+5);
	glVertex2d(x+10, y);
	glVertex2d(x-5, y-5);
	glEnd();
}

void objectAtRandomPosition()
{
	int x, y;
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 10; i++)
	{
		float f = gettime();
		cout << f << " ";
		x = ((int)f % 640)+30;
		y = ((int)f % 480)+30;
		displayObject(x, y);
	}
	glFlush();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		switch (displaycount)
		{
		case 0:
			p.push_back({ x, height - y });
			break;
		case 2:
			m.setPosition(x, height-y);
			displayGameCharacter();
			break;
		}
	}
		
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		switch (displaycount)
		{
		case 0:
			displayPoints();
			break;
		case 1:
			displayGameCharacter();
			break;
		case 2:
			objectAtRandomPosition();
			break;
		}
		displaycount++;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 150);

	glutCreateWindow("New");
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);

	myInit();

	glutMainLoop();
	return 0;

}