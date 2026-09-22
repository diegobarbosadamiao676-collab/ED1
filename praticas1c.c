#include <stdio.h>
#include <stdlib.h>
typedef struct {
char nome[50];
float preco;
} Fruta;
int main() {
FILE *arquivo = fopen("frutas.txt", "w");
if (arquivo == NULL) {
printf("Erro ao abrir o ficheiro!\n");
return 1;
}
Fruta f;
char opcao;
do {
printf("Nome da fruta: ");
scanf(" %[^\n]", f.nome);
printf("Preco da fruta: ");
scanf("%f", &f.preco);
fprintf(arquivo, "%s,%.2f\n", f.nome, f.preco);
printf("Deseja cadastrar mais uma fruta? (s/n): ");
scanf(" %c", &opcao);
} while (opcao == 's' || opcao == 'S');
fclose(arquivo);
printf("\nRegisto encerrado. arquivo 'frutas.txt' gravado com sucesso.\n");
return 0;
}
