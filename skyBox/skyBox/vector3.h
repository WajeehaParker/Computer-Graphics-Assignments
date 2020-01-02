#include "point3.h"
#include <stdio.h>
#include "math.h"

class Vector3
{
public:
	 Vector3() {dx = 0.0; dy = 0.0; dz = 0.0;}//  constructors
	Vector3(float x, float y, float z)
	{
		dx = x;
		dy = y;
		dz = z;
	}
	void set (float x, float y, float z)
	{
		dx = x;
		dy = y;
		dz = z;
	
	}
	void set (Point3 p)
	{
		dx = p.getX();
		dy = p.getY();
		dz = p.getZ();
		}
	
	float length(void);
	float get_dx(void);	// return sides
	float get_dy(void);
	float get_dz(void);

	
	void putVector(Vector3 u); // print vector
	void  line (Point3 p, Point3 q);
	void  draw (Vector3 v, Point3 p);//draw a vector anchored at a point.
	
//    //point + vector = point
////    Point3 operator+ (Point3 u, Vector3 v);   //  overloaded +
//	
//    // vector = point_2 - point_1
//	Vector3 operator- (Point3 q, Point3 p);   // vector from p to q
//	Vector3 operator- (Vector3 u);			  //  overloaded  unary -
//	
//	Vector3 operator+ (Vector3 u, Vector3 v); //  overloaded +
//	Vector3 operator- (Vector3 u, Vector3 v);  //  overloaded -
//	Vector3 operator* (float s, Vector3 u);  // scalar product
	
	//float inner(Vector3 u, Vector3 v);
//	float operator* (Vector3 u, Vector3 v);   // inner product
	Vector3 cross (Vector3 u, Vector3 v);   // vector product -- 3D only

	Vector3 normalize (Vector3 u);      //  scale to unit length; if zero, stays zero

	float cosAngleBetween(Vector3 u, Vector3 v);  //return cosine of angle between vectors
	float angleBetween(Vector3 u, Vector3 v);  //return angle between vectors

	Vector3 project(Vector3 u, Vector3 v);  // projection of u onto v
    Vector3 reflect(Vector3 a, Vector3 m);  // reflection of a in m
	float directionOf(Vector3 v);  // angle in which vector points(radians) // not in 3D

	/*void set(float dx, float dy, float dz)
	{
		dx = dx; dy = dy; dz = dz;
	}*/
	void set(const Vector3& v)
	{
		dx = v.dx; dy = v.dy; dz = v.dz;
	}
	void flip()
	{
		dx = -dx; dy = -dy; dz = -dz;
	} // reverse this vector
	void setDiff(Point3& a, Point3& b)//set to difference a - b
	{
		dx = a.x - b.x; dy = a.y - b.y; dz = a.z - b.z;
	}
	void normalize()//adjust this vector to unit length
	{
		double sizeSq = dx * dx + dy * dy + dz * dz;
		if (sizeSq < 0.0000001)
		{
			cerr << "\nnormalize() sees vector (0,0,0)!";
			return; // does nothing to zero vectors;
		}
		float scaleFactor = 1.0 / (float)sqrt(sizeSq);
		dx *= scaleFactor; dy *= scaleFactor; dz *= scaleFactor;
	}

	/*Vector3(float xx, float yy, float zz)
	{
		dx = xx; dy = yy; dz = zz;
	}*/
	Vector3(const Vector3& v)
	{
		dx = v.dx; dy = v.dy; dz = v.dz;
	}
	/*Vector3()
	{
		dx = dy = dz = 0;
	} *///default constructor
	Vector3 cross(Vector3 b) //return this cross b
	{
		Vector3 c(dy*b.dz - dz * b.dy, dz*b.dx - dx * b.dz, dx*b.dy - dy * b.dx);
		return c;
	}
	float dot(Vector3 b) // return this dotted with b-
	{
		return dx * b.dx + dy * b.dy + dz * b.dz;
	}
	Vector3 operator*(float scalar) // multiply vector by scalar
	{
		Vector3 c (scalar*dx, scalar*dy, scalar*dz);
		return c;
	}
	//Vector3 friend operator*(float scalar, Vector3 v) // multiply vector by scalar
	//{
	//	Vector3 c(scalar*v.x, scalar*v.y, scalar*v.z);
	//	return c;
	//}
	/*Vector3 operator+(const Vector3& v)
	{
		Vector3 c(dx + v.dx, dy + v.dy, dz + v.dz);
		return c;
	}
	Vector3 operator-(const Vector3& v)
	{
		Vector3 c(dx - v.dx, dy - v.dy, dz - v.dz);
		return c;
	}*/
//private:
	float dx;
	float dy;
	float dz;
};


float Vector3:: length(void)
{
	return sqrt(dx * dx + dy * dy + dz * dz);
}

float Vector3::  get_dx(void)    // return x component
{
	return dx;
}

float Vector3::  get_dy(void)  // return y component
{
	return dy;
}

float Vector3::  get_dz(void)  // return z component
{
	return dz;
}

void Vector3::putVector(Vector3 u)
{
	printf("< %f, %f, %f >\n", u.get_dx(), u.get_dy(), u.get_dz());
}

void Vector3:: line (Point3 p, Point3 q)
	{
		glBegin(GL_LINE_STRIP);
			glVertex3f((GLfloat)p.getX(), (GLfloat)p.getY(),(GLfloat)p.getZ());
			glVertex3f((GLfloat)q.getX(), (GLfloat)q.getY(),(GLfloat)p.getZ());
		glEnd();
		glFlush();
	}


void Vector3::  draw (Vector3 v, Point3 p)	//draw a vector anchored at a point.
{
	glLineWidth(8.0);
	Point3 q(p.getX() + v.get_dx(), p.getY() + v.get_dy(),p.getZ() + v.get_dz() );
	line(p,  q);
	
	glColor3f(0,0,0);
	glPointSize(8.0);
	glBegin(GL_POINTS);
	glVertex3f(q.getX(),q.getY(),q.getZ());
	glEnd();
	
}

    //point + vector = point
    Point3 operator+ (Point3 u, Vector3 v);   //  overloaded +
	// vector = point_2 - point_1
	Vector3 operator- (Point3 q, Point3 p);   // vector from p to q
	Vector3 operator- (Vector3 u);			  //  overloaded  unary -
	
	Vector3 operator+ (Vector3 u, Vector3 v); //  overloaded +
	Vector3 operator- (Vector3 u, Vector3 v);  //  overloaded -
	Vector3 operator* (float s, Vector3 u);  // scalar product
	float inner(Vector3 u, Vector3 v);
	float operator* (Vector3 u, Vector3 v);   // inner product or dotproduct
	
//point + vector = point
Point3 operator+ (Point3 u, Vector3 v)   //  overloaded +
{
	float x; float y; float z;
	Point3 temp;
	x = u.getX() + v.get_dx();
	y = u.getY() + v.get_dy();
	z = u.getZ() + v.get_dz();
	temp = Point3(x,y,z);
	return temp;
}
// vector = point_2 - point_1
Vector3 operator- (Point3 q, Point3 p)   // vector from p to q
{
	Vector3 temp;
	temp.set(q.getX() - p.getX(), q.getY() - p.getY(), q.getZ() - p.getZ());
	return temp;
}

Vector3 operator- (Vector3 v) //  overloaded  unary -
{
	float x; float y; float z;
	Vector3 temp;
	x =  - v.get_dx();
	y =  - v.get_dy();
	z =  - v.get_dz();
	temp = Vector3(x,y,z);
	return temp;
}


Vector3 operator+ (Vector3 u, Vector3 v)  //  overloaded +
{
	float x; float y; float z;
	Vector3 temp;
	x = u.get_dx() + v.get_dx();
	y = u.get_dy() + v.get_dy();
	z = u.get_dz() + v.get_dz();
	temp = Vector3(x,y,z);
	return temp;
}


Vector3 operator- (Vector3 u, Vector3 v)  //  overloaded -
{
	float x; float y; float z;
	Vector3 temp;
	x = u.get_dx() - v.get_dx();
	y = u.get_dy() - v.get_dy();
	z = u.get_dz() - v.get_dz();
	temp = Vector3(x,y,z);
	return temp;
}


Vector3 operator* (float s, Vector3 u)  // scalar product
{   
	Vector3 temp (s * u.get_dx(), s* u.get_dy(), s* u.get_dz());
	return temp;
}

float inner(Vector3 u , Vector3 v) // dot Product
{
	return u.get_dx() * v.get_dx() + u.get_dy() * v.get_dy() + u.get_dz() * v.get_dz();
}

float operator* (Vector3 u, Vector3 v) // dotProduct
{
	return inner(u,v);
}


Vector3 Vector3::cross (Vector3 u, Vector3 v)    // vector product -- 3D only
{
	Vector3 temp;
	temp.set(u.get_dy() * v.get_dz() - u.get_dz() * v.get_dy(),
		     u.get_dz() * v.get_dx() - u.get_dx() * v.get_dz(),
		     u.get_dx() * v.get_dy() - u.get_dy() * v.get_dx());
	return temp;
}


Vector3 Vector3::normalize (Vector3 u)  //  scale to unit length; if zero, stays zero
{
	
	float len ;
	len = u.length();
//		printf("U.length:%f \n",len);

	if (len = 0.0)
	{
		Vector3 temp(0.0, 0.0, 0.0);
		return temp;
	}
	else
	{
	len = u.length();
//		printf("u.length:%f \n",len);

//		Vector3 temp(u.get_dx()/len, u.get_dy()/len);
		return (1.0 / len) * u;
	}
}

float Vector3::cosAngleBetween(Vector3 u, Vector3 v)  //return cosine of angle between vectors
{
	return normalize(u) * normalize(v);
}

float Vector3::angleBetween(Vector3 u, Vector3 v)  //return angle between vectors
{
	return acos ( cosAngleBetween(u, v));
}


  //Vector3 perp(Vector3 u )  // not defined for 3-vectors

Vector3 Vector3::project(Vector3 u, Vector3 v)  // projection of u onto v
{	// v must be nonzero
	return ((v * u)/(v * v))* v;
}

Vector3 Vector3::reflect(Vector3 a, Vector3 m)  // reflection of a in m
{
	Vector3 nm;
	nm = normalize (m);
	return a - (2*(a * nm))* nm;
}

