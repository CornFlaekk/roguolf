#include <raylib.h>
#include <vector>
#include <iostream>

#include "Obstacle.h"

void Obstacle::setTexture(Texture tex)
{
    texture = tex;
}

void Obstacle::draw()
{
    for(int i = 0; i < (int) positions.size(); i++)
    {
        DrawTexture(texture, positions[i][0], positions[i][1], WHITE);
    }
}

void Obstacle::setPosition(int x, int y)
{
    positions.push_back({x, y});
    collisionRectangles.push_back((Rectangle) {(float) x, (float) y, (float) (texture.width), (float) (texture.height)});
}

void Obstacle::setPositionFromCenter(int x, int y)
{
    positions.push_back({x - (texture.width/2), y - (texture.height/2)});
    collisionRectangles.push_back((Rectangle) {(float) (x - texture.width/2), (float) (y - texture.height/2), (float) (texture.width), (float) (texture.height)});
}

void Obstacle::clearPositions()
{
    positions.clear();
    collisionRectangles.clear();
}

std::vector<Rectangle> Obstacle::getCollisionRectangles()
{
    return collisionRectangles;
}