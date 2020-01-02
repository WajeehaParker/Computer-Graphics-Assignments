#include <stdlib.h>
#include <glut.h>
#include "RGBA.h"
#include <stdio.h>
#include "camera.h"

static GLubyte my_texels[1][1][1];
static GLuint texName;
//Camera cam;
RGBApixmap pix[1];

int l1 = 1, l2 = 0, l3 = 0;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 640 / 480, 2.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.6);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 51, 51, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_texels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_texels);

} 

//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, texName);
//
//	float pi = 3.14285714;
//	double deltheta = 2 * pi / 180;
//	double delalpha = pi / 360;
//	float alphas, thetas;
//	int radius = 10;
//	int stack = 30, slice = 30;
//	//int stack = 360, slicebegin = -90, slice end = 90;  alpha+=5, theta+=5
//
//	for (int theta = 0; theta < stack; theta++)
//	{
//		for (int alpha = 0; alpha < slice; alpha++)
//		{
//			/*glBegin(GL_QUADS);
//			glTexCoord2f(0.0, 0.0);
//			glVertex3f(theta, alpha, 0);
//			glTexCoord2f(0.0, 1.0);
//			glVertex3f(theta+5, alpha, 0);
//			glTexCoord2f(1.0, 1.0);
//			glVertex3f(theta+5, alpha+5, 0);
//			glTexCoord2f(1.0, 0.0);
//			glVertex3f(theta, alpha+5, 0);
//			glEnd();*/
//			alphas = (theta*pi) / stack;
//			thetas = (alpha*pi * 2) / slice;
//			glBegin(GL_LINE_LOOP);		
//			glVertex3f(radius*sin(alphas)*sin(thetas), radius*sin(alphas)*cos(thetas), radius*cos(alphas));
//			glVertex3f(radius*sin(alphas)*sin(thetas + deltheta), radius*sin(alphas)*cos(thetas + deltheta), radius*cos(alphas));
//			glVertex3f(radius*sin(alphas + delalpha)*sin(thetas + deltheta), radius*sin(alphas + delalpha)*cos(thetas + deltheta), radius*cos(alphas + delalpha));
//			glVertex3f(radius*sin(alpha + delalpha)*sin(thetas), radius*sin(alphas + delalpha)*cos(thetas), radius*cos(alphas + delalpha));
//			glEnd();
//		}
//	}
//
//	glFlush();
//	glDisable(GL_TEXTURE_2D);
//}

int nstacks = 30, nslices = 30;

void sphere(int slices, int stacks)
{
	int radius = 10;
	float pi = 3.14285714;
	double deltheta = 2 * pi / nslices;
	double delalpha = pi / nstacks;
	float alpha, theta;

	for (int i = 0; i < stacks; i++)
	{
		for (int j = 0; j < slices; j++)
		{
			alpha = (i*pi) / stacks;
			theta = (j*pi * 2) / slices;
			glBegin(GL_QUADS);		
			glTexCoord2f(0.0, 0.0);
			glVertex3f(radius*sin(alpha)*sin(theta), radius*sin(alpha)*cos(theta), radius*cos(alpha));
			glTexCoord2f(0.0, 1.0);
			glVertex3f(radius*sin(alpha)*sin(theta + deltheta), radius*sin(alpha)*cos(theta + deltheta), radius*cos(alpha));
			glTexCoord2f(1.0, 1.0);
			glVertex3f(radius*sin(alpha + delalpha)*sin(theta + deltheta), radius*sin(alpha + delalpha)*cos(theta + deltheta), radius*cos(alpha + delalpha));
			glTexCoord2f(1.0, 0.0);
			glVertex3f(radius*sin(alpha + delalpha)*sin(theta), radius*sin(alpha + delalpha)*cos(theta), radius*cos(alpha + delalpha));
			glEnd();
		}
	}


}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName);

	sphere(30, 30);

	glFlush();
	glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
	glViewport(0, 0, 640, 480);
	glLoadIdentity();
	gluLookAt(0, 0, 0, l1, l2, l3, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 640 / 480, 2.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.6);
}

void myKeyboard(unsigned char theKey, int mousex, int mousey)
{
	GLint x = mousex;
	GLint y = 480 - mousey;
	switch (theKey)
	{
	case 'a':
		if (l1 > -1.0)
			l1 -= 0.1;
		//glutPostRedisplay();
		glutReshapeFunc(reshape);
		break;
	case 's':
		if (l1 < 1.0)
			l1 += 0.1;
		//glutPostRedisplay();
		glutReshapeFunc(reshape);
		break;
	case 'd':
		if (l2 < 1.0)
			l2 += 0.1;
		//glutPostRedisplay();
		glutReshapeFunc(reshape);
		break;
	case 'w':
		if (l2 > -1.0)
			l2 -= 0.1;
		//glutPostRedisplay();
		glutReshapeFunc(reshape);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	pix[0].readBMPFile("sky.bmp", texName);
	pix[0].setTexture(texName);
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(reshape);
	//cam.set(2.3, 1.3, 2, 0, 0.25, 0, 0, 1, 0);
	gluLookAt(0, 0, 0, l1, l2, l3, 0, 1, 0);
	glutMainLoop();
	return 0;
}