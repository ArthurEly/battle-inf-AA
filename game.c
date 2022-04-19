#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"
#include "mapa.h"

#define NRO_INIMIGOS 1
#define NRO_PROJETEIS 100

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

void SetActiveScreen(int screen_id);

extern Texture2D escudo;
extern Texture2D g_textura_jogador;
extern Texture2D g_textura_inimigo_patrulha;
extern Texture2D g_textura_inimigo_perseguicao;

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

PROJETIL projeteis[NRO_PROJETEIS]={0};
int contador_projeteis= 0;

int mapa[MAPA_LINHAS][MAPA_COLUNAS] = {
    //8-> borda lateral
    //9-> borda superior/inferior
    {8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,8},
    {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,8},
    {8,1,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,8},
    {8,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,1,0,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,0,0,0,0,8},
    {8,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1,0,0,0,0,1,0,8},
    {8,1,0,1,0,1,1,1,0,1,1,1,1,0,1,1,1,0,0,1,1,0,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,8},
    {8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,8}
};
BLOCO blocos[MAPA_LINHAS][MAPA_COLUNAS] = {0};

//alterar os DOIS valores
Rectangle tanque_textura_R = {0,0,35/2,35/2};
const float altura_tanques_local = 35;
const float largura_tanques_local = 35;

JOGADOR jogador = {
        .jogador_R.x = 1100,
        .jogador_R.y = 400,
        .jogador_R.height = 35, //aqui tamb�m
        .jogador_R.width = 35, //aqui tamb�m
        .vidas = 3,
        .pontuacao = 0,
        .angulo = 0,
        .vel = {0,0},
        .multiplicador_vel = 1,
//     .cor =  WHITE,
        .origem_textura={0,0}
};

int tanques_posicionados=0;

void DrawGameplayScreen(){
    ClearBackground(RAYWHITE);
    int i,j,k;
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
    for(i=0; i<vidas; i++){
        DrawTextureEx(escudo, (Vector2){i*65, 0}, 0, 0.11, WHITE);
    }

    //if(segundos % 1 == 0 && timer_segundos == 0){
        if(contador_inimigos < NRO_INIMIGOS){
            criarNovoInimigo(blocos, &inimigos[contador_inimigos],altura_tanques_local,largura_tanques_local);
            contador_inimigos++;
        }else{
            for(i=0; i<NRO_INIMIGOS; i++){
                if (inimigos[i].vidas == 0){
                    criarNovoInimigo(blocos, &inimigos[i],altura_tanques_local,largura_tanques_local);
                }
            }
         }

    //}

    if(!tanques_posicionados){
        for(i=0; i<MAPA_LINHAS; i++){
            for(j=0; j<MAPA_COLUNAS; j++){
                posicionarJogador(mapa[i][j],&jogador,i,j);
            }
        }
        tanques_posicionados = 1;
    }

    for(i=0;i<contador_inimigos;i++){
        if(inimigos[i].vidas !=0){
            int contador_colisao_inimigo = 0;

            for(j=0; j<MAPA_LINHAS; j++){
                for(k=0; k<MAPA_COLUNAS; k++){
                    if (blocos[j][k].tipo != 0){
                        if(checarColisaoInimigoEBloquinho(&inimigos[i].inimigo_R, &blocos[j][k].bloco_R)){
                            contador_colisao_inimigo++;
                        }
                    }
                }
            }

            if (contador_colisao_inimigo > 0){
                girarSentidoHorario(&inimigos[i]);
                inimigos[i].colidindo = true;
            } else {
                inimigos[i].colidindo = false;
            }


            movimentarInimigos(&jogador, &inimigos[i]);
        }

        Texture2D tanque_inimigo_textura;

        if(inimigos[i].emMovimento == 2){
            tanque_inimigo_textura = g_textura_inimigo_perseguicao;

            if(contador_projeteis < NRO_PROJETEIS)
                contador_projeteis++;
            else
                contador_projeteis = 0;

            atirarProjetilInimigo(&projeteis[contador_projeteis],inimigos[i]);
        }
        else{
            tanque_inimigo_textura = g_textura_inimigo_patrulha;
        }

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
            if(jogador.colidindo == false){
                movimentacaoJogador(&jogador);
            }
    }

    for(i=0; i<contador_inimigos; i++){
        if (checarColisaoJogadorEInimigo(&jogador.jogador_R, &inimigos[i].inimigo_R)){
            removerInimigo(inimigos,i);
            if (jogador.vidas > 0){
                jogador.vidas--;
            }
        }
    }

    int contador_colisoes = 0;
    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            if (blocos[i][j].tipo != 0){
                if(checarColisaoJogadorEBloquinho(&jogador.jogador_R, &blocos[i][j].bloco_R)){
                    contador_colisoes++;
                }
            }
        }
    }

    if(contador_colisoes > 0)
        pararJogador(&jogador);
    else
        retomarJogador(&jogador);

    if(IsKeyPressed(KEY_SPACE)){
        if(contador_projeteis < NRO_PROJETEIS)
            contador_projeteis++;
        else
            contador_projeteis = 0;
        atirarProjetilJogador(&projeteis[contador_projeteis],jogador);
    }

    for(i=0; i<NRO_PROJETEIS; i++){
        if (projeteis[i].em_movimento == 1){
            movimentarProjeteis(&projeteis[i]);
            renderizarProjeteis(&projeteis[i]);

            for(j=0; j<contador_inimigos; j++){
                if(projeteis[i].tanque_de_origem == 'j'){
                    if (checarColisaoProjeteisEInimigo(&projeteis[i], &inimigos[j])){
                        removerInimigo(inimigos,j);
                        removerProjetil(projeteis,i);
                        jogador.pontuacao += 800;
                    }
                } else{
                    if (checarColisaoProjeteisEJogador(&projeteis[i], &jogador)){
                        removerProjetil(projeteis,i);
                        jogador.vidas--;
                        printf("vose moreu\n");
                    }
                }
            }

            for(j=0; j<MAPA_LINHAS; j++){
                for(k=0; k<MAPA_COLUNAS; k++){
                    if(blocos[j][k].tipo == 1 || blocos[j][k].tipo == 8 || blocos[j][k].tipo == 9){
                        if (checarColisaoProjeteisEBlocos(&projeteis[i], &blocos[j][k])){
                            if(blocos[j][k].destrutivel){
                                removerBloquinho(&blocos[j][k]);
                            }
                            removerProjetil(projeteis,i);
                        }
                    }
                }
            }

            for(j=i+1; j<NRO_PROJETEIS; j++){
                if (projeteis[j].em_movimento == 1){
                    if(checarColisaoDeProjeteis(&projeteis[i],&projeteis[j])){
                        removerProjetil(projeteis,i);
                        removerProjetil(projeteis,j);
                    }
                }
            }
        }
    }

    atualizarMapa(mapa,blocos);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(111);
    }
}
