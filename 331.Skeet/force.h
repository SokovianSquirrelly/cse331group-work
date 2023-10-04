/************************************************************************
 * Header File:
 *    Force
 * Author:
 *    Efrain Gomez Fajardo
 * Summary:
 *    Environmental factors that affect a Bird
 ************************************************************************/
#pragma once


class Bird;
/***********************************
* FORCE
* Abstract representation of a force
************************************/
class Force
{
   virtual void apply(Bird* b) = 0;
};

/***********************************
* StandardDrag: FORCE
* Drag experienced by the Standard
************************************/
class StandardDrag : public Force
{
   void apply(Bird* b);
};

/***********************************
* CrazyDrag: FORCE
* Drag experienced by the Crazy
************************************/
class CrazyDrag : public Force
{
   void apply(Bird* b);
};

/***********************************
* FloaterGravity: FORCE
* Gravity experienced by the Floater
************************************/
class FloaterGravity : public Force
{
   void apply(Bird* b);
};

/***********************************
* SinkerGravity: FORCE
* Gravity experienced to the Sinker
************************************/
class SinkerGravity : public Force
{
   void apply(Bird* b);
};

/***********************************
* CrazyMovement: FORCE
* Movement that the Crazy does.
************************************/
class CrazyMovement : public Force
{
   void apply(Bird* b);
};

/***********************************
* KillCheck: FORCE
* Check made to kill the Birds
************************************/
class KillCheck : public Force
{
   void apply(Bird* b);
};