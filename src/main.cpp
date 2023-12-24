#include <raylib.h>
#include "Ball.h"

Color dark_blue = {44, 44, 127, 255};
int screen_width = 640;
int screen_height = 480;

Ball ball;

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
        
        ball.update();
        ball.draw();

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
    Image image = LoadImage("images/ball.png");
    Texture ball_tex = LoadTextureFromImage(image);
    ball.setTexture(ball_tex);

    UnloadImage(image);
}