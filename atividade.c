#include "raylib.h"
#include <stdlib.h>
#define LARGURA_JANELA 800
#define ALTURA_JANELA 600
#define TAM_CELULA 40
typedef struct {
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;
int **criarMatriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = GetRandomValue(0, 1);
        }
    }
    return matriz;
}
void liberarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}
Bola *criarBolas(int quantidade) {
    Bola *bolas = (Bola *)malloc(quantidade * sizeof(Bola));
    for (int i = 0; i < quantidade; i++) {
        Bola *b = (bolas + i);
        b->pos = (Vector2){ GetRandomValue(50, LARGURA_JANELA - 50), 
                            GetRandomValue(50, ALTURA_JANELA - 50) };
        b->vel = (Vector2){ GetRandomValue(-3, 3), GetRandomValue(-3, 3) };
        b->raio = 10;
        b->cor = RED;
    }
    return bolas;
}
void atualizarBola(Bola *b) {
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;
    if (b->pos.x - b->raio < 0 || b->pos.x + b->raio > LARGURA_JANELA)
        b->vel.x *= -1;
    if (b->pos.y - b->raio < 0 || b->pos.y + b->raio > ALTURA_JANELA)
        b->vel.y *= -1;
}
int main(void) {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Exercício 1");
    SetTargetFPS(60);
    int linhas = ALTURA_JANELA / TAM_CELULA;
    int colunas = LARGURA_JANELA / TAM_CELULA;
    int **matriz = criarMatriz(linhas, colunas);
    int quantidadeBolas = 12;
    Bola *bolas = criarBolas(quantidadeBolas);
    while (!WindowShouldClose()) {
        // ESPACO: Adiciona nova bola
        if (IsKeyPressed(KEY_SPACE)) {
            quantidadeBolas++;
            bolas = (Bola *) realloc(bolas, quantidadeBolas * sizeof(Bola));
            Bola *b = bolas + (quantidadeBolas - 1);
            b->pos = (Vector2){ GetRandomValue(50, LARGURA_JANELA - 50), 
                                GetRandomValue(50, ALTURA_JANELA - 50) };
            b->vel = (Vector2){ GetRandomValue(-3, 3), GetRandomValue(-3, 3) };
            b->raio = 10;
            b->cor = RED;
        }
        // BACKSPACE: Remove a ultima bola
        if (IsKeyPressed(KEY_BACKSPACE) && quantidadeBolas > 0) {
            quantidadeBolas--;
            if (quantidadeBolas > 0) {
                bolas = (Bola *) realloc(bolas, quantidadeBolas * sizeof(Bola));
            } else {
                free(bolas);
                bolas = NULL;
            }
        }
        // Atualiza a posicao de cada bola
        for (int i = 0; i < quantidadeBolas; i++) {
            atualizarBola(bolas + i);
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            // Desenho das bolas
            for (int i = 0; i < quantidadeBolas; i++) {
                Bola *b = bolas + i;
                DrawCircleV(b->pos, b->raio, b->cor);
            }
            DrawText(TextFormat("Bolas: %d", quantidadeBolas), 10, 10, 20, BLACK);
        EndDrawing();
    }
    liberarMatriz(matriz, linhas);
    if (bolas != NULL) free(bolas);

    CloseWindow();
    return 0;
}
