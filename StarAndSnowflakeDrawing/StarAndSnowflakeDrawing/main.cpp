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

void starMotif()
{
	glBegin(GL_LINE_STRIP);
		glVertex2d(-25, 0);
		glVertex2d(0, 100);
		glVertex2d(15, 25);
		glVertex2d(5, 25);
		glVertex2d(0, 50);
		glVertex2d(-15, -5);
		glVertex2d(-25, 0);
	glEnd();
}

void star(void)
{
	Translate2D(100, 100);
	for (int i = 0; i < 5; i++)
	{
		rotate2D(72.0);
		starMotif();
	}
}

void snowFlakeMotif(void)
{
	glBegin(GL_LINE_STRIP);
		glVertex2d(0, 2);
		glVertex2d(50, 2);
		glVertex2d(62, 25);
		glVertex2d(64, 23);
		glVertex2d(52, 2);
		glVertex2d(75, 2);
		glVertex2d(87, 25);
		glVertex2d(89, 23);
		glVertex2d(77, 2);
		glVertex2d(100, 2);
		glVertex2d(102, 0);
	glEnd();
}

void snowflake(void)
{
	Translate2D(400, 200);
	for (int i = 0; i < 6; i++)
	{
		snowFlakeMotif();
		scale2D(1.0, -1.0);
		snowFlakeMotif();
		scale2D(1.0, -1.0);
		rotate2D(60.0);
	}
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	star();
	snowflake();

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