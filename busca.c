#include <stdio.h>
#include <string.h>
#include "busca.h"

/* ---- Busca Linear por ID ---- */
Ponto* buscaLinear(Ponto** arr, int n, int id) {
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] && arr[i]->id == id) {
            printf("[SUCESSO] Busca linear: ponto ID %d encontrado.\n", id);
            return arr[i];
        }
    printf("[ERRO] Busca linear: ID %d nao encontrado.\n", id);
    return NULL;
}

/* ---- Busca Binaria por ID (array ordenado) ---- */
Ponto* buscaBinaria(Ponto** arr, int n, int id) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int mid = esq + (dir - esq) / 2;
        if (!arr[mid]) { esq++; continue; }
        if (arr[mid]->id == id) {
            printf("[SUCESSO] Busca binaria: ponto ID %d encontrado.\n", id);
            return arr[mid];
        }
        if (arr[mid]->id < id) esq = mid + 1;
        else                   dir = mid - 1;
    }
    printf("[ERRO] Busca binaria: ID %d nao encontrado.\n", id);
    return NULL;
}

/* ---- Busca por Nome (linear) ---- */
Ponto* buscaPorNome(Ponto** arr, int n, const char* nome) {
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] && strcmp(arr[i]->nome, nome) == 0) {
            printf("[SUCESSO] Encontrado: '%s' (ID %d).\n", nome, arr[i]->id);
            return arr[i];
        }
    printf("[ERRO] Nome '%s' nao encontrado.\n", nome);
    return NULL;
}

/* ---- Busca em AVL ---- */
Ponto* buscaEmAVL(AVL* avl, int id) {
    if (!avl) return NULL;
    NoAVL* no = buscarAVL(avl->raiz, id);
    if (no) {
        printf("[SUCESSO] Busca AVL: ponto ID %d encontrado.\n", id);
        return no->ponto;
    }
    printf("[ERRO] Busca AVL: ID %d nao encontrado.\n", id);
    return NULL;
}

/* ---- Busca em Hash ---- */
Ponto* buscaEmHash(HashTable* ht, int id) {
    return buscarHash(ht, id);
}

/* ---- Ordenar array de ponteiros por ID (selection sort simples) ---- */
void ordenarPontosPorID(Ponto** arr, int n) {
    int i, j, minIdx;
    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] && arr[minIdx] && arr[j]->id < arr[minIdx]->id)
                minIdx = j;
        if (minIdx != i) { Ponto* t = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = t; }
    }
}
