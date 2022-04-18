#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "construcao.h"

void renderizarBloquinho(BLOCO bloco){
    DrawRectangle(
        bloco.bloco_R.x,
        bloco.bloco_R.y,
        bloco.bloco_R.width,
        bloco.bloco_R.height,
        bloco.cor
    );
}
