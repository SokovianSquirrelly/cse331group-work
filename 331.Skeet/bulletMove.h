#pragma once
#include "bullet.h"
#include "effect.h"
#include <list>
using namespace std;

/***********************************************************************
 * Header File:
 *    BulletMove : Movement of the bullets
 * Author:
 *    Ashley Offret and Br. Helfrich
 * Summary:
 *    Movement of the bullets
 ************************************************************************/

class Bullet;

/*********************************************
 * Move
 * Base class for Move functions in "Bullet."
 *********************************************/
class MoveBullet
{
public:
   virtual void moveBullet(std::list<Effect*>& effects) = 0;
protected:
   void move(std::list<Effect*>& effects, Bullet* bullet)
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
class MoveMissile : public MoveBullet
{
public:
   virtual void moveBullet(std::list<Effect*>& effects, Missile*& missile) //Add pointer to missile
    {
      //Update the effects
      effects.push_back(new Exhaust(missile->getPosition(), missile->getVelocity()));
      //Move the missile.
      move(effects, missile);
    }
   
};

/*********************************************
 * Move Bomb
 * Derived class for Bomb Move functions in "Bullet."
 *********************************************/
class MoveBomb : public MoveBullet
{
public:
   virtual void moveBullet(std::list<Effect*>&effects, Bomb * & bomb) 
   {
      //Check if it needs to die.
      bomb->timeToDie--;
      if (!bomb->timeToDie)
         bomb->kill();

      //Move the bomb
      move(effects, bomb);
   }

};

/*********************************************
 * Move Shrapnel
 * Derived class for Shrapnel Move functions in "Bullet."
 *********************************************/
class MoveShrapnel : public MoveBullet
{
public:
   virtual void moveBullet(std::list<Effect*>& effects, Shrapnel*& shrapnel) //Add pointer to missile
   {
      //Check if it needs to die.
      shrapnel->timeToDie--;
      if (!shrapnel->timeToDie)
         shrapnel->kill();

      //Update the effects
      effects.push_back(new Streek(shrapnel->getPosition(), shrapnel->getVelocity()));

      //Move the bomb
      move(effects, shrapnel);
   }
};