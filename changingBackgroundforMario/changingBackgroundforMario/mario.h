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

	RGBApixmap pix1, pix2;
	float pos_X, pos_Y;

	Mario()

	{
		pix1.readBMPFile("MarioStanding.bmp");
		this->pos_X = 0.0;
		this->pos_Y = 0.0;
	};

	void setPosition(float x, float y)
	{
		this->pos_X = x;
		this->pos_Y = y;
	}
	void render();
	void changeBGcolor(mRGBA color);
};

void Mario::render()
{
	glRasterPos2i(this->pos_X, this->pos_Y);
	pix1.mDraw();
}

void Mario::changeBGcolor(mRGBA color)
{
	pix2.nRows = pix1.nRows;
	pix2.nCols = pix1.nCols;
	pix2.pixel = new mRGBA[pix2.nRows * pix2.nCols];
	
	for (long i = 0; i < pix1.nRows*pix1.nCols; i++)
	{
		if (pix1.pixel[i].r == 192 && pix1.pixel[i].g == 192 && pix1.pixel[i].b == 192 && pix1.pixel[i].a == 255)
		{
			pix2.pixel[i].r = color.r;
			pix2.pixel[i].g = color.g;
			pix2.pixel[i].b = color.b;
			pix2.pixel[i].a = color.a;
		}
		else 
			pix2.pixel[i] = pix1.pixel[i];
	}
	glRasterPos2i(30, 0);
	pix2.mDraw();
}