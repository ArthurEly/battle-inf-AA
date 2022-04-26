#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"
#include "mapa.h"
#include "cel_energia.h"
#include "string.h"

#define NRO_INIMIGOS 5
#define TEMPO_DE_SPAWN_INIMIGOS 1
#define NRO_PROJETEIS 100
#define NRO_CELS_ENERGIA 3

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

#define TAMANHO_TANQUES 35

#define FALSE 0
#define TRUE 1

typedef struct game{
    JOGADOR jogador;
    INIMIGO inimigos[NRO_INIMIGOS];
    PROJETIL projeteis[NRO_PROJETEIS];
    CELULA cels_energia[NRO_CELS_ENERGIA];
    BLOCO blocos[MAPA_LINHAS][MAPA_COLUNAS];
    int mapa[MAPA_LINHAS][MAPA_COLUNAS];
    int segundos;
    int contador_inimigos;
    int contador_projeteis;
    int contador_cels_energia;
    int contador_interno_cel_energia;
    int fase;
}GAME;

void SetActiveScreen(int screen_id);

extern Texture2D energia;
extern Texture2D tijolo;
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
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,8}
};
int mapa_carregado = FALSE;
BLOCO blocos[MAPA_LINHAS][MAPA_COLUNAS] = {0};

Rectangle tanque_textura_R = {0,0,TAMANHO_TANQUES/2,TAMANHO_TANQUES/2};
Rectangle energia_textura = {0,0, 25, 25};

JOGADOR jogador = {
        .jogador_R.x = 1100,
        .jogador_R.y = 0,
        .jogador_R.height = TAMANHO_TANQUES, //aqui também
        .jogador_R.width = TAMANHO_TANQUES, //aqui também
        .vidas = 3,
        .pontuacao = 0,
        .angulo = 0,
        .vel = {0,0},
        .multiplicador_vel = 1,
        .cor =  {255, 255, 255, 255},
        .origem_textura={0,0},
        .abates = 0,
};
int jogador_posicionado = FALSE;

CELULA cels_energia[NRO_CELS_ENERGIA]={0};
int contador_cels_energia = 0;
int altura_cel_energia = 35;
int largura_cel_energia = 35;
int contador_interno_cel_energia = 0;

GAME jogo;
int jogo_carregado = FALSE;
int fase = 1;

void DrawGameplayScreen(int cod_game){
    ClearBackground(RAYWHITE);
    int i,j,k;
    timerSegundos();
    /**
        MAPA
    */
    if (cod_game == 1 && !jogo_carregado){
        carregarJogoSalvo();
        jogo_carregado = TRUE;
        mapa_carregado = TRUE;
    }

    if (jogador.abates == 5 && fase != 2){
        printf("TA MALUUUUUUUUUUUUUUUUUUUUUUUUUCO");
        mapa_carregado = FALSE;
        fase++;
    }

    char nivel = fase+'0';
    if (!mapa_carregado){
        resetarJogo();
        jogador_posicionado = FALSE;
        FILE *nivel_fp;

        char nome_nivel[10] = {"nivelx.txt"};
        nome_nivel[5] = nivel;

        nivel_fp = fopen(nome_nivel,"rb");

        if (nivel_fp != NULL){
            carregarMapa(mapa,nivel_fp);
        }else{
            printf("Erro na abertura do arquivo %s",nome_nivel);
        }

        mapa_carregado = TRUE;
    }

    if(!jogador_posicionado){
        for(i=0; i<MAPA_LINHAS; i++){
            for(j=0; j<MAPA_COLUNAS; j++){
                if (mapa[i][j] == 10){
                    posicionarJogador(mapa[i][j],&jogador,i,j);
                }
            }
        }
        jogador_posicionado = TRUE;
    }

    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            transcreverMapa(&mapa[i][j],i,j,(MAPA_LINHAS-1),(MAPA_COLUNAS-1),blocos);
            renderizarBloquinho(blocos[i][j]);
        }
    }

    DrawText(TextFormat("Fase: %i", fase), 600, 20, 48, ORANGE);
    DrawText(TextFormat("Pontuacao: %i", jogador.pontuacao), 250, 30, 36, DARKGRAY);
    for(i=0; i<jogador.vidas; i++){
        DrawTextureEx(escudo, (Vector2){i*65, 0}, 0, 0.11, WHITE);
    }

    /**
        INIMIGOS
    */
    if(contador_inimigos < NRO_INIMIGOS){
        //if(segundos % TEMPO_DE_SPAWN_INIMIGOS == 0 && timer_segundos == 0){
            criarNovoInimigo(mapa, blocos, &inimigos[contador_inimigos],TAMANHO_TANQUES,TAMANHO_TANQUES);
            contador_inimigos++;
        //}
    }else{
        //if(segundos % TEMPO_DE_SPAWN_INIMIGOS == 0 && timer_segundos == 0){
            bool nao_reviveu_inimigo = true;
            for(i=0;i<contador_inimigos;i++){
                if(inimigos[i].vidas == 0 && nao_reviveu_inimigo){
                    criarNovoInimigo(mapa, blocos, &inimigos[i],TAMANHO_TANQUES,TAMANHO_TANQUES);
                    nao_reviveu_inimigo = false;
                }
            }
        //}
    }

    for(i=0;i<contador_inimigos;i++){
        if(inimigos[i].vidas == 1){
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

            //COLISAO INIMIGOS
            for(j=0; j<contador_inimigos; j++){
                if (i != j){
                    if(checarColisaoEntreInimigos(&inimigos[i].inimigo_R, &inimigos[j].inimigo_R)){
                        colidirInimigos(&inimigos[i], &inimigos[j]);
                    }
                }
            }

            movimentarInimigos(mapa,&jogador, &inimigos[i]);


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
    }
    /**
        JOGADOR
    */
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
        jogador.cor
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
        if(contador_projeteis < NRO_PROJETEIS){
            contador_projeteis++;
        }
        else{
            contador_projeteis = 0;
        }
        atirarProjetilJogador(&projeteis[contador_projeteis],jogador);
    }
    /**
        PROJETEIS
    */
    for(i=0; i<NRO_PROJETEIS; i++){
        if (projeteis[i].em_movimento == 1){
            movimentarProjeteis(&projeteis[i]);
            renderizarProjeteis(&projeteis[i]);

            for(j=0; j<contador_inimigos; j++){
                if (checarColisaoProjeteisEInimigo(&projeteis[i], &inimigos[j])){
                    if(projeteis[i].tanque_de_origem == 'j'){
                        jogador.abates++;
                        removerInimigo(inimigos,j);
                        removerProjetil(projeteis,i);
                        jogador.pontuacao += 800;
                    }
                }
            }

            if (checarColisaoProjeteisEJogador(&projeteis[i], &jogador)){
                if(projeteis[i].tanque_de_origem == 'i'){
                    removerProjetil(projeteis,i);
                    jogador.vidas--;
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
    /**
        CELULAS DE ENERGIA
    */
    if(contador_cels_energia < NRO_CELS_ENERGIA){
        if(segundos % 1 == 0 && timer_segundos == 0){
            criarCelulaDeEnergia(mapa, blocos, &cels_energia[contador_cels_energia],altura_cel_energia,largura_cel_energia);
            contador_cels_energia++;
        }
    }else{
        if(segundos % 1 == 0 && timer_segundos == 0){
            for(i=0; i<NRO_CELS_ENERGIA; i++){
                if (cels_energia[i].ativa == false){
                    criarCelulaDeEnergia(mapa, blocos, &cels_energia[i],altura_cel_energia,largura_cel_energia);
                }
            }
        }
    }

    for(i=0; i<NRO_CELS_ENERGIA; i++){
        if(cels_energia[i].ativa == true){
            DrawRectangle(
                cels_energia[i].cel_energia_R.x,
                cels_energia[i].cel_energia_R.y,
                cels_energia[i].cel_energia_R.width,
                cels_energia[i].cel_energia_R.height,
                YELLOW
            );
            DrawTexturePro(
            energia,
            energia_textura,
            cels_energia[i].cel_energia_R,
            cels_energia[i].origem_textura,
            0,
            cels_energia[i].cor
         );

            if (checarColisaoJogadorECelEnergia(&jogador.jogador_R, &cels_energia[i].cel_energia_R)){
                if (contador_interno_cel_energia < 20){
                    contador_interno_cel_energia += 10;
                }
                energizarJogador(&jogador,&cels_energia[i]);
                removerCelEnergia(&cels_energia[i]);
            }
        }
    }

    if (jogador.energizado == true){
        if(segundos % 1 == 0 && timer_segundos == 0){
            contador_interno_cel_energia--;
            if(contador_interno_cel_energia == 0){
                jogador.energizado = false;
                jogador.multiplicador_vel = 1;
                jogador.cor = WHITE;

            }
        }
        if (timer_segundos>0 && timer_segundos < 0.5){
                jogador.cor = YELLOW;
            }else if(timer_segundos>0.5){
                jogador.cor = WHITE;
            }
    }
    /**
        MAPA DNV
    */
    atualizarMapa(mapa,blocos,jogador,inimigos,contador_inimigos);

    //qause funcao de salvar
    if(IsKeyPressed(KEY_S)){
        salvarJogo();
    }

    if(IsKeyPressed(KEY_C)){
        carregarJogoSalvo();
    }

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(111);
    }
}

void salvarJogo(){
    FILE *save_fp;
    GAME jogo_salvo;
    save_fp = fopen("ultimo-save.bin","wb+");
    jogo_salvo.jogador = jogador;
    memcpy(jogo_salvo.inimigos, inimigos, sizeof(inimigos));
    memcpy(jogo_salvo.projeteis, projeteis, sizeof(projeteis));
    memcpy(jogo_salvo.cels_energia, cels_energia, sizeof(cels_energia));
    memcpy(jogo_salvo.blocos, blocos, sizeof(blocos));
    memcpy(jogo_salvo.mapa, mapa, sizeof(mapa));
    jogo_salvo.segundos = segundos;
    jogo_salvo.contador_inimigos = contador_inimigos;
    jogo_salvo.contador_projeteis = contador_projeteis;
    jogo_salvo.contador_cels_energia = contador_cels_energia;
    jogo_salvo.contador_interno_cel_energia = contador_interno_cel_energia;
    jogo_salvo.fase = fase;
    if (save_fp != NULL){
        fwrite(&jogo_salvo, sizeof(GAME), 1, save_fp);
        rewind(save_fp);
        GAME jooj;
        if(fread(&jooj, sizeof(GAME), 1, save_fp) == 1){
            printarMapa(jooj.mapa);
        }else{
            printf("erro na leitura do jogo salvo\n");
        }
    }
    fclose(save_fp);
}

void carregarJogoSalvo(){
    FILE *save_fp;
    save_fp = fopen("ultimo-save.bin","rb");

    if (save_fp != NULL){
        rewind(save_fp);
        GAME jooj;
        if(fread(&jooj, sizeof(GAME), 1, save_fp) == 1){
            jogador = jooj.jogador;
            memcpy(inimigos, jooj.inimigos, sizeof(inimigos));
            memcpy(projeteis, jooj.projeteis, sizeof(projeteis));
            memcpy(cels_energia, jooj.cels_energia, sizeof(cels_energia));
            memcpy(blocos, jooj.blocos, sizeof(blocos));
            memcpy(mapa, jooj.mapa, sizeof(mapa));
            segundos = jooj.segundos;
            contador_inimigos = jooj.contador_inimigos;
            contador_projeteis = jooj.contador_projeteis;
            contador_cels_energia = jooj.contador_cels_energia;
            contador_interno_cel_energia = jooj.contador_interno_cel_energia;
            fase = jooj.fase;
        }else{
            printf("erro na leitura do jogo salvo\n");
        }
    }
    fclose(save_fp);
}

void resetarJogo(){
    timer_segundos = 0;
    segundos = 0;
    contador_inimigos = 0;

    INIMIGO z_inimigos[NRO_INIMIGOS]={0};
    memcpy(inimigos, z_inimigos, sizeof(inimigos));

    PROJETIL z_projeteis[NRO_PROJETEIS]={0};
    memcpy(projeteis, z_projeteis, sizeof(inimigos));
    contador_projeteis= 0;

    BLOCO z_blocos[MAPA_LINHAS][MAPA_COLUNAS] = {0};
    memcpy(blocos, z_blocos, sizeof(inimigos));

    JOGADOR z_jogador = {
            .jogador_R.height = TAMANHO_TANQUES, //aqui também
            .jogador_R.width = TAMANHO_TANQUES, //aqui também
            .vidas = 3,
            .pontuacao = 0,
            .angulo = 0,
            .vel = {0,0},
            .multiplicador_vel = 1,
            .cor =  {255, 255, 255, 255},
            .origem_textura={0,0},
            .abates = 0,
    };
    jogador = z_jogador;

    CELULA z_cels_energia[NRO_CELS_ENERGIA]={0};
    memcpy(cels_energia, z_cels_energia, sizeof(inimigos));
    contador_cels_energia = 0;
    contador_interno_cel_energia = 0;
}

void carregarMapa(int mapa[][MAPA_COLUNAS], FILE *nivel_fp){
    int i=1;
    int j=1;
    char objeto;
    while(!feof(nivel_fp)){
        objeto = fgetc ( nivel_fp );
        if (objeto == '-'){
            mapa[i][j] = 0;
            j++;
        }

        if (objeto == '#'){
            mapa[i][j] = 1;
            j++;
        }

        if (objeto == 'T'){
            mapa[i][j] = 10;
            j++;
        }

        if(j == 40){
            j = 1;
            i++;
        }
        printf("%c",objeto);
    }
    printarMapa(mapa);
}
