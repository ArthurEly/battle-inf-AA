#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"

void movimentacaoJogador(JOGADOR *jogador){
    int velocidade = 3*jogador->multiplicador_vel;
    if (IsKeyDown(KEY_RIGHT) && jogador->jogador_R.x + jogador->jogador_R.width<1010){
        jogador->vel.vx += velocidade;
        jogador->angulo = 90;
        jogador->origem_textura.x = 0;
        jogador->origem_textura.y = jogador->jogador_R.height;
        jogador->ponto_de_colisao.x = jogador->jogador_R.x + jogador->jogador_R.width - jogador->ponto_de_colisao.width*0.35;
        jogador->ponto_de_colisao.y = jogador->jogador_R.y + jogador->jogador_R.height/2 - jogador->ponto_de_colisao.height*0.45;
    }

    else if (IsKeyDown(KEY_LEFT) && jogador->jogador_R.x >10){
        jogador->vel.vx += (-velocidade);
        jogador->angulo = 270;
        jogador->origem_textura.x = jogador->jogador_R.width;
        jogador->origem_textura.y = 0;
        jogador->ponto_de_colisao.x = jogador->jogador_R.x;
        jogador->ponto_de_colisao.y = jogador->jogador_R.y + jogador->jogador_R.height/2;
    }

    else if (IsKeyDown(KEY_DOWN) && jogador->jogador_R.y + jogador->jogador_R.height<700){
        jogador->vel.vy += velocidade;
        jogador->angulo = 180;
        jogador->origem_textura.x = jogador->jogador_R.width;
        jogador->origem_textura.y = jogador->jogador_R.height;
        jogador->ponto_de_colisao.x = jogador->jogador_R.x + jogador->jogador_R.width/2;
        jogador->ponto_de_colisao.y = jogador->jogador_R.y + jogador->jogador_R.height;
    }

    else if (IsKeyDown(KEY_UP) && jogador->jogador_R.y>100){
        jogador->vel.vy += (-velocidade);
        jogador->angulo = 0;
        jogador->origem_textura.x = 0;
        jogador->origem_textura.y = 0;
        jogador->ponto_de_colisao.x = jogador->jogador_R.x + jogador->jogador_R.width/2;
        jogador->ponto_de_colisao.y = jogador->jogador_R.y;
    }

    jogador->jogador_R.x += jogador->vel.vx;
    jogador->jogador_R.y += jogador->vel.vy;

    jogador->vel.vx = 0;
    jogador->vel.vy = 0;
}

void pararJogador(JOGADOR *jogador){
    jogador->multiplicador_vel = 0;
}

void retomarJogador(JOGADOR *jogador){
    jogador->multiplicador_vel = 1;
}

//aqui tem que ir o array de construção, projetil inimigo, e inimigos
bool checarColisaoJogadorEInimigo(Rectangle *jogador_R, Rectangle *inimigo_R){
    bool colidiu = CheckCollisionRecs(*jogador_R,*inimigo_R);
    return colidiu;
}

bool checarColisaoJogadorEBloquinho(Rectangle *ponto_de_colisao, Rectangle *bloco_R){
    bool colidiu = CheckCollisionRecs(*ponto_de_colisao,*bloco_R);
    return colidiu;
}

