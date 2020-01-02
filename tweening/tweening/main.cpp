#include <string>
#include <glut.h>
#include <vector>

using namespace std;

struct p {
	float x, y;
};

vector<p> Pa = { {1,1}, {-1,1}, {-1,-1}, {1,-1} };
vector<p> Pb = { {5,-2}, {4,3}, {4,0}, {3,-2} };
vector<p> result;

int width = 640, height = 480;

void tweenPolygons(float t)
{
	for(int i=0; i<4; i++)
		result.push_back({ (Pa.at(i).x*(1 - t)) + (Pb.at(i).x*t), (Pa.at(i).y*(1 - t)) + (Pb.at(i).y*t) });

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 4; i++)
		glVertex2d(result.at(i).x, result.at(i).y);
	glEnd();
}

void setWindow(int left, int right, int top, int bottom)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, top, bottom);
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(4.0);
	setWindow(-10, 10, -10, 10);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	tweenPolygons(0.5);

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