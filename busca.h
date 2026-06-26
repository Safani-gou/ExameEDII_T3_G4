#ifndef BUSCA_H
#define BUSCA_H

#include "ponto.h"
#include "avl.h"
#include "hash.h"

/*
 * Modulo de algoritmos de busca.
 * Permite pesquisar pontos da rede por ID ou por nome,
 * usando diferentes estruturas e algoritmos.
 */

/* Busca em array de ponteiros de Pontos */
Ponto* buscaLinear (Ponto** arr, int n, int id);
Ponto* buscaBinaria(Ponto** arr, int n, int id); /* array deve estar ordenado por ID */
Ponto* buscaPorNome(Ponto** arr, int n, const char* nome);

/* Busca nas estruturas de dados */
Ponto* buscaEmAVL  (AVL* avl, int id);
Ponto* buscaEmHash (HashTable* ht, int id);

/* Ordena array de ponteiros por ID (necessario para busca binaria) */
void ordenarPontosPorID(Ponto** arr, int n);

#endif /* BUSCA_H */
