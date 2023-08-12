#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <vector>
#include "Map.h"
#include "Ball.h"
#include "Wall.h"
#include "Physics.h"

class Render
{
private:
    SDL_Renderer *renderer;
    Uint32 totalFrameTicks;

public:
    Render(SDL_Renderer *render);
    
    void renderScreen(Map map, vector<Ball> balls, Uint32 startTicks_);
    
    
};

#endif