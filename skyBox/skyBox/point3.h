#include "glut.h"

class Point3
{
public:
	 Point3() {x = y = z = 0.0f;}		//constructor 1
	 Point3(float xx, float yy, float zz)  //constructor 2
	{
		x = xx; 
		y = yy;
		z = zz;
	}	
	void set (float xx, float yy, float zz)  
	{
		x = xx; 
		y = yy;
		z = zz;
	}
		void set (Point3 p)  
	{
		x = p.getX(); 
		y = p.getY();
		z = p.getZ();
	}
	float getX()  {return x;}
	float getY()  {return y;}
	float getZ()  {return z;}

	 void setX(float xx)  { x=xx;}
	 void setY(float yy)  { y=yy;}
	 void setZ(float zz)  {  z=zz;}

	void draw(void)  
	{
		glBegin(GL_POINTS);  //draw this point
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}

  //private:
	float x,y,z;
};