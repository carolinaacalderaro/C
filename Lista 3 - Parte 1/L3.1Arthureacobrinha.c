#include <stdio.h>

int absoluto(int valor) {
    if (valor < 0) {
        return valor * -1;
    }
    return valor;
}

int obter_direcao(int diferenca) {
    if (diferenca > 0) {
        return 1;
    }
    if (diferenca < 0) {
        return -1;
    }
    return 0;
}

int calcular_distancia(int x1, int y1, int x2, int y2) {
    return absoluto(x1 - x2) + absoluto(y1 - y2);
}

int buscar_fruta_proxima(int pos_x, int pos_y, int frutas_x[], int frutas_y[], int coletadas[], int qtd_frutas) {
    int menor_distancia = 9999;
    int indice_alvo = -1;

    for (int i = 0; i < qtd_frutas; i++) {
        if (coletadas[i] == 0) {
            int distancia = calcular_distancia(pos_x, pos_y, frutas_x[i], frutas_y[i]);

            if (distancia < menor_distancia) {
                menor_distancia = distancia;
                indice_alvo = i;
            }
        }
    }
    return indice_alvo;
}

int posicao_valida(int x, int y, int corpo_x[], int corpo_y[], int tamanho_cobra) {
    for (int i = 0; i < tamanho_cobra - 1; i++) {
        if (corpo_x[i] == x && corpo_y[i] == y) {
            return 0;
        }
    }
    return 1;
}

int mover_cobra(int destino_x, int destino_y, int corpo_x[], int corpo_y[], int tamanho_cobra) {
    int pos_x = corpo_x[0];
    int pos_y = corpo_y[0];
    
    int dif_x = destino_x - pos_x;
    int dif_y = destino_y - pos_y;
    
    int novo_x = pos_x;
    int novo_y = pos_y;
    int moveu = 0;

    int tentativa_x[2];
    int tentativa_y[2];

    if (absoluto(dif_x) >= absoluto(dif_y)) {
        tentativa_x[0] = pos_x + obter_direcao(dif_x);
        tentativa_y[0] = pos_y;
        tentativa_x[1] = pos_x;
        tentativa_y[1] = pos_y + obter_direcao(dif_y);
    } else {
        tentativa_x[0] = pos_x;
        tentativa_y[0] = pos_y + obter_direcao(dif_y);
        tentativa_x[1] = pos_x + obter_direcao(dif_x);
        tentativa_y[1] = pos_y;
    }

    for (int i = 0; i < 2; i++) {
        if (moveu == 0) {
            int aproxima = 0;
            if (tentativa_x[i] != pos_x && dif_x != 0) {
                aproxima = 1;
            }
            if (tentativa_y[i] != pos_y && dif_y != 0) {
                aproxima = 1;
            }

            if (aproxima == 1) {
                if (posicao_valida(tentativa_x[i], tentativa_y[i], corpo_x, corpo_y, tamanho_cobra) == 1) {
                    novo_x = tentativa_x[i];
                    novo_y = tentativa_y[i];
                    moveu = 1;
                }
            }
        }
    }

    if (moveu == 1) {
        for (int i = tamanho_cobra - 1; i > 0; i--) {
            corpo_x[i] = corpo_x[i - 1];
            corpo_y[i] = corpo_y[i - 1];
        }
        corpo_x[0] = novo_x;
        corpo_y[0] = novo_y;
    }

    return moveu;
}

int main() {
    int tamanho_tabuleiro;
    int qtd_frutas;

    int frutas_x[10] = {0};
    int frutas_y[10] = {0};
    int coletadas[10] = {0};
    int corpo_x[50] = {0};
    int corpo_y[50] = {0};

    scanf("%d", &tamanho_tabuleiro);
    scanf("%d", &qtd_frutas);

    for (int i = 0; i < qtd_frutas; i++) {
        scanf("(%d,%d)", &frutas_x[i], &frutas_y[i]);
    }

    printf("Inicializando analise do movimento.\n");

    int tamanho_cobra = 1;
    int movimentos_totais = 0;

    corpo_x[0] = tamanho_tabuleiro / 2;
    corpo_y[0] = tamanho_tabuleiro / 2;

    for (int i = 0; i < qtd_frutas; i++) {
        int indice_alvo = buscar_fruta_proxima(corpo_x[0], corpo_y[0], frutas_x, frutas_y, coletadas, qtd_frutas);

        if (indice_alvo != -1) {
            int destino_x = frutas_x[indice_alvo];
            int destino_y = frutas_y[indice_alvo];
            int conseguiu = 1;

            while ((corpo_x[0] != destino_x || corpo_y[0] != destino_y) && conseguiu == 1) {
                conseguiu = mover_cobra(destino_x, destino_y, corpo_x, corpo_y, tamanho_cobra);
                
                if (conseguiu == 1) {
                    movimentos_totais++;
                }
            }

            if (conseguiu == 1) {
                coletadas[indice_alvo] = 1;
                tamanho_cobra++;

                printf("Fruta coletada, tamanho atual: %d e %d movimentos ate o momento.\n", tamanho_cobra, movimentos_totais);
            }
        }
    }

    printf("Interessante o comportamento, foram %d movimentos para coletar tudo. Eu nao podia ser mais craque, agora e bom eu voltar para os tickets.\n", movimentos_totais);

    return 0;
}