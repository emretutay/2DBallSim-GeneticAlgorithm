#ifndef PHYSICS_H
#define PHYSICS_H


#include "Ball.h"
#include "Map.h"
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>


class Physics
{
private:

    vector<Ball> balls; // Vector that contains the balls in the simulation
    float dt;      // Amount of time in a time step 
    Uint32 lastUpdate;  // Time of the last physics update
    float gravity = 100; // Gravity
    
   
    
public:
    float vStable = 0.05; // The stability value

    Physics(vector<Ball> b, float dt_, Uint32 lastU);
    Physics();

    // Function prototypes
    void setBalls(vector<Ball> balls);
    vector<Ball> getBalls(); 
    void setLastUpdate(Uint32 time);
    Uint32 getLastUpdate();
    void setDt(float dt_);
    float getDt();
    vector<Ball> updateBall(const Map& map);
    bool checkCollision( Ball& ball, const Wall& wall);
    void resolveCollision();

    vector<pair<Ball*, Ball*>> vecCollidingObjects;  // Vector of pairs that contain the colliding objects



    

};
#endif