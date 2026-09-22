#include <stdio.h>
#include <stdlib.h>

void operacao(int *valor1, int *valor2, char *comando, int *Resultados, int *pos) {
    int res = 0, valida = 1;

    if (*comando == '+') {
        res = (*valor1) + (*valor2);
    }
    else if (*comando == '-') {
        res = (*valor1) - (*valor2);
    }
    else if (*comando == '*') {
        res = (*valor1) * (*valor2);
    }
    else if (*comando == '/') {
        if (*valor2 == 0) {
            valida = 0;
        }
        else {
            res = (*valor1) / (*valor2);
        }
    }

    else {
        valida = 0;
    }

    if (valida == 1) {
        Resultados[*pos] = res;

        printf("Operação %d: %d %c %d = %d\n", (*pos) + 1, *valor1, *comando, *valor2, res);

        (*pos)++;
    }

    else {
        printf("Operação Inválida! Próxima!\n");
    }
}

int main() {
    int v1, v2;
    char op;
    int capacidade = 1, quantidade_validas = 0;

    int * Resultados = (int*) calloc(1, sizeof(int));
    if (Resultados == NULL) {
        return 1;
    }
    
    printf("=Iniciando Cálculos=\n");

    while(scanf("%d %c %d", &v1, &op, &v2) != EOF) {
        if (quantidade_validas >= capacidade) {
            capacidade *= 2;

            int *temp = (int*) realloc(Resultados, capacidade * sizeof(int));

            if (temp == NULL) {
                free(Resultados);
                return 1;
            }

            Resultados = temp;
        }

        operacao(&v1, &v2, &op, Resultados, &quantidade_validas);
    }

    printf("\n");
    printf("Operações concluídas:\n");

    for (int i = 0; i < quantidade_validas; i++) {
        printf("Resultado Operação %d: %d\n", i + 1, Resultados[i]);
    }

    free(Resultados);

    return 0;
}