


#include<stdio.h>
#include<Windows.h>
#include<vector>
#include<glut.h>
#include<iostream>
#include<math.h>
#include<ctype.h>
#include<iomanip>
using namespace std;

//class Point2
//{
//public:
//	Point2();
//	~Point2();
//	Point2(float xx, float yy)
//	{
//		x = xx;
//		y = yy;
//	}
//	float getX() {
//		return x;
//	}
//	float getY() {
//		return y;
//	}
//	void set(Point2& p) {
//		x = p.x;
//		y = p.y;
//	}
//	void set(float dx, float dy)
//	{
//		x = dx;
//		y = dy;
//	}
//	void setX(float xx) { x = xx; }
//	void setY(float yy) { y = yy; }
//private:
//	float x, y;
//};



//==================================================================================
//										Point2 
//==================================================================================




class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw(void)
	{
		glPointSize(4.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);

		glBegin(GL_POINTS); // draw this point
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();

		glDisable(GL_POINT_SMOOTH);


	}// end draw


private:
	float x, y;
}; // end class Point2
static boolean dist(Point2 A, Point2 B, Point2 C) {
	float AB = sqrt(powf(A.getX() - B.getX(), 2) + powf(A.getY() - B.getY(), 2));
	float AC = sqrt(powf(A.getX() - C.getX(), 2) + powf(A.getY() - C.getY(), 2));
	float CB = sqrt(powf(C.getX() - B.getX(), 2) + powf(C.getY() - B.getY(), 2));
	return(AB == (AC + CB));
}
static boolean inLine(Point2 A, Point2 B, Point2 C);
//==================================================================================
//										IntRect 
//==================================================================================

class IntRect
{
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructors
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	} // constructors
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	int getl() { return l; }
	int getr() { return r; }
	int getb() { return b; }
	int gett() { return t; }
	void draw(void); // draw this rectangle using OpenGL
private:
	int l, r, b, t;
}; //end class IntRect:

void IntRect::draw(void)
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(l, b);
	glVertex2i(r, b);
	glVertex2i(r, t);
	glVertex2i(l, t);
	glEnd();
}// end IntRect::draw

 //==================================================================================
 //											RealRect
 //==================================================================================


class RealRect
{
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructors
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	} // constructors
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	float getl() { return l; }
	float getr() { return r; }
	float getb() { return b; }
	float gett() { return t; }
	void draw(void); // draw this rectangle using OpenGL
private:
	float l, r, b, t;
}; //end class RealRect:
void RealRect::draw(void)
{
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(l, b);
	glVertex2f(r, b);
	glVertex2f(r, t);
	glVertex2f(l, t);
	glEnd();

	glLineWidth(1.0);
}// end RealRect


 //==================================================================================
 //											Vector2
 //==================================================================================



class vector2
{
public:
	vector2() { dx = 0.0; dy = 0.0; }//  constructors
	vector2(float x, float y)
	{
		dx = x;
		dy = y;
	}

	void setX(float x) { dx = x; }
	void setY(float y) { dy = y; }
	void set(float x, float y)
	{
		dx = x;
		dy = y;

	}
	//void draw(void); // draw this vector
	float length(void);
	float deltaX(void);	// return sides
	float deltaY(void);
	void setDiff(Point2& a, Point2& b) { dx = b.getX() - a.getX(); dy = b.getY() - a.getY(); }


private:
	float dx;
	float dy;
};

float vector2::length(void)
{
	return sqrt(dx * dx + dy * dy);
}

float vector2::deltaX(void)    // return components
{
	return dx;
}

float vector2::deltaY(void)
{
	return dy;
}


const vector2 i2(1.0, 0.0);
const vector2 j2(0.0, 1.0);



void putVector(vector2 u);
float cosAngleBetween(vector2 u, vector2 v);  //return cosine of angle between vectors
float angleBetween(vector2 u, vector2 v);  //return angle between vectors
float inner(vector2 u, vector2 v);
float operator* (vector2 u, vector2 v);   // inner product
float directionOf(vector2 v);  // angle in which vector points(radians)
Point2 operator+ (Point2 u, vector2 v); //  overloaded +
vector2 normalize(vector2 u);      //  scale to unit length; if zero, stays zero
vector2 perp(vector2 u);
vector2 operator* (float s, vector2 u);  // scalar product
vector2 operator+ (vector2 u, vector2 v); //  overloaded +
vector2 operator- (vector2 u, vector2 v);  //  overloaded -
vector2 operator- (Point2 q, Point2 p);   // vector from p to q
vector2 operator- (vector2 v);   // unary vector minus
vector2 project(vector2 u, vector2 v);  // projection of u onto v
vector2 reflect(vector2 a, vector2 m);  // reflection of a in m




void putVector(vector2 u)
{
	printf("< %f, %f >", u.deltaX(), u.deltaY());
}

float operator* (vector2 u, vector2 v)
{
	return inner(u, v);
}

float inner(vector2 u, vector2 v)
{
	return u.deltaX() * v.deltaX() + u.deltaY() * v.deltaY();
}

float cosAngleBetween(vector2 u, vector2 v)  //return cosine of angle between vectors
{
	return normalize(u) * normalize(v);
}

float angleBetween(vector2 u, vector2 v)  //return angle between vectors
{
	return acos(cosAngleBetween(u, v));
}

float directionOf(vector2 v)  // angle in which vector points(radians)
{
	float pi = 3.141592;

	vector2 nv;
	float angle;
	if (v.length() == 0)
		return 0.0;
	else
	{
		nv = normalize(v);
		angle = acos(nv.deltaY());
		if (nv.deltaY() < 0.0)
			return 2 * pi - angle;
		else
			return angle;
	}
}


float radian2degree(float rad)   // radian to degree  conversion
{
	float pi = 3.141592;
	float degreesPerRadian = 180 / pi;
	return rad * degreesPerRadian;
}

Point2 operator+ (Point2 u, vector2 v)  //  overloaded +
{
	float x; float y;
	x = u.getX() + v.deltaX();
	y = u.getY() + v.deltaY();
	Point2 p(x, y);
	return p;
}

vector2 operator* (float s, vector2 u)  // scalar product
{
	vector2 temp(s * u.deltaX(), s* u.deltaY());
	return temp;
}


vector2 normalize(vector2 u)  //  scale to unit length; if zero, stays zero
{

	float len;
	len = u.length();
	//		printf("U.length:%f \n",len);

	if (len = 0.0)
	{
		vector2 temp(0.0, 0.0);
		return temp;
	}
	else
	{
		len = u.length();
		//		printf("u.length:%f \n",len);

		//		vector2 temp(u.deltaX()/len, u.deltaY()/len);
		return (1.0 / len) * u;
	}
}

vector2 operator+ (vector2 u, vector2 v)  //  overloaded +
{
	float x; float y;
	vector2 temp;
	x = u.deltaX() + v.deltaX();
	y = u.deltaY() + v.deltaY();
	temp = vector2(x, y);
	return temp;
}



vector2 operator- (vector2 u, vector2 v)  //  overloaded -
{
	float x; float y;
	vector2 temp;
	x = u.deltaX() - v.deltaX();
	y = u.deltaY() - v.deltaY();
	temp = vector2(x, y);
	return temp;
}



vector2 perp(vector2 u)
{
	vector2 temp;
	temp.set(-u.deltaY(), u.deltaX());
	return temp;
}

vector2 project(vector2 u, vector2 v)  // projection of u onto v
{	// v must be nonzero
	return ((v * u) / (v * v))* v;
}

vector2 operator- (Point2 q, Point2 p)   // vector from p to q
{
	vector2 temp;
	temp.set(q.getX() - p.getX(), q.getY() - p.getY());
	return temp;
}

vector2 operator- (vector2 v)   // unary vector minus
{
	vector2 temp;
	temp.set(-v.deltaX(), -v.deltaY());
	return temp;
}

vector2 reflect(vector2 a, vector2 m)  // reflection of a in m
{
	vector2 nm;
	nm = normalize(m);
	return -1 * (a - (2 * (a * nm))* nm);
}


//==================================================================================
//										Ray2
//==================================================================================

class ray2
{
public:

	ray2();
	ray2(Point2 p, vector2 v);
	void set(Point2 p, vector2 v);
	Point2 base(void);
	vector2 direction(void);
	void setBase(Point2 p);
	ray2 calReflectedPath();



private:
	Point2 point;
	vector2 dir;
};

// Constructors

ray2::ray2()
{
	Point2 p;
	vector2 v;
	point = p;
	dir = v;
}
ray2::ray2(Point2 p, vector2 v)
{
	point = p;
	dir = v;
}


// getters
Point2 ray2::base(void)
{
	return point;
}// return components

vector2 ray2::direction(void)
{
	return dir;
}

//setters

void ray2::set(Point2 p, vector2 v)
{
	point = p;
	dir = v;
}


void ray2::setBase(Point2 p)
{
	point.set(p.getX(), p.getY());

}

// logic part
ray2 ray2::calReflectedPath()
{
	// See Lecture Discussion and Implement
	// Book Section NO:  

	ray2 r;


	return r;
}


vector2 normalForm(Point2 p1, Point2 p2);
vector2 PointDiff(Point2 p1, Point2 p2);
float tHit(ray2 A, int side);
//==================================================================================
//										BALL
//==================================================================================


class Ball
{
public:

	Ball();
	Ball(float, float, ray2);
	void setMovingPath(Point2, vector2);
	void drawBall(void);
	void moveBall(void);
	ray2 getMovingPath() { return movingPath; }
	Point2 getBase() { ray2 r = this->getMovingPath();  return r.base(); }
	vector2 getDir() { ray2 r = this->getMovingPath();  return r.direction(); }


private:
	float radius;
	float weight;
	ray2  movingPath;

};

Ball::Ball()
{
	radius = 0.5;
	weight = 20;
	movingPath.set(Point2(2, 0), vector2(-4, 0));
}

Ball::Ball(float r, float w, ray2 path)
{
	radius = r;
	weight = w;
	movingPath = path;

}

void Ball::setMovingPath(Point2 p, vector2 v)
{
	movingPath.set(p, v);


}

void Ball::drawBall()
{
	Point2 position = movingPath.base();

	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), 0);
	glutSolidSphere(this->radius, 40, 40);
	glPopMatrix();
}

float gettime()
{
	static __int64 i64Frequency = 0;
	static __int64 i64BeginCount = 0;
	if (i64Frequency == 0) {	// do this only for the first time
		QueryPerformanceFrequency((LARGE_INTEGER*)&i64Frequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&i64BeginCount); //retrieve the number of
																 //ticks since system start (64bit int).

	}
	__int64 i64CurrentCount;
	QueryPerformanceCounter((LARGE_INTEGER*)&i64CurrentCount);
	return  (float)(i64CurrentCount - i64BeginCount) / i64Frequency;
}



void Ball::moveBall()
{
	static float prevtime = 0.0f;		// previous frame’s time
	float currtime = gettime();		// current frame’s time
	float elapsedtime = currtime - prevtime;	// elapsed time	


	Point2 newPosition = movingPath.base() + (elapsedtime*movingPath.direction());
	movingPath.setBase(newPosition);
	//printf("%f\t       %f\n",newPosition.getX(),newPosition.getY());
	//printf("elapsed time is %f\n",elapsedtime);

	prevtime = currtime;

}




//==================================================================================
//==================================================================================										
//==================================================================================




ray2 r(Point2(15, 5), vector2(1, 1));        //vector gives speed
Ball b(0.3, 20, r);
vector<Point2> vertexlist = { {20,2},{16,10},{10,10},{5,5} };


void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.9f, 0.9f, 0.9f, 0.0);
	glColor3f(1, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 30, 0, 30);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex2d(vertexlist.at(i).getX(), vertexlist.at(i).getY());
	}
	glEnd();


	b.drawBall();
	b.moveBall();

	glColor3f(0, 1, 0);

	glutSwapBuffers();
}

void Timer(int iUnused)
{


	glutPostRedisplay();//display call again
	glutTimerFunc(100, Timer, 0);// register timer again

}


struct Line {
	int lineNo;
	float TIn;
	float TOut;
};


struct Clipping
{
	Point2 A_prime,
		B_prime;
};


vector<Line> lineRecord;
vector<Clipping> clipping;
float TIn = 0;
float TOut = 1;



float tHit(ray2 A, int side) {


	Point2 P1 = vertexlist.at(side);
	Point2 P2 = vertexlist.at((side + 1 == vertexlist.size()) ? 0 : side + 1);
	vector2 nBar = normalForm(P1, P2);
	vector2 BdiffA = PointDiff(A.base(), P1);
	vector2 cBar = PointDiff(A.base(), Point2(A.direction().deltaX(), A.direction().deltaY()));

	float nominator = (nBar.deltaX()*BdiffA.deltaX() + nBar.deltaY()*BdiffA.deltaY());
	float Denominator = (nBar.deltaX()*cBar.deltaX() + nBar.deltaY()*cBar.deltaY());
	float tHit = nominator / Denominator;

	if (Denominator > 0)
	{
		TOut = min(TOut, tHit);

	}
	else {
		TIn = max(TIn, tHit);
	}




	Point2 B_prime(A.base().getX() + cBar.deltaX()*TOut, A.base().getY() + cBar.deltaY()*TOut);
	Point2 A_Prime(A.base().getX() + cBar.deltaX()*TIn, A.base().getY() + cBar.deltaY()*TIn);
	clipping.push_back({ A_Prime, B_prime });



	lineRecord.push_back(Line{ side,TIn,TOut });
	cout << std::setprecision(10) << side << "\t\t" << TIn << "\t\t" << TOut << "\n";
	return tHit;
}
vector2 PointDiff(Point2 p1, Point2 p2)
{
	return vector2(p2.getX() - p1.getX(), p2.getY() - p1.getY());
}
vector2 normalForm(Point2 p1, Point2 p2)
{
	vector2 temp(p2.getY() - p1.getY(), -(p2.getX() - p1.getX()));
	return temp;
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(30, 30);
	glutCreateWindow("First Window");

	glutDisplayFunc(myDisplay);
	cout << "L\t\tTin\t\tTout\n";
	for (int i = 0; i < vertexlist.size(); i++)
	{
		tHit(b.getMovingPath(), i);
	}
	cout << "===============================================================\n";
	cout << "A_prime\t\t\t\tB_prime\n";

	for (unsigned i = 0; i < clipping.size(); i++)
	{
		cout << "(" << clipping.at(i).A_prime.getX() << ", " << clipping.at(i).A_prime.getY() << ")\t\t\t\t";
		cout << "(" << clipping.at(i).B_prime.getX() << ", " << clipping.at(i).B_prime.getY() << ")\n";
	}
	Timer(0);
	glutMainLoop();
	return 0;
}

