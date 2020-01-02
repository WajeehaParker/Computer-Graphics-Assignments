#include <iostream>
#include <fstream>
#include <string>
#include <glut.h>
#include <vector>

//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")
//#pragma comment(lib, "glut32.lib")

using namespace std;

int width = 640;
int height = 480;
struct xy {
	int x;
	int y;
};
vector<xy> vectorList;

void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void myInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glColor3f(1, 0, 0);
	glPointSize(4.0);
	setWindow(0.0, 640.0, 0.0, 480.0);
}

void drawBoundingBox()
{
	int xmin=640, xmax=0, ymin=480, ymax=0;
	for (int i = 0; i < vectorList.size(); i++)
	{
		if (vectorList.at(i).x < xmin)
			xmin = vectorList.at(i).x;
		else if (vectorList.at(i).x > xmax)
			xmax = vectorList.at(i).x;
		if (vectorList.at(i).y < ymin)
			ymin = vectorList.at(i).y;
		else if (vectorList.at(i).y > ymax)
			ymax = vectorList.at(i).y;
	}

	glColor3f(0, 0, 1);
	glBegin(GL_LINE_STRIP);
		glVertex2d(xmin, ymax);
		glVertex2d(xmax, ymax);
		glVertex2d(xmax, ymin);
		glVertex2d(xmin, ymin);
		glVertex2d(xmin, ymax);
	glEnd();
}

void drawBoundingCircle()
{
	int xmin = 640, xmax = 0, ymin = 480, ymax = 0;
	for (int i = 0; i < vectorList.size(); i++)
	{
		if (vectorList.at(i).x < xmin)
			xmin = vectorList.at(i).x;
		else if (vectorList.at(i).x > xmax)
			xmax = vectorList.at(i).x;
		if (vectorList.at(i).y < ymin)
			ymin = vectorList.at(i).y;
		else if (vectorList.at(i).y > ymax)
			ymax = vectorList.at(i).y;
	}

	glColor3f(0, 1, 0);
	int radius, x, y;
	int centerx = ((xmax - xmin) / 2)+xmin;
	int centery = ((ymax - ymin) / 2)+ymin;
	xy center{centerx ,centery};
	if (center.x-xmin > center.y-ymin)
		radius = center.x-xmin;
	else radius = center.y-ymin;

	glPointSize(2.0);
	glBegin(GL_POINTS);
		for (int i = 0; i < 300; i++)
		{
			x = (cos(i * 2 * 180 / 300) * radius)+center.x;
			y = (sin(i * 2 * 180 / 300) * radius)+center.y;
			glVertex2d(x, y);
		}
	glEnd();

}

void myDisplay(void)
{
	int x, y;

	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
		glVertex2d(150, 190);
		glVertex2d(350, 190);
		glVertex2d(380, 150);
		glVertex2d(120, 150);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2d(70, 150);
		glVertex2d(430, 150);
		glVertex2d(460, 90);
		glVertex2d(40, 90);
	glEnd();

	vectorList.push_back({ 150, 190 });
	vectorList.push_back({ 350, 190 });
	vectorList.push_back({380, 150});
	vectorList.push_back({ 120, 150 });
	vectorList.push_back({70, 150});
	vectorList.push_back({ 430, 150 });
	vectorList.push_back({460, 90});
	vectorList.push_back({ 40, 90 });

	glBegin(GL_POLYGON);
	for (int i = 0; i < 40; i++)
	{
		x = (cos(i * 2 * 180 / 40) * 25) + 150;
		y = (sin(i * 2 * 180 / 40) * 25) + 80;
		glVertex2d(x, y);
		vectorList.push_back({x,y});
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 40; i++)
	{
		x = (cos(i * 2 * 180 / 40) * 25) + 350;
		y = (sin(i * 2 * 180 / 40) * 25) + 80;
		glVertex2d(x, y);
		vectorList.push_back({ x,y });
	}
	glEnd();

	drawBoundingBox();
	drawBoundingCircle();

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(300, 100);

	glutCreateWindow("Bounding Box And Circle");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}