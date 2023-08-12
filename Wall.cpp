#include "Wall.h"


Wall::Wall(float a, float b, float c, float d, float e ) 
{
    startX = a;  
    startY = b;  
    endX = c;    
    endY = d;   
    radius = e;
    
    
    dx = endX - startX;
    dy = endY - startY;
    float length = sqrt(dx * dx + dy * dy);
    normalX = -dy / length;
    normalY = dx / length; 
}

float Wall::getStartX() const { return startX; }
float Wall::getStartY() const { return startY; }
float Wall::getEndX() const { return endX; }
float Wall::getEndY() const { return endY; }
float Wall::getDx() const { return dx; }
float Wall::getDy() const { return dy; }
float Wall::getNormalX() const { return normalX; }
float Wall::getNormalY() const { return normalY; }
float Wall::getRadius() const{return radius;}
   



   






