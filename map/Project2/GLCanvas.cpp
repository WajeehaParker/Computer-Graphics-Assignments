#include "GL/GLCanvas.h"
#include "Turtle.h"

using namespace GL;

// constructor
GLCanvas::GLCanvas(int width, int height, char* windowTitle)
{
	
	// Command Line Arguments to run from cmd
	char* argv[1];
	char dummyString[8];
	argv[0] = dummyString;
	int argc = 1;
	
	
	glutInit( &argc, argv );  // library initialization
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );// GPU Settings
	glutInitWindowSize( width, height ); // 640 x 480 Resolution in pixels
	glutInitWindowPosition(300, 100 );  // Set position w.r.t TopLeft of Monitor
	glutCreateWindow( windowTitle );    //Set Title

	SetWindow( 0, (float)width, 0, (float)height ); // set origin or 2D camera
	SetViewport( 0, width, 0, height );             // Set View/Click
	cpCP.Set( 0.0f, 0.0f );     // default position of pen

	SetBackgroundColor(107.0f / 255.0f, 134.0f / 255.0f, 1.0f); // bg color
	SetForeColor(1.0, 1.0, 1.0);  // fg color

	

	}






// move to
void GLCanvas::MoveTo(float x, float y)
{
	cpCP.Set( x, y );
}




// move to
void GLCanvas::MoveTo(GLPoint pt)
{
	cpCP.Set( pt.x, pt.y );
}




// line to
void GLCanvas::LineTo(float x, float y)
{

	glBegin( GL_LINES );

		glVertex2f( (GLfloat) cpCP.x, (GLfloat) cpCP.y );
		glVertex2f( (GLfloat) x, (GLfloat) y);

	glEnd();

	cpCP.Set( x, y );
	glFlush();

}




// line to
void GLCanvas::LineTo(GLPoint pt)
{

	glBegin( GL_LINES );

		glVertex2f( (GLfloat) cpCP.x, (GLfloat) cpCP.y );
		glVertex2f( (GLfloat) pt.x, (GLfloat) pt.y);

	glEnd();

	cpCP.Set( pt.x, pt.y );
	glFlush();

}

//void GLCanvas::LineTo(GLPoint pt) {
//	printf("\n%f %f", pt.x, pt.y);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//	glEnable(GL_LINE_SMOOTH);
//	glBegin(GL_LINES);
//	glVertex2f((GLfloat)cpCP.x, (GLfloat)cpCP.y);
//	glVertex2f( (GLfloat) pt.x, (GLfloat) pt.y);
//	glEnd();
//	glDisable(GL_LINE_SMOOTH);
//	glFlush();
//}





// move reletive to
void GLCanvas::MoveRel(float dx, float dy)
{
	cpCP.Set( cpCP.x + dx, cpCP.y + dy );
}




// move reletive to
void GLCanvas::MoveRel(GLPoint dPt)
{
	cpCP.Set( cpCP.x + dPt.x, cpCP.y + dPt.y );
}




// line reletive to
void GLCanvas::LineRel(float dx, float dy)
{

	float x = cpCP.x + dx;
	float y = cpCP.y + dy;

	LineTo( x, y );
	cpCP.Set( x, y );

}




// line reletive to
void GLCanvas::LineRel(GLPoint dPt)
{

	float x = cpCP.x + dPt.x;
	float y = cpCP.y + dPt.y;

	LineTo( x, y );
	cpCP.Set( x, y );

}




// set world window
void GLCanvas::SetWindow(float left, float right, float bottom, float top)
{

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	gluOrtho2D( (GLdouble) left,
				(GLdouble) right,
				(GLdouble) bottom,
				(GLdouble) top );

	wwWindow.Set( left, right, bottom, top );

	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

}




// set viewport
void GLCanvas::SetViewport(int left, int right, int bottom, int top)
{

	glViewport( left,
				bottom,
				right - left,
				top - bottom );

}




// clear screen
void GLCanvas::ClearScreen(void)
{
	
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

}




// set background color
 void GLCanvas::SetBackgroundColor(float red, float green, float blue)
{
	
	glClearColor( red,
				  green,
				  blue,
				  1.0 );

}




// set fore color
void GLCanvas::SetForeColor(float red, float green, float blue)
{

	glColor3f( red, green, blue );

}

//void GLCanvas::renderScene(void(*fun_ptr)())
//{
//
//
//}

//void GLCanvas::renderScene(*())
//{
//	
//	
//	glutDisplayFunc(fun_ptr);
//	glutMainLoop();
//	
//}









