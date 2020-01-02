#pragma once
#include <glut.h>
#include "RGBApixMap.h"

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
		glPointSize(2.0);

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

class Mario
{
public:

	RGBApixmap pix1, pix2, pix3;
	float pos_X, pos_Y;

	Mario()
	{
		pix1.readBMPFile("img1.bmp");
		pix2.readBMPFile("img2.bmp");
		this->pos_X = 0.0;
		this->pos_Y = 0.0;
	};

	void setPosition(float x, float y)
	{
		this->pos_X = x;
		this->pos_Y = y;
	}
	void render(int x, int y);
	void merge(float t);
};

void Mario::render(int x, int y)
{
	glRasterPos2i(x, y);
	pix3.mDraw();
}

void Mario::merge(float t)
{
	pix3.nCols = pix1.nCols;
	pix3.nRows = pix1.nRows;
	pix3.pixel = new mRGBA[pix3.nRows * pix3.nCols];
	for (long i = 0; i < pix3.nCols*pix3.nRows; i++)
	{
		pix3.pixel[i].r = ((1 - t)*pix1.pixel[i].r) + (pix2.pixel[i].r * t);
		pix3.pixel[i].g = ((1 - t)*pix1.pixel[i].g) + (pix2.pixel[i].g * t);
		pix3.pixel[i].b = ((1 - t)*pix1.pixel[i].b) + (pix2.pixel[i].b * t);
		pix3.pixel[i].a = ((1 - t)*pix1.pixel[i].a) + (pix2.pixel[i].a * t);
	}
}