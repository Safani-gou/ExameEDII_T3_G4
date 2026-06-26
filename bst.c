/*
 * bst.c - Implementacao da Arvore Binaria de Busca (BST)
 *
 * A BST organiza os pontos da rede por ID, permitindo
 * insercao, busca e remocao em O(log n) no caso medio.
 *
 * NOTA: A BST nao e dona da memoria dos Pontos.
 * Apenas guarda referencias (ponteiros). A libertacao
 * da memoria do Ponto e feita pelo Sistema (menu.c).
 *
 * Grupo: ExameEDII_T3_G4 | ISPTC 2025/2
 */

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/*
 * criarBST - aloca e inicializa uma BST vazia.
 */
BST* criarBST() {
    BST* b = (BST*)malloc(sizeof(BST));
    if (!b) { printf("[ERRO] Falha ao criar BST.\n"); return NULL; }
    b->raiz     = NULL;
    b->tamanho  = 0;
    return b;
}

/*
 * inserirBST - insere um Ponto na BST mantendo a propriedade de ordem.
 * Retorna a nova raiz da subarvore (pode mudar se a arvore estava vazia).
 */
NoBST* inserirBST(NoBST* raiz, Ponto* p) {
    if (!raiz) {
        /* no encontrado o local de insercao: cria novo no */
        NoBST* no = (NoBST*)malloc(sizeof(NoBST));
        if (!no) { printf("[ERRO] Falha de memoria BST.\n"); return NULL; }
        no->ponto = p;
        no->esq   = no->dir = NULL;
        printf("[SUCESSO] Ponto ID %d inserido na BST.\n", p->id);
        return no;
    }
    /* navega pela arvore comparando IDs */
    if      (p->id < raiz->ponto->id) raiz->esq = inserirBST(raiz->esq, p);
    else if (p->id > raiz->ponto->id) raiz->dir = inserirBST(raiz->dir, p);
    else printf("[ERRO] ID %d ja existe na BST.\n", p->id);
    return raiz;
}

/*
 * buscarBST - procura um Ponto pelo ID.
 * Retorna o no encontrado, ou NULL se nao existir.
 * Complexidade: O(log n) medio, O(n) pior caso.
 */
NoBST* buscarBST(NoBST* raiz, int id) {
    if (!raiz) return NULL;
    if (id == raiz->ponto->id) return raiz;
    if (id  < raiz->ponto->id) return buscarBST(raiz->esq, id);
    return buscarBST(raiz->dir, id);
}

/*
 * minNoBST - retorna o no com menor ID numa subarvore.
 * Usado na remocao para encontrar o sucessor in-order.
 */
NoBST* minNoBST(NoBST* no) {
    while (no->esq) no = no->esq;
    return no;
}

/*
 * removerBST - remove o no com o ID dado da BST.
 *
 * IMPORTANTE: remove apenas o NO da arvore (free do NoBST).
 * NAO chama free() no campo ponto - a memoria do Ponto
 * e gerida externamente pelo Sistema.
 *
 * Casos:
 *   - No sem filhos: remove directamente
 *   - No com um filho: substitui pelo filho
 *   - No com dois filhos: substitui pelo sucessor in-order
 */
NoBST* removerBST(NoBST* raiz, int id) {
    if (!raiz) {
        printf("[ERRO] ID %d nao encontrado na BST.\n", id);
        return NULL;
    }
    if      (id < raiz->ponto->id) raiz->esq = removerBST(raiz->esq, id);
    else if (id > raiz->ponto->id) raiz->dir = removerBST(raiz->dir, id);
    else {
        /* no encontrado */
        if (!raiz->esq) {
            NoBST* t = raiz->dir;
            free(raiz); /* liberta apenas o no da BST, NAO o Ponto */
            printf("[SUCESSO] No ID %d removido da BST.\n", id);
            return t;
        }
        if (!raiz->dir) {
            NoBST* t = raiz->esq;
            free(raiz);
            printf("[SUCESSO] No ID %d removido da BST.\n", id);
            return t;
        }
        /* dois filhos: substitui pelo sucessor in-order (minimo da direita) */
        NoBST* suc = minNoBST(raiz->dir);
        raiz->ponto = suc->ponto;
        raiz->dir   = removerBST(raiz->dir, suc->ponto->id);
    }
    return raiz;
}

/*
 * emOrdemBST - percurso em ordem (esq, raiz, dir).
 * Imprime os pontos por ordem crescente de ID.
 */
void emOrdemBST(NoBST* raiz) {
    if (!raiz) return;
    emOrdemBST(raiz->esq);
    imprimirPonto(raiz->ponto);
    emOrdemBST(raiz->dir);
}

/*
 * destruirBSTNo - liberta recursivamente todos os nos da arvore.
 * NAO liberta os Pontos apontados pelos nos.
 */
void destruirBSTNo(NoBST* no) {
    if (!no) return;
    destruirBSTNo(no->esq);
    destruirBSTNo(no->dir);
    free(no);
}

/*
 * destruirBST - liberta a estrutura BST e todos os seus nos.
 */
void destruirBST(BST* bst) {
    if (!bst) return;
    destruirBSTNo(bst->raiz);
    free(bst);
}
