#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    int populacao;
    int periculosidade;
    char funcao[100];
} Espionagem;

int comparar(const void *a, const void *b) {
    Espionagem *c1 = (Espionagem *)a;
    Espionagem *c2 = (Espionagem *)b;

    if (c2 -> populacao != c1 -> populacao) {
        return (c2 -> populacao) - (c1 -> populacao);
    }
    if (c2 -> periculosidade != c1 -> periculosidade) {
        return (c2 -> periculosidade) - (c1 -> periculosidade);
    }

    return strcmp(c1 -> nome, c2 -> nome);
}

int main() {
    char frase[200];
    Espionagem lista[100];
    int totalCidadelas = 0;
    char chaveSecreta[100];

    while (fgets(frase, 200, stdin) != NULL) {
        if (strchr(frase, '!') != NULL) {
            frase[strcspn(frase, "\n")] = '0';

            strcpy(chaveSecreta, frase);

            continue;
        }
        char nomeTemp[100];
        char funcaoTemp[100];
        int indiceNome = 0, indiceFuncao = 0, populacao = 0, periculosidade = 0, achou_espaco_duplo = 0;

        for (int i = 0; frase[i] != '\0'; i++) {
            if (frase[i] >= 'A' && frase[i] <= 'Z') {
                nomeTemp[indiceNome] = frase[i];
                indiceNome++;
            }

            if (frase[i] >= '0' && frase[i] <= 9) {
                populacao = (populacao * 10) + (frase[i] - '0');
            }
            if (frase[i] == '*') {
                periculosidade++;
            }
            if (frase[i] == ' ' && frase[i+1] == ' ') {
                achou_espaco_duplo = 1;
                i++;
                continue;
            }
            if (achou_espaco_duplo) {
                if ((frase[i] >= 'A' && frase[i] <= 'Z') || (frase[i] >= 'a' && frase[i] <= 'z')) {
                    funcaoTemp[indiceFuncao] = frase[i];
                    indiceFuncao++;
                }
            }
        }
        nomeTemp[indiceNome] = '\0';
        funcaoTemp[indiceFuncao] = '\0';

        if (strlen(nomeTemp) > 0) {
            if (nomeTemp[0] >= 'a' && nomeTemp[0] <= 'z') {
                nomeTemp[0] = nomeTemp[0] - 32;
            }
            for (int i = 1; nomeTemp[i] != '\0'; i++) {
                if (nomeTemp[i] >= 'A' && nomeTemp[i] <= 'Z') {
                    nomeTemp[i] = nomeTemp[i] + 32;
                }
            }
        }

        strcpy(lista[totalCidadelas].nome, nomeTemp);
        lista[totalCidadelas].populacao = populacao;
        lista[totalCidadelas].periculosidade = periculosidade;
        strcpy(lista[totalCidadelas].funcao, funcaoTemp);

        totalCidadelas++;
    }

    qsort(lista, totalCidadelas, sizeof(Espionagem), comparar);

    int chaveEncontrada = -1;

    for (int i = 0; chaveSecreta[i] != '\0'; i++) {
        if (chaveSecreta[i] >= '0' && chaveSecreta[i] <= 9) {
            sscanf(&chaveSecreta[i], "%d", &chaveEncontrada);
            break;
        }
    }

    return 0;
}