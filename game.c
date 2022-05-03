#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"
#include "mapa.h"
#include "cel_energia.h"
#include "highscores.h"
#include "string.h"


void SetActiveScreen(int screen_id);

/*da pra mudar isso dps*/
const Rectangle tanque_textura_R = {0,0,TAMANHO_TANQUES/2,TAMANHO_TANQUES/2};
const Rectangle energia_textura = {0,0, ALTURA_CELS_ENERGIA, LARGURA_CELS_ENERGIA};
const Rectangle bala_textura_R = {0,0, 35, 35};
const Rectangle bala_R = {0,0, 35, 35};

void DrawGameplayScreen(GAME *jogo){
    //printf("%d.%.2f\n",jogo->segundos, jogo->milisegundos);

    ClearBackground(RAYWHITE);
    DrawTextureEx(jogo->texturas.fundo, (Vector2){-75,0}, 0, 1, WHITE);
    Color cor_jogo_fundo = {50,50,50,255};
    DrawRectangle(TAMANHO_BORDA_MAPA,CABECALHO+TAMANHO_BORDA_MAPA,1000,600,cor_jogo_fundo);
    int i,j,k;

    if(jogo->jogador.vidas == 0){
        PlaySound(jogo->sons.explosao_inimigo);
        SetActiveScreen(112);
    }
    //tirar esse NRO_INIMIGOS != 0 depois
    if ((jogo->jogador.abates == NRO_INIMIGOS && NRO_INIMIGOS != 0) && jogo->fase != 6){
        if (!jogo->mapa.passagem_aberta){
            abrirPassagem(jogo->mapa.mapa_atual);
            jogo->mapa.passagem_aberta = TRUE;
        }else{
            for (i=0; i<MAPA_LINHAS; i++){
                if (jogo->blocos[i][MAPA_COLUNAS-1].tipo == 6){
                    if(checarColisaoJogadorEPassagem(&jogo->jogador.jogador_R, &jogo->blocos[i][MAPA_COLUNAS-1].bloco_R)){
                        jogo->fase++;
                        passarDeFase(jogo);
                    }
                }
            }
        }
    }

    if (!jogo->mapa.mapa_carregado){
        char nivel = jogo->fase+'0';
        int guardarFase = jogo->fase;
        int guardarVidas = jogo->jogador.vidas;
        int guardarPontuacao = jogo->jogador.pontuacao;
        printarMapa(jogo->mapa.mapa_inicial);
        if(!jogo->mapa.mapa_foi_pre_carregado){
            FILE *nivel_fp;
            printf("oia\n");
            char nome_nivel[17+1] = {"niveis/nivelx.txt"};
            nome_nivel[12] = nivel;

            nivel_fp = fopen(nome_nivel,"r");

            if (nivel_fp != NULL){
                carregarMapa(jogo->mapa.mapa_atual,nivel_fp);
                carregarMapa(jogo->mapa.mapa_inicial,nivel_fp);
            }else{
                perror("main Erro na abertura do arquivo");
            }
        }else{
            memcpy(jogo->mapa.mapa_atual,jogo->mapa.mapa_inicial, sizeof(jogo->mapa.mapa_atual));
        }
        reiniciarJogo(jogo);
        jogo->fase = guardarFase;
        jogo->jogador.vidas = guardarVidas;
        jogo->jogador.pontuacao = guardarPontuacao;

        jogo->mapa.mapa_carregado = TRUE;
    }

    if(!jogo->jogador.jogador_posicionado){
        for(i=0; i<MAPA_LINHAS; i++){
            for(j=0; j<MAPA_COLUNAS; j++){
                if (jogo->mapa.mapa_atual[i][j] == 10){
                    posicionarJogador(jogo->mapa.mapa_atual[i][j],&jogo->jogador,i,j);
                }
            }
        }
        jogo->jogador.jogador_posicionado = true;
    }

    /**
        MAPA
    */
    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            transcreverMapa(&jogo->mapa.mapa_atual[i][j],i,j,(MAPA_LINHAS-1),(MAPA_COLUNAS-1),jogo->blocos);
            renderizarBloquinho(&jogo->texturas,jogo->blocos[i][j]);
        }
    }
    /**
    JOGADOR
    */
    DrawTexturePro(
        jogo->texturas.jogador,
        tanque_textura_R,
        jogo->jogador.jogador_R,
        jogo->jogador.origem_textura,
        jogo->jogador.angulo,
        jogo->jogador.cor
    );

    if (IsKeyDown(KEY_LEFT) ||
        IsKeyDown(KEY_RIGHT)||
        IsKeyDown(KEY_DOWN) ||
        IsKeyDown(KEY_UP)   ){
            if(jogo->jogador.colidindo == false){
                movimentacaoJogador(&jogo->jogador);
            }
    }

    for(i=0; i<jogo->contador_inimigos; i++){
        if (checarColisaoJogadorEInimigo(&jogo->jogador.jogador_R, &jogo->inimigos[i].inimigo_R)){
            criarExplosao(&jogo->explosoes[jogo->contador_explosoes], jogo->inimigos[i].inimigo_R, jogo->texturas.explosa);
            jogo->contador_explosoes++;
            removerInimigo(jogo->inimigos,i);
            PlaySound(jogo->sons.explosao_inimigo);
            if (jogo->jogador.vidas > 0){
                PlaySound(jogo->sons.hit_jogador);
                jogo->jogador.vidas--;
            }
        }
    }

    int contador_colisoes = 0;
    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            if (jogo->blocos[i][j].tipo != 0){
                if(checarColisaoJogadorEBloquinho(&jogo->jogador.jogador_R, &jogo->blocos[i][j].bloco_R)){
                    contador_colisoes++;
                }
            }
        }
    }

    if(contador_colisoes > 0)
        pararJogador(&jogo->jogador);
    else
        retomarJogador(&jogo->jogador);

    if(IsKeyPressed(KEY_SPACE)){
        PlaySound(jogo->sons.tiro);
        if(jogo->contador_projeteis < NRO_PROJETEIS){
            jogo->contador_projeteis++;
        }
        else{
            jogo->contador_projeteis = 0;
        }
        atirarProjetilJogador(&jogo->projeteis[jogo->contador_projeteis],jogo->jogador);
    }
    /**
        INIMIGOS
    */
    if(jogo->contador_inimigos < NRO_INIMIGOS){
        if(jogo->segundos % TEMPO_DE_SPAWN_INIMIGOS == 0 && jogo->milisegundos == 0){
            criarNovoInimigo(jogo->mapa.mapa_atual, jogo->blocos, &jogo->inimigos[jogo->contador_inimigos],TAMANHO_TANQUES,TAMANHO_TANQUES);
            jogo->contador_inimigos++;
        }
    }else{
        if(jogo->segundos % TEMPO_DE_SPAWN_INIMIGOS == 0 && jogo->milisegundos == 0){
            bool nao_reviveu_inimigo = true;
            for(i=0;i<jogo->contador_inimigos;i++){
                if(jogo->inimigos[i].vidas == 0 && nao_reviveu_inimigo && !jogo->inimigos[i].abatidoPeloJogador){
                    criarNovoInimigo(jogo->mapa.mapa_atual, jogo->blocos, &jogo->inimigos[i],TAMANHO_TANQUES,TAMANHO_TANQUES);
                    nao_reviveu_inimigo = false;
                }
                else if(jogo->inimigos[i].vidas == 0 && nao_reviveu_inimigo && jogo->mapa.mapa_foi_pre_carregado){
                    criarNovoInimigo(jogo->mapa.mapa_atual, jogo->blocos, &jogo->inimigos[i],TAMANHO_TANQUES,TAMANHO_TANQUES);
                }
            }
        }
    }

    for(i=0;i<jogo->contador_inimigos;i++){
        if(jogo->inimigos[i].vidas == 1){
            int contador_colisao_inimigo = 0;

            for(j=0; j<MAPA_LINHAS; j++){
                for(k=0; k<MAPA_COLUNAS; k++){
                    if (jogo->blocos[j][k].tipo != 0){
                        if(checarColisaoInimigoEBloquinho(&jogo->inimigos[i].inimigo_R, &jogo->blocos[j][k].bloco_R)){
                            contador_colisao_inimigo++;
                        }
                    }
                }
            }

            if (contador_colisao_inimigo > 0){
                girarSentidoHorario(&jogo->inimigos[i]);
                jogo->inimigos[i].colidindo = true;
            } else {
                jogo->inimigos[i].colidindo = false;
            }

            //COLISAO INIMIGOS
            for(j=0; j<jogo->contador_inimigos; j++){
                if (i != j){
                    if(checarColisaoEntreInimigos(&jogo->inimigos[i].inimigo_R, &jogo->inimigos[j].inimigo_R)){
                        colidirInimigos(&jogo->inimigos[i], &jogo->inimigos[j]);
                    }
                }
            }

            if (jogo->inimigos[i].vidas > 0){
                movimentarInimigos(jogo->mapa.mapa_atual,&jogo->jogador, &jogo->inimigos[i]);
            }

            Texture2D tanque_inimigo_textura;

            if(jogo->inimigos[i].emMovimento == 2){
                tanque_inimigo_textura = jogo->texturas.inimigo_perseguicao;

                if(jogo->contador_projeteis < NRO_PROJETEIS){
                    jogo->contador_projeteis++;
                }
                else{
                    jogo->contador_projeteis = 0;
                }

                int atirar = GetRandomValue(0,100);
                if (atirar == 0){
                    atirarProjetilInimigo(&jogo->projeteis[jogo->contador_projeteis],jogo->inimigos[i]);
                    PlaySound(jogo->sons.tiro);
                }
            }
            else{
                tanque_inimigo_textura = jogo->texturas.inimigo_patrulha;
            }

            DrawTexturePro(
                tanque_inimigo_textura,
                tanque_textura_R,
                jogo->inimigos[i].inimigo_R,
                jogo->inimigos[i].origem_textura,
                jogo->inimigos[i].angulo,
                jogo->inimigos[i].cor
            );
        }
    }
    /**
        PROJETEIS
    */

    for(i=0; i<NRO_PROJETEIS; i++){

        if (jogo->projeteis[i].em_movimento == 1){
            movimentarProjeteis(&jogo->projeteis[i]);


            renderizarProjeteis(&jogo->projeteis[i], jogo->texturas.bala);

            for(j=0; j<jogo->contador_inimigos; j++){
                if (checarColisaoProjeteisEInimigo(&jogo->projeteis[i], &jogo->inimigos[j])){
                    if(jogo->projeteis[i].tanque_de_origem == 'j'){
                        PlaySound(jogo->sons.explosao_inimigo);
                        criarExplosao(&jogo->explosoes[jogo->contador_explosoes], jogo->inimigos[j].inimigo_R, jogo->texturas.explosa);
                        jogo->contador_explosoes++;
                        jogo->jogador.abates++;
                        removerInimigo(jogo->inimigos,j);
                        removerProjetil(jogo->projeteis,i);
                        jogo->inimigos[j].abatidoPeloJogador = true;
                        jogo->jogador.pontuacao += 800;
                    }
                }
            }

            if (checarColisaoProjeteisEJogador(&jogo->projeteis[i], &jogo->jogador)){
                if(jogo->projeteis[i].tanque_de_origem == 'i'){
                    removerProjetil(jogo->projeteis,i);
                    criarExplosao(&jogo->explosoes[jogo->contador_explosoes], jogo->projeteis[i].projetil_R, jogo->texturas.explosa);
                    PlaySound(jogo->sons.hit_jogador);
                    jogo->jogador.vidas--;
                }
            }

            for(j=0; j<MAPA_LINHAS; j++){
                for(k=0; k<MAPA_COLUNAS; k++){
                    if(jogo->blocos[j][k].tipo == 1 || jogo->blocos[j][k].tipo == 8 || jogo->blocos[j][k].tipo == 9){
                        if (checarColisaoProjeteisEBlocos(&jogo->projeteis[i], &jogo->blocos[j][k])){
                            if(jogo->blocos[j][k].destrutivel){
                                removerBloquinho(&jogo->blocos[j][k]);
                                PlaySound(jogo->sons.construcao);
                            }
                            removerProjetil(jogo->projeteis,i);
                        }
                    }
                }
            }

            for(j=i+1; j<NRO_PROJETEIS; j++){
                if (jogo->projeteis[j].em_movimento == 1){
                    if(checarColisaoDeProjeteis(&jogo->projeteis[i],&jogo->projeteis[j])){
                        removerProjetil(jogo->projeteis,i);
                        removerProjetil(jogo->projeteis,j);
                    }
                }
            }
        }
    }

    /**
        CELULAS DE ENERGIA
    */
    int rand = 0;
    rand = GetRandomValue(0,3);
    if(rand == 0){
        if(jogo->contador_cels_energia < NRO_CELS_ENERGIA){
            if(jogo->segundos % TEMPO_DE_SPAWN_CELS_ENERGIA == 0 && jogo->milisegundos == 0){
                if(jogo->cels_energia[i].cel_energia_posicionada == FALSE){
                    criarCelulaDeEnergia(jogo->mapa.mapa_atual, jogo->blocos, &jogo->cels_energia[jogo->contador_cels_energia]);
                    jogo->contador_cels_energia++;
                }
            }
        }else{
            if(jogo->segundos % TEMPO_DE_SPAWN_CELS_ENERGIA == 0 && jogo->milisegundos == 0){
                for(i=0; i<NRO_CELS_ENERGIA; i++){
                    if (jogo->cels_energia[i].ativa == false && jogo->cels_energia[i].cel_energia_posicionada == FALSE){
                        criarCelulaDeEnergia(jogo->mapa.mapa_atual, jogo->blocos, &jogo->cels_energia[i]);
                    }
                }
            }
        }
    }
    for(i=0; i<NRO_CELS_ENERGIA; i++){
        if(jogo->cels_energia[i].ativa == true){
            DrawTexturePro(
                jogo->texturas.energia,
                energia_textura,
                jogo->cels_energia[i].cel_energia_R,
                jogo->cels_energia[i].origem_textura,
                0,
                jogo->cels_energia[i].cor
            );

            if (checarColisaoJogadorECelEnergia(&jogo->jogador.jogador_R, &jogo->cels_energia[i].cel_energia_R)){
                if (jogo->contador_interno_cel_energia < 20){
                    jogo->contador_interno_cel_energia += 10;
                }
                PlaySound(jogo->sons.power_up);
                energizarJogador(&jogo->jogador,&jogo->cels_energia[i]);
                removerCelEnergia(&jogo->cels_energia[i]);
            }
        }
    }
    if (jogo->jogador.energizado == true){
        mudarCorBorda(jogo->blocos,YELLOW);

        if(jogo->segundos % 1 == 0 && jogo->milisegundos == 0){
            jogo->contador_interno_cel_energia--;
        }

        if (jogo->milisegundos < 500){
            jogo->jogador.cor = YELLOW;
        }else if(jogo->milisegundos > 500){
            jogo->jogador.cor = WHITE;
        }

        if(jogo->contador_interno_cel_energia == 0){
            jogo->jogador.energizado = false;
            jogo->jogador.multiplicador_vel = 1;
            jogo->jogador.cor = WHITE;
            mudarCorBorda(jogo->blocos,GRAY);
        }

    }
    /**
        EXPLOSOES
    */
    if (jogo->contador_explosoes == NRO_EXPLOSOES){
        jogo->contador_explosoes = 0;
    }

    for(i=0; i<NRO_EXPLOSOES; i++){
        if (jogo->explosoes[i].ativa){
            renderizarExplosoes(&jogo->explosoes[i]);
        }
    }
    /**
        MAPA DNV
    */
    atualizarMapa(jogo->mapa.mapa_atual,jogo->blocos,jogo->jogador,jogo->inimigos,jogo->contador_inimigos,jogo->cels_energia, jogo->contador_cels_energia);

    /**
        LAYOUT
    */

    //DrawRectangle(0,0,1020,CABECALHO,BLUE);
    for(i=0; i<jogo->jogador.vidas; i++){
        DrawTextureEx(jogo->texturas.escudo, (Vector2){i*65, 0}, 0, 0.11, WHITE);
    }
    DrawText(TextFormat("Pontuacao: %i", jogo->jogador.pontuacao), 375, 30, 36, WHITE);
    DrawText(TextFormat("Fase: %i", jogo->fase), 800, 20, 48, ORANGE);

    DrawRectangle(1020,0,130,CABECALHO,DARKGRAY);
    DrawText(TextFormat("%ds", jogo->segundos), 1045, 25, 48, ORANGE);

    Rectangle miniatura_cel_energia_R = {1050,CABECALHO+30,70,70};
    Vector2 miniatura_origem_textura = {0,0};
    Color cor_miniatura;
    Color cor_contador_cel_energia;
    if(jogo->jogador.energizado){
        cor_miniatura = WHITE;
        DrawRectangle(1020,CABECALHO,130,200,YELLOW);
        cor_contador_cel_energia = DARKBLUE;
    }else{
        cor_miniatura = DARKGRAY;
        cor_contador_cel_energia = ORANGE;
    }
    DrawTexturePro(
        jogo->texturas.energia,
        energia_textura,
        miniatura_cel_energia_R,
        miniatura_origem_textura,
        0,
        cor_miniatura
    );
    DrawText(TextFormat("%ds", jogo->contador_interno_cel_energia), 1065, CABECALHO+130, 32, cor_contador_cel_energia);

    DrawRectangle(1020,CABECALHO+200,130,420,DARKGRAY);
    if(!jogo->mapa.passagem_aberta){
        DrawText(TextFormat("Kills"), 1040, CABECALHO+220, 48, ORANGE);
        DrawText(TextFormat("%d", (NRO_INIMIGOS*(jogo->fase-1)+jogo->jogador.abates)), 1075, CABECALHO+270, 48, ORANGE);
        int linha = 0;
        int coluna = 0;
        for (i=0; i<jogo->contador_inimigos;i++){
            if(jogo->inimigos[i].vidas > 0){
                Rectangle miniatura = {1045+(40*coluna),435+(40*linha),30,30};
                Rectangle miniatura_R = {0,0,TAMANHO_TANQUES/2,TAMANHO_TANQUES/2};
                Vector2 miniatura_origem_textura = {30/2,30/2};
                Texture2D miniatura_textura;
                if(jogo->inimigos[i].emMovimento == 2){
                    miniatura_textura = jogo->texturas.inimigo_perseguicao;
                }
                else{
                    miniatura_textura = jogo->texturas.inimigo_patrulha;
                }
                DrawTexturePro(
                    miniatura_textura,
                    miniatura_R,
                    miniatura,
                    miniatura_origem_textura,
                    jogo->inimigos[i].angulo,
                    jogo->inimigos[i].cor
                );
            }

            if(coluna == 2){
                linha++;
            }

            if(coluna < 2){
                coluna++;
            }else{
                coluna = 0;
            }
        }
        DrawText(TextFormat("Faltam"), 1050, 625, 24, ORANGE);
        DrawText(TextFormat("%d inimigos",(NRO_INIMIGOS - jogo->jogador.abates)), 1030, 660, 24, ORANGE);
    }else{
        DrawText(TextFormat("Prox. fase!", jogo->jogador.abates), 1020, 625, 24, ORANGE);
        DrawText(TextFormat("<----------",(NRO_INIMIGOS - jogo->jogador.abates)), 1020, 660, 24, ORANGE);
    }

    if(IsKeyPressed(KEY_S)){
        salvarJogo(jogo);
    }

    if(IsKeyPressed(KEY_R)){
        reiniciarJogo(jogo);
    }

    if(IsKeyPressed(KEY_I)){
        printarMapa(jogo->mapa.mapa_inicial);
    }

    if(IsKeyPressed(KEY_C)){
        carregarJogoSalvo(jogo);
    }

    if(IsKeyPressed(KEY_M)){
        printarMapa(jogo->mapa.mapa_atual);
    }

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(111);
    }
}

void DrawNewGameplayScreen(GAME *jogo){
    resetarJogo(jogo);
    SetActiveScreen(11);
}

void DrawSavedGameGameplayScreen(GAME *jogo){
    printf("altura morte DrawSavedGameGameplayScreen: %d\n",jogo->texturas.morte.height);
    printf("largura morte DrawSavedGameGameplayScreen: %d\n",jogo->texturas.morte.width);
    carregarJogoSalvo(jogo);
    printf("altura morte DrawSavedGameGameplayScreen: %d\n",jogo->texturas.morte.height);
    printf("largura morte DrawSavedGameGameplayScreen: %d\n",jogo->texturas.morte.width);
    SetActiveScreen(11);
}

void salvarJogo(GAME *jogo){
    FILE *save_fp;
    GAME jogo_salvo;
    save_fp = fopen("saves/ultimo-save.bin","wb+");

    jogo_salvo.jogador = jogo->jogador;

    memcpy(jogo_salvo.inimigos, jogo->inimigos, sizeof(jogo->inimigos));
    jogo_salvo.contador_inimigos = jogo->contador_inimigos;

    memcpy(jogo_salvo.projeteis, jogo->projeteis, sizeof(jogo->projeteis));
    jogo_salvo.contador_projeteis = jogo->contador_projeteis;

    memcpy(jogo_salvo.cels_energia, jogo->cels_energia, sizeof(jogo->cels_energia));
    jogo_salvo.contador_cels_energia = jogo->contador_cels_energia;
    jogo_salvo.contador_interno_cel_energia = jogo->contador_interno_cel_energia;

    memcpy(jogo_salvo.explosoes, jogo->explosoes, sizeof(jogo->explosoes));
    jogo_salvo.contador_explosoes = jogo->contador_explosoes;

    memcpy(jogo_salvo.blocos, jogo->blocos, sizeof(jogo->blocos));
    jogo_salvo.mapa = jogo->mapa;

    jogo_salvo.segundos = jogo->segundos;
    jogo_salvo.fase = jogo->fase;
    jogo_salvo.milisegundos = jogo->milisegundos;

    jogo_salvo.jogo_carregado = jogo->jogo_carregado;

    if (save_fp != NULL){
        if (fwrite(&jogo_salvo, sizeof(GAME), 1, save_fp) != 1){
            perror("problema em salvar o jogo\n");
        }
        rewind(save_fp);
        GAME jooj;
        if(fread(&jooj, sizeof(GAME), 1, save_fp) == 1){
            printarMapa(jooj.mapa.mapa_atual);
        }else{
            perror("erro na leitura do jogo salvo\n");
        }
    }
    fclose(save_fp);
}

void carregarJogoSalvo(GAME *jogo){
    FILE *save_fp;
    save_fp = fopen("saves/ultimo-save.bin","rb");
    if (save_fp != NULL){
        rewind(save_fp);
        GAME jooj;
        printf("3\n");
        if(fread(&jooj, sizeof(GAME), 1, save_fp) == 1){
            jogo->jogador = jooj.jogador;
            memcpy(jogo->inimigos, jooj.inimigos, sizeof(jogo->inimigos));
            jogo->contador_inimigos = jooj.contador_inimigos;

            memcpy(jogo->projeteis, jooj.projeteis, sizeof(jogo->projeteis));
            jogo->contador_projeteis = jooj.contador_projeteis;

            memcpy(jogo->cels_energia, jooj.cels_energia, sizeof(jogo->cels_energia));
            jogo->contador_cels_energia = jooj.contador_cels_energia;
            jogo->contador_interno_cel_energia = jooj.contador_interno_cel_energia;

            memcpy(jogo->explosoes, jooj.explosoes, sizeof(jogo->explosoes));
            jogo->contador_explosoes = jooj.contador_explosoes;

            memcpy(jogo->blocos, jooj.blocos, sizeof(jogo->blocos));

            jogo->mapa = jooj.mapa;

            jogo->segundos = jooj.segundos;
            jogo->milisegundos = jooj.milisegundos;
            jogo->fase = jooj.fase;
            jogo->jogo_carregado = jooj.jogo_carregado;
        }else{
            perror("erro na leitura do save ");
        }
    }else{
        perror("erro na abertura do arquivo");
    }
    fclose(save_fp);
}

void passarDeFase(GAME *jogo){
    FILE *nivel_fp;

    char nivel = jogo->fase+'0';

    char nome_nivel[17+1] = {"niveis/nivelx.txt"};
    nome_nivel[12] = nivel;

    nivel_fp = fopen(nome_nivel,"r");
    if (nivel_fp != NULL){
        carregarMapa(jogo->mapa.mapa_atual,nivel_fp);
    }else{
        perror("passar Erro na abertura do arquivo");
    }
    fecharPassagem(jogo->mapa.mapa_atual);
    jogo->mapa.passagem_aberta = FALSE;

    INIMIGO z_inimigos[NRO_INIMIGOS]={0};
    memcpy(jogo->inimigos, z_inimigos, sizeof(jogo->inimigos));

    PROJETIL z_projeteis[NRO_PROJETEIS]={0};
    memcpy(jogo->projeteis, z_projeteis, sizeof(jogo->projeteis));
    jogo->contador_projeteis= 0;

    BLOCO z_blocos[MAPA_LINHAS][MAPA_COLUNAS] = {0};
    memcpy(jogo->blocos, z_blocos, sizeof(jogo->blocos));

    jogo->jogador.abates = 0;

    CELULA z_cels_energia[NRO_CELS_ENERGIA]={0};
    memcpy(jogo->cels_energia, z_cels_energia, sizeof(jogo->cels_energia));
    jogo->contador_cels_energia = 0;
    jogo->contador_interno_cel_energia = 0;

    EXPLOSAO z_explosoes[NRO_EXPLOSOES]={0};
    memcpy(jogo->explosoes, z_explosoes, sizeof(jogo->explosoes));
    jogo->contador_explosoes = 0;

    jogo->jogador.jogador_posicionado = false;
}

void reiniciarJogo(GAME *jogo){
    jogo->milisegundos = 0;
    jogo->segundos = 0;
    jogo->jogo_carregado = FALSE;
    jogo->fase = 1;

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
            .jogador_posicionado = false,
            .nome = {"Soldado"}
    };
    jogo->jogador = z_jogador;

    INIMIGO z_inimigos[NRO_INIMIGOS]={0};
    memcpy(jogo->inimigos, z_inimigos, sizeof(jogo->inimigos));
    jogo->contador_inimigos = 0;

    PROJETIL z_projeteis[NRO_PROJETEIS]={0};
    memcpy(jogo->projeteis, z_projeteis, sizeof(jogo->projeteis));
    jogo->contador_projeteis= 0;

    BLOCO z_blocos[MAPA_LINHAS][MAPA_COLUNAS] = {0};
    memcpy(jogo->blocos, z_blocos, sizeof(jogo->blocos));

    memcpy(jogo->mapa.mapa_atual, jogo->mapa.mapa_inicial, sizeof(jogo->mapa.mapa_atual));
    jogo->mapa.mapa_carregado = FALSE;
    jogo->mapa.passagem_aberta = FALSE;

    CELULA z_cels_energia[NRO_CELS_ENERGIA]={0};
    memcpy(jogo->cels_energia, z_cels_energia, sizeof(jogo->cels_energia));
    jogo->contador_cels_energia = 0;
    jogo->contador_interno_cel_energia = 0;

    EXPLOSAO z_explosoes[NRO_EXPLOSOES]={0};
    memcpy(jogo->explosoes, z_explosoes, sizeof(jogo->explosoes));
    jogo->contador_explosoes = 0;
}

void resetarJogo(GAME *jogo){
    reiniciarJogo(jogo);
    jogo->mapa.mapa_foi_pre_carregado = FALSE;
}

void carregarMapa(int mapa[][MAPA_COLUNAS], FILE *nivel_fp){
    int i=1;
    int j=1;
    char objeto;
    if(nivel_fp != NULL){
        rewind(nivel_fp);
        while(!feof(nivel_fp)){
            objeto = fgetc ( nivel_fp );
            if (objeto == '#'){
                mapa[i][j] = 1;
                j++;
            }

            if (objeto == '-'){
                mapa[i][j] = 0;
                j++;
            }


            if (objeto == 'T'){
                mapa[i][j] = 10;
                j++;
            }

            if(j == 41){
                j = 1;
                i++;
            }
            printf("%c",objeto);
        }
        printarMapa(mapa);
    }else{
        perror("erro no carregar mapa");
    }

}
