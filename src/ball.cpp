#include <raylib.h>
#include "Ball.h"

void Ball::update(){
    if (IsKeyDown( KEY_W ))
    {
        y = y - speed;
    }
    if (IsKeyDown( KEY_S ))
    {
        y = y + speed;
    }
    if (IsKeyDown( KEY_A ))
    {
        x = x - speed;
    }
    if (IsKeyDown( KEY_D ))
    {
        x = x + speed;
    }
}

void Ball::draw()
{
    DrawTexture(texture, x, y, WHITE);
}

void Ball::setSpeed(int p_speed)
{
    speed = p_speed;
}

void Ball::setTexture(Texture p_texture)
{
    texture = p_texture;
}