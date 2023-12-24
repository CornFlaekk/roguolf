#include <raylib.h>
#include "Ball.h"

Color dark_blue = {44, 44, 127, 255};
int screen_width = 854;
int screen_height = 480;

Ball ball;
Texture bgTexture;

void init();
void loadTextures();

int main()
{
    init();
    loadTextures();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();    
        ClearBackground(dark_blue);
        DrawTexture(bgTexture, 0, 0, WHITE);
        
        ball.update();
        ball.draw();

        DrawFPS(0,0);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void init()
{
    InitWindow(screen_width, screen_height, "RoGolf");
    SetTargetFPS(60);
}

void loadTextures()
{
    Image image = LoadImage("images/ball_medium.png");
    Texture ball_tex = LoadTextureFromImage(image);
    ball.setTexture(ball_tex);

    image = LoadImage("images/background.png");
    bgTexture = LoadTextureFromImage(image); 

    UnloadImage(image);
}