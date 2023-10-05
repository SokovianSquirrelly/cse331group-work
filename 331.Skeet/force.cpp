/***********************************************************************
 * Source File:
 *    Force : Natural effects that affect Bird
 * Author:
 *    Efrain Gomez Fajardo
 * Summary:
 *    Changes that apply to Bird by just existing
 *
 *    The movement of the birds and the specific formulas for each type of movement. 
 *    This includes inertia, gravity, anti-gravity, drag, strong drag, and random. 
 *    This class will also check if the bird/skeet is dead and if the movement should stop. 
 *    There are also 2 functions for generating and checking randomly generated 
 *    numbers for the random movement. 
 ************************************************************************/

#include "force.h"
#include "bird.h"
#include <cassert>

/******************************************************************
* RANDOM
* These functions generate a random number.
****************************************************************/
//double randomInt(int min, int max)
//{
//   assert(min < max);
//   int num = (rand() % (max - min)) + min;
//   assert(min <= num && num <= max);
//   return num;
//}
//
//double randomFloat(double min, double max)
//{
//   assert(min <= max);
//   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
//   assert(min <= num && num <= max);
//   return num;
//}

/*********************************
* INERTIA
* Adding velocity to the position
**********************************/
void Inertia::apply(Bird* b)
{
   b->getPosition().add(b->getVelocity());
}

/*********************************
* STANDARD DRAG
* Velocity is multiplied 0.990
**********************************/
void StandardDrag::apply(Bird* b)
{
   b->getVelocity() *= .990;
}

/*********************************
* CRAZY DRAG
* Velocity is multiplied 0.995
**********************************/
void CrazyDrag::apply(Bird* b)
{
   b->getVelocity() *= .995;
}

/*********************************
* FLOATER GRAVITY
* Velocity y is multiplied 0.05
**********************************/
void FloaterGravity::apply(Bird* b)
{
   b->getVelocity().addDy(0.05);
}

/*********************************
* SINKER GRAVITY
* Velocity y is multiplied -0.07
**********************************/
void SinkerGravity::apply(Bird* b)
{
   b->getVelocity().addDy(-0.07);
}

/*********************************
* CRAZY MOVEMENT
* Random generated changes in position
**********************************/
void CrazyMovement::apply(Bird* b)
{
   /*if (randomInt(0, 15) == 0)
   {
      b->getVelocity().addDy(randomFloat(-1.5, 1.5));
      b->getVelocity().addDx(randomFloat(-1.5, 1.5));
   }*/
}

/*********************************
* KILL CHECK
* Check if the bird is out of screen
**********************************/
void KillCheck::apply(Bird* b)
{
   //if (b->isOutOfBounds())
   //{
   //   b->kill();
   //   b->setPoints(b->getPoints() *= -1); // points go negative when it is missed!
   //}
}
