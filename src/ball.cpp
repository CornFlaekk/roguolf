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
        drawGuidingCircles();
    }
}

void Ball::drawGuidingCircles()
{
    float distance_multipliers[] = {0.20, 0.35, 0.50};

    for (int i = 0; i < (sizeof(distance_multipliers)/sizeof(distance_multipliers[0])); i++)
    {
        float multiplier = distance_multipliers[i];

        int circle_x = x+(texture.width/2) + (x - GetMouseX()) * multiplier;
        int circle_y = y+(texture.height/2) + (y - GetMouseY()) * multiplier;

        while (circle_x < 0 || circle_y < 0 || circle_x > GetScreenWidth() || circle_y > GetScreenHeight())
        {
            if (circle_x < 0) circle_x = abs(circle_x);
            if (circle_y < 0) circle_y = abs(circle_y);
            if (circle_x > GetScreenWidth()) circle_x = GetScreenWidth() - (circle_x - GetScreenWidth());
            if (circle_y > GetScreenHeight()) circle_y = GetScreenHeight() - (circle_y - GetScreenHeight());
        }

        DrawCircle(circle_x, circle_y, 4, WHITE);
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