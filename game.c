#include "game.h"
#include "raylib.h"
#include "stdio.h"
void SetActiveScreen(int screen_id);
extern Texture2D g_tank_texture;

Vector2 playerPosition = { (float)1000/2, (float)800/2 };
float playerAngle = 0;

Rectangle playerTextutre = { 0, 0, 100, 100};
Rectangle playerRectangle = { 1000/2.0f, 800/2.0f, 100*2.0f, 100*2.0f };
Vector2 origin = { 100, 100};
float angle = 0;

void DrawGameplayScreen(){

    if (IsKeyDown(KEY_RIGHT)){
        playerRectangle.x += 2.0f;
        angle=90;
    }

    if (IsKeyDown(KEY_LEFT)){
        playerRectangle.x -= 2.0f;
        angle=270;
    }

    if (IsKeyDown(KEY_DOWN)){
        playerRectangle.y += 2.0f;
        angle=180;
    }

    if (IsKeyDown(KEY_UP)){
        playerRectangle.y -= 2.0f;
        angle=0;
    }


    printf("aang %.0f\n",angle);
    ClearBackground(RAYWHITE);

    DrawTexturePro(
                g_tank_texture,
                playerTextutre,
                playerRectangle,
                origin,
                angle,
                WHITE
    );

    DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(111);
    }
}
