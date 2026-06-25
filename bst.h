#ifndef BST_H
#define BST_H

#include "ponto.h"

/* No da arvore BST */
typedef struct NoBST {
    Ponto*       ponto;
    struct NoBST* esq;
    struct NoBST* dir;
} NoBST;

/* Arvore BST */
typedef struct { NoBST* raiz; int tamanho; } BST;

BST*    criarBST();
NoBST*  inserirBST(NoBST* raiz, Ponto* p);
NoBST*  buscarBST(NoBST* raiz, int id);
NoBST*  removerBST(NoBST* raiz, int id);
void    emOrdemBST(NoBST* raiz);
void    destruirBSTNo(NoBST* no);
void    destruirBST(BST* bst);
NoBST*  minNoBST(NoBST* no);

#endif
