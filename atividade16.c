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
    e->raio = 25.0f;
    e->vida = 100;

    if (tipo == ENTIDADE_JOGADOR) {
        e->cor = BLUE;
    } else if (tipo == ENTIDADE_INIMIGO) {
        e->cor = RED;
        e->extra.dano = 15;
    } else {
        e->cor = GREEN;
        e->extra.valor = 100;
    }

    return e;
}

void entidadeDesenhar(Entidade *e) {
    if (e == NULL) return;
    DrawCircleV(e->pos, e->raio, e->cor);
}

int main(void) {
    const int larguraTela = 800;
    const int alturaTela = 600;

    InitWindow(larguraTela, alturaTela, "Exercicio 2 - Reaproveitando o modulo");
    SetTargetFPS(60);

    Entidade *entidade1 = entidadeCriar(ENTIDADE_JOGADOR, (Vector2){200, 300});
    Entidade *entidade2 = entidadeCriar(ENTIDADE_INIMIGO, (Vector2){400, 300});
    Entidade *entidade3 = entidadeCriar(ENTIDADE_ITEM, (Vector2){600, 300});

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (entidade1 != NULL) entidadeDesenhar(entidade1);
            if (entidade2 != NULL) entidadeDesenhar(entidade2);
            if (entidade3 != NULL) entidadeDesenhar(entidade3);

            DrawText("Exercicio 2 - Reuso do modulo em outro programa", 10, 10, 20, DARKGRAY);
            DrawText("Azul: Jogador | Vermelho: Inimigo | Verde: Item", 10, 40, 18, GRAY);
        EndDrawing();
    }

    if (entidade1 != NULL) free(entidade1);
    if (entidade2 != NULL) free(entidade2);
    if (entidade3 != NULL) free(entidade3);

    CloseWindow();
    return 0;
}
