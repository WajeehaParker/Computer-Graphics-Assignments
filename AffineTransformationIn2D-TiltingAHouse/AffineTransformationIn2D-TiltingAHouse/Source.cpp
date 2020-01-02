#include <glut.h>

int width = 640, height = 480;

void initCT(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void scale2D(double sx, double sy)
{
	glMatrixMode(GL_MODELVIEW);
	glScaled(sx, sy, 1.0);
}

void Translate2D(double dx, double dy)
{
	glMatrixMode(GL_MODELVIEW);
	glTranslated(dx, dy, 0);
}

void rotate2D(double angle)
{
	glMatrixMode(GL_MODELVIEW);
	glRotated(angle, 0.0, 0.0, 1.0);
}

void setWindow(int left, int right, int top, int bottom)
{
	//glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
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

void house(void)
{
	glBegin(GL_LINE_STRIP);
		glVertex2d(0,0);
		glVertex2d(0,100);
		glVertex2d(50,150);
		glVertex2d(100,100);
		glVertex2d(100,0);
		glVertex2d(0,0);
	glEnd();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	house();
	Translate2D(100, 100);
	rotate2D(30.0);
	house();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 150);

	glutCreateWindow("New");
	myInit();
	glutDisplayFunc(myDisplay);

	

	glutMainLoop();
	return 0;

}