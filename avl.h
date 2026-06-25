#ifndef AVL_H
#define AVL_H

#include "ponto.h"

typedef struct NoAVL {
    Ponto*       ponto;
    struct NoAVL* esq;
    struct NoAVL* dir;
    int           altura;
} NoAVL;

typedef struct { NoAVL* raiz; } AVL;

AVL*   criarAVL();
NoAVL* inserirAVL(NoAVL* raiz, Ponto* p);
NoAVL* removerAVL(NoAVL* raiz, int id);
NoAVL* buscarAVL(NoAVL* raiz, int id);
void   emOrdemAVL(NoAVL* raiz);
void   destruirAVL(AVL* avl);
void   destruirAVLNo(NoAVL* no);

#endif
