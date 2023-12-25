#include <raylib.h>
#include <iostream>

#include "PowerBar.h"

void PowerBar::draw(float ball_accel, float ball_accel_preview)
{
    if (ball_accel == 0) ball_accel = ball_accel_preview;
    
    DrawTexture(empty_texture, 0, GetScreenHeight() - empty_texture.height, WHITE);
    Rectangle src = {0, 0, (ball_accel * (float) colors_texture.width), (float) colors_texture.height};
    Vector2 origin = {0, (float) GetScreenHeight() - colors_texture.height};
    DrawTextureRec(colors_texture, src, origin, WHITE);
}

void PowerBar::setEmptyTexture(Texture tex)
{
    empty_texture = tex;
}

void PowerBar::setColorsTexture(Texture tex)
{
    colors_texture = tex;
}

int PowerBar::getHeight()
{
    return empty_texture.height;
}