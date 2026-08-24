#include <stdio.h>

int main() {
    int energia_pou = 10;

    while (energia_pou > 0) {
        char acao;
        int energia;
        scanf("%c %d", &acao, &energia);

        if (acao == 'a') {
            if (energia_pou >= 10) {
                printf("O Pou está muito gordinho... ele precisa brincar!\n");

            }
            else {
                for (int i = 1; i <= energia; i++) {
                    energia_pou += 1;
                    printf("Alimento %d foi consumido.\n", i);
                }

                printf("%d de energia recuperado! Meu total agora é %d.\n", energia, energia_pou);
                }
        }

        else if(acao == 'b') {
            if (energia ==1) {
                printf("Queimei meus neurônios em Memory!\n");
            }

            else if(energia == 2) {
                printf("Novo recorde em Free Fall!\n");
            }

            else if(energia == 3) {
                printf("Cliff Jump é demais!\n");
            }

            else if(energia == 4) {
                printf("Sky Jump é o clássico!\n");
            }
            
            energia_pou -= energia;

        }
    }

    printf("CONGRATURATION. THIS STORY IS HAPPY END. THANK YOU.");

    return 0;
}