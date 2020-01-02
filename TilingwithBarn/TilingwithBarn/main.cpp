
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <glut.h>

#define PI 3.1415926535898
using namespace std;

//*********************************
// Lab Instructions
//*********************************

//   Do not change objects geometry and coordinates
//   You need to work in display and handle Mouse and Keyboard  events for setting and controlling Cameras
//   Set Perspective Camera  gluPerspective(fov,aspectRatio,zNear,zFar) as explained in class
//   Set Orthographic views  glOrtho(left, right, bottom, top, zNear, zFar) as explained in class
//   Carefully Look At Mouse Handlers how it make use of flage to change views
//   Implement User Camera Controls i.e.  Keyboard and/or mouse interaction
//   Implement flyby that simulates First Person Camera


//*********************************
// DRAWING ROUTINES Prototypes
//*********************************
void drawFloor(void);
void drawHouse(void);
void drawMountain(float bradius, float height);
void drawCtrees(float bradius, float height);
void drawTrees(float bradius, float height);

//

//*******************************************
// GLOBAL VARIABLES for Viewing Transformation
//*******************************************

float ww = 800.0, wh = 800.0;

//zNear and zFar values
float f = 520.0;
float n = 10.0;
float fov = 89.0;  // theta = arctan(top/zNear)  =arctan(400/10) =89


static GLdouble viewer[] = { 525.0,30.0,-200.0 };  // eye/ Camera Position
static GLdouble object[] = { 600,30,-300 };  // look Position
static GLdouble up[] = { 0.0,1.0,0.0 };

// 3 ortho views  i.e. Front veiw, Side View and Top View
static GLdouble ort1[] = { -500.0,500.0,-500,500.0 };   //Left right bottom top
static GLdouble ort2[] = { -200.0,200.0,0,300.0 };  //Left right bottom top
static GLdouble ort3[] = { -200.0,200.0,-45.0,200.0 }; //Left right bottom top


int upi = 0, ortho = 0, ortfront = 0, ortright = 0, orttop = 0;  // Flags to set Views


//*********************************
// DRAWING ROUTINES 
//*********************************


//Draw Floor Routine
// Let we want to draw 600 x 600 floor on xz plane
void drawFloor()
{
	//float i,j;
	float x, y = 0.0, z, z1;
	float xmax = ww - 200.0;  // 800 -200 = 600
	float zmax = ww - 200.0;  // 800 -200 = 600
	float xmin, zmin;
	float step = 5.0;

	xmin = 200.0;
	zmin = 200.0;

	glColor3f(0.0, 0.2, 0.0);

	//Floor Rectangular pattern
	for (x = xmin; x < xmax; x += step)
	{

		for (z = zmin; z < zmax; z += step) // first step on z-axis
		{
			z1 = -z;
			glBegin(GL_LINE_LOOP);
			glVertex3f(x, y, z1);               //<200.0,0.0,-200>                      start Point
			glVertex3f(x, y, z1 - step + 1.0);      //<200.0,0.0,-200-delz-1.0)             move 5 steps forward and 1 step back
			glVertex3f(x + step - 1.0, y, z1 - step + 1.0); // <200+step-1.0,0,-200-delz-1.0>   move 5 steps right and 1 step left
			glVertex3f(x + step - 1.0, y, z1);          // <200+step-1.0,0,-200>            move 5 steps backward toward start to complete square

			glEnd();

		}
		glColor3f(0.0, 0.0, 1.0);

	}
	glFlush();
}


//Draw House Routine

void drawHouse()
{
	int circle_points;
	float size, angle;
	int i;

	//House Main Vertices
	GLfloat housevert[] = { 500.0,0.0,-300.0,  //0
				 500.0,50.0,-300.0, //1
				 525.0,65.0,-300.0, //2
				 550.0,50.0,-300.0, //3
					 550.0,0.0,-300.0,  //4
				 500.0,0.0,-400.0,  //5
				 500.0,50.0,-400.0, //6
				 525.0,65.0,-400.0, //7
				 550.0,50.0,-400.0, //8
					 550.0,0.0,-400.0 };  //9
	glLineWidth(2.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, housevert);

	glColor3f(1.0, 0.0, 0.0);

	// Front Wall
	glBegin(GL_LINE_LOOP);
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(3);
	glArrayElement(4);
	glEnd();

	//Right Wall
	glBegin(GL_LINE_LOOP);
	glArrayElement(4);
	glArrayElement(3);
	glArrayElement(8);
	glArrayElement(9);
	glEnd();

	//Left Wall
	glBegin(GL_LINE_LOOP);
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(6);
	glArrayElement(5);
	glEnd();

	//Back Wall
	glBegin(GL_LINE_LOOP);
	glArrayElement(5);
	glArrayElement(6);
	glArrayElement(8);
	glArrayElement(9);
	glEnd();

	glColor3f(0.0, 0.0, 0.85);

	//Front Roof
	glBegin(GL_LINE_STRIP);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(3);
	glEnd();

	//Back Roof
	glBegin(GL_LINE_STRIP);
	glArrayElement(6);
	glArrayElement(7);
	glArrayElement(8);
	glEnd();

	//Right Roof
	glBegin(GL_LINE_STRIP);
	glArrayElement(3);
	glArrayElement(2);
	glArrayElement(7);
	glArrayElement(8);
	glEnd();

	//Left Roof
	glBegin(GL_LINE_STRIP);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(7);
	glArrayElement(6);
	glEnd();

	glColor3f(0.4, 0.4, 0.6);
	//Front Door
	glBegin(GL_LINE_LOOP);
	glVertex3f(515.0, 1.0, -300.0);
	glVertex3f(515.0, 25.0, -300.0);
	glVertex3f(535.0, 25.0, -300.0);
	glVertex3f(535.0, 1.0, -300.0);
	glEnd();

	//Right Window
	glColor3f(0.3, 1.0, 0.6);
	glBegin(GL_LINE_LOOP);
	glVertex3f(550, 20.0, -320.0);
	glVertex3f(550, 30.0, -320.0);
	glVertex3f(550, 30.0, -380.0);
	glVertex3f(550, 20.0, -380.0);
	glEnd();

	//Left Window
	glColor3f(0.7, 1.0, 0.3);
	glBegin(GL_LINE_LOOP);
	glVertex3f(500, 25.0, -345.0);
	glVertex3f(500, 35.0, -345.0);
	glVertex3f(500, 35.0, -390.0);
	glVertex3f(500, 25.0, -390.0);
	glEnd();

	//Circular Window
	size = 4.0;
	circle_points = 100;
	glColor3f(0.3, 0.5, 0.8);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < circle_points; i++) {
		angle = 2 * PI*i / circle_points;
		glVertex3f(525.0 + size * cos(angle), 56.0 + size * sin(angle), -400.0);
	}
	glEnd();

	glLineWidth(1.0);
}

// Draw The Moon Routine

void drawMoon()
{
	GLUquadricObj *moon;
	moon = gluNewQuadric();
	gluQuadricDrawStyle(moon, GLU_LINE);

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(230.0, 190.0, -550.0);
	gluSphere(moon, 15.0, 30, 30);


	glPopMatrix();
}

//Draw Mountain
//Input to the routine is the base radius and height of the mountain

void drawMountain(float bradius, float height)
{
	GLUquadricObj *mount;

	mount = gluNewQuadric();
	gluQuadricDrawStyle(mount, GLU_LINE);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.1, 0.3);
	gluCylinder(mount, bradius, 0.0, height, 40, 5);
	glPopMatrix();
}

//Draw Trees
//Input to the routine is the base radius and height of the trees

void drawTrees(float bradius, float height)
{
	GLUquadricObj *trees;

	trees = gluNewQuadric();
	gluQuadricDrawStyle(trees, GLU_LINE);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3f(0.4, 0.3, 0.2);
	gluCylinder(trees, bradius, bradius, height, 40, 4);
	glTranslatef(0.0, 0.0, height + 3.0);
	glColor3f(0.0, 1.0, 0.0);
	gluSphere(trees, 3 * bradius, 30, 30);
	glPopMatrix();
}

//Draw Christmas Tree
//Input to the routine is the base radius and height of the trees

void drawCtrees(float bradius, float height)
{
	GLUquadricObj *ctrees;

	ctrees = gluNewQuadric();
	gluQuadricDrawStyle(ctrees, GLU_LINE);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(ctrees, bradius, 0.0, height, 40, 5);
	glPopMatrix();
}


//*********************************
// DRAW EVERYTHING CALLBACK
//*********************************

void drawEverything()
{
	drawFloor();
	drawMoon();

	glPushMatrix();
	glTranslatef(300.0, 0.0, -500.0);
	drawMountain(95.0, 150.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(380.0, 0.0, -510.0);
	drawMountain(80.0, 100.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 0.0, -300.0);
	drawTrees(3.0, 20.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(525.0, 0.0, -550.0);
	drawTrees(6.0, 25.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(300.0, 0.0, -250.0);
	drawTrees(5.0, 35.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(560.0, 0.0, -240.0);
	drawTrees(1.5, 50.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0, 0.0, -400.0);
	drawTrees(2.0, 10.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(487.0, 0.0, -210.0);
	drawTrees(2.0, 10.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(220.0, 0.0, -220.0);
	drawCtrees(9.0, 12.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(220.0, 10.0, -220.0);
	drawCtrees(6.0, 7.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(220.0, 15.0, -220.0);
	drawCtrees(4.0, 4.0);
	glPopMatrix();

	drawHouse();
}

//void drawSolidHouse()
//{
//	glBegin()
//}

void drawScene()
{
	glColor3f(1, 0, 1);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			glPushMatrix();
			glTranslatef(200 + (20 * i), 5, -200 + (-20 * j));
			glutSolidCube(10);
			glPopMatrix();
		}
	}
}


//*********************************
// DISPLAY RESHAPE ROUTINE
//*********************************

void myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, 1.333, n, f);
	glMatrixMode(GL_MODELVIEW);

	ww = w;
	wh = h;
}


//*********************************
// SCREEN INITIALIZATION ROUTINE
//*********************************

void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}


//*********************************
// INITIAL OBJECT DISPLAY ROUTINE
//*********************************

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (ortho == 0)  //Normal View : Perspective Projection
	{
		//Place the camera and set target
		glLoadIdentity();
		gluLookAt(viewer[0], viewer[1], viewer[2], object[0], object[1], object[2], up[0], up[1], up[2]);

		//Define Viewing Volume

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov, 1.333, n, f);
		glMatrixMode(GL_MODELVIEW);

		//Draw Objects
		//drawEverything();
		
		drawFloor();
		drawScene();
	}

	if (ortho == 1) //Orthographic View, Multiple Viewports
	{
		glColor3f(1.0, 1.0, 1.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex2f(0.0, wh / 2.0);
		glVertex2f(ww, wh / 2.0);
		glEnd();
		glFlush();
		glLineWidth(1.0);

		//Bottom Right : Perspective Projection
		glViewport(ww / 2 + 1, 0, ww / 2, wh / 2 - 1);
		glLoadIdentity();
		gluLookAt(viewer[0], viewer[1], viewer[2], object[0], object[1], object[2], up[0], up[1], up[2]);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov, 1.0, n, f);

		glMatrixMode(GL_MODELVIEW);
		drawEverything();

		//Top Left : Front Orthographic
		glViewport(0, wh / 2 + 1, ww / 2, wh / 2);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(ort1[0], ort1[1], ort1[2], ort1[3], n, f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
		//drawEverything();
		drawScene();

		//Top Right : Right Orthographic
		glViewport(ww / 2 + 1, wh / 2 + 1, ww, wh);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(ort2[0], ort2[1], ort2[2], ort2[3], n, f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
		//drawEverything();
		drawScene();

		//Bottom Left : Top Orthographic
		glViewport(0, 0, ww / 2, wh / 2);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(ort3[0], ort3[1], ort3[2], ort3[3], n, f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
		//drawEverything();
		drawScene();
	}

	glutSwapBuffers(); //Double Buffer
}


//*********************************
// FLY-BY THE SCENERY ROUTINE
//*********************************

void flyby()
{
	object[0]--;
	object[0]--;
	object[0]--;
	object[0]--;
	object[0]--;
	fov--;
	fov--;
	fov--;
	fov--;
	fov--;


	//Objects gradually appear
	//Run through the house
	//Move around
	//Fly High
	//Orbit around the scenery
}


void myTimer(int t)
{
	flyby();
	glutTimerFunc(150, myTimer, 1);
	glutPostRedisplay();
}




//************************************
// MOUSE ACTIVITIES
//************************************

void mouse(int btn, int state, int x, int y)
{
	// SET FLAGS FOR CHANGING UP VECTOR 
	// ALSO IDENTIFY WHICH ORTHOGRAPHIC PROJECTION IS ACTIVE

	y = wh - y;

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) upi = 1;

	else if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		upi = 0;
		if (y > wh / 2 && x < ww / 2)
		{
			ortfront = 1;
			ortright = 0;
			orttop = 0;
			glutPostRedisplay();
		}
		else if (y > wh / 2 && x > ww / 2)
		{
			ortfront = 0;
			ortright = 1;
			orttop = 0;
			glutPostRedisplay();
		}
		else if (y < wh / 2 && x < ww / 2)
		{
			ortfront = 0;
			ortright = 0;
			orttop = 1;
			glutPostRedisplay();
		}
	}
}


//************************************
// KEYBOARD ACTIVITIES
//************************************

void keys(unsigned char key, int x, int y)
{
	if (key == 'x') viewer[0]--;  //Move to -x direction
	if (key == 'X') viewer[0]++;  //Move to +x direction
	if (key == 'y') viewer[1]--;  //Move to -y direction
	if (key == 'Y') viewer[1]++;  //Move to +y direction
	if (key == 'z') viewer[2]++;  //Move to +z direction
	if (key == 'Z') viewer[2]--;  //Move to -z direction


	if (key == '8') object[1]++;  //Set higher target point  
	if (key == '2') object[1]--;  //Set lower target point
	if (key == '4') object[0]--;  //Set target point to the left
	if (key == '6') object[0]++;  //Set target point to the right
	if (key == 'd') object[2]--;  //Set camera to closer target point
	if (key == 'D') object[2]++;  //Set camera to farther target point

	//ZOOM, Changing FOV
	if (key == 'v') fov++;  //zoom out
	if (key == 'V') fov--; //zoom in

	//Change near clipping plane
	if (key == 'n') n++;
	if (key == 'N') n--;

	//Change far clipping plane
	if (key == 'f') f++;
	if (key == 'F') f--;

	//Orthographic Front View Interactions
	if (ortfront == 1)
	{
		if (key == 'l') ort1[0]++;
		if (key == 'L') ort1[0]--;
		if (key == 'r') ort1[1]++;
		if (key == 'R') ort1[1]--;
		if (key == 'b') ort1[2]++;
		if (key == 'B') ort1[2]--;
		if (key == 't') ort1[3]++;
		if (key == 'T') ort1[3]--;
	}

	//Orthographic Right Side View Interactions
	if (ortright == 1)
	{
		if (key == 'l') ort2[0]++;
		if (key == 'L') ort2[0]--;
		if (key == 'r') ort2[1]++;
		if (key == 'R') ort2[1]--;
		if (key == 'b') ort2[2]++;
		if (key == 'B') ort2[2]--;
		if (key == 't') ort2[3]++;
		if (key == 'T') ort2[3]--;
	}


	//Orthographic Top View Interactions
	if (orttop == 1)
	{
		if (key == 'l') ort3[0]++;
		if (key == 'L') ort3[0]--;
		if (key == 'r') ort3[1]++;
		if (key == 'R') ort3[1]--;
		if (key == 'b') ort3[2]++;
		if (key == 'B') ort3[2]--;
		if (key == 't') ort3[3]++;
		if (key == 'T') ort3[3]--;
	}

	glutPostRedisplay();
}


//*********************************
// RIGHT BUTTON MENU
//*********************************

void Reset()
{
	//zNear and zFar values
	f = 520.0;
	n = 10.0;
	fov = 89.0;  // theta = arctan(top/zNear)  =arctan(400/10) =89

	viewer[0] = 525.0;   viewer[1] = 30.0;   viewer[2] = -200.0; // eye/ Camera Position
	object[0] = 600;     object[1] = 30;     object[2] = -300;  // look Position
	up[0] = 0.0;         up[1] = 1.0;        up[2] = 0.0;

	// 3 ortho views  i.e. Front veiw, Side View and Top View
	ort1[0] = -500.0;   ort1[1] = 500.0;   ort1[2] = -500.0;   ort1[3] = 500.0; //Left right bottom top
	ort2[0] = -200.0;   ort2[1] = 200.0;   ort2[2] = 0;        ort2[3] = 300.0; //Left right bottom top
	ort3[0] = -200.0;   ort3[1] = 200.0;   ort3[2] = -45.0;    ort3[3] = 200.0; //Left right bottom top

	upi = 0; ortho = 0; ortfront = 0;  ortright = 0; orttop = 0;  // Flags to set Views
}

void right_menu(int id)
{
	if (id == 2) exit(1);
	else
	{
		//SETTING EVERYTHING TO INITIAL CONDITIONS (RESET)

		Reset();

		glutPostRedisplay();
	}
}


//*********************************
// MIDDLE BUTTON MENU
//*********************************


void left_menu(int id)
{
	if (id == 1)
	{
		glutTimerFunc(1000, myTimer, 2019);  //Activate Fly-by
	}

	else if (id == 2) {  //Normal, Perspective View
		myReshape(ww, wh);
		ortho = 0;
		ortfront = 0;
		ortright = 0;
		orttop = 0;
		glutPostRedisplay();
	}

	else if (id == 3)  //Orthographic View
	{
		ortho = 1;
		glutPostRedisplay();
	}
}


//*********************************
// MAIN ROUTINE
//*********************************

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//Set display parameters : double buffer, RGB color, depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(ww, wh);
	glutCreateWindow("Basic Viewing System");
	glutInitWindowPosition(300, 300);

	myinit();

	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);

	// RIGHT BUTTON MENU
	glutCreateMenu(right_menu);
	glutAddMenuEntry("1.Reset", 1);
	glutAddMenuEntry("2.Quit Program", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//MIDDLE BUTTON MENU
	glutCreateMenu(left_menu);
	glutAddMenuEntry("1.Fly-by", 1);
	glutAddMenuEntry("2.Perspective View", 2);
	glutAddMenuEntry("3.Orthographic View", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);

	//ENABLE DEPTH TEST
	glEnable(GL_DEPTH_TEST);

	//START PROGRAM
	glutMainLoop();
}


//************************************************************************
// 				END OF PROGRAM
//************************************************************************


