

#include <iostream>
using namespace std;

#include <glut.h>
//#include <gl/gl.h>


#ifndef _GLPoint
#define _GLPoint

namespace GL
{

	class GLPoint
	{

	public:

		float x, y;



		GLPoint() : x(0), y(0)
		{}



		GLPoint(float x, float y) : x(x), y(y)
		{}



		void Set(float x, float y)
		{

			this->x = x;
			this->y = y;

		}



		void Draw(void)
		{
			
			glPointSize(4.0);

			glBegin( GL_POINTS );
				
				glVertex2f( x, y );
			
			glEnd();
			//glutSwapBuffers();

		}

	};

}

#endif