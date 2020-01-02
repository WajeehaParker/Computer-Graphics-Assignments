
#include "import.h"  // simply contain list of all required header files

Camera cam;   // create object of type camera
Mesh t;       // create datastructures to hold tetrahedron Book Example 6.2.3   
float Angle;  // just for animation 

//<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// <<<<<<<<< Lab 08  3D Tetrahedron, 3D Barn , 3D cube>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//0- Successful run of mesh.cpp show you a 3D tetrahedron with each face having different material
//0- Check out key board handler for camera controls
//1- Open 3D barn Example from Book 2nd Edition Example 6.2.1 or from 3rd edition
//2- Go to main ()at the bottom of mesh.cpp and change t= Mesh( 4, 4, 4 ) with b = Mesh(10,7,7)
//3- Modify t.InitializeTetrahedron() inside mesh.h according to 3D barn data describe in book example;
//4 -  Go to displaySolid() function and check that every thing is ok there
//5 - Set initial view of camera from main() if required otherwise run the code to see your first mesh
//6 - Carefully test all functions form camera.h using keyboard and relate it to 3D rotation discussion in class
//7 - Now initialze Mesh using reading data from file in main for e.g. b = Mesh("a.txt"); 
//8 - Combine/merge Lab07 and Lab08 code to enrich your 3D scene at your best
//9 - You are encourage to put boundary checks and 3d Bounding Box just we did for 2D 


//<<<<<<<<<<<<<<<<<<<<<<<< mySpecialKeys >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeys(int key, int x, int y)
{
  switch(key)
  {	
    // controls for camera
  case GLUT_KEY_UP:  cam.pitch(30.0); break; // pitch camera down
  case GLUT_KEY_DOWN: cam.pitch(-30.0); break; // pitch camera up	
  case GLUT_KEY_RIGHT: cam.yaw(-30.0); break; // yaw camera left
  case GLUT_KEY_LEFT: cam.yaw( 30.0); break;  // yaw camera right
  case GLUT_KEY_F1: exit(0);
  }
  glutPostRedisplay(); // draw it again
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char key, int x, int y)
{
  // NOTE: CTRL-F = 'F' - 64

  switch(key)
  {	
  case 'f': cam.slide(0,0,-0.1); break; // slide camera forward
  case 'b': cam.slide(0,0,0.1);  break; // slide camera back
  case 'l': cam.slide(-0.1,0,0); break;
  case 'r': cam.slide(0.1,0,0);  break;
  case 'u': cam.slide(0,0.1,0);  break;
  case 'd': cam.slide(0,-0.1,0); break;
  case 'm': cam.roll(-1.0); break; // roll counter-clockwise
  case 'n': cam.roll(1.0); break; // roll clockwise
  case 'Q': exit(0);
  default : break;
  }
  glutPostRedisplay(); // draw it again
}

//<<<<<<<<<<<<<<<<<<< axis >>>>>>>>>>>>>>
void axis(double length)
{ // draw a z-axis, with cone at end
	glPushMatrix();
	glBegin(GL_LINES);
	   glVertex3d(0, 0, 0); glVertex3d(0,0,length); // along the z-axis
	glEnd();
	glTranslated(0, 0,length -0.2); 
	glutWireCone(0.04, 0.2, 12, 9);
	glPopMatrix();
}	

void drawaxes(double length)
{  //Draw x,y,z-axes
  glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    //glColor3d(1,1,1); // draw white lines
    axis(length);				 // x-axis
    glPushMatrix(); 
    glRotated(90, 0,1.0, 0);
    axis(length);				// y-axis
    glRotated(-90.0, 1, 0, 0);
    axis(length);				// z-axis
  glPopMatrix();	
}

// Lighting Effect
void Lighting ()
{
	float LightAmbient[] = { 0.4, 0.4, 0.8, 1.0 };
	float LightDiffuse[] = { 0.6, 0.6, 0.3, 1.0 };
	float Light_Specular[] = { 0.5, 0.5, 0.5, 1.0 };
	float Light_Position[] = { 0.0, 0.0, 0.3, 0.0 };

	float Model_Ambient[] = { 0.4, 0.4, 0.4, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	    
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Model_Ambient);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
} 

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolid(void)
{
  glEnable(GL_DEPTH_TEST);   
  cam.setShape(50.0, 64.0f/48.0f, 0.1, 100.0); // ortho vs. perspective 

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  cam.setModelViewMatrix(); // load OpenGL's modelview matrix using glLoadMatrixf

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
  
  glColor3f(0,0,1);	
  drawaxes(2.0);
  
  glPushAttrib(GL_LIGHTING);     // save context
	Lighting();                  // introduce lights in 3D scene
	glColor3f(0,1,0);	
	glRotatef(Angle+=0.5,0,1,0); // you can take it to timer
	t.drawMesh();  
  glPopAttrib();            // restore context
 
 glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("First Mesh");
  glutSpecialFunc(mySpecialKeys);
  glutKeyboardFunc(myKeyboard);
  glutDisplayFunc(displaySolid);
  glClearColor(0.10f, 0.10f, 0.10f,0.0f);  // background is light-gray
  glViewport(0,0,640,480);
  t= Mesh( 10, 7, 7 );
  //t = Mesh(const_cast<char*>("barn.txt"));
  //t.InitializeTetrahedron();
  t.InitializeCube();
  cam.set(2.3, 1.3, 2, 0, 0.25, 0, 0,1,0);
  glutMainLoop();
}

 


