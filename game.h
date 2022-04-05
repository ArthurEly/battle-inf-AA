#include "raylib.h"
#include "stdio.h"

Vector2 ballPosition = { (float)1000/2, (float)800/2 };
Vector2 ballSize = { 100, 100 };

void DrawGameplayScreen(){
    Texture2D tank = LoadTexture("assets/tank.png");

    if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
    if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;

    ClearBackground(RAYWHITE);

    DrawTexture(tank, 15, 40, WHITE);
    DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

    DrawRectangleV(ballPosition, ballSize, GREEN);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(111);
    }
}
