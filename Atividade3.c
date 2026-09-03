#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

typedef struct {
    Vector2 pos;
    float raio;
    Vector2 vel;
} Bola;

Bola *criarBolas(int quantidade) {
    Bola *bolas = (Bola *) malloc(quantidade * sizeof(Bola));
    for (int i = 0; i < quantidade; i++) {
        Bola *b = (bolas + i);
        b->pos = (Vector2){ GetRandomValue(50, LARGURA_JANELA - 50), GetRandomValue(50, ALTURA_JANELA - 50) };
        b->vel = (Vector2){ (float)GetRandomValue(-3, 3), (float)GetRandomValue(-3, 3) };
        b->raio = 12.0f;
    }
    return bolas;
}

int main() {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 1 - Vetor Dinamico de Bolas");
    SetTargetFPS(60);

    int qtdBolas = 5;
    Bola *bolas = criarBolas(qtdBolas);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP)) {
            qtdBolas++;
            bolas = (Bola *) realloc(bolas, qtdBolas * sizeof(Bola));
            (bolas + qtdBolas - 1)->pos = (Vector2){ LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f };
            (bolas + qtdBolas - 1)->vel = (Vector2){ 2.0f, 2.0f };
            (bolas + qtdBolas - 1)->raio = 12.0f;
        }

        for (int i = 0; i < qtdBolas; i++) {
            Bola *b = (bolas + i);
            b->pos.x += b->vel.x;
            b->pos.y += b->vel.y;

            if (b->pos.x <= b->raio || b->pos.x >= LARGURA_JANELA - b->raio) b->vel.x *= -1;
            if (b->pos.y <= b->raio || b->pos.y >= ALTURA_JANELA - b->raio) b->vel.y *= -1;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < qtdBolas; i++) {
            DrawCircleV((bolas + i)->pos, (bolas + i)->raio, MAROON);
        }

        DrawText("Seta para CIMA: adiciona bola (realloc)", 10, 10, 18, DARKGRAY);
        EndDrawing();
    }

    // Liberação de memória
    free(bolas);
    CloseWindow();
    return 0;
}
