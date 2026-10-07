#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

union Identificacao {
    unsigned int matricula;
    unsigned long long cpf;
    unsigned int temporario;
};

struct Permissoes {
    unsigned laboratorio : 1;
    unsigned biblioteca : 1;
    unsigned estacionamento : 1;
    unsigned servidores : 1;
    unsigned noturno : 1;
    unsigned bloqueado : 1;
};

typedef struct {
    char tipo;
    union Identificacao id;
    struct Permissoes perm;
} Cartao;

int cartoes_iguais(Cartao c1, char tipo_busca, union Identificacao id_busca) {
    if (c1.tipo != tipo_busca) {
        return 0;
    }

    if (tipo_busca == 'M') {
        return c1.id.matricula == id_busca.matricula;
    }
    else if (tipo_busca == 'C') {
        return c1.id.cpf == id_busca.cpf;
    }
    else if (tipo_busca == 'T') {
        return c1.id.temporario == id_busca.temporario;
    }

    return 0;
}

int main() {
    int N;

    scanf("%d", &N);

    Cartao cartoes[100];

    for (int i = 0; i < N; i++) {
        scanf(" %c", &cartoes[i].tipo);

        if (cartoes[i].tipo == 'M') {
            scanf("%u", &cartoes[i].id.matricula);
        }
        else if (cartoes[i].tipo == 'C'){
            scanf("%llu", &cartoes[i].id.cpf);
        }
        else if (cartoes[i].tipo == 'T') {
            scanf("%u", &cartoes[i].id.temporario);
        }

        int lab, bib, est, ser, notu, blo;

        scanf("%d %d %d %d %d %d", &lab, &bib, &est, &ser, &notu, &blo);

        cartoes[i].perm.laboratorio = lab;
        cartoes[i].perm.biblioteca = bib;
        cartoes[i].perm.estacionamento = est;
        cartoes[i].perm.servidores = ser;
        cartoes[i].perm.noturno = notu;
        cartoes[i].perm.bloqueado = blo;
    }

    int Q;

    scanf("%d", &Q);

    for (int j = 0; j < Q; j++) {
        char tipo_req;
        union Identificacao id_req;
        char area, periodo;

        scanf(" %c", &tipo_req);

        if (tipo_req == 'M') {
            scanf("%u", &id_req.matricula);
        }
        else if (tipo_req == 'C') {
            scanf("%llu", &id_req.cpf);
        }
        else if (tipo_req == 'T') {
            scanf("%u", &id_req.temporario);
        }

        scanf(" %c %c", &area, &periodo);

        int indice_encontrado = -1;

        for (int k = 0; k < N; k++) {
            if (cartoes_iguais(cartoes[k], tipo_req, id_req)) {
                indice_encontrado = k;
                break;
            }
        }

        if (indice_encontrado == -1) {
            printf("CARTAO NAO ENCONTRADO\n");
            continue;
        }

        Cartao c = cartoes[indice_encontrado];

        if (c.perm.bloqueado == 1) {
            printf("ACESSO NEGADO\n");
            continue;
        }

        int tem_permissao_area = 0;
        if (area == 'L' && c.perm.laboratorio == 1) tem_permissao_area = 1;
        else if (area == 'B' && c.perm.biblioteca == 1) tem_permissao_area = 1;
        else if (area == 'E' && c.perm.estacionamento == 1) tem_permissao_area = 1;
        else if (area == 'S' && c.perm.servidores == 1) tem_permissao_area = 1;

        if (!tem_permissao_area) {
            printf("ACESSO NEGADO\n");
            continue;
        }

        if (periodo == 'N' && c.perm.noturno == 0) {
            printf("ACESSO NEGADO\n");
            continue;
        }

        printf("ACESSO LIBERADO\n");
    }

    return 0;
}