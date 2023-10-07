/***********************************************************************
 * Header File:
 *    Fragment : Pieces that fly off a dead bird
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Pieces that fly off a dead bird
 ************************************************************************/

#pragma once
#include "position.h"

/**********************
 * Effect: stuff that is not interactive
 **********************/
class Effect
{
protected:
    Position pt;      // location of the effect
    double age;       // 1.0 = new, 0.0 = dead
    double size;      // size of the fragment
    Position ptEnd;
    Velocity v;

    /*********************************
    * RENDER EFFECT
    * Abstract template
    **********************************/
    class RenderEffect
    {
    public:
       void execute(const Effect *effect) const;

    private:
       virtual void drawLines() const = 0;
       virtual void drawTriangleFan() const = 0;
       void setColor(float) const;
       virtual void drawEffect(Position, Position, float) const = 0;
       void finishDrawing() const;
    };

    /*********************************
    * RENDER FRAGMENT : RENDER EFFECT
    * Concrete template
    **********************************/
    class RenderFragment : public RenderEffect
    {
    private:
       void drawLines() const;
       void drawTriangleFan() const;
       void drawEffect(Position, Position, float) const;
    };

    /*********************************
    * RENDER TRAIL : RENDER EFFECT
    * Concrete template
    **********************************/
    class RenderTrail : public RenderEffect
    {
    private:
       void drawLines() const;
       void drawTriangleFan() const;
       void drawEffect(Position, Position, float) const;
    };

public:
    // create a fragment based on the velocity and position of the bullet
    Effect(const Position & pt) : pt(pt), age(0.5) {}
    
    // draw it
    virtual void render() const;
    
    // move it forward with regards to inertia. Let it age
    virtual void fly() = 0;
    
    // it is dead when age goes to 0.0
    bool isDead() const { return age <= 0.0; }
};

/**********************
 * FRAGMENT
 * Pieces that fly off a dead bird
 **********************/
class Fragment : public Effect
{
public:
    // create a fragment based on the velocity and position of the bullet
    Fragment(const Position & pt, const Velocity & v);
    
    // draw it
    void render() const;
    
    // move it forward with regards to inertia. Let it age
    void fly();
};

/**********************
 * STREEK
 * Stuff that trails off the back of shrapnel
 **********************/
class Streek : public Effect
{
public:
    // create a fragment based on the velocity and position of the bullet
    Streek(const Position & pt, Velocity v);
    
    // move it forward with regards to inertia. Let it age
    void fly();
};

/**********************
 * EXHAUST
 * Stuff that comes out the back of a missile when in flight
 **********************/
class Exhaust : public Effect
{
public:
    // create a fragment based on the velocity and position of the bullet
    Exhaust(const Position & pt, Velocity v);
    
    // move it forward with regards to inertia. Let it age
    void fly();
};