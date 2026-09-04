#include <stdio.h>

int main() {
    int n, posicao = 0;

    scanf("%d", &n);

    int vetor[n];

    for (int i=0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    for (int i=0; i < n; i++) {
        if (vetor[i] == 0) {
            posicao = i;

            for (int j=posicao-1; j >= 0; j--) {
                printf("%d ", vetor[j]);
            }
            printf("0 ");
            
        }


    }


    return 0;
}