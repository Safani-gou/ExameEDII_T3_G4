#ifndef BUSCA_H
#define BUSCA_H

#include "ponto.h"
#include "ligacao.h"
#include "avl.h"
#include "hash.h"

/* Busca em arrays de pontos */
Ponto* buscaLinear (Ponto** arr, int n, int id);
Ponto* buscaBinaria(Ponto** arr, int n, int id);  /* arr deve estar ordenado por ID */
Ponto* buscaPorNome(Ponto** arr, int n, const char* nome);

/* Busca nas estruturas */
Ponto* buscaEmAVL  (AVL* avl, int id);
Ponto* buscaEmHash (HashTable* ht, int id);

/* Ordenar array de ponteiros por ID (para busca binaria) */
void ordenarPontosPorID(Ponto** arr, int n);

#endif
