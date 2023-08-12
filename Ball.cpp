#include "Ball.h"


Ball::Ball(float a, float b, float c, float d, float e, float f, float g , float h)
{
    x = a; 
    y = b; 
    vx = c; 
    vy = d;
    ax = e;
    ay = f;
    radius = g;
    mass = h;
    
}

Ball::Ball() = default;

void Ball::setVelocity(float v_x, float v_y) {
    vx = v_x;
    vy = v_y;
} 

void Ball::setPosition(float x_, float y_) {
    x = x_;
    y = y_;
}

void Ball::setAcceleration(float ax_, float ay_) {
    ax = ax_;
    ay = ay_;
}

void Ball::setRadius(float r){
    radius = r;
}

void Ball::setMass(float m){
    mass = m;
}
    
float Ball::getX() const {return x;}
float Ball::getY() const {return y;}
float Ball::getVx() const {return vx;}
float Ball::getVy() const {return vy;}
float Ball::getAx() const {return ax;}
float Ball::getAy() const {return ay;}
float Ball::getRadius() const {return radius;}
float Ball::getMass() const {return mass;}
    





    




