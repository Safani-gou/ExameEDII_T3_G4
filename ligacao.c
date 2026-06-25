#include <stdio.h>
#include <stdlib.h>
#include "ligacao.h"

/* Cria uma nova ligacao alocada na heap */
Ligacao* criarLigacao(int origem, int destino, float custo, float distancia) {
    Ligacao* l = (Ligacao*)malloc(sizeof(Ligacao));
    if (!l) {
        printf("[ERRO] Falha ao alocar memoria para ligacao.\n");
        return NULL;
    }
    l->origem    = origem;
    l->destino   = destino;
    l->custo     = custo;
    l->distancia = distancia;
    printf("[SUCESSO] Ligacao %d -> %d criada (Custo: %.2f Kz, Dist: %.2f m).\n",
           origem, destino, custo, distancia);
    return l;
}

/* Imprime os dados de uma ligacao */
void imprimirLigacao(const Ligacao* l) {
    if (!l) { printf("[ERRO] Ligacao invalida.\n"); return; }
    printf("  %d -> %d | Custo: %.2f Kz | Distancia: %.2f m\n",
           l->origem, l->destino, l->custo, l->distancia);
}

/* Libera memoria */
void destruirLigacao(Ligacao* l) {
    if (l) free(l);
}

/* Comparadores para ordenacao */
int compararPorCusto(const void* a, const void* b) {
    const Ligacao* la = (const Ligacao*)a;
    const Ligacao* lb = (const Ligacao*)b;
    if (la->custo < lb->custo) return -1;
    if (la->custo > lb->custo) return  1;
    return 0;
}

int compararPorDistancia(const void* a, const void* b) {
    const Ligacao* la = (const Ligacao*)a;
    const Ligacao* lb = (const Ligacao*)b;
    if (la->distancia < lb->distancia) return -1;
    if (la->distancia > lb->distancia) return  1;
    return 0;
}
