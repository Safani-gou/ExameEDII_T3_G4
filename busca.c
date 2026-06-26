/*
 * busca.c - Implementacao dos Algoritmos de Busca
 *
 * Implementa 5 algoritmos de pesquisa sobre os pontos da rede:
 *   1. Busca Linear   - O(n), sem requisitos de ordenacao
 *   2. Busca Binaria  - O(log n), requer array ordenado por ID
 *   3. Busca em AVL   - O(log n), aproveita a arvore balanceada
 *   4. Busca em Hash  - O(1) medio, acesso directo por ID
 *   5. Busca por Nome - O(n), comparacao de strings
 *
 * Grupo: ExameEDII_T3_G4 | ISPTC 2025/2
 */

#include <stdio.h>
#include <string.h>
#include "busca.h"

/*
 * buscaLinear - percorre o array sequencialmente ate encontrar o ID.
 * Complexidade: O(n) - verifica cada elemento um por um.
 * Vantagem: funciona em qualquer array, sem ordenacao previa.
 */
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

/*
 * buscaBinaria - divide o espaco de busca a cada iteracao.
 * Complexidade: O(log n) - muito mais rapida que a linear.
 * Pre-requisito: array DEVE estar ordenado por ID.
 */
Ponto* buscaBinaria(Ponto** arr, int n, int id) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int mid = esq + (dir - esq) / 2; /* evita overflow de inteiros */
        if (!arr[mid]) { esq++; continue; }
        if (arr[mid]->id == id) {
            printf("[SUCESSO] Busca binaria: ponto ID %d encontrado.\n", id);
            return arr[mid];
        }
        /* descarta a metade errada */
        if (arr[mid]->id < id) esq = mid + 1;
        else                   dir = mid - 1;
    }
    printf("[ERRO] Busca binaria: ID %d nao encontrado.\n", id);
    return NULL;
}

/*
 * buscaPorNome - busca linear usando strcmp para comparar nomes.
 * Complexidade: O(n) - verifica cada elemento.
 */
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

/*
 * buscaEmAVL - aproveita a estrutura balanceada da AVL.
 * Complexidade: O(log n) garantido em todos os casos.
 */
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

/*
 * buscaEmHash - acesso directo pelo slot hash do ID.
 * Complexidade: O(1) medio - o mais rapido na pratica.
 */
Ponto* buscaEmHash(HashTable* ht, int id) {
    return buscarHash(ht, id); /* delegado ao modulo hash.c */
}

/*
 * ordenarPontosPorID - ordena um array de ponteiros por ID crescente.
 * Necessario antes de usar buscaBinaria().
 * Algoritmo: Selection Sort (simples e suficiente para este uso).
 */
void ordenarPontosPorID(Ponto** arr, int n) {
    int i, j, minIdx;
    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] && arr[minIdx] && arr[j]->id < arr[minIdx]->id)
                minIdx = j;
        if (minIdx != i) {
            Ponto* t    = arr[i];
            arr[i]      = arr[minIdx];
            arr[minIdx] = t;
        }
    }
}
