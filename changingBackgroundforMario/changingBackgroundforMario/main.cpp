#include <stdlib.h>
#include <glut.h>
#include "mario.h"

int width = 640, height = 480;

Mario m;

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
	setWindow(0, 100, 0, 100);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	m.render();
	mRGBA newColor(31, 202, 241, 255);
	m.changeBGcolor(newColor);
	
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