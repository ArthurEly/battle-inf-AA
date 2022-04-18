#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"
#include "mapa.h"

#define NRO_INIMIGOS 8

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

void SetActiveScreen(int screen_id);

extern Texture2D escudo;
extern Texture2D g_textura_jogador;
extern Texture2D g_textura_inimigo_patrulha;
extern Texture2D g_textura_inimigo_perseguicao;
extern const int g_altura_tanques;
extern const int g_largura_tanques;

float timer_segundos = 0;
int segundos = 0;
void timerSegundos(){
    timer_segundos += 0.0166666666666667;
    if(timer_segundos > 1){
        segundos++;
        timer_segundos = 0;
    }
}

int contador_inimigos = 0;

INIMIGO inimigos[NRO_INIMIGOS]={0};

PROJETIL projeteis[10]={0};
int contador_projeteis= 0;

int mapa[MAPA_LINHAS][MAPA_COLUNAS] = {
    //8-> borda lateral
    //9-> borda superior/inferior

    {8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,8}
};
BLOCO blocos[MAPA_LINHAS][MAPA_COLUNAS] = {0};

//alterar os DOIS valores
Rectangle tanque_textura_R = {0,0,40/2,40/2};
const int local_altura_tanques = 40;
const int local_largura_tanques = 40;

JOGADOR jogador = {
        .jogador_R.x = 500,
        .jogador_R.y = 400,
        .jogador_R.height = 40,
        .jogador_R.width = 40,
        .ponto_de_colisao.x = 500,
        .ponto_de_colisao.y = 400,
        .ponto_de_colisao.height = 5,
        .ponto_de_colisao.width = 5,
        .vidas = 3,
        .pontuacao = 0,
        .angulo = 0,
        .vel = {0,0},
        .multiplicador_vel = 1,
//     .cor =  WHITE,
        .origem_textura={0,0}
};

void DrawGameplayScreen(){
    ClearBackground(RAYWHITE);
    int i,j;
    int vidas=jogador.vidas;
    timerSegundos();
    int fase=1;

    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            transcreverMapa(&mapa[i][j],i,j,(MAPA_LINHAS-1),(MAPA_COLUNAS-1),blocos);
            renderizarBloquinho(blocos[i][j]);
        }
    }

    DrawText(TextFormat("Fase: %i", fase), 600, 20, 48, ORANGE);
    DrawText(TextFormat("Pontuacao: %i", jogador.pontuacao), 250, 30, 36, DARKGRAY);
    for(int i; i<vidas; i++){
        DrawTextureEx(escudo, (Vector2){i*65, 0}, 0, 0.11, WHITE);
    }


    //if(segundos % 2 == 0 && timer_segundos == 0){
    if(contador_inimigos < NRO_INIMIGOS){
        criarNovoInimigo(&inimigos[contador_inimigos],local_altura_tanques,local_largura_tanques);
        contador_inimigos++;
    }else{
        for(i=0; i<NRO_INIMIGOS; i++){
            if (inimigos[i].vidas == 0){
                criarNovoInimigo(&inimigos[i],local_altura_tanques,local_largura_tanques);
            }
        }
    }
    //}

    for(i=0;i<contador_inimigos;i++){
        if(inimigos[i].vidas !=0){
            movimentarInimigos(&jogador, &inimigos[i]);
        }

        Texture2D tanque_inimigo_textura;

        if(inimigos[i].emMovimento == 2)
            tanque_inimigo_textura = g_textura_inimigo_perseguicao;
        else
            tanque_inimigo_textura = g_textura_inimigo_patrulha;


        DrawRectangle(
            inimigos[i].inimigo_R.x,
            inimigos[i].inimigo_R.y,
            inimigos[i].inimigo_R.height,
            inimigos[i].inimigo_R.width,
            DARKGREEN
        );

        DrawTexturePro(
            tanque_inimigo_textura,
            tanque_textura_R,
            inimigos[i].inimigo_R,
            inimigos[i].origem_textura,
            inimigos[i].angulo,
            inimigos[i].cor
        );
    }

    DrawRectangle(
        jogador.jogador_R.x,
        jogador.jogador_R.y,
        jogador.jogador_R.height,
        jogador.jogador_R.width,
        SKYBLUE
    );

    DrawRectangle(
        jogador.ponto_de_colisao.x,
        jogador.ponto_de_colisao.y,
        jogador.ponto_de_colisao.height,
        jogador.ponto_de_colisao.width,
        GRAY
    );

    DrawTexturePro(
        g_textura_jogador,
        tanque_textura_R,
        jogador.jogador_R,
        jogador.origem_textura,
        jogador.angulo,
        WHITE
    );

    if (IsKeyDown(KEY_LEFT) ||
        IsKeyDown(KEY_RIGHT)||
        IsKeyDown(KEY_DOWN) ||
        IsKeyDown(KEY_UP)   ){
            movimentacaoJogador(&jogador);
    }

    for(i=0; i<contador_inimigos; i++){
        if (checarColisaoJogadorEInimigo(&jogador.jogador_R, &inimigos[i].inimigo_R)){
            removerInimigo(inimigos,i);
            if (jogador.vidas > 0){
                jogador.vidas--;
            }
        }
    }

    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            if (blocos[i][j].tipo != 0){
                //parei aqui
                if(checarColisaoJogadorEBloquinho(&jogador.ponto_de_colisao, &blocos[i][j].bloco_R)){
                    pararJogador(&jogador);
                }
                else if(!checarColisaoJogadorEBloquinho(&jogador.ponto_de_colisao, &blocos[i][j].bloco_R)){
                    retomarJogador(&jogador);
                }
            }
        }
    }

    if(IsKeyPressed(KEY_SPACE)){
        if(contador_projeteis < 10){
            contador_projeteis++;
        } else{
            contador_projeteis = 0;
        }
        atirarProjetil(&projeteis[contador_projeteis],jogador);
    }

    for(i=0; i<10; i++){
        if (projeteis[i].em_movimento == 1){
            movimentarProjeteis(&projeteis[i]);
            renderizarProjeteis(&projeteis[i]);

            for(j=0; j<contador_inimigos; j++){
                if (checarColisaoProjeteis(&projeteis[i], &inimigos[j])){
                    removerInimigo(inimigos,j);
                    removerProjetil(projeteis,i);
                    jogador.pontuacao += 800;
                }
            }
        }
    }

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(111);
    }
}
