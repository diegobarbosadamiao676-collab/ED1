#include <stdio.h>
#include "raylib.h"
#define ARQUIVO_SAVE "save.bin"
int main(void)
{
InitWindow(800, 450, "Apagar jogo salvo");
char mensagem[100] = "";
float tempoMensagem = 0.0f;
while (!WindowShouldClose())
{
if (IsKeyPressed(KEY_DELETE))
{
if (remove(ARQUIVO_SAVE) == 0)
{
snprintf(mensagem,sizeof(mensagem),"Jogo salvo apagado com sucesso!");
}
else
{
snprintf(
mensagem,
sizeof(mensagem),
"Nenhum save encontrado."
);
}
tempoMensagem = 3.0f;
}
if (tempoMensagem > 0.0f)
tempoMensagem -= GetFrameTime();
BeginDrawing();
ClearBackground(RAYWHITE);
DrawText(
"Pressione DELETE para apagar o jogo salvo",
100,
150,
25,
BLACK
);
 if (tempoMensagem > 0.0f)
{
DrawText(
mensagem,
100,
220,
25,
RED
);
}
EndDrawing();
}
CloseWindow();
return 0;
}
