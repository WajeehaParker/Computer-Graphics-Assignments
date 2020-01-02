/* 
 * File:   Turtle.h
 * Author: humera
 *
 * Created on August 8, 2011, 9:34 AM
 */
#include "glut.h"
#include <cmath>

#ifndef TURTLE_H
#define	TURTLE_H

#pragma once
class Point2
{
  public:
    Point2() { x = y = 0.0f;} // constructor 1
    Point2(float xx,float yy) { x = xx; y = yy;} // constructor 2
    void set(float xx,float yy) { x = xx; y = yy;} 
    float getX() { return x;}
    float getY() { return y;}
    void draw(void) 
    { 
		glPointSize(4.0);
		
		glEnable( GL_BLEND);
  		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  		glHint( GL_POINT_SMOOTH_HINT, GL_NICEST); 
 		glEnable( GL_POINT_SMOOTH);

		glBegin(GL_POINTS); // draw this point
			glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();

		glDisable( GL_POINT_SMOOTH);

    }// end draw
  private:
    float x, y;
}; // end class Point2

class Turtle
{
private:
    Point2 CP;
    float CD;

public:

    Turtle(Point2 p, float angle)
    {
        CP.set(p.getX(),p.getY());
        CD = angle;
    }
    void moveTo(Point2 p){ CP.set(p.getX(),p.getY());}

    void lineTo(Point2 newp)
    {
        glBegin(GL_LINES);
            glVertex2f((GLfloat)CP.getX(), (GLfloat)CP.getY());
            glVertex2f((GLfloat)newp.getX(), (GLfloat)newp.getY()); // draw the line
        glEnd();

        CP.set(newp.getX(), newp.getY()); // update the CP
    }

    void turnTo(float angle){ CD = angle;}
    void turn(float angle){ CD += angle;} //Use a negative argument to make a right turn.

    void forward(float dist, int isVisible)
    {
        const float RadPerDeg = 0.017453393; //radians per degree
        float x = CP.getX() + dist * cos(RadPerDeg * CD);
        float y = CP.getY() + dist * sin(RadPerDeg * CD);
        if(isVisible)
            lineTo(Point2(x, y));
        else
            moveTo(Point2(x, y));
            }
};

#endif	/* TURTLE_H */

