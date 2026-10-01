#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[205];
    int populacao;
    char funcao[205];
    int perigo;
} Cidadela;

void formatar_palavra(char *destino, const char *origem) {
    int tam = strlen(origem);
    
    if (tam == 0) {
        destino[0] = '\0';
        return;
    }

    if (origem[0] >= 'a' && origem[0] <= 'z') {
        destino[0] = origem[0] - 32;
    } 
    else {
        destino[0] = origem[0];
    }

    for (int i = 1; i < tam; i++) {
        if (origem[i] >= 'A' && origem[i] <= 'Z') {
            destino[i] = origem[i] + 32;
        } 
        else {
            destino[i] = origem[i];
        }
    }
    
    destino[tam] = '\0'; 
}

int comparar_cidadelas(const void *a, const void *b) {
    Cidadela *c1 = (Cidadela *)a;
    Cidadela *c2 = (Cidadela *)b;

    if (c1->populacao != c2->populacao) {
        if (c1->populacao > c2->populacao) {
            return -1;
        } else {
            return 1;
        }
    }
    
    if (c1->perigo != c2->perigo) {
        return c2->perigo - c1->perigo;
    }
    
    return strcmp(c1->nome, c2->nome);
}

int main() {
    int cap = 10;   
    int total = 0;  

    Cidadela *lista = (Cidadela *) malloc(cap * sizeof(Cidadela));

    char linha[300];
    int achou_chave = 0;
    int chave = 0;

    while (fgets(linha, sizeof(linha), stdin)) {
        int tam = strlen(linha);

        char nome_bruto[205] = "";
        char func_bruta[205] = "";
        
        int valor_num = 0;
        int perigo = 0;
        int tem_exclamacao = 0;
        int i_nome = 0;
        int i_func = 0;

        for (int i = 0; i < tam; i++) {
            if (linha[i] == '!') {
                tem_exclamacao = 1;
            }

            if (linha[i] >= 'A' && linha[i] <= 'Z') {
                nome_bruto[i_nome] = linha[i];
                i_nome++;
            }

            if (linha[i] >= '0' && linha[i] <= '9') {
                valor_num = (valor_num * 10) + (linha[i] - '0');
            }

            if (linha[i] == '*') {
                perigo++;
            }

            if (i < tam - 1 && linha[i] == ' ' && linha[i+1] == ' ') {
                if (i + 2 < tam && ((linha[i+2] >= 'a' && linha[i+2] <= 'z') || (linha[i+2] >= 'A' && linha[i+2] <= 'Z'))) {
                    func_bruta[i_func] = linha[i+2]; 
                    i_func++;                        
                }
                i++; 
            }
        }

        nome_bruto[i_nome] = '\0';
        func_bruta[i_func] = '\0';

        if (tem_exclamacao) {
            chave = valor_num;
            achou_chave = 1;
        } 
        else {
            if (total >= cap) {
                cap = cap * 2;
                lista = (Cidadela *) realloc(lista, cap * sizeof(Cidadela));
            }

            Cidadela c;
            formatar_palavra(c.nome, nome_bruto);
            formatar_palavra(c.funcao, func_bruta);
            c.populacao = valor_num;
            c.perigo = perigo;

            lista[total] = c;
            total++;
        }
    }

    if (!achou_chave) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } 
    else {
        qsort(lista, total, sizeof(Cidadela), comparar_cidadelas);

        if (chave >= 1 && chave <= total) {
            Cidadela alvo = lista[chave - 1]; 

            printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ",
                   alvo.nome, alvo.populacao, alvo.funcao);

            for (int i = 0; i < alvo.perigo; i++) {
                printf("*");
            }
            printf(".");

            if (alvo.populacao >= 1000 && alvo.perigo > 3) {
                printf(" Talvez seja melhor desistir...\n");
            } 
            else if (alvo.populacao >= 1000) {
                printf(" Um lugar denso, vai ser difícil achar ela.\n");
            } 
            else if (alvo.perigo > 3) {
                printf(" Vai ser complicado entrar lá.\n");
            } 
            else {
                printf("\n");
            }
        }
    }

    free(lista);

    return 0;
}