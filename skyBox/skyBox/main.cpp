#include <stdlib.h>
#include <glut.h>
#include "RGBA.h"
#include <stdio.h>
#include "camera.h"

static GLubyte my_texels[1][1][1];
static GLuint texName;
Camera cam;
RGBApixmap pix[1];

int l1 = 0, l2 = 0, l3 = 1;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	cam.setShape(50.0, 64.0f / 48.0f, 0.1, 100.0);
	//gluPerspective(50.0, 640 / 480, 2.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cam.setModelViewMatrix();
	glTranslatef(0.0, 0.0, -2.6);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 51, 51, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_texels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_texels);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName);

	glBegin(GL_QUADS);             //FRONT
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();
	
	glBegin(GL_QUADS);               //TOP
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glEnd();

	glBegin(GL_QUADS);               //RIGHT
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();
	
	glBegin(GL_QUADS);               //LEFT
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glEnd();
	
	glBegin(GL_QUADS);               //BOTTOM
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();

	glBegin(GL_QUADS);             //BACK
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glFlush();
	glDisable(GL_TEXTURE_2D);
}

//void reshape(int w, int h)
//{
//	glViewport(0, 0, 640, 480);
//	glLoadIdentity();
//	gluLookAt(0, 0, 0, l1, l2, l3, 0, 1, 0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(50.0, 640 / 480, 2.0, 30.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslatef(0.0, 0.0, -2.6);
//}

void myKeyboard(unsigned char theKey, int mousex, int mousey)
{
	switch (theKey)
	{
	case 'f': cam.slide(0, 0, -0.1); break; // slide camera forward
	case 'b': cam.slide(0, 0, 0.1);  break; // slide camera back
	case 'l': cam.slide(-0.1, 0, 0); break;
	case 'r': cam.slide(0.1, 0, 0);  break;
	case 'u': cam.slide(0, 0.1, 0);  break;
	case 'd': cam.slide(0, -0.1, 0); break;
	case 'm': cam.roll(-1.0); break; // roll counter-clockwise
	case 'n': cam.roll(1.0); break; // roll clockwise
	case 'Q': exit(0);
	default: break;
	}
	glutPostRedisplay();

	/*GLint x = mousex;
	GLint y = 480 - mousey;
	switch (theKey)
	{
	case 'a':
		if (l1 > -1.0)
			l1-=0.1;
		break;
	case 's':
		if (l1 < 1.0)
			l1+=0.1;
		break;
	case 'd':
		if (l2 < 1.0)
			l2+=0.1;
		break;
	case 'w':
		if (l2 > -1.0)
			l2-=0.1;
		break;
	default:
		break;
	}*/
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
	//glutReshapeFunc(reshape);
	cam.set(2.3, 1.3, 2, 0, 0.25, 0, 0, 1, 0);
	gluLookAt(0, 0, 0, l1, l2, l3, 0, 1, 0);
	glutMainLoop();
	return 0;
}