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
        if (x_accel > MAX_ACCEL_X) x_accel = MAX_ACCEL_X;
        else if (x_accel < -MAX_ACCEL_X) x_accel = -MAX_ACCEL_X;
        if (y_accel > MAX_ACCEL_Y) y_accel = MAX_ACCEL_Y;
        else if (y_accel < -MAX_ACCEL_Y) y_accel = -MAX_ACCEL_Y;
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
    if (y >= ((GetScreenHeight() - powerbar_height) - texture.height))
    {
        y_accel = -1 * std::abs(y_accel);
    }

    x = x + x_accel * 0.12;
    y = y + y_accel * 0.12;
    x_accel = x_accel * 0.95;
    y_accel = y_accel * 0.95;

    calcAccelPreview();

}

void Ball::draw()
{
    DrawTexture(texture, x, y, WHITE);
    if (x_accel == 0 && y_accel == 0 && IsCursorOnScreen())
    {
        calcAnimation();
        drawGuidingCircles();
    }
}

void Ball::calcAnimation()
{
    animation_frame++;
    if (animation_frame > (GetFPS()/60))
    {
        animation_id++;
        animation_frame = 0;
    }
    if (animation_id > MAX_ANIMATIONS)
        animation_id = 0;
    
    distance_multipliers = {0.05 + (0.01 * animation_id), 0.20 + (0.01 *animation_id), 0.35 + (0.01 * animation_id)};
}

void Ball::drawGuidingCircles()
{
    int bg_height = GetScreenHeight() - powerbar_height;
    
    for (int i = 0; i < (int) distance_multipliers.size() ; i++)
    {
        float multiplier = distance_multipliers[i];
        int circle_x = 0, circle_y = 0;

        if ( (x - GetMouseX()) <= MAX_ACCEL_X && (x - GetMouseX()) >= -MAX_ACCEL_X )
            circle_x = x+(texture.width/2) + (x - GetMouseX()) * multiplier;
        else if ( (x - GetMouseX() > MAX_ACCEL_X) )
            circle_x = x+(texture.width/2) + MAX_ACCEL_X * multiplier;
        else
            circle_x = x+(texture.width/2) - MAX_ACCEL_X * multiplier;

        if ( (y - GetMouseY()) <= MAX_ACCEL_Y && (y - GetMouseY()) >= -MAX_ACCEL_Y )
            circle_y = y+(texture.height/2) + (y - GetMouseY()) * multiplier;
        else if ( (y - GetMouseY() > MAX_ACCEL_Y) )
            circle_y = y+(texture.height/2) + MAX_ACCEL_Y * multiplier;    
        else
            circle_y = y+(texture.height/2) - MAX_ACCEL_Y * multiplier;
        

        while (circle_x < 0 || circle_y < 0 || circle_x > GetScreenWidth() || circle_y > bg_height)
        {
            if (circle_x < 0) circle_x = abs(circle_x);
            if (circle_y < 0) circle_y = abs(circle_y);
            if (circle_x > GetScreenWidth()) circle_x = GetScreenWidth() - (circle_x - GetScreenWidth());
            if (circle_y > bg_height) circle_y = bg_height - (circle_y - bg_height);
        }

        DrawCircle(circle_x, circle_y, 4, WHITE);
    }
}

void Ball::calcAccelPreview()
{
    x_accel_preview = abs(x - GetMouseX());
    y_accel_preview = abs(y - GetMouseY());

    if (x_accel_preview > MAX_ACCEL_X) x_accel_preview = MAX_ACCEL_X;
    if (y_accel_preview > MAX_ACCEL_Y) y_accel_preview = MAX_ACCEL_Y;

}

void Ball::setX(int val)
{
    x = val;
}

void Ball::setY(int val)
{
    y = val;
}

void Ball::setSpeed(int p_speed)
{
    speed = p_speed;
}

void Ball::setTexture(Texture p_texture)
{
    texture = p_texture;
}

void Ball::setPowerBarHeight(int value)
{
    powerbar_height = value;
}

void Ball::setMaxAccel()
{
    MAX_ACCEL_X = GetScreenWidth() * 0.6;
    MAX_ACCEL_Y = GetScreenHeight() * 0.6;
}

/**
 * @return Calculated from mouse position. Value in range [0-100].
*/
float Ball::getPreviewAccel()
{
    return (float) (x_accel_preview + y_accel_preview) / (MAX_ACCEL_X + MAX_ACCEL_Y);
}

float Ball::getAccel()
{
    return (float) (abs(x_accel) + abs(y_accel)) / (MAX_ACCEL_X + MAX_ACCEL_Y);
}

int Ball::getSpeed()
{
    return speed;
}

int Ball::getAccelX()
{
    return x_accel;
}

int Ball::getAccelY()
{
    return y_accel;
}

void Ball::invertAccelX()
{
    x_accel *= -1;
}

void Ball::invertAccelY()
{
    y_accel *= -1;
}

Vector2 Ball::getCenter()
{
    return (Vector2) {(float) x + texture.width/2, (float) y + texture.height/2};
}