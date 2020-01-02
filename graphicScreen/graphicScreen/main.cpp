#include <glut.h>

int width = 640, height = 480;

void setWindow(int left, int right, int top, int bottom)
{
	//glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(left, right, bottom, top, znear, zfar);
	//gluOrtho2D(left, right, bottom, top);
	gluOrtho2D(left, right, top, bottom);
}

void myInit(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	setWindow(0, width, 0, height);
}

void myKeyboard(unsigned char theKey, int mousex, int mousey)
{
	GLint x = mousex;
	GLint y = height - mousey;
	switch (theKey)
	{
		case 'p':
		
		case GLUT_KEY_LEFT:

		case 'E':
			exit(-1);
		default:
			break;	
	}
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glVertex2i(100, 50);
	glVertex2i(100, 130);
	glVertex2i(150, 130);
	glEnd();

	//glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 150);
	
	glutCreateWindow("New");
	glutDisplayFunc(myDisplay);
	//glutReshapeFunc(myReshape);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);

	myInit();
	
	glutMainLoop();
	return 0;

}