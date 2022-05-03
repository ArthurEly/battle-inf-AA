#ifndef EXPLOSOES_H_INCLUDED
#define EXPLOSOES_H_INCLUDED
#include "game.h"

typedef struct explosao{
    Rectangle explosao_R;
    bool ativa;
    int frames;
    int currentFrame;
    int currentLine;
    Texture2D textura;
}EXPLOSAO;

void criarExplosao(EXPLOSAO *explosao, Rectangle base_R, Texture textura);
void renderizarExplosoes(EXPLOSAO *explosao);
#endif


