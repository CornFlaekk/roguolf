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
    for(Rectangle rect : textureCollisionRectangles)
    {
        Rectangle onScreenCollisionRect = {(float) rect.x + x, (float) rect.y + y, rect.width, rect.height};
        onScreenCollisionRectangles.push_back(onScreenCollisionRect);
    }
    }

void Obstacle::setPositionFromCenter(int x, int y)
{
    positions.push_back({x - (texture.width/2), y - (texture.height/2)});
    for(Rectangle rect : textureCollisionRectangles)
    {
        Rectangle onScreenCollisionRect = {(float) (rect.x + x - texture.width/2), (float) (rect.y + y - texture.height/2), rect.width, rect.height};
        onScreenCollisionRectangles.push_back(onScreenCollisionRect);
    }
}

void Obstacle::clearPositions()
{
    positions.clear();
    onScreenCollisionRectangles.clear();
}

void Obstacle::setTextureCollisionRectangle(Rectangle collision)
{
    textureCollisionRectangles.push_back(collision);
}

std::vector<Rectangle> Obstacle::getOnScreenCollisionRectangles()
{
    return onScreenCollisionRectangles;
}