#pragma once
#include "bullet.h"
#include "effect.h"

/***********************************************************************
 * Header File:
 *    BulletMove : Movement of the bullets
 * Author:
 *    Ashley Offret and Br. Helfrich
 * Summary:
 *    Movement of the bullets
 ************************************************************************/

/*********************************************
 * Move
 * Base class for Move functions in "Bullet."
 *********************************************/
class Move
{
public:
   //Make basic move here, put factory inside bullet class.
   //virtual void moveBullet(std::list<Effect*>& effects, enum bulletType)
   //{
   //  /* switch (bulletType)
   //   {
   //   case MISSILE:
   //      MoveMissile missile;
   //      return missile.

   //   default:
   //      break;
   //   }*/
   //};

   virtual void moveBullet(std::list<Effect*>& effects) = 0;
protected:
   void move(Bullet* bullet)
   {
      // inertia
      bullet->getPosition().add(bullet->getVelocity());

      // out of bounds checker
      if (bullet->isOutOfBounds())
         bullet->kill();
   }
};

/*********************************************
 * Move Missile
 * Derived class for Missile Move functions in "Bullet."
 *********************************************/
class MoveMissile : public Move
{
public:
   virtual void moveBullet(std::list<Effect*>& effects, Missile*& missile) //Add pointer to missile
    {
      effects.push_back(new Exhaust(missile->getPosition(), missile->getVelocity()));

      move(missile);
    }
   
};

/*********************************************
 * Move Bomb
 * Derived class for Bomb Move functions in "Bullet."
 *********************************************/
class MoveBomb : public Move
{
public:
   virtual void moveBullet(std::list<Effect*>&effects, Bomb * & bomb) //Add pointer to missile
   {
      effects.push_back(new Exhaust(bomb->getPosition(), bomb->getVelocity()));

      move(bomb);
   }

};

/*********************************************
 * Move Shrapnel
 * Derived class for Shrapnel Move functions in "Bullet."
 *********************************************/
class MoveShrapnel : public Move
{
public:
   virtual void moveBullet(std::list<Effect*>& effects, Shrapnel*& shrapnel) //Add pointer to missile
   {
      effects.push_back(new Exhaust(shrapnel->getPosition(), shrapnel->getVelocity()));

      move(shrapnel);
   }
};