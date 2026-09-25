#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*Acao_t)(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas);

int acaoIgnorar(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    return estado_atual;
}

int acaoDeslocar(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    *energia -= *(int *)payload;
    if (*energia < 0) {
        *energia = 0;
        return 2; 
    }
    return estado_atual;
}

int acaoMinerar(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    *energia += *(int *)payload;
    return 1; 
}

int acaoTransmitir(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    printf("[TRANSMISSAO] %s\n", (char *)payload);

    *energia -= 5;
    if (*energia < 0) *energia = 0;
    return estado_atual;
}

int acaoClonar(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    int expansao = *(int *)payload;
    
    if (*energia < 70) {
        printf("[SISTEMA] Falha na clonagem: energia insuficiente\n");
        return estado_atual;
    }
    
    *energia -= 70;
    
    Acao_t ***p_matriz = (Acao_t ***)matriz;
    int linhas_atuais = *linhas;
    int colunas_antigas = *colunas;
    int novas_colunas = colunas_antigas + expansao;
    
    for (int i = 0; i < linhas_atuais; i++) {
        Acao_t *temp = realloc((*p_matriz)[i], novas_colunas * sizeof(Acao_t));
        if (temp == NULL) exit(1);
        (*p_matriz)[i] = temp;
        
        for (int j = colunas_antigas; j < novas_colunas; j++) {
            (*p_matriz)[i][j] = acaoIgnorar;
        }
    }
    
    *colunas = novas_colunas;
    printf("[SISTEMA] Sonda clonada e matriz expandida para %d eventos\n", novas_colunas);
    
    return 0; 
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int q;
    scanf("%d", &q);
    
    Acao_t **matriz = (Acao_t **)malloc(n * sizeof(Acao_t *));
    
    for (int i = 0; i < n; i++) {
        matriz[i] = (Acao_t *)malloc(m * sizeof(Acao_t));
        if (matriz[i] == NULL) {
            for (int k = 0; k < i; k++) free(matriz[k]);
            free(matriz);
            exit(1);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matriz[i][j] = acaoIgnorar;
        }
    }
    
    for (int k = 0; k < q; k++) {
        int est, ev;
        char codigo;
        scanf("%d %d %c", &est, &ev, &codigo);
        
        if (est >= 0 && est < n && ev >= 0 && ev < m) {
            if (codigo == 'I') matriz[est][ev] = acaoIgnorar;
            else if (codigo == 'D') matriz[est][ev] = acaoDeslocar;
            else if (codigo == 'M') matriz[est][ev] = acaoMinerar;
            else if (codigo == 'T') matriz[est][ev] = acaoTransmitir;
            else if (codigo == 'C') matriz[est][ev] = acaoClonar;
        }
    }
    
    int estado_atual, energia;
    scanf("%d %d", &estado_atual, &energia);
    
    int linhas = n;
    int colunas = m;
    int ev_telemetria;
    char tipo_dado;
    
    while (scanf("%d %c", &ev_telemetria, &tipo_dado) != EOF) {
        void *payload = NULL;
        int val_int = 0;
        char val_str[100];
        
        if (tipo_dado == 'I') {
            scanf("%d", &val_int);
            payload = &val_int;
        } else if (tipo_dado == 'S') {
            scanf("%s", val_str);
            payload = val_str;
        }
        
        if (estado_atual >= 0 && estado_atual < linhas && ev_telemetria >= 0 && ev_telemetria < colunas) {
            estado_atual = matriz[estado_atual][ev_telemetria](estado_atual, &energia, payload, &matriz, &linhas, &colunas);
        }
        
        printf("[CLONE] Evento: %d | Energia: %d | Novo Estado: %d\n", ev_telemetria, energia, estado_atual);
    }
    
    for (int i = 0; i < linhas; i++) free(matriz[i]);
    free(matriz);
    
    return 0;
}