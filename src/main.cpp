#include <raylib.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "Ball.h"
#include "PowerBar.h"
#include "Obstacle.h"
#include "Enemy.h"

bool debug = true;

Color dark_blue = {44, 44, 127, 255};
int screen_width = 854;
int screen_height = 480;

Ball ball;
bool collided = false;
Texture bgTexture;
PowerBar powerBar;

//Obstacles
Obstacle rockVertical;
Obstacle block2x2Blue;
Obstacle block1x2Blue;
Obstacle block1x1Blue;

//Enemies
Enemy tigerWoods1x;
Enemy tigerWoods2x;
Enemy tigerWoods3x;
Enemy tigerWoods4x;


void init();
void loadTextures();
void loadParameters();
void loadObstacles();
void loadEnemies();
void checkColissions();
bool checkObstacleCollisions(Obstacle obs);
bool checkEnemyCollisions(Enemy enemy);
void manageBallCollision(Rectangle collision);

int main()
{
    init();
    loadTextures();
    loadParameters();
    loadObstacles();
    loadEnemies();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();    
        ClearBackground(dark_blue);
        DrawTexture(bgTexture, 0, 0, WHITE);

        checkColissions();
        
        ball.update();
        ball.draw();
        float accel_preview = ball.getPreviewAccel();
        float accel = ball.getAccel();

        rockVertical.draw();
        block2x2Blue.draw();
        block1x2Blue.draw();
        block1x1Blue.draw();

        tigerWoods1x.draw();
        tigerWoods2x.draw();
        tigerWoods3x.draw();
        tigerWoods4x.draw();

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

    image = LoadImage("images/obstacle_rock_vertical.png");
    texture = LoadTextureFromImage(image);
    rockVertical.setTexture(texture);
    rockVertical.setTextureCollisionRectangle((Rectangle) {0, 0, (float) texture.width, (float) texture.height});

    image = LoadImage("images/block_2x2_blue.png");
    texture = LoadTextureFromImage(image);
    block2x2Blue.setTexture(texture);
    block2x2Blue.setTextureCollisionRectangle((Rectangle) {0, 0, (float) texture.width, (float) texture.height});

    image = LoadImage("images/block_1x2_blue.png");
    texture = LoadTextureFromImage(image);
    block1x2Blue.setTexture(texture);
    block1x2Blue.setTextureCollisionRectangle((Rectangle) {0, 0, (float) texture.width, (float) texture.height});

    image = LoadImage("images/block_1x1_blue.png");
    texture = LoadTextureFromImage(image);
    block1x1Blue.setTexture(texture);
    block1x1Blue.setTextureCollisionRectangle((Rectangle) {0, 0, (float) texture.width, (float) texture.height});

    image = LoadImage("images/tiger_woods_1x.png");
    texture = LoadTextureFromImage(image);
    tigerWoods1x.setTexture(texture);
    tigerWoods1x.setTextureCollisionRectangle((Rectangle) {0, 0, (float) texture.width, (float) texture.height});

    image = LoadImage("images/tiger_woods_2x.png");
    texture = LoadTextureFromImage(image);
    tigerWoods2x.setTexture(texture);
    tigerWoods2x.setTextureCollisionRectangle((Rectangle) {0, 0, (float) texture.width, (float) texture.height});

    image = LoadImage("images/tiger_woods_3x.png");
    texture = LoadTextureFromImage(image);
    tigerWoods3x.setTexture(texture);
    tigerWoods3x.setTextureCollisionRectangle((Rectangle) {0, 0, (float) texture.width, (float) texture.height});

    image = LoadImage("images/tiger_woods_4x.png");
    texture = LoadTextureFromImage(image);
    tigerWoods4x.setTexture(texture);
    tigerWoods4x.setTextureCollisionRectangle((Rectangle) {0, 0, (float) texture.width, (float) texture.height});

    UnloadImage(image);
}

void loadParameters()
{
    ball.setPowerBarHeight(powerBar.getHeight());
    ball.setMaxAccel();
}

void loadObstacles()
{
    block2x2Blue.setPosition(100, GetScreenHeight() - (96+32));

    block1x2Blue.setPosition(600, 300);

    block1x1Blue.setPosition(100, 100);
}

void loadEnemies()
{
    tigerWoods3x.setPosition(700, 200);
    tigerWoods3x.setLife(2);
}

void checkColissions()
{
    if (collided)
    {
        collided = false;
        return;
    }
    
    collided = checkObstacleCollisions(rockVertical);
    collided = checkObstacleCollisions(block2x2Blue);
    collided = checkObstacleCollisions(block1x2Blue);
    collided = checkObstacleCollisions(block1x1Blue);

    collided = checkEnemyCollisions(tigerWoods3x);

}

bool checkObstacleCollisions(Obstacle obs)
{
    std::vector<Rectangle> collisions = obs.getOnScreenCollisionRectangles();
    if(collisions.size() == 0)
        return false;
    
    for(Rectangle coll : collisions)
    {
        if(CheckCollisionCircleRec(ball.getCenter(), ball.radius, coll))
        {
            //if(debug) std::cout << "COLLISION - RADIUS(" << ball.radius << ") - RECTANGLE(()" << coll.x << "," << coll.y << ")-()" << coll.x + coll.width << "," << coll.y + coll.height << "))" <<  std::endl;            
            manageBallCollision(coll);
            return true;
        }
    }
    return false;
}

bool checkEnemyCollisions(Enemy enemy)
{
    std::vector<Rectangle> collisions = enemy.getOnScreenCollisionRectangles();
    if(collisions.size() == 0)
        return false;
    
    for(Rectangle coll : collisions)
    {
        if(CheckCollisionCircleRec(ball.getCenter(), ball.radius, coll))
        {
            //if(debug) std::cout << "COLLISION - RADIUS(" << ball.radius << ") - RECTANGLE(()" << coll.x << "," << coll.y << ")-()" << coll.x + coll.width << "," << coll.y + coll.height << "))" <<  std::endl;            
            enemy.hit(ball.getDamage());
            manageBallCollision(coll);
            return true;
        }
    }
    return false;
}

void manageBallCollision(Rectangle collision)
{
    if(CheckCollisionPointRec((Vector2) {(float) ball.getCenter().x + ball.radius, ball.getCenter().y}, collision)
        || CheckCollisionPointRec((Vector2) {(float) ball.getCenter().x - ball.radius, ball.getCenter().y}, collision))
    {
        ball.invertAccelX();
    }

    else if(CheckCollisionPointRec((Vector2) {(float) ball.getCenter().x, ball.getCenter().y + ball.radius}, collision)
        || CheckCollisionPointRec((Vector2) {(float) ball.getCenter().x , ball.getCenter().y - ball.radius}, collision))
    {
        ball.invertAccelY();
    }
}