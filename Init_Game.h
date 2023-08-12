#ifndef INIT_GAME_H
#define INIT_GAME_H


#include <SDL2/SDL.h>
#include <vector>
#include "Map.h"
#include "Ball.h"
#include "Wall.h"
#include "Physics.h"
#include "Render.h"



class Init_Game
{
private:
    vector<Ball> balls; // The vector that contains the balls of the game
    
public:
    Init_Game(vector<Ball> balls_);
    Init_Game();
    void setSlowloops(int s_loop);
    bool returnEnd();
    vector<Ball> returnBalls();
    bool checkBalls();
    int slow_loops;
    bool end;
};

#endif


