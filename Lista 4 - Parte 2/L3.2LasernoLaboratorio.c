#include <stdio.h>

int mudar_direcao(int direcao, char espelho) {
    if (espelho == '/') {
        if (direcao == 0) {
            direcao = 3;
        }
        else if (direcao == 3) {
            direcao = 0;
        }
        else if (direcao == 1) {
            direcao = 2;
        }
        else if (direcao == 2) {
            direcao = 1;
        }
    }

    else if (espelho == '\\') {
        if (direcao == 0) {
            direcao = 2;
        }
        else if (direcao == 2) {
            direcao = 0;
        }
        else if (direcao == 1) {
            direcao = 3;
        }
        else if (direcao == 3) {
            direcao = 1;
        }
    }

    return direcao;
}

int main() {
    int L, C;

    scanf("%d %d", &L, &C);

    char matriz[L][C + 1];

    for (int i=0; i<L; i++) {
        scanf("%s", matriz[i]);
    }

    int linha, coluna;

    scanf("%d %d", &linha, &coluna);

    char direcao[20];

    scanf("%s", direcao);

    int direcao_numero;

    if (direcao[0] == 'C') {
        direcao_numero = 0;
    }
    else if (direcao[0] == 'B') {
        direcao_numero = 1;
    }
    else if (direcao[0] == 'E') {
        direcao_numero = 2;
    }
    else {
        direcao_numero = 3;
    }

    int direcionamento_linha[4] = {-1, 1, 0, 0};
    int direcionamento_coluna[4] = {0, 0, -1, 1};

    while (linha >= 0 && linha < L && coluna >= 0 && coluna < C) {
        if (matriz[linha][coluna] == '.') {
            matriz[linha][coluna] = '*';
        }

        if (matriz[linha][coluna] == '#') {
            linha = -1;
        }
        else {
            if (matriz[linha][coluna] == '/' || matriz[linha][coluna] == '\\') {
                direcao_numero = mudar_direcao(direcao_numero, matriz[linha][coluna]);
            }

            linha += direcionamento_linha[direcao_numero];
            coluna += direcionamento_coluna[direcao_numero];
        }
    }

    for (int i=0; i<L; i++) {
        printf("%s\n", matriz[i]);
    }

    return 0;
}