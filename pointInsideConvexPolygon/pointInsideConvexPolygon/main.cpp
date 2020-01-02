#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <vector>
#include "vector.h"

using namespace std;

int width = 640, height = 480;

vector<Point2> p;
Point2 q;

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

void pointPosition()
{
	vector2 v1, v2;
	float a;
	for (int i = 0; i < p.size(); i++)
	{
		v1 = q - p.at(i);
		if (i == p.size()-1)
			v2 = p.at(0) - p.at(i);
		else
			v2 = p.at(i + 1) - p.at(i);
		a = v2.deltaX();
		v2.setX(-v2.deltaY());
		v2.setY(a);
		a = v1 * v2;
		if (a > 0)
		{
			cout << "Point lie outside the polygon";
			break;
		}
	}
	if(a<0)
		cout << "Point lie inside the polygon";
}

void myDisplay()
{

}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		p.push_back(Point2(x,height-y));
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		q= Point2(x, height - y);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i < p.size(); i++)
			glVertex2d(p.at(i).getX(), p.at(i).getY());
	glEnd();

	if (q.getX() && q.getY())
		pointPosition();

	glFlush();
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