#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

HashTable* criarHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) { printf("[ERRO] Falha ao criar HashTable.\n"); return NULL; }
    int i;
    for (i = 0; i < TAM_HASH; i++) ht->tabela[i] = NULL;
    ht->tamanho = 0;
    printf("[SUCESSO] Tabela Hash criada (tamanho: %d).\n", TAM_HASH);
    return ht;
}

int hashFunc(int id) { return id % TAM_HASH; }

int inserirHash(HashTable* ht, Ponto* p) {
    if (!ht || !p) return 0;
    int h = hashFunc(p->id);
    /* Verifica duplicata */
    NoHash* cur = ht->tabela[h];
    while (cur) {
        if (cur->ponto->id == p->id) { printf("[ERRO] ID %d ja existe na Hash.\n", p->id); return 0; }
        cur = cur->prox;
    }
    NoHash* no = (NoHash*)malloc(sizeof(NoHash));
    if (!no) return 0;
    no->ponto = p;
    no->prox  = ht->tabela[h];
    ht->tabela[h] = no;
    ht->tamanho++;
    printf("[SUCESSO] Ponto ID %d inserido na Hash (slot %d).\n", p->id, h);
    return 1;
}

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

int removerHash(HashTable* ht, int id) {
    if (!ht) return 0;
    int h = hashFunc(id);
    NoHash* ant = NULL, *cur = ht->tabela[h];
    while (cur) {
        if (cur->ponto->id == id) {
            if (ant) ant->prox = cur->prox; else ht->tabela[h] = cur->prox;
            free(cur);
            ht->tamanho--;
            printf("[SUCESSO] ID %d removido da Hash.\n", id);
            return 1;
        }
        ant = cur; cur = cur->prox;
    }
    printf("[ERRO] ID %d nao encontrado na Hash.\n", id);
    return 0;
}

void listarHash(const HashTable* ht) {
    if (!ht) return;
    printf("\n=== TABELA HASH (%d elementos) ===\n", ht->tamanho);
    int i;
    for (i = 0; i < TAM_HASH; i++) {
        if (!ht->tabela[i]) continue;
        printf("  [slot %3d]: ", i);
        NoHash* cur = ht->tabela[i];
        while (cur) { printf("ID%d(%s) ", cur->ponto->id, cur->ponto->nome); cur = cur->prox; }
        printf("\n");
    }
}

void destruirHash(HashTable* ht) {
    if (!ht) return;
    int i;
    for (i = 0; i < TAM_HASH; i++) {
        NoHash* cur = ht->tabela[i];
        while (cur) { NoHash* p = cur->prox; free(cur); cur = p; }
    }
    free(ht);
}
