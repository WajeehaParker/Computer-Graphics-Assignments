#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <ctime>
#include "mario.h"

int width = 640, height = 480;
Mario m=Mario();

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

int gettime(void)
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return timeinfo->tm_sec;
}

void myDisplay(void)
{
	/*float t = 0.1;
	int initialtime = gettime();
	int duration =10;
	m.merge(t);
	t += 0.1;
	while (t <= 1.0)
	{
		if (gettime() == initialtime + duration)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			m.merge(t);
			m.render(100,100);
			duration += 10;
			t += 0.1;
			glutSwapBuffers();
			glFlush();
		}
	}*/

	glClear(GL_COLOR_BUFFER_BIT);
	int x=0, y=0;
	float t = 0.1;
	while (t <= 1.0)
	{
		m.merge(t);
		if (x >= width)
		{
			x = 0;
			y += 100;
		}
		m.render(x,y);
		t += 0.1;
		x+=80;
	}
	glutSwapBuffers();
	glFlush();	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 150);

	glutCreateWindow("New");
	glutDisplayFunc(myDisplay);

	myInit();

	glutMainLoop();
	return 0;

}