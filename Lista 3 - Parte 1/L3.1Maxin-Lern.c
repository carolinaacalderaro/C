#include <stdio.h>
#include <math.h>


void ler_dataset(float caule[], float folha[], float raiz[], float broto[], int rotulos[], int n) {
    for (int i=0; i < n; i++) {
        scanf("%f %f %f %f %d", &caule[i], &folha[i], &raiz[i], &broto[i], &rotulos[i]);
    }
}

void calcular_centroides(float caule[], float folha[], float raiz[], float broto[], int rotulos[], int n, float centroide_caule[], float centroide_folha[], float centroide_raiz[], float centroide_broto[]) {
    int n_lunaria = 0, n_ignea = 0, n_bruma = 0;
    for (int j=0; j<n; j++) {
        if (rotulos[j] == 0) {
            n_lunaria += 1;
        } 
        else if (rotulos[j] == 1) {
            n_ignea += 1;
        }
        else {
            n_bruma += 1;
        }
    }
    
    for (int i=0; i<n; i++) {
        if (rotulos[i] == 0) {
            centroide_caule[rotulos[i]] += caule[i] / n_lunaria;
            centroide_folha[rotulos[i]] += folha[i] / n_lunaria;
            centroide_raiz[rotulos[i]] += raiz[i] / n_lunaria;
            centroide_broto[rotulos[i]] += broto[i] / n_lunaria;
        }
         else if (rotulos[i] == 1) {
            centroide_caule[rotulos[i]] += caule[i] / n_ignea;
            centroide_folha[rotulos[i]] += folha[i] / n_ignea;
            centroide_raiz[rotulos[i]] += raiz[i] / n_ignea;
            centroide_broto[rotulos[i]] += broto[i] / n_ignea;
        }
        else {
            centroide_caule[rotulos[i]] += caule[i] / n_bruma;
            centroide_folha[rotulos[i]] += folha[i] / n_bruma;
            centroide_raiz[rotulos[i]] += raiz[i] / n_bruma;
            centroide_broto[rotulos[i]] += broto[i] / n_bruma;
        }
    }
}

float distancia_quadrados(float caule, float folha, float raiz, float broto, float centroide_caule, float centroide_folha, float centroide_raiz, float centroide_broto) {
    float distancia = pow(caule - centroide_caule, 2) + pow(folha - centroide_folha, 2) + pow(raiz - centroide_raiz, 2) + pow(broto - centroide_broto, 2);
    
    return distancia;
}

int classificar(float caule, float folha, float raiz, float broto, float centroide_caule[], float centroide_folha[], float centroide_raiz[], float centroide_broto[]) {
    float distancia[3];

    for (int i=0; i < 3; i++) {
        distancia[i] = sqrt(distancia_quadrados(caule, folha, raiz, broto, centroide_caule[i], centroide_folha[i], centroide_raiz[i], centroide_broto[i]));
    }

    int menor = 0;

    for (int i=1; i<3; i++) {
        if (distancia[i] < distancia[menor]) {
            menor = i;
        }
    }

    return menor;
}

void classificar_conjunto(float caule[], float folha[], float raiz[], float broto[], int n, float centroide_caule[], float centroide_folha[], float centroide_raiz[], float centroide_broto[],int previstos[]) {
    for (int i=0; i<n; i++) {
        previstos[i] = classificar(caule[i], folha[i], raiz[i], broto[i], centroide_caule, centroide_folha, centroide_raiz, centroide_broto);
    }
}

void imprimir_especie(int classe) {
    if (classe == 0) {
        printf("Lunaria\n");
    }
    else if (classe == 1) {
        printf("Ignea\n");
    }
    else {
        printf("Bruma\n");
    }
}

void imprimir_previsoes(int previstos[], int n) {
    for (int i=0; i<n; i++) {
        printf("Amostra %d: ", i + 1);
        imprimir_especie(previstos[i]);
    }
}

float calcular_acuracia(int previstos[], int reais[], int n) {
    int acertos = 0;
    for (int i=0; i<n; i++) {
        if (previstos[i] == reais[i]) {
            acertos++;
        }
    }

    return ((float) acertos / n) * 100;
}

int main() {
    int treino, teste;

    scanf("%d", &treino);

    float caule_treino[treino], folha_treino[treino], raiz_treino[treino], broto_treino[treino];
    int rotulos[treino];
    float centroide_caule[3] = {0.0, 0.0, 0.0}, centroide_folha[3] = {0.0, 0.0, 0.0}, centroide_raiz[3] = {0.0, 0.0, 0.0}, centroide_broto[3] = {0.0, 0.0, 0.0};

    ler_dataset(caule_treino, folha_treino, raiz_treino, broto_treino, rotulos, treino);
    calcular_centroides(caule_treino, folha_treino, raiz_treino, broto_treino, rotulos, treino, centroide_caule, centroide_folha, centroide_raiz, centroide_broto);

    scanf("%d", &teste);

    float caule_teste[teste], folha_teste[teste], raiz_teste[teste], broto_teste[teste];
    int rotulo_esperado[teste], previstos[teste];

    for (int i=0; i<teste; i++) {
        scanf("%f %f %f %f %d", &caule_teste[i], &folha_teste[i], &raiz_teste[i], &broto_teste[i], &rotulo_esperado[i]);
    
    }

    classificar_conjunto(caule_teste, folha_teste, raiz_teste, broto_teste, teste, centroide_caule, centroide_folha, centroide_raiz, centroide_broto, previstos);

    imprimir_previsoes(previstos, teste);

    float acuracia = calcular_acuracia(previstos, rotulo_esperado, teste);
    
    printf("Acuracia: %.2f%%\n", acuracia);
    return 0;
}