/***********************************************************************
 * Source File:
 *    Fragment : Pieces that fly off a dead bird
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Pieces that fly off a dead bird
 ************************************************************************/

#include "effect.h"
#include <cassert>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32

/******************************************************************
 * RANDOM
 * This function generates a random number.
 ****************************************************************/
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}



/***************************************************************/
/***************************************************************/
/*                       CONSTRUCTORS                          */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * FRAGMENT constructor
 *************************************************************************/
Fragment::Fragment(const Position & pt, const Velocity & v) : Effect(pt)
{
   // the velocity is a random kick plus the velocity of the thing that died
   this->v.setDx(v.getDx() * 0.5 + random(-6.0, 6.0));
   this->v.setDy(v.getDy() * 0.5 + random(-6.0, 6.0));
   
    // age
    age = random(0.4, 1.0);
    
    // size
    size = random(1.0, 2.5);
}

/************************************************************************
 * STREEK constructor
 *************************************************************************/
Streek::Streek(const Position & pt, Velocity v) : Effect(pt)
{
   ptEnd = pt;
   v *= -1.0;
   ptEnd += v;
   
    // age
    age = 0.5;
}

/************************************************************************
 * EXHAUST constructor
 *************************************************************************/
Exhaust::Exhaust(const Position & pt, Velocity v) : Effect(pt)
{
    ptEnd = pt;
    v *= -1.0;
    ptEnd += v;

    // age
    age = 0.5;
}

/***************************************************************/
/***************************************************************/
/*                           RENDER                            */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * EFFECT RENDER
 * Draw a missile exhaust or shrapnel streak on the screen
 *************************************************************************/
void Effect::render() const
{
   RenderTrail trailRender;
   trailRender.execute(this);
}

/************************************************************************
 * FRAGMENT RENDER
 * Draw the fragment on the screen
 *************************************************************************/
void Fragment::render() const
{
    RenderFragment fragmentRender;
    fragmentRender.execute(this);
}

/***************************************************************/
/***************************************************************/
/*                            FLY                              */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * FRAGMENT FLY
 * Move the fragment on the screen
 *************************************************************************/
void Fragment :: fly()
{
    // move it forward with inertia (no gravity)
    pt += v;
    
    // increase the age so it fades away
    age -= 0.02;
    size *= 0.95;
}

/************************************************************************
 * STREEK FLY
 * The streek will just fade away
 *************************************************************************/
void Streek :: fly()
{
    // move it forward with inertia (no gravity)
    pt += v;
    
   // increase the age so it fades away
   age -= 0.10;
}

/************************************************************************
 * EXHAUST FLY
 * The exhaust will just fade away
 *************************************************************************/
void Exhaust :: fly()
{
   // move it forward with inertia (no gravity)
   pt += v;
    
   // increase the age so it fades away
   age -= 0.025;
}

/***************************************************************/
/***************************************************************/
/*                      RENDER EFFECTS                         */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * EXECUTE
 * All of the steps for render() are here
 *************************************************************************/
void Effect::RenderEffect::execute(const Effect* effect) const
{
   // If the bullet is dead, we just stop here
   if (effect->isDead())
      return;

   drawLines();
   drawTriangleFan();
   setColor(effect->age);
   drawEffect(effect->pt, effect->ptEnd, effect->size);
   finishDrawing();
}

/************************************************************************
 * RENDER EFFECT - SET COLOR
 * Sets the color of the effect depending on its age
 *************************************************************************/
void Effect::RenderEffect::setColor(float age) const
{
   glColor3f((GLfloat)age, (GLfloat)age, (GLfloat)age);
}

/************************************************************************
 * RENDER EFFECT - FINISH DRAWING
 * Calls glEnd in order to end drawing
 *************************************************************************/
void Effect::RenderEffect::finishDrawing() const
{
   glEnd();
}

/***************************************************************/
/***************************************************************/
/*                     RENDER FRAGMENT                         */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * RENDER FRAGMENT - DRAW LINES
 * The fragment doesn't use this
 *************************************************************************/
void Effect::RenderFragment::drawLines() const
{
   // This method intentionally left blank
}

/************************************************************************
 * RENDER FRAGMENT - DRAW TRIANGLE FAN
 * Gives instructions to start drawing the triangle fan
 *************************************************************************/
void Effect::RenderFragment::drawTriangleFan() const
{
   glBegin(GL_TRIANGLE_FAN);
}

/************************************************************************
 * RENDER FRAGMENT - DRAW EFFECT
 * Gives more detailed instruction on drawing the fragments
 *************************************************************************/
void Effect::RenderFragment::drawEffect(Position pt, Position ptEnd, float size) const
{
   glVertex2f((GLfloat)(pt.getX() - size), (GLfloat)(pt.getY() - size));
   glVertex2f((GLfloat)(pt.getX() + size), (GLfloat)(pt.getY() - size));
   glVertex2f((GLfloat)(pt.getX() + size), (GLfloat)(pt.getY() + size));
   glVertex2f((GLfloat)(pt.getX() - size), (GLfloat)(pt.getY() + size));
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
}


/***************************************************************/
/***************************************************************/
/*                       RENDER TRAIL                          */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * RENDER TRAIL - DRAW LINES
 * Gives instructions on what shape to draw, specifically lines for the
 * exhaust and streak
 *************************************************************************/
void Effect::RenderTrail::drawLines() const
{
   glBegin(GL_LINES);
}

/************************************************************************
 * RENDER FRAGMENT - DRAW LINES
 * The fragment doesn't use this
 *************************************************************************/
void Effect::RenderTrail::drawTriangleFan() const
{
   // This method intentionally left blank
}

/************************************************************************
 * RENDER TRAIL - DRAW EFFECT
 * Gives more detailed instruction on drawing the exhaust and streak
 *************************************************************************/
void Effect::RenderTrail::drawEffect(Position pt, Position ptEnd, float size) const
{
   glVertex2f((GLfloat)pt.getX(), (GLfloat)pt.getY());
   glVertex2f((GLfloat)ptEnd.getX(), (GLfloat)ptEnd.getY());

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
}