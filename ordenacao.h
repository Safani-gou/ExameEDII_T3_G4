#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "ligacao.h"

typedef enum { POR_CUSTO, POR_DISTANCIA } CriterioOrdem;

void insertionSort (Ligacao* arr, int n, CriterioOrdem c);
void selectionSort (Ligacao* arr, int n, CriterioOrdem c);
void shellSort     (Ligacao* arr, int n, CriterioOrdem c);
void mergeSort     (Ligacao* arr, int n, CriterioOrdem c);
void quickSort     (Ligacao* arr, int esq, int dir, CriterioOrdem c);
void heapSort      (Ligacao* arr, int n, CriterioOrdem c);

void compararTodosAlgoritmos(Ligacao* arr, int n);
float getValor(const Ligacao* l, CriterioOrdem c);

#endif
