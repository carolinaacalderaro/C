#include <stdio.h>
#include <stdlib.h>

void ataqueSequencial(char** tabuleiro, int n, int tentativa, int* linha, int* coluna) {
    *linha = tentativa / n;
    *coluna = tentativa % n;
}

void ataqueReverso(char** tabuleiro, int n, int tentativa, int* linha, int* coluna) {
    int total_celulas = n * n;
    int index_reverso = total_celulas - 1 - tentativa;
    *linha = index_reverso / n;
    *coluna = index_reverso % n;
}

void liberarTabuleiro(char** tabuleiro, int n) {
    if (tabuleiro != NULL) {
        for (int i = 0; i < n; i++) {
            if (tabuleiro[i] != NULL) {
                free(tabuleiro[i]);
            }
        }
        free(tabuleiro);
    }
}

int main() {
    int n, q;
    
    scanf("%d", &n);
    scanf("%d", &q);
    char** tabuleiro = malloc(n * sizeof(char*));
    if (tabuleiro == NULL) {
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        tabuleiro[i] = NULL;
    }

    for (int i = 0; i < n; i++) {
        tabuleiro[i] = (char*) malloc(n * sizeof(char));
        if (tabuleiro[i] == NULL) {
            liberarTabuleiro(tabuleiro, n);
            exit(1);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tabuleiro[i][j] = '~';
        }
    }

    for (int i = 0; i < q; i++) {
        int l, c;
        scanf("%d %d", &l, &c);
        if (l >= 0 && l < n && c >= 0 && c < n) {
            tabuleiro[l][c] = 'N';
        }
    }

    int escolha;
    scanf("%d", &escolha);

    void (*estrategias[2])(char**, int, int, int*, int*) = {
        ataqueSequencial,
        ataqueReverso
    };

    int tentativas = 0;
    int navios_restantes = q;
    int max_tentativas = n * n;

    do {
        int l, c;

        estrategias[escolha - 1](tabuleiro, n, tentativas, &l, &c);
        tentativas++;

        if (tabuleiro[l][c] == 'N') {
            tabuleiro[l][c] = 'X';
            navios_restantes--;
        } else if (tabuleiro[l][c] == '~') {
            tabuleiro[l][c] = 'O';
        }
    } while (tentativas < max_tentativas && navios_restantes > 0);

    printf("Tentativas ate vencer: %d\n", tentativas);
    printf("Tabuleiro final:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", tabuleiro[i][j]);
            if (j < n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    liberarTabuleiro(tabuleiro, n);

    return 0;
}

