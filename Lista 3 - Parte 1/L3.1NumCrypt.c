#include <stdio.h>

void codificar(int deslocamento, int vetor[], int n) {
    printf("Código codificado: ");

    for (int i=0; i < n; i++) {
        if ((vetor[i] + deslocamento) > 9) {
            vetor[i] = (vetor[i] + deslocamento) % 10;
        }
        else {
            vetor[i] += deslocamento;
        }

        printf("%d ", vetor[i]);
    }
}

void decodificar(int deslocamento, int vetor[], int n) {
    printf("Código decodificado: ");

    for (int i=0; i < n; i++) {
        if (vetor[i] - deslocamento < 0) {
            vetor[i] = 10 + (vetor[i] - deslocamento);
        }

        else {
            vetor[i] -= deslocamento;
        }

        printf("%d ", vetor[i]);
    }
}

int verificador(int vetor[], int n) {
    int soma = 0, verificacao;
    for (int i=0; i < n; i++) {
        soma += vetor[i];
    }

    verificacao = soma % 10;

    printf("\nVerificador: %d", verificacao);

    return verificacao;
}

int main() {
    int n, deslocamento;
    char operacao;

    scanf("%d", &n);

    int vetor[n]; 

    for (int i=0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    scanf("%d", &deslocamento);

    scanf(" %c", &operacao);

    if (operacao == 'C') {
        codificar(deslocamento, vetor, n);
    }
    else {
        decodificar(deslocamento, vetor, n);
    }

    int verificacao = verificador(vetor, n);

    printf("\nNível de segurança: ");

    if (verificacao >= 0 && verificacao <= 2) {
        printf("BAIXO");
    }
    else if (verificacao <= 6) {
        printf("MÉDIO");
    }
    else {
        printf("ALTO");
    }

    return 0;
}