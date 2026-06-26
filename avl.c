/*
 * avl.c - Implementacao da Arvore AVL (Arvore Balanceada)
 *
 * A AVL e uma BST auto-balanceada que garante O(log n)
 * para insercao, remocao e busca em TODOS os casos
 * (incluindo o pior caso, ao contrario da BST simples).
 *
 * O balanceamento e mantido atraves de 4 tipos de rotacao:
 *   - Rotacao Simples Direita (caso Esquerda-Esquerda)
 *   - Rotacao Simples Esquerda (caso Direita-Direita)
 *   - Rotacao Dupla Esquerda-Direita (caso Esquerda-Direita)
 *   - Rotacao Dupla Direita-Esquerda (caso Direita-Esquerda)
 *
 * Grupo: ExameEDII_T3_G4 | ISPTC 2025/2
 */

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/* ---- Funcoes auxiliares internas ---- */

/* altura - retorna a altura de um no (0 para NULL) */
static int altura(NoAVL* n) { return n ? n->altura : 0; }

/* max2 - retorna o maior de dois inteiros */
static int max2(int a, int b) { return a > b ? a : b; }

/* fatorBalanco - diferenca de alturas entre filho esq e dir */
static int fatorBalanco(NoAVL* n) {
    return n ? altura(n->esq) - altura(n->dir) : 0;
}

/* atualizarAltura - recalcula a altura de um no a partir dos filhos */
static void atualizarAltura(NoAVL* n) {
    if (n) n->altura = 1 + max2(altura(n->esq), altura(n->dir));
}

/*
 * novoNo - aloca um novo no AVL com altura 1 (folha).
 */
static NoAVL* novoNo(Ponto* p) {
    NoAVL* n = (NoAVL*)malloc(sizeof(NoAVL));
    if (!n) { printf("[ERRO] Falha de memoria AVL.\n"); return NULL; }
    n->ponto  = p;
    n->esq    = n->dir = NULL;
    n->altura = 1;
    return n;
}

/*
 * rotDir - Rotacao Simples para a Direita (caso Esq-Esq).
 * Usada quando o filho esquerdo esta mais pesado.
 *
 *       y                x
 *      / \              / \
 *     x   T3   =>     T1   y
 *    / \                  / \
 *   T1  T2               T2  T3
 */
static NoAVL* rotDir(NoAVL* y) {
    NoAVL* x = y->esq;
    NoAVL* T = x->dir;
    x->dir = y;
    y->esq = T;
    atualizarAltura(y);
    atualizarAltura(x);
    return x; /* nova raiz */
}

/*
 * rotEsq - Rotacao Simples para a Esquerda (caso Dir-Dir).
 * Usada quando o filho direito esta mais pesado.
 */
static NoAVL* rotEsq(NoAVL* x) {
    NoAVL* y = x->dir;
    NoAVL* T = y->esq;
    y->esq = x;
    x->dir = T;
    atualizarAltura(x);
    atualizarAltura(y);
    return y; /* nova raiz */
}

/*
 * balancear - verifica e corrige o balanceamento de um no.
 * Aplica a rotacao adequada conforme o factor de balanco.
 */
static NoAVL* balancear(NoAVL* n) {
    atualizarAltura(n);
    int fb = fatorBalanco(n);

    /* caso Esq-Esq: rotacao simples direita */
    if (fb > 1 && fatorBalanco(n->esq) >= 0)
        return rotDir(n);

    /* caso Esq-Dir: rotacao dupla (esq depois dir) */
    if (fb > 1 && fatorBalanco(n->esq) < 0) {
        n->esq = rotEsq(n->esq);
        return rotDir(n);
    }
    /* caso Dir-Dir: rotacao simples esquerda */
    if (fb < -1 && fatorBalanco(n->dir) <= 0)
        return rotEsq(n);

    /* caso Dir-Esq: rotacao dupla (dir depois esq) */
    if (fb < -1 && fatorBalanco(n->dir) > 0) {
        n->dir = rotDir(n->dir);
        return rotEsq(n);
    }
    return n; /* ja balanceado */
}

/*
 * criarAVL - aloca e inicializa uma AVL vazia.
 */
AVL* criarAVL() {
    AVL* a = (AVL*)malloc(sizeof(AVL));
    if (!a) return NULL;
    a->raiz = NULL;
    return a;
}

/*
 * inserirAVL - insere um Ponto na AVL e rebalanceia automaticamente.
 * Retorna a nova raiz da subarvore apos o balanceamento.
 */
NoAVL* inserirAVL(NoAVL* raiz, Ponto* p) {
    /* insercao normal como BST */
    if (!raiz) {
        printf("[SUCESSO] Ponto ID %d inserido na AVL.\n", p->id);
        return novoNo(p);
    }
    if      (p->id < raiz->ponto->id) raiz->esq = inserirAVL(raiz->esq, p);
    else if (p->id > raiz->ponto->id) raiz->dir = inserirAVL(raiz->dir, p);
    else {
        printf("[ERRO] ID %d ja existe na AVL.\n", p->id);
        return raiz;
    }
    /* rebalanceia no caminho de volta (recursao) */
    return balancear(raiz);
}

/*
 * buscarAVL - procura um Ponto pelo ID na AVL.
 * Complexidade garantida: O(log n).
 */
NoAVL* buscarAVL(NoAVL* raiz, int id) {
    if (!raiz) return NULL;
    if (id == raiz->ponto->id) return raiz;
    if (id  < raiz->ponto->id) return buscarAVL(raiz->esq, id);
    return buscarAVL(raiz->dir, id);
}

/* minNoAVL - retorna o no com menor ID (usado na remocao) */
static NoAVL* minNoAVL(NoAVL* n) {
    while (n->esq) n = n->esq;
    return n;
}

/*
 * removerAVL - remove o no com o ID dado e rebalanceia.
 *
 * IMPORTANTE: remove apenas o NO da AVL (free do NoAVL).
 * NAO chama free() no campo ponto.
 */
NoAVL* removerAVL(NoAVL* raiz, int id) {
    if (!raiz) {
        printf("[ERRO] ID %d nao encontrado na AVL.\n", id);
        return NULL;
    }
    if      (id < raiz->ponto->id) raiz->esq = removerAVL(raiz->esq, id);
    else if (id > raiz->ponto->id) raiz->dir = removerAVL(raiz->dir, id);
    else {
        /* no encontrado */
        if (!raiz->esq || !raiz->dir) {
            NoAVL* t = raiz->esq ? raiz->esq : raiz->dir;
            free(raiz); /* liberta apenas o no, NAO o Ponto */
            printf("[SUCESSO] No ID %d removido da AVL.\n", id);
            return t;
        }
        /* dois filhos: substitui pelo sucessor in-order */
        NoAVL* suc = minNoAVL(raiz->dir);
        raiz->ponto = suc->ponto;
        raiz->dir   = removerAVL(raiz->dir, suc->ponto->id);
    }
    return balancear(raiz);
}

/*
 * emOrdemAVL - percurso em ordem, imprime pontos por ID crescente.
 */
void emOrdemAVL(NoAVL* raiz) {
    if (!raiz) return;
    emOrdemAVL(raiz->esq);
    imprimirPonto(raiz->ponto);
    emOrdemAVL(raiz->dir);
}

/*
 * destruirAVLNo - liberta recursivamente os nos (NAO os Pontos).
 */
void destruirAVLNo(NoAVL* no) {
    if (!no) return;
    destruirAVLNo(no->esq);
    destruirAVLNo(no->dir);
    free(no);
}

/*
 * destruirAVL - liberta a estrutura AVL e todos os seus nos.
 */
void destruirAVL(AVL* avl) {
    if (!avl) return;
    destruirAVLNo(avl->raiz);
    free(avl);
}
