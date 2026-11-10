#include <stdio.h>
#include <stdlib.h>

typedef struct No {
int dado;
struct No *anterior;
struct No *proximo;
} No;

typedef struct Lista {
No *inicio;
No *fim;
} Lista;

// Inicializar lista
void inicializar(Lista *lista) {
lista->inicio = NULL;
lista->fim = NULL;
}

// Inserir elemento no inicio
void inserirInicio(Lista *lista, int valor) {
No *novo = malloc(sizeof(No));

if (novo == NULL) return;  

novo->dado = valor;  
novo->anterior = NULL;  
novo->proximo = lista->inicio;  

if (lista->inicio == NULL) {  
    lista->fim = novo;  
} else {  
    lista->inicio->anterior = novo;  
}  

lista->inicio = novo;

}

// Inserir elemento no final
void inserirFinal(Lista *lista, int valor) {
No *novo = malloc(sizeof(No));

if (novo == NULL) return;  

novo->dado = valor;  
novo->proximo = NULL;  
novo->anterior = lista->fim;  

if (lista->fim == NULL) {  
    lista->inicio = novo;  
} else {  
    lista->fim->proximo = novo;  
}  

lista->fim = novo;

}

// Contar elementos
int contarElementos(Lista *lista) {
int contador = 0;
No *atual = lista->inicio;

while (atual != NULL) {  
    contador++;  
    atual = atual->proximo;  
}  

return contador;

}

// Inserir em uma posicao
void inserirPosicao(Lista *lista, int valor, int posicao) {
int quantidade = contarElementos(lista);

if (posicao < 1 || posicao > quantidade + 1) {  
    printf("Posicao invalida!\n");  
    return;  
}  

if (posicao == 1) {  
    inserirInicio(lista, valor);  
    return;  
}  

if (posicao == quantidade + 1) {  
    inserirFinal(lista, valor);  
    return;  
}  

No *novo = malloc(sizeof(No));  

if (novo == NULL) return;  

No *atual = lista->inicio;  

for (int i = 1; i < posicao; i++) {  
    atual = atual->proximo;  
}  

novo->dado = valor;  
novo->anterior = atual->anterior;  
novo->proximo = atual;  

atual->anterior->proximo = novo;  
atual->anterior = novo;

}

// Remover do inicio
void removerInicio(Lista *lista) {
if (lista->inicio == NULL) {
printf("Lista vazia!\n");
return;
}

No *remover = lista->inicio;  

if (lista->inicio == lista->fim) {  
    lista->inicio = NULL;  
    lista->fim = NULL;  
} else {  
    lista->inicio = lista->inicio->proximo;  
    lista->inicio->anterior = NULL;  
}  

free(remover);

}

// Remover do final
void removerFinal(Lista *lista) {
if (lista->fim == NULL) {
printf("Lista vazia!\n");
return;
}

No *remover = lista->fim;  

if (lista->inicio == lista->fim) {  
    lista->inicio = NULL;  
    lista->fim = NULL;  
} else {  
    lista->fim = lista->fim->anterior;  
    lista->fim->proximo = NULL;  
}  

free(remover);

}

// Buscar um valor
No *buscar(Lista *lista, int valor) {
No *atual = lista->inicio;

while (atual != NULL) {  
    if (atual->dado == valor) {  
        return atual;  
    }  

    atual = atual->proximo;  
}  

return NULL;

}

// Remover um valor
void removerValor(Lista *lista, int valor) {
No *atual = buscar(lista, valor);

if (atual == NULL) {  
    printf("Valor nao encontrado!\n");  
    return;  
}  

if (atual == lista->inicio) {  
    removerInicio(lista);  
    return;  
}  

if (atual == lista->fim) {  
    removerFinal(lista);  
    return;  
}  

atual->anterior->proximo = atual->proximo;  
atual->proximo->anterior = atual->anterior;  

free(atual);

}

// Imprimir do inicio ao final
void imprimirDireto(Lista *lista) {
No *atual = lista->inicio;

while (atual != NULL) {  
    printf("%d ", atual->dado);  
    atual = atual->proximo;  
}  

printf("\n");

}

// Imprimir do final ao inicio
void imprimirInverso(Lista *lista) {
No *atual = lista->fim;

while (atual != NULL) {  
    printf("%d ", atual->dado);  
    atual = atual->anterior;  
}  

printf("\n");

}

// Liberar memoria
void liberarLista(Lista *lista) {
No *atual = lista->inicio;

while (atual != NULL) {  
    No *remover = atual;  
    atual = atual->proximo;  
    free(remover);  
}  

lista->inicio = NULL;  
lista->fim = NULL;

}

// Programa principal
int main() {
Lista lista;
int opcao, valor, posicao;

inicializar(&lista);  

do {  
    printf("\n1 - Inserir no inicio\n");  
    printf("2 - Inserir no final\n");  
    printf("3 - Inserir em uma posicao\n");  
    printf("4 - Remover do inicio\n");  
    printf("5 - Remover do final\n");  
    printf("6 - Remover um valor\n");  
    printf("7 - Buscar um valor\n");  
    printf("8 - Imprimir do inicio ao final\n");  
    printf("9 - Imprimir do final ao inicio\n");  
    printf("10 - Contar elementos\n");  
    printf("11 - Remover todos os elementos\n");  
    printf("0 - Sair\n");  

    printf("Escolha: ");  
    scanf("%d", &opcao);  

    switch (opcao) {  
        case 1:  
            printf("Valor: ");  
            scanf("%d", &valor);  
            inserirInicio(&lista, valor);  
            break;  

        case 2:  
            printf("Valor: ");  
            scanf("%d", &valor);  
            inserirFinal(&lista, valor);  
            break;  

        case 3:  
            printf("Valor: ");  
            scanf("%d", &valor);  
            printf("Posicao: ");  
            scanf("%d", &posicao);  
            inserirPosicao(&lista, valor, posicao);  
            break;  

        case 4:  
            removerInicio(&lista);  
            break;  

        case 5:  
            removerFinal(&lista);  
            break;  

        case 6:  
            printf("Valor: ");  
            scanf("%d", &valor);  
            removerValor(&lista, valor);  
            break;  

        case 7:  
            printf("Valor: ");  
            scanf("%d", &valor);  

            if (buscar(&lista, valor) != NULL) {  
                printf("Valor encontrado!\n");  
            } else {  
                printf("Valor nao encontrado!\n");  
            }  
            break;  

        case 8:  
            imprimirDireto(&lista);  
            break;  

        case 9:  
            imprimirInverso(&lista);  
            break;  

        case 10:  
            printf("Quantidade: %d\n",  
                   contarElementos(&lista));  
            break;  

        case 11:  
            liberarLista(&lista);  
            printf("Todos os elementos foram removidos!\n");  
            break;  
    }  

} while (opcao != 0);  

liberarLista(&lista);  

return 0;

}
Me ensine esse código completo e claro coloque cometários devida o em 15 partes
