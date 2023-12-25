#include <raylib.h>
#include <iostream>

#include "Ball.h"
#include "PowerBar.h"

Color dark_blue = {44, 44, 127, 255};
int screen_width = 854;
int screen_height = 480;

Ball ball;
Texture bgTexture;
PowerBar powerBar;

void init();
void loadTextures();
void loadParameters();

int main()
{
    init();
    loadTextures();
    loadParameters();
    std::cout << powerBar.getHeight() << "\n";

    while(WindowShouldClose() == false)
    {
        BeginDrawing();    
        ClearBackground(dark_blue);
        DrawTexture(bgTexture, 0, 0, WHITE);
        
        ball.update();
        ball.draw();
        float accel_preview = ball.getPreviewAccel();
        float accel = ball.getAccel();

        powerBar.draw(accel, accel_preview);

        DrawFPS(0,0);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void init()
{
    InitWindow(screen_width, screen_height, "RoGuolf");
    SetTargetFPS(60);
}

void loadTextures()
{
    Image image = LoadImage("images/ball_medium.png");
    Texture texture = LoadTextureFromImage(image);
    ball.setTexture(texture);

    image = LoadImage("images/background.png");
    bgTexture = LoadTextureFromImage(image); 

    image = LoadImage("images/power_bar_empty.png");
    texture = LoadTextureFromImage(image);
    powerBar.setEmptyTexture(texture);

    image = LoadImage("images/power_bar_colors.png");
    texture = LoadTextureFromImage(image);
    powerBar.setColorsTexture(texture);

    UnloadImage(image);
}

void loadParameters()
{
    ball.setPowerBarHeight(powerBar.getHeight());
    ball.setMaxAccel();
}