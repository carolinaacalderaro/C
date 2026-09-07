#include <stdio.h>

int main() {
    int n, posicao = 0, posicao_antiga = -1;

    scanf("%d", &n);

    int vetor[n];

    for (int i=0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    for (int i=0; i < n; i++) {
        if (vetor[i] == 0) {
            posicao = i;

            for (int j=posicao-1; j > posicao_antiga; j--) {
                printf("%d ", vetor[j]);
            }
            posicao_antiga = posicao;
            printf("0 ");
            
        }
    }

    if (vetor[n-1] != 0) {
            for (int k=n-1; k > posicao_antiga; k--) {
                printf("%d ", vetor[k]);
            }
    }

    return 0;
}