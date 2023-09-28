/***********************************************************************
 * Header File:
 *    Bird : Everything that can be shot
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#pragma once
#include "position.h"

/**********************
* BIRD TYPE
* The different types of birds
***********************/
enum BirdType
{
   STANDARD,
   SINKER,
   FLOATER,
   CRAZY,
   FAKE     // This fake bird is only here so that the crazy bird will actually spawn
};

/**********************
 * BIRD
 * Everything that can be shot
 **********************/
class Bird
{
protected:
   static Position dimensions; // size of the screen
   Position pt;                  // position of the flyer
   Velocity v;                // velocity of the flyer
   double radius;             // the size (radius) of the flyer
   bool dead;                 // is this flyer dead?
   int points;                // how many points is this worth?
   
public:
   Bird() : dead(false), points(0), radius(1.0) { }
   
   // setters
   void operator=(const Position    & rhs) { pt = rhs;    }
   void operator=(const Velocity & rhs) { v = rhs;     }
   void kill()                          { dead = true; }
   void setPoints(int pts)              { points = pts;}

   // getters
   bool isDead()           const { return dead;   }
   Position getPosition()     const { return pt;     }
   Velocity getVelocity()  const { return v;      }
   double getRadius()      const { return radius; }
   int getPoints() const { return points; }
   bool isOutOfBounds() const
   {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
              pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }

   // special functions
   virtual void draw() = 0;
   virtual void advance() = 0;
};

/*********************************************
 * STANDARD
 * A standard bird: slows down, flies in a straight line
 *********************************************/
class Standard : public Bird
{
public:
    Standard(double radius = 25.0, double speed = 5.0, int points = 10);
    void draw();
    void advance();
};

/*********************************************
 * FLOATER
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class Floater : public Bird
{
public:
    Floater(double radius = 30.0, double speed = 5.0, int points = 15);
    void draw();
    void advance();
};

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class Crazy : public Bird
{
public:
    Crazy(double radius = 30.0, double speed = 4.5, int points = 30);
    void draw();
    void advance();
};

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class Sinker : public Bird
{
public:
    Sinker(double radius = 30.0, double speed = 4.5, int points = 20);
    void draw();
    void advance();
};

/*********************************************
 * BIRD FACTORY
 * The abstract factory needed to spawn the birds
 *********************************************/
class BirdFactory
{
public:
   virtual Bird* factory(BirdType type) = 0;
};

/*********************************************
 * BIRD FACTORY LEVEL 1
 * Builds the standard birds for level 1
 *********************************************/
class BirdFactoryLevel1 : public BirdFactory
{
   Bird* factory(BirdType type);
};

/*********************************************
 * BIRD FACTORY LEVEL 2
 * Builds the standard and sinker birds for
 * level 2
 *********************************************/
class BirdFactoryLevel2 : public BirdFactory
{
   Bird* factory(BirdType type);
};

/*********************************************
 * BIRD FACTORY LEVEL 3
 * Builds the standard, sinker, and floater
 * birds for level 3
 *********************************************/
class BirdFactoryLevel3 : public BirdFactory
{
   Bird* factory(BirdType type);
};

/*********************************************
 * BIRD FACTORY LEVEL 4
 * Builds all kinds of birds for level 4
 *********************************************/
class BirdFactoryLevel4 : public BirdFactory
{
   Bird* factory(BirdType type);
};