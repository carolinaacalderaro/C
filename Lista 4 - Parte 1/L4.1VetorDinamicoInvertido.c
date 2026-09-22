#include <stdio.h>
#include <stdlib.h>

int *insere(int *vetor, int *quantidade, int *capacidade, int valor) {
    if (*quantidade >= *capacidade) {
        *capacidade *= 2;

        int *temp = (int*) realloc(vetor, (*capacidade) * sizeof(int));

        if (temp == NULL) {
            free(vetor);
            exit(1);
        }

        vetor = temp;
    }

    vetor[*quantidade] = valor;
    (*quantidade)++;

    return vetor;
}

void imprime_invertido(int *vetor, int quantidade) {
    if (quantidade == 0) {
        printf("\n");

        return;
    }

    for (int i = quantidade - 1; i >= 0; i--) {
        printf("%d", vetor[i]);

        if (i > 0) {
            printf(" ");
        }
    }

    printf("\n");
}

int main() {
    int capacidade = 1, quantidade = 0, valor;

    int *vetor = (int*) malloc(capacidade * sizeof(int));
    
    if (vetor == NULL) {
            return 1;
    }

    while (1) {
        scanf("%d", &valor);

        if (valor == -1) {
            break;
        }

        vetor = insere(vetor, &quantidade, &capacidade, valor);
    }

    imprime_invertido(vetor, quantidade);

    free(vetor);

    return 0;
}