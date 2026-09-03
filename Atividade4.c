#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

// Enum com as 4 raridades
typedef enum {
    MOEDA_BRONZE = 0,
    MOEDA_PRATA,
    MOEDA_OURO,
    MOEDA_DIAMANTE
} TipoMoeda;

typedef struct {
    Vector2 pos;
    float raio;
    TipoMoeda tipo;
    int valor;
    bool coletada;
    float tempoColeta;
} Moeda;

Color corDaMoeda(TipoMoeda tipo) {
    switch (tipo) {
        case MOEDA_BRONZE:   return (Color){160, 90, 40, 255};
        case MOEDA_PRATA:    return (Color){190, 190, 190, 255};
        case MOEDA_OURO:     return GOLD;
        case MOEDA_DIAMANTE: return SKYBLUE;
        default:             return WHITE;
    }
}

int valorDaMoeda(TipoMoeda tipo) {
    switch (tipo) {
        case MOEDA_BRONZE:   return 5;
        case MOEDA_PRATA:    return 10;
        case MOEDA_OURO:     return 25;
        case MOEDA_DIAMANTE: return 50;
        default:             return 0;
    }
}

Moeda *criarMoedas(int quantidade) {
    Moeda *moedas = (Moeda *) malloc(quantidade * sizeof(Moeda));
    
    for (int i = 0; i < quantidade; i++) {
        Moeda *m = (moedas + i);
        m->pos = (Vector2){ GetRandomValue(30, LARGURA_JANELA - 30), GetRandomValue(30, ALTURA_JANELA - 30) };
        m->raio = 10.0f;
        
        int sorteio = GetRandomValue(0, 9);
        if (sorteio == 0) {
            m->tipo = MOEDA_DIAMANTE;
        } else {
            m->tipo = (TipoMoeda) GetRandomValue(MOEDA_BRONZE, MOEDA_OURO);
        }

        m->valor = valorDaMoeda(m->tipo);
        m->coletada = false;
        m->tempoColeta = 0.0f;
    }
    
    return moedas;
}

bool tentarColetar(Moeda *m, Vector2 posJogador, float raioJogador, int *pontuacao) {
    if (m->coletada) return false;

    float dx = m->pos.x - posJogador.x;
    float dy = m->pos.y - posJogador.y;
    float distancia = (dx * dx + dy * dy);
    float somaRaios = (m->raio + raioJogador) * (m->raio + raioJogador);

    if (distancia <= somaRaios) {
        m->coletada = true;
        m->tempoColeta = (float) GetTime(); // Grava o instante da coleta
        *pontuacao += m->valor;
        return true;
    }

    return false;
}

void atualizarMoedas(Moeda *moedas, int quantidade) {
    float tempoAtual = (float) GetTime();

    for (int i = 0; i < quantidade; i++) {
        Moeda *m = (moedas + i);

        if (m->coletada && (tempoAtual - m->tempoColeta >= 3.0f)) {
            m->pos = (Vector2){ GetRandomValue(30, LARGURA_JANELA - 30), GetRandomValue(30, ALTURA_JANELA - 30) };
            
            int sorteio = GetRandomValue(0, 9);
            if (sorteio == 0) {
                m->tipo = MOEDA_DIAMANTE;
            } else {
                m->tipo = (TipoMoeda) GetRandomValue(MOEDA_BRONZE, MOEDA_OURO);
            }
            
            m->valor = valorDaMoeda(m->tipo);
            m->coletada = false;
        }
    }
}

int main() {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 2 - Exercicios 1 e 2");
    SetTargetFPS(60);

    Vector2 posJogador = { LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f };
    float raioJogador = 15.0f;
    float velocidade = 4.0f;
    int pontuacao = 0;

    int totalMoedas = 10;
    Moeda *moedas = criarMoedas(totalMoedas);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) posJogador.x += velocidade;
        if (IsKeyDown(KEY_LEFT))  posJogador.x -= velocidade;
        if (IsKeyDown(KEY_DOWN))  posJogador.y += velocidade;
        if (IsKeyDown(KEY_UP))    posJogador.y -= velocidade;

        for (int i = 0; i < totalMoedas; i++) {
            tentarColetar((moedas + i), posJogador, raioJogador, &pontuacao);
        }

        atualizarMoedas(moedas, totalMoedas);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < totalMoedas; i++) {
            Moeda *m = (moedas + i);
            if (!m->coletada) {
                DrawCircleV(m->pos, m->raio, corDaMoeda(m->tipo));
            }
        }

        DrawCircleV(posJogador, raioJogador, BLUE);
        DrawText(TextFormat("Pontuacao: %d", pontuacao), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    free(moedas);
    CloseWindow();

    return 0;
}
