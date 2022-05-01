#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "explosoes.h"

void criarExplosao(EXPLOSAO *explosao, Rectangle base_R, Texture textura){
    explosao->ativa = true;
    explosao->explosao_R.x = base_R.x - base_R.width;
    explosao->explosao_R.y = base_R.y - base_R.height;
    explosao->explosao_R.height = base_R.height;
    explosao->explosao_R.width = base_R.width;
    explosao->textura = textura;
    explosao->frames = 0;
    explosao->currentFrame = 0;
    explosao->currentLine = 0;
}

void renderizarExplosoes(EXPLOSAO *explosao){
    float frameWidth = (float)(explosao->textura.width/NUM_FRAMES_PER_LINE);
    float frameHeight = (float)(explosao->textura.height/NUM_LINES);
    Rectangle explosao_R = {0,0, frameWidth, frameHeight};

    explosao->frames++;
    if (explosao->frames > 2){
        explosao->currentFrame++;

        if (explosao->currentFrame >= NUM_FRAMES_PER_LINE){
                explosao->currentFrame = 0;
            explosao->currentLine++;

            if (explosao->currentLine >= NUM_LINES)
            {
                explosao->currentLine = 0;
                explosao->ativa = false;
            }
        }
        explosao->frames = 0;
    }
    if (explosao->currentFrame != 0 || explosao->currentLine != 0){
        explosao_R.x = frameWidth * explosao->currentFrame;
        explosao_R.y = frameHeight * explosao->currentLine;
        Vector2 posicao_explosao = {explosao->explosao_R.x, explosao->explosao_R.y};
        DrawTextureRec(explosao->textura, explosao_R, posicao_explosao, WHITE);
    }
}
