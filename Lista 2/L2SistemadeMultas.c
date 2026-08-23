#include <stdio.h>

int main() {
    int C, P, arrecadacao_multas = 0, carros_ponto = 0;
    
    scanf("%d %d", &C, &P);

    for (int i = 0; i < C; i++) {
        float infracoes = 0, hora_anterior, minuto_anterior, posicao_anterior; 

        for (int j = 0; j < P; j++) {
            float hora, minuto, posição;
            scanf("%f %f %f", &hora, &minuto, &posição);
            
            if (j > 0) {
                float tempo_anterior = hora_anterior * 60 + minuto_anterior;
                float tempo_atual = hora * 60 + minuto;

                float tempo = tempo_atual - tempo_anterior;
                float distancia = posição - posicao_anterior;

                if (distancia < 0) {
                    distancia = - distancia;
                }

                if (distancia * 60 > tempo * 100) {
                    infracoes++;
                }
            }

            hora_anterior = hora;
            minuto_anterior = minuto;
            posicao_anterior = posição;
        }
    
        if (infracoes >= 1) {
            arrecadacao_multas += 100;
        }
        if (infracoes >= 2) {
            arrecadacao_multas += 200;
        }
        if (infracoes >= 3) {
            arrecadacao_multas += 300;
        }
        if (infracoes >= 4) {
            arrecadacao_multas += 1000;
            carros_ponto++;
        }

    }

    printf("Arrecadacao Multas: %d\n", arrecadacao_multas);
    printf("Carros com ponto na carteira: %d", carros_ponto);

    return 0;
}