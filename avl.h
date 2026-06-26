#ifndef AVL_H
#define AVL_H

#include "ponto.h"

/*
 * NoAVL - no da Arvore AVL (Adelson-Velsky e Landis).
 * Cada no guarda a sua altura para calcular o factor de balanco.
 * Factor de balanco = altura(esq) - altura(dir)
 * A arvore esta balanceada quando |fator| <= 1 em todos os nos.
 */
typedef struct NoAVL {
    Ponto*        ponto;  /* ponteiro para o Ponto (memoria partilhada) */
    struct NoAVL* esq;    /* subarvore esquerda                         */
    struct NoAVL* dir;    /* subarvore direita                          */
    int           altura; /* altura do no (folha = 1)                   */
} NoAVL;

/*
 * AVL - estrutura raiz da arvore AVL.
 */
typedef struct {
    NoAVL* raiz;
} AVL;

/* ---- Prototipos ---- */
AVL*   criarAVL();
NoAVL* inserirAVL(NoAVL* raiz, Ponto* p);  /* rebalanceia automaticamente */
NoAVL* removerAVL(NoAVL* raiz, int id);    /* NAO liberta o Ponto         */
NoAVL* buscarAVL(NoAVL* raiz, int id);
void   emOrdemAVL(NoAVL* raiz);
void   destruirAVLNo(NoAVL* no);
void   destruirAVL(AVL* avl);

#endif /* AVL_H */
