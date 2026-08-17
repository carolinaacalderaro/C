#include <stdio.h>

int main() {
    int total_dinheiro, x, y, z, A = 0, B = 0, C = 0, sobra = 0, investiu = -1, novo_total = 0, dinheiro_final = 0;
    
    scanf("%d", &total_dinheiro);
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);

    if ((x * total_dinheiro) % 100 == 0 && (y * total_dinheiro) % 100 == 0 && (z * total_dinheiro) % 100 == 0) {
        A = (x * total_dinheiro) / 100;
        B = (y * total_dinheiro) / 100;
        C = (z * total_dinheiro) / 100;
        
        sobra = total_dinheiro - A - B - C;

        investiu = 0;
    }

    if (investiu == -1) {
        novo_total = total_dinheiro + 1;

        if ((x * novo_total) % 100 == 0 && (y * novo_total) % 100 == 0 && (z * novo_total) % 100 == 0) {
            A = x * novo_total / 100;
            B = y * novo_total / 100;
            C = z * novo_total / 100;
            
            sobra = novo_total - A - B - C;

            if (sobra > 1) {
                investiu = 1;
            }
        }
    }

    if (investiu == -1) {
        novo_total = total_dinheiro + 2;

        if ((x * novo_total) % 100 == 0 && (y * novo_total) % 100 == 0 && (z * novo_total) % 100 == 0) {
            A = x * novo_total / 100;
            B = y * novo_total / 100;
            C = z * novo_total / 100;
            
            sobra = novo_total - A - B - C;

            if (sobra > 2) {
                investiu = 2;
            }
        }
    }

    if (investiu == -1) {
        novo_total = total_dinheiro + 3;

        if ((x * novo_total) % 100 == 0 && (y * novo_total) % 100 == 0 && (z * novo_total) % 100 == 0) {
            A = x * novo_total / 100;
            B = y * novo_total / 100;
            C = z * novo_total / 100;
            
            sobra = novo_total - A - B - C;

            if (sobra > 3) {
                investiu = 3;
            }
        }
    }

    if (investiu != -1) {

        dinheiro_final = (3 - investiu) + sobra;

        printf("Cada homem ficou com %d, %d e %d reais, respectivamente.\n", A, B, C);
    }

    else {
        dinheiro_final = 3;

        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
    }

    if (investiu == 2) {
        char l1, l2, l3;

        scanf(" %c %c %c", &l1, &l2, &l3);

        int soma = (l1 - 'a' + 1) + (l2 - 'a' + 1) + (l3 - 'a' + 1);

        printf("%d\n", soma);
    }

    else if (investiu == 3) {
        int i1, i2, i3, parcelas = 0;

        scanf("%d %d %d", &i1, &i2, &i3);

        if (i1 % 3 == 0 || i2 % 3 == 0 || i3 % 3 == 0) {
            if (i1 % 3 ==0) {
                parcelas += i1 / 3;
            }

            if (i2 % 3 == 0) {
                parcelas += i2 / 3;
            }

            if (i3 % 3 == 0) {
                parcelas += i3 / 3;
            }
        printf("%d\n", parcelas);
        }
    }

    if (dinheiro_final >= 7) {
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir na noite passada!\n");
    }

    else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }

    return 0;
}