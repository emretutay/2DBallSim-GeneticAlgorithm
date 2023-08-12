#ifndef WALL_H
#define WALL_H

#include <cmath>

class Wall {
public:
    Wall(float a, float b, float c, float d, float e);

    // Function prototypes
    float getStartX() const;
    float getStartY() const;
    float getEndX() const;
    float getEndY() const;
    float getDx() const;
    float getDy() const;
    float getNormalX() const;
    float getNormalY() const;
    float getRadius() const;

private:
    float startX;    // x-coordinate of the starting point of the wall 
    float startY;    // y-coordinate of the starting point of the wall 
    float endX;      // x-coordinate of the ending point of the wall 
    float endY;      // y-coordinate of the ending point of the wall 
    float dx;        // length of wall in x axis  
    float dy;        // length of wall in y axis    
    float normalX;   // normal of wall - x
    float normalY;   // normal of wall -y   
    float radius;    // radius of the wall (thickness in pixels)
};

#endif // WALL_H
