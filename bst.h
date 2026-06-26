#ifndef BST_H
#define BST_H

#include "ponto.h"

/*
 * NoBST - no da Arvore Binaria de Busca.
 * A BST e ordenada pelo campo id do Ponto.
 * Filho esquerdo tem id menor, direito tem id maior.
 */
typedef struct NoBST {
    Ponto*        ponto; /* ponteiro para o Ponto (memoria partilhada) */
    struct NoBST* esq;   /* subarvore esquerda (ids menores)           */
    struct NoBST* dir;   /* subarvore direita  (ids maiores)           */
} NoBST;

/*
 * BST - estrutura raiz da arvore binaria de busca.
 */
typedef struct {
    NoBST* raiz;
    int    tamanho;
} BST;

/* ---- Prototipos ---- */
BST*   criarBST();
NoBST* inserirBST(NoBST* raiz, Ponto* p);
NoBST* buscarBST(NoBST* raiz, int id);
NoBST* removerBST(NoBST* raiz, int id);  /* NAO liberta o Ponto */
NoBST* minNoBST(NoBST* no);
void   emOrdemBST(NoBST* raiz);
void   destruirBSTNo(NoBST* no);
void   destruirBST(BST* bst);

#endif /* BST_H */
