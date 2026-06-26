/*
 * hash.c - Implementacao da Tabela Hash com Encadeamento
 *
 * A tabela hash permite acesso directo a qualquer Ponto
 * pelo seu ID em O(1) no caso medio.
 *
 * Funcao hash: h(id) = id % TAM_HASH (TAM_HASH = 101, primo)
 * Colisoes resolvidas por encadeamento separado (lista ligada).
 *
 * Grupo: ExameEDII_T3_G4 | ISPTC 2025/2
 */

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

/*
 * criarHashTable - aloca e inicializa uma tabela hash vazia.
 * Todos os slots sao inicializados a NULL.
 */
HashTable* criarHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) { printf("[ERRO] Falha ao criar HashTable.\n"); return NULL; }
    int i;
    for (i = 0; i < TAM_HASH; i++) ht->tabela[i] = NULL;
    ht->tamanho = 0;
    printf("[SUCESSO] Tabela Hash criada (tamanho: %d).\n", TAM_HASH);
    return ht;
}

/*
 * hashFunc - funcao de dispersao.
 * Mapeia um ID inteiro para um indice [0, TAM_HASH-1].
 * Usa modulo com numero primo para distribuicao uniforme.
 */
int hashFunc(int id) {
    return id % TAM_HASH;
}

/*
 * inserirHash - insere um Ponto na tabela hash.
 * Em caso de colisao, o novo no e inserido no inicio da lista (O(1)).
 * Retorna 1 em sucesso, 0 se o ID ja existe ou em falha de memoria.
 */
int inserirHash(HashTable* ht, Ponto* p) {
    if (!ht || !p) return 0;
    int h = hashFunc(p->id);

    /* verifica se o ID ja existe neste slot */
    NoHash* cur = ht->tabela[h];
    while (cur) {
        if (cur->ponto->id == p->id) {
            printf("[ERRO] ID %d ja existe na Hash.\n", p->id);
            return 0;
        }
        cur = cur->prox;
    }
    /* insere no inicio da lista do slot */
    NoHash* no = (NoHash*)malloc(sizeof(NoHash));
    if (!no) { printf("[ERRO] Falha de memoria Hash.\n"); return 0; }
    no->ponto       = p;
    no->prox        = ht->tabela[h];
    ht->tabela[h]   = no;
    ht->tamanho++;
    printf("[SUCESSO] Ponto ID %d inserido na Hash (slot %d).\n", p->id, h);
    return 1;
}

/*
 * buscarHash - procura um Ponto pelo ID.
 * Complexidade: O(1) medio, O(n) pior caso (muitas colisoes).
 * Retorna o Ponto encontrado, ou NULL se nao existir.
 */
Ponto* buscarHash(HashTable* ht, int id) {
    if (!ht) return NULL;
    int h = hashFunc(id);
    NoHash* cur = ht->tabela[h];
    while (cur) {
        if (cur->ponto->id == id) {
            printf("[SUCESSO] Ponto ID %d encontrado na Hash.\n", id);
            return cur->ponto;
        }
        cur = cur->prox;
    }
    printf("[ERRO] ID %d nao encontrado na Hash.\n", id);
    return NULL;
}

/*
 * removerHash - remove o no da tabela hash pelo ID.
 *
 * IMPORTANTE: remove apenas o NoHash (free do NoHash).
 * NAO chama free() no campo ponto - a memoria do Ponto
 * e gerida externamente pelo Sistema.
 *
 * Retorna 1 em sucesso, 0 se nao encontrado.
 */
int removerHash(HashTable* ht, int id) {
    if (!ht) return 0;
    int h = hashFunc(id);
    NoHash* ant = NULL;
    NoHash* cur = ht->tabela[h];
    while (cur) {
        if (cur->ponto->id == id) {
            /* remove o no da lista ligada */
            if (ant) ant->prox    = cur->prox;
            else     ht->tabela[h] = cur->prox;
            free(cur); /* liberta apenas o NoHash, NAO o Ponto */
            ht->tamanho--;
            printf("[SUCESSO] ID %d removido da Hash.\n", id);
            return 1;
        }
        ant = cur;
        cur = cur->prox;
    }
    printf("[ERRO] ID %d nao encontrado na Hash.\n", id);
    return 0;
}

/*
 * listarHash - imprime todos os elementos da tabela hash,
 * agrupados por slot, mostrando as colisoes existentes.
 */
void listarHash(const HashTable* ht) {
    if (!ht) return;
    printf("\n=== TABELA HASH (%d elementos) ===\n", ht->tamanho);
    int i;
    for (i = 0; i < TAM_HASH; i++) {
        if (!ht->tabela[i]) continue; /* slot vazio */
        printf("  [slot %3d]: ", i);
        NoHash* cur = ht->tabela[i];
        while (cur) {
            printf("ID%d(%s) ", cur->ponto->id, cur->ponto->nome);
            cur = cur->prox;
        }
        printf("\n");
    }
}

/*
 * destruirHash - liberta todos os NoHash e a propria estrutura.
 * NAO liberta os Pontos apontados pelos nos.
 */
void destruirHash(HashTable* ht) {
    if (!ht) return;
    int i;
    for (i = 0; i < TAM_HASH; i++) {
        NoHash* cur = ht->tabela[i];
        while (cur) {
            NoHash* prox = cur->prox;
            free(cur); /* liberta o NoHash, NAO o Ponto */
            cur = prox;
        }
    }
    free(ht);
}
