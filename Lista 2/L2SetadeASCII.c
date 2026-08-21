#include <stdio.h>

int main() {
    int n, meio, metade = 0;
    scanf("%d", &n);

    if (n % 2 == 0) {
        meio = n / 2 - 1;
    }
    else {
        meio = n / 2;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > meio) {
                metade = 1;
            }

            if (metade == 0){
            
                if (j >= meio - i && j <= meio + i) {
                    printf(".");
                }
                else {
                    printf("#");
                }

            }
            else {
                if (j == meio) {
                    printf(".");
                }
                else {
                    printf("#");
                }
            }
        }
        printf("\n");
    } 
    
    return 0;
}