#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;
    int atrib2;
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;
    SubSistema sistemas[];
};

void subrotina_defesa(Mecha *m, int slot, int input, int *output) {
    int dano_final = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);

    if (dano_final < 0) {
        dano_final = 0;
    }

    *output = dano_final;
}

void subrotina_utilidade(Mecha *m, int slot, int input, int *output) {
    int recuperado = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);

    m->energia_atual += recuperado;
    *output = recuperado;
}

void subrotina_ataque(Mecha *m, int slot, int input, int *output) {
    int custo = m->sistemas[slot].atrib2;

    if (m->energia_atual < custo) {
        *output = 0;
    }
    else {
        int dano = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;

        m->energia_atual -= custo;
        *output = dano;
    }
}

int comparar_mechas(const void *a, const void *b) {
    Mecha **m1 = (Mecha **)a;
    Mecha **m2 = (Mecha **)b;

    if ((*m1)->id < (*m2)->id) {
        return -1;
    }
    else if ((*m1)->id > (*m2)->id) {
        return 1;
    }

    return 0;
}

int main() {
    int n;

    scanf("%d", &n);

    Mecha **esquadrao = (Mecha **)malloc(n * sizeof(Mecha *));

    for (int i = 0; i < n; i++) {
        int id, energia, q;
        char modelo[50];

        scanf("%d %s %d %d", &id, modelo, &energia, &q);

        Mecha *m = (Mecha *)malloc(sizeof(Mecha) + q * sizeof(SubSistema));

        m->id = id;
        strcpy(m->modelo, modelo);
        m->energia_atual = energia;
        m->num_sistemas = q;

        for (int j = 0; j < q; j++) {
            char tipo;

            scanf(" %c %s %d %d", &tipo, m->sistemas[j].nome, &m->sistemas[j].atrib1, &m->sistemas[j].atrib2);

            if (tipo == 'D') {
                m->sistemas[j].subrotina = subrotina_defesa;
            }
            else if (tipo == 'U') {
                m->sistemas[j].subrotina = subrotina_utilidade;
            }
            else if (tipo == 'A') {
                m->sistemas[j].subrotina = subrotina_ataque;
            }
        }

        scanf("%d", &m->valor_wintermute);

        esquadrao[i] = m;
    }

    qsort(esquadrao, n, sizeof(Mecha *), comparar_mechas);

    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < n; i++) {
        Mecha *m = esquadrao[i];

        printf("ID: %d | MECHA: %s | ENERGIA: %d\n",
               m->id, m->modelo, m->energia_atual);

        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == subrotina_defesa) {
                int resultado = 0;

                m->sistemas[j].subrotina(
                    m, j, m->valor_wintermute, &resultado
                );

                printf("-> [DEFESA] %s | Dano final sofrido: %d\n",
                       m->sistemas[j].nome, resultado);
            }
        }

        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == subrotina_utilidade) {
                int resultado = 0;

                m->sistemas[j].subrotina(
                    m, j, m->valor_wintermute, &resultado
                );

                printf("-> [UTILIDADE] %s | Energia atual: %d\n",
                       m->sistemas[j].nome, m->energia_atual);
            }
        }

        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == subrotina_ataque) {
                int resultado = 0;
                int energia_suficiente = m->energia_atual >= m->sistemas[j].atrib2;

                m->sistemas[j].subrotina(
                    m, j, m->valor_wintermute, &resultado
                );

                if (!energia_suficiente) {
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n",
                           m->sistemas[j].nome);
                }
                else {
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n",
                           m->sistemas[j].nome,
                           resultado,
                           m->energia_atual);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("-----------------------------------------\n");
    }

    printf("Esquadrao pronto para o combate.\n");

    for (int i = 0; i < n; i++) {
        free(esquadrao[i]);
    }

    free(esquadrao);

    return 0;
}