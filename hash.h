#ifndef HASH_H
#define HASH_H

#include "ponto.h"

#define TAM_HASH 101  /* Numero primo para melhor distribuicao */

typedef struct NoHash {
    Ponto*        ponto;
    struct NoHash* prox; /* Encadeamento para colisoes */
} NoHash;

typedef struct { NoHash* tabela[TAM_HASH]; int tamanho; } HashTable;

HashTable* criarHashTable();
int        hashFunc(int id);
int        inserirHash(HashTable* ht, Ponto* p);
Ponto*     buscarHash(HashTable* ht, int id);
int        removerHash(HashTable* ht, int id);
void       listarHash(const HashTable* ht);
void       destruirHash(HashTable* ht);

#endif
