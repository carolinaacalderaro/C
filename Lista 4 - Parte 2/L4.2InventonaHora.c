#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void liberarInventario(char** inventario, int qtd) {
    if (inventario != NULL) {
        for (int i = 0; i < qtd; i++) {
            if (inventario[i] != NULL) {
                free(inventario[i]);
            }
        }
        free(inventario);
    }
}

int main() {
    int capacidade = 4;
    int qtd_itens = 0;
    
    char** inventario = malloc(capacidade * sizeof(char*));
    if (inventario == NULL) {
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (qtd_itens >= capacidade) {
            capacidade *= 2;
            char** temp = realloc(inventario, capacidade * sizeof(char*));
            if (temp == NULL) {
                liberarInventario(inventario, qtd_itens);
                exit(1);
            }
            inventario = temp;
        }

        inventario[qtd_itens] = malloc((strlen(buffer) + 1) * sizeof(char));
        if (inventario[qtd_itens] == NULL) {
            liberarInventario(inventario, qtd_itens);
            exit(1);
        }

        strcpy(inventario[qtd_itens], buffer);
        printf("Sucesso! Mais um item pra colecao: %s\n", inventario[qtd_itens]);
        qtd_itens++;
    }

    for (int i = 0; i < qtd_itens; i++) {
        printf("%d. %s\n", i + 1, inventario[i]);
    }

    printf("O que vou fazer com tudo isso?\n");

    liberarInventario(inventario, qtd_itens);

    return 0;
}