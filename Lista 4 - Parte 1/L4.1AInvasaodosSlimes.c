#include <stdio.h>
#include <stdlib.h>

int *insere_slime(int *slimes, int *quantidade, int*capacidade, int valor) {
    if (*quantidade >= *capacidade) {
        (*capacidade) *= 2;

        int *temp = (int*) realloc(slimes, (*capacidade) * sizeof(int));

        if (temp == NULL) {
            free(slimes);
            exit(1);
        }

        slimes = temp;
    }

    slimes[*quantidade] = valor;
    (*quantidade)++;

    return slimes;
}

void processar_fusoes(int *slimes, int *quantidade) {
    int i = 0;

    while (i < (*quantidade) - 1) {
        if (slimes[i] == slimes[i+1]) {
            slimes[i]++;

            for (int j = i+1; j < (*quantidade) - 1; j++) {
                slimes[j] = slimes[j+1];
            }

            (*quantidade)--;

            if (i > 0) {
                i--;
            }
        }

        else {
            i++;
        }
    }
}

int main() {
    int capacidade = 1, quantidade = 0, valor;

    int *slimes = (int*) malloc(capacidade * sizeof(int));

    if (slimes == NULL) {
        return 1;
    }

    while (scanf("%d", &valor) != EOF && valor != -1) {
        slimes = insere_slime(slimes, &quantidade, &capacidade, valor);
    }

    processar_fusoes(slimes, &quantidade);

    printf("Slimes restantes:");

    for (int k = 0; k < quantidade; k++) {
        printf(" %d", slimes[k]);
    }

    free(slimes);

    return 0;
}