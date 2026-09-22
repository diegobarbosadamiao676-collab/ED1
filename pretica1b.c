#include <stdio.h>
#include <stdlib.h>

int main() {
FILE *arquivo = fopen("alunos.txt", "w");
if (arquivo == NULL) {
printf("Erro ao abrir o ficheiro!\n");
return 1;
 }
int n;
printf("Digite o numero de alunos (N): ");
scanf("%d", &n);
for (int i = 0; i < n; i++) {
char nome[100];
float nota1, nota2;
printf("\nAluno %d:\n", i + 1);
printf("Nome: ");
scanf(" %[^\n]", nome);
printf("Nota 1: ");
scanf("%f", &nota1);
printf("Nota 2: ");
scanf("%f", &nota2);
fprintf(arquivo, "%s %.2f %.2f\n", nome, nota1, nota2);
}
fclose(arquivo);
printf("\nDados armazenados em 'alunos.txt' com sucesso.\n");
return 0;
}
