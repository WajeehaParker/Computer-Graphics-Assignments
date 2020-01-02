
#ifndef _GLRect
#define _GLRect

namespace GL
{

	struct GLRect
	{

		int left;
		int right;
		int bottom;
		int top;


		
		GLRect() : 
				   left(0),
				   right(0),
				   bottom(0),
				   top(0)
		{
		}


		
		GLRect(int left, int right, int bottom, int top) :
				   left(left),
				   right(right),
				   bottom(bottom),
				   top(top)
		{
		}



		void Set(int left, int right, int bottom, int top)
		{

			this->left = left;
			this->right = right;
			this->bottom = bottom;
			this->top = top;

		}



		void Draw(void)
		{
			
			glBegin( GL_LINE_LOOP );
				
				glVertex2i( left, bottom );
				glVertex2i( left, top );
				glVertex2i( right, top );
				glVertex2i( right, bottom );
			
			glEnd();

		}


	};

}

#endif