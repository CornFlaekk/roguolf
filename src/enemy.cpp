#include <raylib.h>
#include <vector>
#include <iostream>

#include "Enemy.h"

int redFrames;
int life = 2;

void Enemy::setTexture(Texture tex)
{
    texture = tex;
}

void Enemy::draw()
{
    for(int i = 0; i < (int) positions.size(); i++)
    {
        if(redFrames > 0)
        {
            animate(i);
        }
        else if(redFrames == 0 && life == 0)
        {
            clearPositions();
        }
        else
        {
            DrawTexture(texture, positions[i][0], positions[i][1], WHITE);
        }
    }
}

void Enemy::animate(int i)
{
    if(redFrames > 0)
    {
        DrawTexture(texture, positions[0][0], positions[0][1], RED);
        redFrames--;
    }
}

void Enemy::setPosition(int x, int y)
{
    positions.push_back({x, y});
    for(Rectangle rect: textureCollisionRectangles)
    {
        Rectangle onScreenCollisionRect = {(float) rect.x + x, (float) rect.y + y, rect.width, rect.height};
        onScreenCollisionRectangles.push_back(onScreenCollisionRect);
    }
}

void Enemy::clearPositions()
{
    positions.clear();
    onScreenCollisionRectangles.clear();
}

void Enemy::setTextureCollisionRectangle(Rectangle collision)
{
    textureCollisionRectangles.push_back(collision);
}

std::vector<Rectangle> Enemy::getOnScreenCollisionRectangles()
{
    return onScreenCollisionRectangles;
}

void Enemy::setLife(int val)
{
    life = val;
}

int Enemy::getLife()
{
    return life;
}

void Enemy::hit(int damage)
{
    life -= damage;
    redFrames += 10;
    if (life < 0) life = 0;
}