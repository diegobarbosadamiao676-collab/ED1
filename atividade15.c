#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    ENTIDADE_JOGADOR,
    ENTIDADE_INIMIGO,
    ENTIDADE_ITEM
} TipoEntidade;

typedef union {
    int dano;
    int valor;
} ExtraEntidade;

typedef struct {
    TipoEntidade tipo;
    Vector2 pos;
    float raio;
    int vida;
    Color cor;
    ExtraEntidade extra;
} Entidade;

Entidade *entidadeCriar(TipoEntidade tipo, Vector2 pos) {
    Entidade *e = (Entidade *)malloc(sizeof(Entidade));
    if (e == NULL) return NULL;

    e->tipo = tipo;
    e->pos = pos;
    e->raio = 20.0f;
    e->vida = 100;

    if (tipo == ENTIDADE_JOGADOR) {
        e->cor = BLUE;
    } else if (tipo == ENTIDADE_INIMIGO) {
        e->cor = RED;
        e->extra.dano = 10;
    } else {
        e->cor = GREEN;
        e->extra.valor = 50;
    }

    return e;
}

bool entidadeColidiu(Entidade *a, Entidade *b) {
    if (a == NULL || b == NULL) return false;
    return CheckCollisionCircles(a->pos, a->raio, b->pos, b->raio);
}

void entidadeDesenhar(Entidade *e) {
    if (e == NULL) return;
    DrawCircleV(e->pos, e->raio, e->cor);
}

void entidadeAplicarDano(Entidade *e, int dano) {
    if (e == NULL) return;
    e->vida -= dano;
    if (e->vida < 0) e->vida = 0;
}

bool entidadeEstaViva(Entidade *e) {
    if (e == NULL) return false;
    return e->vida > 0;
}

int main(void) {
    const int larguraTela = 800;
    const int alturaTela = 600;

    InitWindow(larguraTela, alturaTela, "Exercicio 1 - Nova funcao no modulo");
    SetTargetFPS(60);

    Entidade *jogador = entidadeCriar(ENTIDADE_JOGADOR, (Vector2){400, 300});
    Entidade *inimigo = entidadeCriar(ENTIDADE_INIMIGO, (Vector2){420, 300});

    while (!WindowShouldClose()) {
        if (inimigo != NULL && entidadeColidiu(jogador, inimigo)) {
            entidadeAplicarDano(inimigo, 2);
        }

        if (inimigo != NULL && !entidadeEstaViva(inimigo)) {
            free(inimigo);
            inimigo = NULL;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (jogador != NULL) entidadeDesenhar(jogador);
            if (inimigo != NULL) entidadeDesenhar(inimigo);

            DrawText("Exercicio 1 - Verificacao de vida da entidade", 10, 10, 20, DARKGRAY);

            if (inimigo != NULL) {
                DrawText(TextFormat("Vida do Inimigo: %d", inimigo->vida), 10, 40, 18, RED);
            } else {
                DrawText("Inimigo foi derrotado e removido!", 10, 40, 18, DARKGREEN);
            }
        EndDrawing();
    }

    if (jogador != NULL) free(jogador);
    if (inimigo != NULL) free(inimigo);

    CloseWindow();
    return 0;
}
