#include "Render.h"





Render::Render(SDL_Renderer *render){
        renderer = render;
        
}



/*
    Renders everything on the map into the screen

    Time Complexity : O(n) Linear time
    Space Complexity : O(n) Linear space


*/

void Render::renderScreen(Map map, vector<Ball> balls, Uint32 startTicks){

        // Sets renderer color to black and clear previous context
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);    

        // Renders all walls
        for (const auto& wall : map.getWalls())
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, wall.getStartX(), wall.getStartY(), wall.getEndX(), wall.getEndY());
        }
        
        // Renders all balls
        for(const auto& ball : balls){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect ballRect = { static_cast<int>(ball.getX() - ball.getRadius()), static_cast<int>(ball.getY() - ball.getRadius()), static_cast<int>(ball.getRadius() * 2), static_cast<int>(ball.getRadius() * 2) };
            SDL_RenderFillRect(renderer, &ballRect);
        }
        
        

        SDL_RenderPresent(renderer);
        

        
    }


