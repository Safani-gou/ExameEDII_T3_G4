#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BST* criarBST() {
    BST* b = (BST*)malloc(sizeof(BST));
    if (!b) { printf("[ERRO] Falha ao criar BST.\n"); return NULL; }
    b->raiz = NULL; b->tamanho = 0;
    return b;
}

NoBST* inserirBST(NoBST* raiz, Ponto* p) {
    if (!raiz) {
        NoBST* no = (NoBST*)malloc(sizeof(NoBST));
        if (!no) { printf("[ERRO] Falha de memoria BST.\n"); return NULL; }
        no->ponto = p; no->esq = no->dir = NULL;
        printf("[SUCESSO] Ponto ID %d inserido na BST.\n", p->id);
        return no;
    }
    if (p->id < raiz->ponto->id)      raiz->esq = inserirBST(raiz->esq, p);
    else if (p->id > raiz->ponto->id) raiz->dir = inserirBST(raiz->dir, p);
    else printf("[ERRO] ID %d ja existe na BST.\n", p->id);
    return raiz;
}

NoBST* buscarBST(NoBST* raiz, int id) {
    if (!raiz) return NULL;
    if (id == raiz->ponto->id) return raiz;
    if (id  < raiz->ponto->id) return buscarBST(raiz->esq, id);
    return buscarBST(raiz->dir, id);
}

NoBST* minNoBST(NoBST* no) {
    while (no->esq) no = no->esq;
    return no;
}

NoBST* removerBST(NoBST* raiz, int id) {
    if (!raiz) { printf("[ERRO] ID %d nao encontrado na BST.\n", id); return NULL; }
    if (id < raiz->ponto->id)      raiz->esq = removerBST(raiz->esq, id);
    else if (id > raiz->ponto->id) raiz->dir = removerBST(raiz->dir, id);
    else {
        if (!raiz->esq) { NoBST* t = raiz->dir; free(raiz); printf("[SUCESSO] Removido da BST.\n"); return t; }
        if (!raiz->dir) { NoBST* t = raiz->esq; free(raiz); printf("[SUCESSO] Removido da BST.\n"); return t; }
        NoBST* suc = minNoBST(raiz->dir);
        raiz->ponto = suc->ponto;
        raiz->dir = removerBST(raiz->dir, suc->ponto->id);
    }
    return raiz;
}

void emOrdemBST(NoBST* raiz) {
    if (!raiz) return;
    emOrdemBST(raiz->esq);
    imprimirPonto(raiz->ponto);
    emOrdemBST(raiz->dir);
}

void destruirBSTNo(NoBST* no) {
    if (!no) return;
    destruirBSTNo(no->esq);
    destruirBSTNo(no->dir);
    free(no);
}

void destruirBST(BST* bst) {
    if (!bst) return;
    destruirBSTNo(bst->raiz);
    free(bst);
}
