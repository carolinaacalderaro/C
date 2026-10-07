#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

typedef union {
    int valor_sinal;
    unsigned int valor_raw;
    struct {
        unsigned int resto : 30;
        unsigned int msb   : 2;
    } campos;
} SenhaUnion;

int main() {
    int hab_beep, hora_ini, min_ini;
    int dif_bau, senha_correta;
    SenhaUnion tentativa;

    scanf("%d | %d | %d", &hab_beep, &hora_ini, &min_ini);
    scanf("%d | %d", &dif_bau, &senha_correta);
    scanf("%d", &tentativa.valor_sinal);

    int tentativa_inicial = tentativa.valor_sinal;

    int inicio_ok = (hora_ini >= 18 || hora_ini < 4);

    int dif_relativa = (dif_bau - hab_beep) - 5;

    int etapas;
    if (dif_relativa <= 5) {
        etapas = 1;
    }
    else if (dif_relativa <= 10) {
        etapas = 2;
    }
    else {
        etapas = 3;
    }

    int min_por_etapa = 0;
    if (hab_beep != 0) {
        min_por_etapa = 120 / hab_beep;
    }
    int min_totais = etapas * min_por_etapa;

    int min_fin = min_ini + min_totais;
    int hora_fin = hora_ini + (min_fin / 60);
    min_fin %= 60;
    hora_fin %= 24;

    unsigned int fator = 1;
    unsigned int limite = 1073741824u;

    for (int i = 0; i < etapas; i++) {
        tentativa.valor_raw *= fator;

        unsigned int op = tentativa.campos.msb;
        unsigned int resto = tentativa.campos.resto / fator;

        unsigned int novo_valor = 0;

        if (op == 0) {
            novo_valor = resto + (unsigned int)(dif_bau / 10);
        }
        else if (op == 1) {
            novo_valor = resto - (unsigned int)(hab_beep / 20);
        }
        else if (op == 2) {
            novo_valor = resto * (unsigned int)(2 * hab_beep);
        }
        else if (op == 3) {
            unsigned int divisor = (unsigned int)(dif_bau / 5);
            if (divisor != 0) {
                novo_valor = resto / divisor;
            }
        }

        tentativa.valor_raw = novo_valor % limite;

        fator *= 4;
        limite /= 4;
    }

    printf("(%d) horario inicial: (%02d:%02d) | resultado encontrado: (%d)   horario final:(%02d:%02d)\n",
           tentativa_inicial, hora_ini, min_ini, tentativa.valor_sinal, hora_fin, min_fin);

    int terminou_a_tempo = 1;
    if (hora_fin > 4 && hora_fin < 18) {
        terminou_a_tempo = 0;
    } 
    else if (hora_fin == 4 && min_fin > 0) {
        terminou_a_tempo = 0;
    }

    if (tentativa.valor_sinal == senha_correta && terminou_a_tempo && inicio_ok) {
        printf("Beep sabia, Beep sempre sabe, BEEEEEEPPPPP\n");
    }
    else {
        printf("beepp, NA PROXIMA BEEP ABRIRAAAAAA\n");
    }

    return 0;
}