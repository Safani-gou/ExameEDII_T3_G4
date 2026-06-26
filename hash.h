#ifndef HASH_H
#define HASH_H

#include "ponto.h"

/*
 * TAM_HASH - tamanho da tabela hash.
 * Numero primo para melhor distribuicao e menos colisoes.
 */
#define TAM_HASH 101

/*
 * NoHash - no da lista encadeada para resolucao de colisoes.
 * Quando dois IDs mapeiam para o mesmo slot, sao encadeados.
 */
typedef struct NoHash {
    Ponto*        ponto; /* ponteiro para o Ponto (memoria partilhada) */
    struct NoHash* prox; /* proximo no no mesmo slot (colisao)         */
} NoHash;

/*
 * HashTable - tabela hash com encadeamento separado.
 * Permite busca em O(1) no caso medio.
 * Funcao hash: h(id) = id % TAM_HASH
 */
typedef struct {
    NoHash* tabela[TAM_HASH]; /* array de cabecas de listas */
    int     tamanho;          /* numero total de elementos  */
} HashTable;

/* ---- Prototipos ---- */
HashTable* criarHashTable();
int        hashFunc(int id);
int        inserirHash(HashTable* ht, Ponto* p);
Ponto*     buscarHash(HashTable* ht, int id);
int        removerHash(HashTable* ht, int id); /* NAO liberta o Ponto */
void       listarHash(const HashTable* ht);
void       destruirHash(HashTable* ht);

#endif /* HASH_H */
