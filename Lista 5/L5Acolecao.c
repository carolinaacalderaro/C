#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char titulo[50];
    char genero[50];
    char estudio[50];
    char console[50];
    int nota;
    int anoLancamento;
} Jogo;

void buscar_imprimir(Jogo colecao[], int n, char parametro[], int tipo) {
    int cont = 0;

    for (int i = 0; i < n; i++) {
        int deucerto = 0;

        if (tipo == 1 && strcmp(colecao[i].estudio, parametro) == 0) {
            deucerto = 1;
        }
        else if (tipo == 2 && strcmp(colecao[i].console, parametro) == 0) {
            deucerto = 1;
        }
        else if (tipo == 3 && colecao[i].anoLancamento == atoi(parametro)) {
            deucerto = 1;
        }
         if (tipo == 4 && colecao[i].titulo[0] == parametro[0]) {
            deucerto = 1;
        }

        if (deucerto) {
            printf("%s\n", colecao[i].titulo);
            cont++;
        }   
    }

    if (cont > 0) {
        printf("Tenho %d jogos || %s.\n", cont, parametro);
    }
    else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

int main() {
    int n;

    Jogo colecao[100];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s %s %s %s %d %d", 
            colecao[i].titulo,
            colecao[i].genero,
            colecao[i].estudio,
            colecao[i].console,
            &colecao[i].nota,
            &colecao[i].anoLancamento);
        
        if (colecao[i].nota > 7) {
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");
        }
        else if (colecao[i].nota < 4) {
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }
    }

    char funcao[30];
    char parametro[30];

    while (scanf("%s", funcao) != EOF) {
        if(strcmp(funcao, "printColecao") == 0) {
            for (int i = 0; i < n; i++) {
                printf("%s %d\n", colecao[i].titulo, colecao[i].nota);
            }
        }
        else {
            scanf("%s", parametro);

            if (strcmp(funcao, "printStudio") == 0) {
                buscar_imprimir(colecao, n, parametro, 1);
            }
            else if (strcmp(funcao, "printConsole") == 0) {
                buscar_imprimir(colecao, n, parametro, 2);
            }
            else if (strcmp(funcao, "printAno") == 0) {
                buscar_imprimir(colecao, n, parametro, 3);
            }
            else if (strcmp(funcao, "printLetra") == 0) {
                buscar_imprimir(colecao, n, parametro, 4);
            }
        }
    }

    printf("Enjoei de jogar, agora vou ver TV.\n");
    
    return 0;
}