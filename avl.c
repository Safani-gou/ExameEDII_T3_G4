#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/* Utilitarios */
static int altura(NoAVL* n)          { return n ? n->altura : 0; }
static int max2(int a, int b)        { return a > b ? a : b; }
static int fatorBalanco(NoAVL* n)    { return n ? altura(n->esq) - altura(n->dir) : 0; }
static void atualizarAltura(NoAVL* n){ if(n) n->altura = 1 + max2(altura(n->esq), altura(n->dir)); }

static NoAVL* novoNo(Ponto* p) {
    NoAVL* n = (NoAVL*)malloc(sizeof(NoAVL));
    if (!n) { printf("[ERRO] Falha de memoria AVL.\n"); return NULL; }
    n->ponto = p; n->esq = n->dir = NULL; n->altura = 1;
    return n;
}

/* Rotacoes */
static NoAVL* rotDir(NoAVL* y) {
    NoAVL* x = y->esq; NoAVL* T = x->dir;
    x->dir = y; y->esq = T;
    atualizarAltura(y); atualizarAltura(x);
    return x;
}
static NoAVL* rotEsq(NoAVL* x) {
    NoAVL* y = x->dir; NoAVL* T = y->esq;
    y->esq = x; x->dir = T;
    atualizarAltura(x); atualizarAltura(y);
    return y;
}

static NoAVL* balancear(NoAVL* n) {
    atualizarAltura(n);
    int fb = fatorBalanco(n);
    if (fb > 1) {
        if (fatorBalanco(n->esq) < 0) n->esq = rotEsq(n->esq);
        return rotDir(n);
    }
    if (fb < -1) {
        if (fatorBalanco(n->dir) > 0) n->dir = rotDir(n->dir);
        return rotEsq(n);
    }
    return n;
}

AVL* criarAVL() {
    AVL* a = (AVL*)malloc(sizeof(AVL));
    if (!a) return NULL;
    a->raiz = NULL; return a;
}

NoAVL* inserirAVL(NoAVL* raiz, Ponto* p) {
    if (!raiz) { printf("[SUCESSO] Ponto ID %d inserido na AVL.\n", p->id); return novoNo(p); }
    if (p->id < raiz->ponto->id)      raiz->esq = inserirAVL(raiz->esq, p);
    else if (p->id > raiz->ponto->id) raiz->dir = inserirAVL(raiz->dir, p);
    else { printf("[ERRO] ID %d ja existe na AVL.\n", p->id); return raiz; }
    return balancear(raiz);
}

NoAVL* buscarAVL(NoAVL* raiz, int id) {
    if (!raiz) return NULL;
    if (id == raiz->ponto->id) return raiz;
    if (id  < raiz->ponto->id) return buscarAVL(raiz->esq, id);
    return buscarAVL(raiz->dir, id);
}

static NoAVL* minNoAVL(NoAVL* n) { while(n->esq) n = n->esq; return n; }

NoAVL* removerAVL(NoAVL* raiz, int id) {
    if (!raiz) { printf("[ERRO] ID %d nao encontrado na AVL.\n", id); return NULL; }
    if (id < raiz->ponto->id)      raiz->esq = removerAVL(raiz->esq, id);
    else if (id > raiz->ponto->id) raiz->dir = removerAVL(raiz->dir, id);
    else {
        if (!raiz->esq || !raiz->dir) {
            NoAVL* t = raiz->esq ? raiz->esq : raiz->dir;
            free(raiz); printf("[SUCESSO] Removido da AVL.\n");
            return t;
        }
        NoAVL* suc = minNoAVL(raiz->dir);
        raiz->ponto = suc->ponto;
        raiz->dir = removerAVL(raiz->dir, suc->ponto->id);
    }
    return balancear(raiz);
}

void emOrdemAVL(NoAVL* raiz) {
    if (!raiz) return;
    emOrdemAVL(raiz->esq);
    imprimirPonto(raiz->ponto);
    emOrdemAVL(raiz->dir);
}

void destruirAVLNo(NoAVL* no) {
    if (!no) return;
    destruirAVLNo(no->esq);
    destruirAVLNo(no->dir);
    free(no);
}

void destruirAVL(AVL* avl) {
    if (!avl) return;
    destruirAVLNo(avl->raiz);
    free(avl);
}
