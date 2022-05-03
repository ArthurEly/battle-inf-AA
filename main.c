#include "raylib.h"
#include "game.h"
#include "menu.h"
#include "carregar.h"
#include "highscores.h"
#include "pause_menu.h"
#include "tela_morte.h"
#include "stdio.h"
#include "string.h"

void SetActiveScreen(int screen_id);
void DrawScreen(GAME *jogo, int screen_id);
void DrawLoadMapGameplayScreen(FILE *mapa_fp);
void DrawNewGameplayScreen(GAME *jogo);
void DrawMainMenuScreen();
void timerSegundos(int *segundos, float *milisegundos);

int g_screens[7]={
        10, //Main Menu Screen
        11, //jogo
        111, //menu de pausa dentro do jogo
        112, //tela de morte
        12, //Continue Screen
        13, //Load Map Screen
        14,  //HighScore Screen
    };
int g_active_screen = 11;
const int SCREENS_QTDY = sizeof(g_screens)/sizeof(g_screens[0]);

int main(void)
{
    GAME g_jogo;
    const int screenHeight = 600 + (2*TAMANHO_BORDA_MAPA) + CABECALHO;
    const int screenWidth = 1000 + TAMANHO_LAYOUT_LATERAL;

    InitWindow(screenWidth, screenHeight, "Battle INF");
    InitAudioDevice();

    SetTargetFPS(60);
    /**
    * PLANOS DE FUNDO
    */
    g_jogo.texturas.texture = LoadTexture("assets/FUNDO JOGO.png");
    g_jogo.texturas.pause = LoadTexture("assets/Tela pause.png");
    g_jogo.texturas.highscore = LoadTexture("assets/Highscores.png");
    g_jogo.texturas.carregar = LoadTexture("assets/Carregar mapa.png");
    g_jogo.texturas.morte = LoadTexture("assets/Tela morte.png");

    g_jogo.texturas.energia = LoadTexture("assets/energy_drop.png");
    g_jogo.texturas.energia.height = ALTURA_CELS_ENERGIA;
    g_jogo.texturas.energia.width = LARGURA_CELS_ENERGIA;

    g_jogo.texturas.escudo = LoadTexture("assets/shield.png");

    g_jogo.texturas.explosa = LoadTexture("assets/explosao.png");

    g_jogo.sons.construcao = LoadSound("assets/sons/construcao.wav");
    SetSoundVolume(g_jogo.sons.construcao,0.1);

    g_jogo.sons.explosao_inimigo = LoadSound("assets/sons/explosao_inimigo.wav");
    SetSoundVolume(g_jogo.sons.explosao_inimigo,0.3);

    g_jogo.sons.hit_jogador = LoadSound("assets/sons/hit_jogador.wav");
    SetSoundVolume(g_jogo.sons.hit_jogador,0.5);

    g_jogo.sons.power_up = LoadSound("assets/sons/power_up.wav");
    SetSoundVolume(g_jogo.sons.power_up,0.5);

    g_jogo.sons.tiro = LoadSound("assets/sons/tiro.wav");
    SetSoundVolume(g_jogo.sons.tiro,0.2);

    g_jogo.texturas.tijolo = LoadTexture("assets/brick_texture2.png");
    g_jogo.texturas.tijolo.height = 25;
    g_jogo.texturas.tijolo.width = 25;

    g_jogo.fontes.fonte_legal = LoadFontEx("assets/ironmonger-fb-black.otf", 72, 0, 0);

    g_jogo.texturas.jogador = LoadTexture("assets/tanque_player.png");
    g_jogo.texturas.jogador.height = TAMANHO_TANQUES/2;
    g_jogo.texturas.jogador.width = TAMANHO_TANQUES/2;

    g_jogo.texturas.inimigo_patrulha = LoadTexture("assets/tanque_verde.png");
    g_jogo.texturas.inimigo_patrulha.height = TAMANHO_TANQUES/2;
    g_jogo.texturas.inimigo_patrulha.width = TAMANHO_TANQUES/2;

    g_jogo.texturas.inimigo_perseguicao = LoadTexture("assets/tanque_inimigo.png");
    g_jogo.texturas.inimigo_perseguicao.height = TAMANHO_TANQUES/2;
    g_jogo.texturas.inimigo_perseguicao.width = TAMANHO_TANQUES/2;


    JOGADOR jogador = {
        .jogador_R.x = 1100,
        .jogador_R.y = 0,
        .jogador_R.height = TAMANHO_TANQUES,
        .jogador_R.width = TAMANHO_TANQUES,
        .vidas = 1,
        .pontuacao = 0,
        .angulo = 0,
        .vel = {0,0},
        .multiplicador_vel = 1,
        .cor =  {255, 255, 255, 255},
        .origem_textura = {0,0},
        .abates = 0,
        .energizado = false,
        .jogador_posicionado = false,
    };

    INIMIGO inimigos[NRO_INIMIGOS]={0};
    int contador_inimigos = 0;

    PROJETIL projeteis[NRO_PROJETEIS]={0};
    int contador_projeteis= 0;

    CELULA cels_energia[NRO_CELS_ENERGIA]={0};
    int contador_cels_energia = 0;
    int contador_interno_cel_energia = 0;

    EXPLOSAO explosoes[NRO_EXPLOSOES] = {0};
    int contador_explosoes = 0;

    BLOCO blocos[MAPA_LINHAS][MAPA_COLUNAS] = {0};

    MAPA mapa;
    mapa.mapa_foi_pre_carregado = FALSE;
    mapa.mapa_carregado = FALSE;
    mapa.passagem_aberta = FALSE;
    int mapa_base[MAPA_LINHAS][MAPA_COLUNAS] = {
        //8-> borda lateral
        //9-> borda superior/inferior
        {7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,7},
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
        {7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,7},
    };
    memcpy(mapa.mapa_atual, mapa_base, sizeof(mapa_base));
    memcpy(mapa.mapa_inicial, mapa_base, sizeof(mapa_base));

    int jogo_carregado = FALSE;
    int fase = 1;

    int segundos = 0;
    float milisegundos = 0.0f;

    g_jogo.jogador = jogador;
    g_jogo.contador_inimigos = contador_inimigos;
    g_jogo.contador_projeteis = contador_projeteis;
    g_jogo.contador_cels_energia = contador_cels_energia;
    g_jogo.contador_interno_cel_energia = contador_interno_cel_energia;
    g_jogo.contador_explosoes = contador_explosoes;
    g_jogo.segundos = segundos;
    g_jogo.milisegundos = milisegundos;
    g_jogo.fase = fase;
    g_jogo.jogo_carregado = jogo_carregado;
    g_jogo.mapa = mapa;

    memcpy(g_jogo.inimigos, inimigos, sizeof(inimigos));
    memcpy(g_jogo.projeteis, projeteis, sizeof(projeteis));
    memcpy(g_jogo.cels_energia, cels_energia, sizeof(cels_energia));
    memcpy(g_jogo.blocos, blocos, sizeof(blocos));
    memcpy(g_jogo.explosoes, explosoes, sizeof(explosoes));

    //feito pra teste
    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0};
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            BeginMode2D(camera);
            DrawScreen(&g_jogo, g_active_screen);
            EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void timerSegundos(int *segundos, float *milisegundos){
    *milisegundos += 16.6666666666667;
    if(*milisegundos > 1000){
        *segundos+=1;
        *milisegundos = 0;
    }
}

void DrawScreen(GAME *jogo, int screen_id){
    switch(screen_id){
        case 10:
            DrawMainMenuScreen(jogo);
            break;

        case 110:
            DrawNewGameplayScreen(jogo);
            break;

        case 11:
            timerSegundos(&jogo->segundos, &jogo->milisegundos);
            DrawGameplayScreen(jogo);
            break;

        case 111:
            DrawPauseMenu(jogo);
            break;

        case 112:
            DrawDeathScreen(jogo);
            break;

        case 12:
            DrawSavedGameGameplayScreen(jogo);
            break;

        case 13:
            DrawCarregarScreen(jogo);
            break;

        case 14:
            DrawHighScoresScreen(jogo);
            break;

        default:
            printf("Não existe tela com esse id");
            break;
    }
}

void SetActiveScreen(int screen_id){
    int i;
    for(i=0;i<SCREENS_QTDY; i++){
        if (g_screens[i] == screen_id){
            g_active_screen = screen_id;
        }
    }
}
