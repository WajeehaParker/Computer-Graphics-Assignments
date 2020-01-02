#include "globals.h"
#include "Turtle.h"
#include "glut.h"
#include <vector>
#include "RGBApixMap.h"
#include "mario.h"
using namespace GL;
using namespace std;

Mario m(Point2(0, 0));

// fun_ptr is a pointer to function fun(). It is used to create wrapper on glutDisplayFunc()
void display(void);
void(*fun_ptr)() = &display;
int main(int argc, char** argv)
{
	cvs.ClearScreen();
	cvs.renderScene(fun_ptr);
	glutMainLoop();
	return 0;
}


void display(void)
{
	m.render();
	GLPoint A;
	A.Set(50, 100);
	A.Draw();

	//For a single line
	cvs.MoveTo(A);
	cvs.LineTo(70, 130);
	
	vector<GLPoint> myVertexList;
	myVertexList.push_back(A);
	cvs.SetForeColor(1, 0, 0);
	GLPoint B = myVertexList.at(0);
	B.Draw();
	

	Point startPosition(50, 100);
	Turtle ninja(startPosition, 45);
	ninja.forward(20, 1.0);
	ninja.turn(-90);
	
	cvs.MoveTo(B);
	cvs.LineTo(65,116);

	vector<GLPoint> myVertexList1;
	myVertexList.push_back(B);
	GLPoint C = myVertexList.at(1);
	C.Draw();
	 
	Point startPosition1(65, 116);
	Turtle ninja1(startPosition1, 305);
	ninja1.forward(20 ,1.0);

	ninja1.turn(104);
	ninja1.forward(30, 1.0);
	ninja1.turn(-105);
	ninja1.forward(13, 1.0);
	ninja1.turn(105);
	ninja1.forward(53, 1.0);
	ninja1.turn(-105);
	ninja1.forward(168, 1.0);
	ninja1.turn(106);
	ninja1.forward(410, 1.0);
	ninja1.turn(-103);
	ninja1.forward(193, 1.0);
	ninja1.turn(103);
	ninja1.forward(262, 1.0);
	ninja1.turn(-106);
	ninja1.forward(123, 1.0);
	ninja1.turn(107);
	ninja1.forward(78, 1.0);
	ninja1.turn(-118);
	ninja1.forward(103, 1.0);

	cvs.showOnStage();

	glFlush();
}