#include <stdio.h>
#include <string.h>

typedef struct {
    char titular[51];
    float saldo;
    int ativa;
} Conta;

int main() {
    FILE *arq;
    Conta c;
    int n, k, i, numero;
    char op[20];
    float valor;

    arq = fopen("contas.bin", "w+b");
    if (arq == NULL) {
        return 1;
    }

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        memset(&c, 0, sizeof(Conta));
        scanf("%f %50[^\n]", &c.saldo, c.titular);
        c.ativa = 1;
        fwrite(&c, sizeof(Conta), 1, arq);
    }

    scanf("%d", &k);
    for (i = 0; i < k; i++) {
        scanf("%s %d", op, &numero);

        valor = 0;
        if (strcmp(op, "DEPOSITAR") == 0 || strcmp(op, "SACAR") == 0) {
            scanf("%f", &valor);
        }

        if (numero < 1 || numero > n) {
            printf("Conta inexistente\n");
            continue;
        }

        fseek(arq, (long)(numero - 1) * sizeof(Conta), SEEK_SET);
        fread(&c, sizeof(Conta), 1, arq);

        if (c.ativa == 0) {
            printf("Conta encerrada\n");
            continue;
        }

        if (strcmp(op, "CONSULTAR") == 0) {
            printf("%s - saldo: %.2f\n", c.titular, c.saldo);
        } 
        else if (strcmp(op, "DEPOSITAR") == 0) {
            c.saldo += valor;
            fseek(arq, (long)(numero - 1) * sizeof(Conta), SEEK_SET);
            fwrite(&c, sizeof(Conta), 1, arq);
            printf("Saldo atual: %.2f\n", c.saldo);
        } 
        else if (strcmp(op, "SACAR") == 0) {
            if (valor > c.saldo) {
                printf("Saldo insuficiente\n");
            } 
            else {
                c.saldo -= valor;
                fseek(arq, (long)(numero - 1) * sizeof(Conta), SEEK_SET);
                fwrite(&c, sizeof(Conta), 1, arq);
                printf("Saldo atual: %.2f\n", c.saldo);
            }
        } 
        else if (strcmp(op, "ENCERRAR") == 0) {
            c.ativa = 0;
            fseek(arq, (long)(numero - 1) * sizeof(Conta), SEEK_SET);
            fwrite(&c, sizeof(Conta), 1, arq);
            printf("Conta encerrada com sucesso\n");
        }
    }

    printf("Contas ativas:\n");
    rewind(arq);
    numero = 1;
    while (fread(&c, sizeof(Conta), 1, arq) == 1) {
        if (c.ativa == 1) {
            printf("%d %s %.2f\n", numero, c.titular, c.saldo);
        }
        numero++;
    }

    fclose(arq);
    return 0;
}