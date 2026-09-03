#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

typedef struct {
    Vector2 pos;
    float raio;
    float dano;
    int vida;
} Jogador;

typedef struct {
    float dano;
    int alcance;
} DadosArma;

typedef struct {
    int cura;
} DadosPocao;

typedef union {
    DadosArma arma;
    DadosPocao pocao;
} DadosItem;

typedef enum {
    ITEM_ARMA,
    ITEM_POCAO
} TipoItem;

typedef struct {
    Vector2 pos;
    float raio;
    TipoItem tipo;
    DadosItem dados;
    bool coletado;
} Item;

Item *criarItens(int quantidade) {
    Item *itens = (Item *) malloc(quantidade * sizeof(Item));

    for (int i = 0; i < quantidade; i++) {
        Item *it = (itens + i);
        it->pos = (Vector2){ GetRandomValue(30, LARGURA_JANELA - 30), GetRandomValue(30, ALTURA_JANELA - 30) };
        it->raio = 12.0f;
        it->coletado = false;
        it->tipo = (TipoItem) GetRandomValue(ITEM_ARMA, ITEM_POCAO);

        if (it->tipo == ITEM_ARMA) {
            it->dados.arma.dano = (float) GetRandomValue(2, 8);
            it->dados.arma.alcance = GetRandomValue(1, 3);
        } else {
            it->dados.pocao.cura = GetRandomValue(10, 30);
        }
    }

    return itens;
}

void aplicarItem(Jogador *j, Item *item) {
    switch (item->tipo) {
        case ITEM_ARMA:
            j->dano += item->dados.arma.dano;
            break;
        case ITEM_POCAO:
            j->vida += item->dados.pocao.cura;
            break;
    }
    item->coletado = true;
}

int main() {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 3 - Tagged Unions");
    SetTargetFPS(60);

    Jogador jogador = { (Vector2){ LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f }, 15.0f, 10.0f, 100 };
    int totalItens = 8;
    Item *itens = criarItens(totalItens);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) jogador.pos.x += 4.0f;
        if (IsKeyDown(KEY_LEFT))  jogador.pos.x -= 4.0f;
        if (IsKeyDown(KEY_DOWN))  jogador.pos.y += 4.0f;
        if (IsKeyDown(KEY_UP))    jogador.pos.y -= 4.0f;

        for (int i = 0; i < totalItens; i++) {
            Item *it = (itens + i);
            if (!it->coletado) {
                float dx = it->pos.x - jogador.pos.x;
                float dy = it->pos.y - jogador.pos.y;
                if ((dx*dx + dy*dy) <= (it->raio + jogador.raio)*(it->raio + jogador.raio)) {
                    aplicarItem(&jogador, it);
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < totalItens; i++) {
            Item *it = (itens + i);
            if (!it->coletado) {
                Color cor = (it->tipo == ITEM_ARMA) ? RED : GREEN;
                DrawCircleV(it->pos, it->raio, cor);
            }
        }

        DrawCircleV(jogador.pos, jogador.raio, BLUE);
        DrawText(TextFormat("Vida: %d  Dano: %.1f", jogador.vida, jogador.dano), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    free(itens);
    CloseWindow();
    return 0;
}
