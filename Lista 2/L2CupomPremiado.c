#include <stdio.h>

int main() {
    int qnt_cupons, premiados = 0, comuns = 0;
    scanf("%d", &qnt_cupons);

    for (int i = 0; i < qnt_cupons; i++) {
        int cupom, pontuacao_cupom = 0, pares = 0, impares = 0;
        scanf("%d", &cupom);

        while(cupom != 0) {
            int algoritmo;
            algoritmo = cupom % 10;

            if (algoritmo % 2 == 0) {
                pares += 1;
                pontuacao_cupom += algoritmo * 2;
            }
            else {
                impares += 1;
                pontuacao_cupom += algoritmo * 3;
            }

            cupom = cupom / 10;
        }
        if (pares > impares) {
            pontuacao_cupom += 5;
        }
        else if (impares > pares) {
            pontuacao_cupom += 3;
        }
        else {
            pontuacao_cupom += 1;
        }

        if (pontuacao_cupom % 10 == 0) {
            printf("%d PREMIADO\n", pontuacao_cupom);
            premiados += 1;
        }
        else {
            printf("%d COMUM\n", pontuacao_cupom);
            comuns += 1;
        }
    }

    printf("Premiados: %d\n", premiados);

    printf("Comuns: %d\n", comuns);

    if (premiados > comuns) {
        printf("Resultado: PROMOCAO");
    }
    else if (comuns > premiados) {
        printf("Resultado: NORMAL");
    }
    else {
        printf("Resultado: EMPATE");
    }

    return 0;
}