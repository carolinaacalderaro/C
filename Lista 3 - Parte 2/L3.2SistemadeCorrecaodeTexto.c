#include <stdio.h>

int eh_maiuscula(char letra) {
    if (letra >= 'A' && letra <= 'Z') {
        return 1;
    }

    return 0;
}

int eh_minuscula(char letra) {
    if (letra >= 'a' && letra <= 'z') {
        return 1;
    }

    return 0;
}

int eh_letra(char letra) {
    if (eh_maiuscula(letra) == 1 || eh_minuscula(letra) == 1) {
        return 1;
    }

    return 0;
}

char virar_maiuscula(char letra) {
    if (eh_minuscula(letra) == 1) {
        return letra - 'a' + 'A';
    }

    return letra;
}

char virar_minuscula(char letra) {
    if (eh_maiuscula(letra) == 1) {
        return letra - 'A' + 'a';
    }

    return letra;
}

int main() {
    char texto[1001];

    int i = 0;
    int erros = 0;
    int frases_minusculas = 0;
    int palavras = 0;

    int inicio_frase = 1;
    int inicio_palavra = 1;

    scanf("%c", &texto[i]);

    while (texto[i] != '\n') {
        i++;
        scanf("%c", &texto[i]);
    }

    texto[i] = '\0';

    if (texto[0] == '\0') {
        printf("Texto vazio! Nota: 0.0");
        return 0;
    }

    for (i = 0; texto[i] != '\0'; i++) {

        if (eh_letra(texto[i]) == 1) {

            if (inicio_frase == 1) {
                palavras++;

                if (eh_minuscula(texto[i]) == 1) {
                    frases_minusculas++;
                    erros++;
                    texto[i] = virar_maiuscula(texto[i]);
                }

                inicio_frase = 0;
                inicio_palavra = 0;
            }

            else {
                if (eh_maiuscula(texto[i]) == 1) {
                    erros++;
                    texto[i] = virar_minuscula(texto[i]);
                }

                if (inicio_palavra == 1) {
                    palavras++;
                    inicio_palavra = 0;
                }
            }
        }

        if (texto[i] == ' ') {
            inicio_palavra = 1;
        }

        if (texto[i] == '.' || texto[i] == '!' || texto[i] == '?') {
            inicio_frase = 1;
            inicio_palavra = 1;
        }
    }

    float nota = 10.0 - (0.5 * erros);

    if (nota < 0.0) {
        nota = 0.0;
    }

    printf("Texto corrigido: \n%s\n", texto); 
    printf("Frases que iniciavam com letra minúscula: %d\n", frases_minusculas); 
    printf("Total de palavras: %d\n", palavras); 
    printf("Total de erros: %d\n", erros); 
    printf("Nota: %.1f", nota);
    
    return 0;
}