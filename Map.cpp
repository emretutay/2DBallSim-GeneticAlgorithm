#include "Map.h"

Map::Map(float wid, float hei){
    width = wid;
    height = hei;
}

const vector<Wall>& Map::getWalls() const 
{ 
    return walls; 
}

Map::Map() = default;

float Map::getWidth() const { return width; }
float Map::getHeight() const { return height; }



void Map::addWall(Wall wall) 
{
    walls.emplace_back(wall);
}

