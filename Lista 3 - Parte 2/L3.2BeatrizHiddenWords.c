#include <stdio.h>

int encontrou(char palavra[], int L, int C, char matriz[L][C], int linha, int coluna, int direcionalmento_linha, int direcionamento_coluna) {
    int i = 0, encontrada = 1;

    while (palavra[i] != '\0' && encontrada == 1) {
        if (linha < 0 || linha >= L || coluna < 0 || coluna >= C) {
            encontrada = 0;
        }
        else if (matriz[linha][coluna] != palavra[i]) {
            encontrada = 0;
        }
        else {
            linha += direcionalmento_linha;
            coluna += direcionamento_coluna;
            i++;
        }
    }

    return encontrada;
}

int main() {
    int L, C, N;

    scanf("%d %d", &L, &C);

    char matriz[L][C];

    for (int i=0; i<L; i++) {
        scanf("%s", matriz[i]);
    }

    scanf("%d", &N);

    char palavra[100];

    int direcionamento_linha[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int direcionamento_coluna[8] = {1, -1, 0, 0, 1, -1, 1, -1};

    char direcoes[8][30] = {"horizontal-direita", "horizontal-esquerda", "vertical-baixo", "vertical-cima", "diagonal-baixo-direita", "diagonal-baixo-esquerda", "diagonal-cima-direita", "diagonal-cima-esquerda"};

    for (int a =0; a < N; a++) {
        scanf("%s", palavra);

        int encontrada = 0, linha_encontrada = 0, coluna_encontrada = 0, direcao_encontrada = 0;

        for (int i=0; i<L && encontrada == 0; i++) {
            for (int j=0; j<C && encontrada == 0; j++) {
                for (int k=0; k<8 && encontrada == 0; k++) {
                    if (encontrou(palavra, L, C, matriz, i, j, direcionamento_linha[k], direcionamento_coluna[k]) == 1) {
                        encontrada = 1;
                        linha_encontrada = i;
                        coluna_encontrada = j;
                        direcao_encontrada = k;
                    }
                }
            }
        }

        if (encontrada == 1) {
            printf("%s encontrada em (%d, %d), direcao: %s\n", palavra, linha_encontrada, coluna_encontrada, direcoes[direcao_encontrada]);
        }
        else {
            printf("%s nao encontrada\n", palavra);
        }
    }

    return 0;
}