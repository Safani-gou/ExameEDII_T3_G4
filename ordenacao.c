#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ordenacao.h"

/* Retorna valor para comparacao */
float getValor(const Ligacao* l, CriterioOrdem c) {
    return c == POR_CUSTO ? l->custo : l->distancia;
}

static void trocar(Ligacao* a, Ligacao* b) { Ligacao t = *a; *a = *b; *b = t; }

/* ---- Insertion Sort ---- */
void insertionSort(Ligacao* arr, int n, CriterioOrdem c) {
    int i, j;
    for (i = 1; i < n; i++) {
        Ligacao chave = arr[i];
        j = i - 1;
        while (j >= 0 && getValor(&arr[j], c) > getValor(&chave, c)) {
            arr[j+1] = arr[j]; j--;
        }
        arr[j+1] = chave;
    }
}

/* ---- Selection Sort ---- */
void selectionSort(Ligacao* arr, int n, CriterioOrdem c) {
    int i, j, minIdx;
    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++)
            if (getValor(&arr[j], c) < getValor(&arr[minIdx], c)) minIdx = j;
        if (minIdx != i) trocar(&arr[i], &arr[minIdx]);
    }
}

/* ---- Shell Sort ---- */
void shellSort(Ligacao* arr, int n, CriterioOrdem c) {
    int gap, i, j;
    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++) {
            Ligacao temp = arr[i];
            for (j = i; j >= gap && getValor(&arr[j-gap], c) > getValor(&temp, c); j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
}

/* ---- Merge Sort ---- */
static void merge(Ligacao* arr, int l, int m, int r, CriterioOrdem c) {
    int n1 = m - l + 1, n2 = r - m;
    Ligacao* L = (Ligacao*)malloc(n1 * sizeof(Ligacao));
    Ligacao* R = (Ligacao*)malloc(n2 * sizeof(Ligacao));
    int i, j, k;
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (getValor(&L[i], c) <= getValor(&R[j], c)) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}
static void mergeSortRec(Ligacao* arr, int l, int r, CriterioOrdem c) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortRec(arr, l, m, c);
        mergeSortRec(arr, m + 1, r, c);
        merge(arr, l, m, r, c);
    }
}
void mergeSort(Ligacao* arr, int n, CriterioOrdem c) { if (n > 1) mergeSortRec(arr, 0, n-1, c); }

/* ---- Quick Sort ---- */
static int particionar(Ligacao* arr, int esq, int dir, CriterioOrdem c) {
    float pivo = getValor(&arr[dir], c);
    int i = esq - 1, j;
    for (j = esq; j < dir; j++)
        if (getValor(&arr[j], c) <= pivo) { i++; trocar(&arr[i], &arr[j]); }
    trocar(&arr[i+1], &arr[dir]);
    return i + 1;
}
void quickSort(Ligacao* arr, int esq, int dir, CriterioOrdem c) {
    if (esq < dir) {
        int p = particionar(arr, esq, dir, c);
        quickSort(arr, esq, p - 1, c);
        quickSort(arr, p + 1, dir, c);
    }
}

/* ---- Heap Sort ---- */
static void heapify(Ligacao* arr, int n, int i, CriterioOrdem c) {
    int maior = i, esq = 2*i+1, dir2 = 2*i+2;
    if (esq < n && getValor(&arr[esq], c) > getValor(&arr[maior], c)) maior = esq;
    if (dir2 < n && getValor(&arr[dir2], c) > getValor(&arr[maior], c)) maior = dir2;
    if (maior != i) { trocar(&arr[i], &arr[maior]); heapify(arr, n, maior, c); }
}
void heapSort(Ligacao* arr, int n, CriterioOrdem c) {
    int i;
    for (i = n/2 - 1; i >= 0; i--) heapify(arr, n, i, c);
    for (i = n - 1; i > 0; i--) { trocar(&arr[0], &arr[i]); heapify(arr, i, 0, c); }
}

/* ---- Comparacao de todos os algoritmos ---- */
void compararTodosAlgoritmos(Ligacao* original, int n) {
    if (n == 0) { printf("[ERRO] Sem ligacoes para ordenar.\n"); return; }
    Ligacao* copia = (Ligacao*)malloc(n * sizeof(Ligacao));
    if (!copia) { printf("[ERRO] Falha de memoria.\n"); return; }

    const char* nomes[] = {"Insertion Sort","Selection Sort","Shell Sort","Merge Sort","Quick Sort","Heap Sort"};
    clock_t ini, fim;
    double tempos[6];
    int i;

    printf("\n=== COMPARACAO DE ALGORITMOS DE ORDENACAO (por custo) ===\n");

    /* Insertion */
    memcpy(copia, original, n * sizeof(Ligacao));
    ini = clock(); insertionSort(copia, n, POR_CUSTO); fim = clock();
    tempos[0] = (double)(fim - ini) / CLOCKS_PER_SEC * 1000.0;

    /* Selection */
    memcpy(copia, original, n * sizeof(Ligacao));
    ini = clock(); selectionSort(copia, n, POR_CUSTO); fim = clock();
    tempos[1] = (double)(fim - ini) / CLOCKS_PER_SEC * 1000.0;

    /* Shell */
    memcpy(copia, original, n * sizeof(Ligacao));
    ini = clock(); shellSort(copia, n, POR_CUSTO); fim = clock();
    tempos[2] = (double)(fim - ini) / CLOCKS_PER_SEC * 1000.0;

    /* Merge */
    memcpy(copia, original, n * sizeof(Ligacao));
    ini = clock(); mergeSort(copia, n, POR_CUSTO); fim = clock();
    tempos[3] = (double)(fim - ini) / CLOCKS_PER_SEC * 1000.0;

    /* Quick */
    memcpy(copia, original, n * sizeof(Ligacao));
    ini = clock(); quickSort(copia, 0, n-1, POR_CUSTO); fim = clock();
    tempos[4] = (double)(fim - ini) / CLOCKS_PER_SEC * 1000.0;

    /* Heap */
    memcpy(copia, original, n * sizeof(Ligacao));
    ini = clock(); heapSort(copia, n, POR_CUSTO); fim = clock();
    tempos[5] = (double)(fim - ini) / CLOCKS_PER_SEC * 1000.0;

    int melhor = 0;
    for (i = 0; i < 6; i++) {
        printf("  %-16s: %.4f ms\n", nomes[i], tempos[i]);
        if (tempos[i] < tempos[melhor]) melhor = i;
    }
    printf("  Algoritmo mais rapido: %s\n", nomes[melhor]);
    free(copia);
}
