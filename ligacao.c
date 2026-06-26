/*
 * ligacao.c - Implementacao do TAD Ligacao
 *
 * Uma ligacao representa uma tubagem entre dois pontos
 * da rede hidraulica, com custo e distancia associados.
 *
 * Grupo: ExameEDII_T3_G4 | ISPTC 2025/2
 */

#include <stdio.h>
#include <stdlib.h>
#include "ligacao.h"

/*
 * criarLigacao - aloca e inicializa uma nova Ligacao na heap.
 */
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

/*
 * imprimirLigacao - exibe os dados de uma ligacao no ecra.
 */
void imprimirLigacao(const Ligacao* l) {
    if (!l) {
        printf("[ERRO] Ligacao invalida.\n");
        return;
    }
    printf("  %d -> %d | Custo: %.2f Kz | Distancia: %.2f m\n",
           l->origem, l->destino, l->custo, l->distancia);
}

/*
 * destruirLigacao - liberta a memoria de uma Ligacao.
 */
void destruirLigacao(Ligacao* l) {
    if (l) free(l);
}

/*
 * compararPorCusto - comparador para ordenacao por custo crescente.
 * Usado pelos algoritmos de ordenacao e por qsort().
 */
int compararPorCusto(const void* a, const void* b) {
    const Ligacao* la = (const Ligacao*)a;
    const Ligacao* lb = (const Ligacao*)b;
    if (la->custo < lb->custo) return -1;
    if (la->custo > lb->custo) return  1;
    return 0;
}

/*
 * compararPorDistancia - comparador para ordenacao por distancia crescente.
 */
int compararPorDistancia(const void* a, const void* b) {
    const Ligacao* la = (const Ligacao*)a;
    const Ligacao* lb = (const Ligacao*)b;
    if (la->distancia < lb->distancia) return -1;
    if (la->distancia > lb->distancia) return  1;
    return 0;
}
