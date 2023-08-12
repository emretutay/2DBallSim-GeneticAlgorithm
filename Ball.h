#ifndef BALL_H
#define BALL_H


#include <iostream>
#include <cmath>

class Ball
{
private:
    float x;  // position in x-axis
    float y;  // position in y-axis
    float vx;   // velocity in x-axis
    float vy;   // velocity in y-axis
    float ax;   // acceleration in x-axis
    float ay;   // acceleration in y-axis
    float radius;  // radius of the ball (pixels)
    float mass;  // mass of the ball
public:
    Ball(float a, float b, float c, float d, float e, float f, float g, float h);
    Ball();
    
    // function prototypes
    void setVelocity(float v_x, float v_y);
    void setPosition(float x_, float y_);
    void setAcceleration(float ax_, float ay_);
    void setRadius(float r);
    void setMass(float m);
    
    float getX() const; 
    float getY() const; 
    float getVx() const; 
    float getVy() const; 
    float getAx() const;
    float getAy() const;
    float getRadius() const; 
    float getMass() const; 

    
};


#endif