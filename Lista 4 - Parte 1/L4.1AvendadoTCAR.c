#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int quantidade;
} CarroEstoque;

typedef struct {
    char nome[50];
} CarroColecao;

CarroEstoque *adiciona_estoque(CarroEstoque *estoque, int *quantidade, int *capacidade, char *nome, int qtd) {
    if (*quantidade >= *capacidade) {
        (*capacidade) *= 2;
        CarroEstoque *temp = (CarroEstoque*) realloc(estoque, (*capacidade) * sizeof(CarroEstoque));
        if (temp == NULL) {
            free(estoque);
            exit(1);
        }
        estoque = temp;
    }
    strcpy(estoque[*quantidade].nome, nome);
    estoque[*quantidade].quantidade = qtd;
    (*quantidade)++;
    return estoque;
}

CarroColecao *adiciona_colecao(CarroColecao *colecao, int *quantidade, int *capacidade, char *nome) {
    if (*quantidade >= *capacidade) {
        (*capacidade) *= 2;
        CarroColecao *temp = (CarroColecao*) realloc(colecao, (*capacidade) * sizeof(CarroColecao));
        if (temp == NULL) {
            free(colecao);
            exit(1);
        }
        colecao = temp;
    }
    strcpy(colecao[*quantidade].nome, nome);
    (*quantidade)++;
    return colecao;
}

int tem_na_colecao(CarroColecao *colecao, int quantidade, char *nome) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(colecao[i].nome, nome) == 0) {
            return 1; 
        }
    }
    return 0; 
}

int main() {
    int cap_est = 1, qtd_est = 0;
    int cap_julio = 1, qtd_julio = 0;
    int cap_cariani = 1, qtd_cariani = 0;
    int cap_vendidos = 1, qtd_vendidos = 0;

    CarroEstoque *estoque = (CarroEstoque*) malloc(cap_est * sizeof(CarroEstoque));
    CarroColecao *julio = (CarroColecao*) malloc(cap_julio * sizeof(CarroColecao));
    CarroColecao *cariani = (CarroColecao*) malloc(cap_cariani * sizeof(CarroColecao));
    CarroEstoque *vendidos = (CarroEstoque*) malloc(cap_vendidos * sizeof(CarroEstoque));

    char buffer[50];
    int qtd_carro;

    while (scanf("%s", buffer) == 1 && strcmp(buffer, "FIM") != 0) {
        scanf("%d", &qtd_carro);
        estoque = adiciona_estoque(estoque, &qtd_est, &cap_est, buffer, qtd_carro);
    }

    while (scanf("%s", buffer) == 1 && strcmp(buffer, "FIM") != 0) {
        julio = adiciona_colecao(julio, &qtd_julio, &cap_julio, buffer);
    }

    while (scanf("%s", buffer) == 1 && strcmp(buffer, "TOGURO") != 0) {
        cariani = adiciona_colecao(cariani, &qtd_cariani, &cap_cariani, buffer);
    }

    for (int i = 0; i < qtd_est; i++) {
        if (estoque[i].quantidade > 0 && !tem_na_colecao(julio, qtd_julio, estoque[i].nome)) {
            julio = adiciona_colecao(julio, &qtd_julio, &cap_julio, estoque[i].nome);
            vendidos = adiciona_estoque(vendidos, &qtd_vendidos, &cap_vendidos, estoque[i].nome, 1);
            estoque[i].quantidade--;
        }
    }
    for (int i = 0; i < qtd_est; i++) {
        if (estoque[i].quantidade > 0 && !tem_na_colecao(cariani, qtd_cariani, estoque[i].nome)) {
            cariani = adiciona_colecao(cariani, &qtd_cariani, &cap_cariani, estoque[i].nome);
            vendidos = adiciona_estoque(vendidos, &qtd_vendidos, &cap_vendidos, estoque[i].nome, 1);
            estoque[i].quantidade--;
        }
    }

    char comando[20];
    scanf("%s", comando);

    if (strcmp(comando, "ESTOQUE") == 0) {
        while (scanf("%s", buffer) == 1 && strcmp(buffer, "FIM") != 0) {
            scanf("%d", &qtd_carro);
            estoque = adiciona_estoque(estoque, &qtd_est, &cap_est, buffer, qtd_carro);
        }

        for (int i = 0; i < qtd_est; i++) {
            if (estoque[i].quantidade > 0 && !tem_na_colecao(julio, qtd_julio, estoque[i].nome)) {
                julio = adiciona_colecao(julio, &qtd_julio, &cap_julio, estoque[i].nome);
                vendidos = adiciona_estoque(vendidos, &qtd_vendidos, &cap_vendidos, estoque[i].nome, 1);
                estoque[i].quantidade--;
            }
        }
        for (int i = 0; i < qtd_est; i++) {
            if (estoque[i].quantidade > 0 && !tem_na_colecao(cariani, qtd_cariani, estoque[i].nome)) {
                cariani = adiciona_colecao(cariani, &qtd_cariani, &cap_cariani, estoque[i].nome);
                vendidos = adiciona_estoque(vendidos, &qtd_vendidos, &cap_vendidos, estoque[i].nome, 1);
                estoque[i].quantidade--;
            }
        }
    }

    printf("Colecao do Julio:");
    for (int i = 0; i < qtd_julio; i++) {
        if (i == 0) {
            printf(" %s", julio[i].nome); 
        } else {
            printf(", %s", julio[i].nome); 
        }
    }
    printf("\n");

    printf("Colecao do Cariani:");
    for (int i = 0; i < qtd_cariani; i++) {
        if (i == 0) {
            printf(" %s", cariani[i].nome);
        } else {
            printf(", %s", cariani[i].nome);
        }
    }
    printf("\n");

    int total_vendidos = 0;
    for (int i = 0; i < qtd_vendidos; i++) {
        total_vendidos += vendidos[i].quantidade;
    }

    printf("Total de carros vendidos = %d\n", total_vendidos);

    printf("Carros vendidos:");
    for (int i = 0; i < qtd_vendidos; i++) {
        if (i == 0) {
            printf(" %s", vendidos[i].nome);
        } else {
            printf(", %s", vendidos[i].nome);
        }
    }
    printf("\n");

    free(estoque);
    free(julio);
    free(cariani);
    free(vendidos);

    return 0;
}