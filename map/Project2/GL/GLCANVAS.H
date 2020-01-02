
#include <string>


#include "GLPoint.h"
#include "GLRect.h"
#include "GLRealRect.h"


#ifndef _GLCanvas
#define _GLCanvas


namespace GL
{

	class GLCanvas
	{

	protected:

		GLPoint cpCP;	// current position in the world
		GLRect vpViewport;				// the current viewport
		GLRealRect wwWindow;			// the current window
		GLfloat CD;
										

	public:
		
		
		GLCanvas(int width, int height, char* windowTitle);

		void renderScene(void(*f_ptr)())
		{
			glutDisplayFunc(f_ptr);
			glutMainLoop();
		}

		void showOnStage()
		{
			glutSwapBuffers();
		}
		

		void SetWindow(float left, float right, float bottom, float top);
		void SetViewport(int left, int right, int bottom, int top);

		float GetWindowAspectRatio(void);

		void ClearScreen(void);

		void SetBackgroundColor(float red, float green, float blue);
		void SetForeColor(float red, float green, float blue);

		void turnTo(float angle);

		void turn(float angle);

		void LineTo(float x, float y);
		void LineTo(GLPoint pt);

		void forward(float dist, int isVisible);

		void MoveTo(float x, float y);
		void MoveTo(GLPoint newCP);

		void MoveRel(float dx, float dy);
		void MoveRel(GLPoint dPt);

		void LineRel(float dx, float dy);
		void LineRel(GLPoint dPt);

		
		GLRect GetViewPort(void) const
		{
			return vpViewport;
		}


		GLRealRect GetWindow(void) const
		{
			return wwWindow;
		}

		
		
		

		
		

	};


}

#endif