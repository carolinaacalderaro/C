#include <stdio.h>
#include <string.h>

int main() {
    FILE *entrada = fopen("requisicoes.txt", "r");
    FILE *saida;
    int n;
    int qtdSucesso = 0, qtdRedirecionamento = 0, qtdCliente = 0, qtdServidor = 0;
    int somaTempo = 0;
    int tempoMaisLento = -1;
    char endpointMaisLento[51] = "";
    double media;
    double taxaErro;
    const char *status;
    int i;

    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo requisicoes.txt\n");
        return 1;
    }

    if (fscanf(entrada, "%d", &n) != 1) {
        printf("Erro ao ler o arquivo requisicoes.txt\n");
        fclose(entrada);
        return 1;
    }

    for (i = 0; i < n; i++) {
        char endpoint[51];
        int codigo;
        int tempo;

        if (fscanf(entrada, "%50s %d %d", endpoint, &codigo, &tempo) != 3) {
            printf("Erro ao ler as requisicoes do arquivo\n");
            fclose(entrada);
            return 1;
        }

        if (codigo >= 200 && codigo <= 299) {
            qtdSucesso++;
        } 
        else if (codigo >= 300 && codigo <= 399) {
            qtdRedirecionamento++;
        } 
        else if (codigo >= 400 && codigo <= 499) {
            qtdCliente++;
        } 
        else if (codigo >= 500 && codigo <= 599) {
            qtdServidor++;
        }

        somaTempo += tempo;

        if (tempo > tempoMaisLento) {
            tempoMaisLento = tempo;
            strcpy(endpointMaisLento, endpoint);        }
    }

    fclose(entrada);

    saida = fopen("relatorio.txt", "w");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo relatorio.txt\n");
        return 1;
    }

    media = (double) somaTempo / n;
    taxaErro = 100.0 * (qtdCliente + qtdServidor) / n;

    if (taxaErro < 10.0) {
        status = "SAUDAVEL";
    } 
    else if (taxaErro < 30.0) {
        status = "ATENCAO";
    } 
    else {
        status = "CRITICO";
    }

    fprintf(saida, "=== RELATORIO DE REQUISICOES ===\n");
    fprintf(saida, "Total de requisicoes: %d\n", n);
    fprintf(saida, "Sucesso (2xx): %d\n", qtdSucesso);
    fprintf(saida, "Redirecionamento (3xx): %d\n", qtdRedirecionamento);
    fprintf(saida, "Erro de cliente (4xx): %d\n", qtdCliente);
    fprintf(saida, "Erro de servidor (5xx): %d\n", qtdServidor);
    fprintf(saida, "Tempo medio de resposta: %.2f ms\n", media);
    fprintf(saida, "Mais lenta: %s (%d ms)\n", endpointMaisLento, tempoMaisLento);
    fprintf(saida, "Taxa de erro: %.2f%%\n", taxaErro);
    fprintf(saida, "STATUS: %s\n", status);

    fclose(saida);

    return 0;
}
