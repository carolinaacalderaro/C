#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sigla[20];
    int nota_acumulada;
} CentroAcademico;

typedef struct {
    int id_trabalho;
    char sigla_centro[20];
    int nota;
} Trabalho;

void converter_txt_para_bin(char *arq_txt, char *arq_bin) {
    FILE *ft = fopen(arq_txt, "r");
    if (ft == NULL) return;
    FILE *fb = fopen(arq_bin, "wb");
    if (fb == NULL) {
        fclose(ft);
        return;
    }

    int id_sessao, q;

    fscanf(ft, "%d", &id_sessao);
    fscanf(ft, "%d", &q);
    fwrite(&id_sessao, sizeof(int), 1, fb);
    fwrite(&q, sizeof(int), 1, fb);

    for (int i = 0; i < q; i++) {
        Trabalho t;
        memset(&t, 0, sizeof(Trabalho));
        fscanf(ft, "%d %19s %d", &t.id_trabalho, t.sigla_centro, &t.nota);
        fwrite(&t, sizeof(Trabalho), 1, fb);
    }

    fclose(ft);
    fclose(fb);
}

void processar_planilha_bin(char *arq_bin, CentroAcademico *centros, int qtd_centros,
                            Trabalho **trabalhos, int *qtd_trabalhos) {
    FILE *fb = fopen(arq_bin, "rb");
    if (fb == NULL) return;

    int id_sessao, q;
    fread(&id_sessao, sizeof(int), 1, fb);
    fread(&q, sizeof(int), 1, fb);

    for (int i = 0; i < q; i++) {
        Trabalho t;
        if (fread(&t, sizeof(Trabalho), 1, fb) != 1) break;

        Trabalho *novo = realloc(*trabalhos, (*qtd_trabalhos + 1) * sizeof(Trabalho));
        if (novo == NULL) break;
        *trabalhos = novo;
        (*trabalhos)[*qtd_trabalhos] = t;
        (*qtd_trabalhos)++;

        for (int j = 0; j < qtd_centros; j++) {
            if (strcmp(centros[j].sigla, t.sigla_centro) == 0) {
                centros[j].nota_acumulada += t.nota;
                break;
            }
        }
    }

    fclose(fb);
}

int main() {
    int c;
    scanf("%d", &c);

    CentroAcademico *centros = malloc(c * sizeof(CentroAcademico));
    for (int i = 0; i < c; i++) {
        scanf("%19s", centros[i].sigla);
        centros[i].nota_acumulada = 0;
    }

    int n;
    scanf("%d", &n);

    Trabalho *trabalhos = NULL;
    int qtd_trabalhos = 0;

    for (int i = 0; i < n; i++) {
        char arq_txt[256], arq_bin[256];
        scanf("%255s %255s", arq_txt, arq_bin);

        converter_txt_para_bin(arq_txt, arq_bin);
        processar_planilha_bin(arq_bin, centros, c, &trabalhos, &qtd_trabalhos);

        printf("Processamento concluido: %s -> %s\n", arq_txt, arq_bin);
    }

    for (int i = 1; i < c; i++) {
        CentroAcademico chave = centros[i];
        int j = i - 1;
        while (j >= 0 && centros[j].nota_acumulada < chave.nota_acumulada) {
            centros[j + 1] = centros[j];
            j--;
        }
        centros[j + 1] = chave;
    }

    for (int i = 1; i < qtd_trabalhos; i++) {
        Trabalho chave = trabalhos[i];
        int j = i - 1;
        while (j >= 0 && trabalhos[j].nota < chave.nota) {
            trabalhos[j + 1] = trabalhos[j];
            j--;
        }
        trabalhos[j + 1] = chave;
    }

    printf("=== RANKING INSTITUCIONAL (CENTROS) ===\n");
    for (int i = 0; i < c; i++) {
        printf("%do Lugar: %s - %d pontos\n", i + 1, centros[i].sigla, centros[i].nota_acumulada);
    }

    printf("=== RANKING INDIVIDUAL (TOP 3 TRABALHOS) ===\n");
    int top = qtd_trabalhos < 3 ? qtd_trabalhos : 3;
    for (int i = 0; i < top; i++) {
        printf("%do Lugar: Trabalho %d (%s) - Nota %d\n", i + 1,
               trabalhos[i].id_trabalho, trabalhos[i].sigla_centro, trabalhos[i].nota);
    }

    free(trabalhos);
    free(centros);
    return 0;
}