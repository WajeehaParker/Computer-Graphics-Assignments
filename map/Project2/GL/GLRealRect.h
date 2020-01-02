
#ifndef _GLRealRect
#define _GLRealRect

namespace GL
{

	struct GLRealRect
	{

		float left;
		float right;
		float bottom;
		float top;


		
		GLRealRect() : 
				   left(0),
				   right(0),
				   bottom(0),
				   top(0)
		{
		}


		
		GLRealRect(float left, float right, float bottom, float top) :
				   left(left),
				   right(right),
				   bottom(bottom),
				   top(top)
		{
		}



		void Set(float left, float right, float bottom, float top)
		{

			this->left = left;
			this->right = right;
			this->bottom = bottom;
			this->top = top;

		}
		
		
		
		void Draw(void)
		{
			
			glBegin( GL_LINE_LOOP );
				
				glVertex2f( left, bottom );
				glVertex2f( left, top );
				glVertex2f( right, top );
				glVertex2f( right, bottom );
			
			glEnd();
			//glutSwapBuffers();

		}


	};

}

#endif