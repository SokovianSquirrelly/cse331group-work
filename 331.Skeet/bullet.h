/***********************************************************************
 * Header File:
 *    Bullet
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that kills other things
 ************************************************************************/

#pragma once
#include "position.h"
#include "effect.h"
#include <list>
#include <cassert>

enum BulletType { PELLET, MISSILE, BOMB, SHRAPNEL };

/*********************************************
 * BULLET
 * Something to shoot something else
 *********************************************/
class Bullet
{
protected:
   static Position dimensions;   // size of the screen
   Position pt;                  // position of the bullet
   Velocity v;                // velocity of the bullet
   double radius;             // the size (radius) of the bullet
   bool dead;                 // is this bullet dead?
   int value;                 // how many points does this cost?
    
public:
   Bullet(double angle = 0.0, double speed = 30.0, double radius = 5.0, int value = 1);
   
   // setters
   void kill()                   { dead = true; }
   void setValue(int newValue)   { value = newValue; }
   
   // getters
   bool isDead()           const { return dead;   }
   Position getPosition()  const { return pt;     }
   Velocity getVelocity()  const { return v;      }
   double getRadius()      const { return radius; }
   int getValue()          const { return value;  }
   bool isOutOfBounds() const //So move can access this.
   {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
         pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }

   // special functions
   virtual void death(std::list<Bullet *> & bullets) {}
   virtual void output() = 0;
   virtual void input(bool isUp, bool isDown, bool isB) {}
   virtual void move(std::list<Effect*> &effects);

protected:
   
   void drawLine(const Position& begin, const Position& end,
                 double red = 1.0, double green = 1.0, double blue = 1.0) const;

   void drawDot(const Position& point, double radius = 2.0,
                double red = 1.0, double green = 1.0, double blue = 1.0) const;
   int    random(int    min, int    max);
   double random(double min, double max);
};

/*********************
 * PELLET
 * Small little bullet
 **********************/
class Pellet : public Bullet
{
public:
   Pellet(double angle, double speed = 15.0) : Bullet(angle, speed, 1.0, 1) {}
   void output();
};

/*********************
 * BOMB
 * Things that go "boom"
 **********************/
class Bomb : public Bullet
{
private:
  
public:
   int timeToDie;
   Bomb(double angle, double speed = 10.0) : Bullet(angle, speed, 4.0, 4), timeToDie(60) {}
   
   void output();
   void move(std::list<Effect*> & effects);
   void death(std::list<Bullet *> & bullets);
};

/*********************
 * Shrapnel
 * A piece that broke off of a bomb
 **********************/
class Shrapnel : public Bullet
{
private:
   
public:
   int timeToDie;
   Shrapnel(const Bomb & bomb)
   {

      // how long will this one live?
      timeToDie = random(5, 15);
      
      // The speed and direction is random
      v.set(random(0.0, 6.2), random(10.0, 15.0));
      pt = bomb.getPosition();

      value = 0;
      
      radius = 3.0;
   }
   
   void output();  
   void move(std::list<Effect*> & effects);
};


/*********************
 * MISSILE
 * Guided missiles
 **********************/
class Missile : public Bullet
{
public:
   Missile(double angle, double speed = 10.0) : Bullet(angle, speed, 1.0, 3) {}
   
   void output();
   void input(bool isUp, bool isDown, bool isB)
   {
      if (isUp)
         v.turn(0.04);
      if (isDown)
         v.turn(-0.04);
   }
   void move(std::list<Effect*> & effects);
};

/*********************************
* Factory
* For the creation of Bullets
**********************************/
inline Bullet* factory(BulletType type, double angle)
{
   switch (type)
   {
   case (PELLET):
      return new Pellet(angle);
   case (MISSILE):
      return new Missile(angle);
   case (BOMB):
      return new Bomb(angle);
   }

   // Program should never reach this point.
   assert(false);
   return (nullptr);
}

/*********************************
* MoveFactory
* For the movement of Bullets
**********************************/
inline Bullet* moveSelection(BulletType type, double angle)
{
   switch (type)
   {
   case (MISSILE):
   //   return new MoveMissile;
      std::cout << "New MoveMissile called";
   case (BOMB):
      //return new MoveBomb;
      std::cout << "New MoveBomb called";
   case (SHRAPNEL):
      //return new MoveShrapnel;
      std::cout << "New MoveShrapnel called";
   }

   // Program should never reach this point.
   assert(false);
   return (nullptr);
}
