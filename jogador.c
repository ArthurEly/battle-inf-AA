#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "cel_energia.h"

void movimentacaoJogador(JOGADOR *jogador){
    int velocidade = 3*jogador->multiplicador_vel;
    if (IsKeyDown(KEY_RIGHT)/* && jogador->jogador_R.x + jogador->jogador_R.width<1010*/){
        jogador->vel.vx += velocidade;
        jogador->angulo = 90;
        jogador->origem_textura.x = 0;
        jogador->origem_textura.y = jogador->jogador_R.height;
    }

    else if (IsKeyDown(KEY_LEFT)/* && jogador->jogador_R.x >10*/){
        jogador->vel.vx += (-velocidade);
        jogador->angulo = 270;
        jogador->origem_textura.x = jogador->jogador_R.width;
        jogador->origem_textura.y = 0;
    }

    else if (IsKeyDown(KEY_DOWN)/* && jogador->jogador_R.y + jogador->jogador_R.height<700*/){
        jogador->vel.vy += velocidade;
        jogador->angulo = 180;
        jogador->origem_textura.x = jogador->jogador_R.width;
        jogador->origem_textura.y = jogador->jogador_R.height;
    }

    else if (IsKeyDown(KEY_UP)/* && jogador->jogador_R.y>100*/){
        jogador->vel.vy += (-velocidade);
        jogador->angulo = 0;
        jogador->origem_textura.x = 0;
        jogador->origem_textura.y = 0;
    }

    jogador->jogador_R.x += jogador->vel.vx;
    jogador->jogador_R.y += jogador->vel.vy;

    jogador->vel.vx = 0;
    jogador->vel.vy = 0;
}

void pararJogador(JOGADOR *jogador){
    jogador->vel.vx = 0;
    jogador->vel.vy = 0;
    jogador->colidindo=true;

    if(jogador->angulo == 0){
        jogador->jogador_R.y = jogador->jogador_R.y+0.5;
    }

    if(jogador->angulo == 90){
        jogador->jogador_R.x = jogador->jogador_R.x-0.5;
    }

    if(jogador->angulo == 180){
        jogador->jogador_R.y = jogador->jogador_R.y-0.5;
    }

    if(jogador->angulo == 270){
        jogador->jogador_R.x = jogador->jogador_R.x+0.5;
    }
}

void retomarJogador(JOGADOR *jogador){
    jogador->colidindo = false;
}

bool checarColisaoJogadorEInimigo(Rectangle *jogador_R, Rectangle *inimigo_R){
    bool colidiu = CheckCollisionRecs(*jogador_R,*inimigo_R);
    return colidiu;
}

bool checarColisaoJogadorEBloquinho(Rectangle *ponto_de_colisao, Rectangle *bloco_R){
    bool colidiu = CheckCollisionRecs(*ponto_de_colisao,*bloco_R);
    return colidiu;
}

bool checarColisaoJogadorECelEnergia(Rectangle *jogador_R, Rectangle *cel_energia_R){
    bool colidiu = CheckCollisionRecs(*jogador_R,*cel_energia_R);
    return colidiu;
}

bool checarColisaoJogadorEPassagem(Rectangle *jogador_R, Rectangle *passagem_R){
    bool colidiu = CheckCollisionRecs(*jogador_R,*passagem_R);
    return colidiu;
}
