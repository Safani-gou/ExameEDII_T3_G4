#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "ligacao.h"

/*
 * CriterioOrdem - criterio de ordenacao das ligacoes.
 * POR_CUSTO     - ordena pelo custo de instalacao (Kz)
 * POR_DISTANCIA - ordena pela distancia da tubagem (m)
 */
typedef enum { POR_CUSTO, POR_DISTANCIA } CriterioOrdem;

/* ---- Prototipos dos 6 algoritmos de ordenacao ---- */
void insertionSort(Ligacao* arr, int n, CriterioOrdem c);
void selectionSort(Ligacao* arr, int n, CriterioOrdem c);
void shellSort    (Ligacao* arr, int n, CriterioOrdem c);
void mergeSort    (Ligacao* arr, int n, CriterioOrdem c);
void quickSort    (Ligacao* arr, int esq, int dir, CriterioOrdem c);
void heapSort     (Ligacao* arr, int n, CriterioOrdem c);

/* Funcao auxiliar e comparacao geral */
float getValor(const Ligacao* l, CriterioOrdem c);
void  compararTodosAlgoritmos(Ligacao* arr, int n);

#endif /* ORDENACAO_H */
