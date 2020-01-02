#include <stdlib.h>
#include <glut.h>
#include <vector>

using namespace std;

int width = 640, height = 480;
struct xyz {
	double x, y, z;
};
vector<xyz> vlist;

void spiralPoints()
{
	float b = 0;
	/*for (float i = 0; i < 8*180; i+=720/200)
	{
		vlist.push_back({ cos(i*3.14*180), sin(i*3.14 * 180), (double)-b++ * i });
	}*/
	for (float t = 0; t < 4*360; t++)
	{
		/*vlist.push_back({ cos(t*3.141592654/180), sin(t*3.141592654/180), (double)-b++ });*/
		vlist.push_back({ cos(t*3.14159/180)*10, sin(t*3.14159 / 180)*10, (double)-b++ });
	}	
}

void drawSpiral()
{
	glLineWidth(1.0);
	spiralPoints();
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < vlist.size(); i++)
		glVertex3d(vlist.at(i).x, vlist.at(i).y, vlist.at(i).z);
	glEnd();
}


void setWindow(int fov, int ar, int znear, int zfar)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ar, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
}

void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	setWindow(5, width/height, 0, 50);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(0, 0, 5);

	drawSpiral();

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