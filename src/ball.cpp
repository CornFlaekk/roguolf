#include <raylib.h>
#include <cmath>
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
    if (IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) && x_accel == 0 && y_accel == 0)
    {
        x_accel = x - GetMouseX();
        y_accel = y - GetMouseY();
    }

    if (x <= 0 )
    {
        x_accel = std::abs(x_accel);
    }
    if (x >= (GetScreenWidth() - texture.width))
    {
        x_accel = -1 * std::abs(x_accel);
    }

    if (y <= 0 )
    {
        y_accel = std::abs(y_accel);
    }
    if (y >= (GetScreenHeight() - texture.height))
    {
        y_accel = -1 * std::abs(y_accel);
    }

    x = x + x_accel * 0.12;
    y = y + y_accel * 0.12;
    x_accel = x_accel * 0.95;
    y_accel = y_accel * 0.95;



}

void Ball::draw()
{
    DrawTexture(texture, x, y, WHITE);
    if (x_accel == 0 && y_accel == 0 && IsCursorOnScreen())
    {
        DrawCircle(x+(texture.width/2) + (x - GetMouseX()) * 0.20, y+(texture.height/2) + (y - GetMouseY()) * 0.20, 4, WHITE);
        DrawCircle(x+(texture.width/2) + (x - GetMouseX()) * 0.35, y+(texture.height/2) + (y - GetMouseY()) * 0.35, 4, WHITE);
        DrawCircle(x+(texture.width/2) + (x - GetMouseX()) * 0.50, y+(texture.height/2) + (y - GetMouseY()) * 0.50, 4, WHITE);
    }
}

void Ball::setSpeed(int p_speed)
{
    speed = p_speed;
}

void Ball::setTexture(Texture p_texture)
{
    texture = p_texture;
}