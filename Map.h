#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>


#include "Wall.h"

using namespace std;

class Map
{
private:
    float width; // Width of the map
    float height; // Height of the map
    vector<Wall> walls; // The vector that contains the walls within the map

    
    

public:
    Map(float wid, float hei);
    Map();

    const vector<Wall>& getWalls() const; 
    float getWidth() const; 
    float getHeight() const; 
    

    void addWall(Wall wall); 
    
};

#endif