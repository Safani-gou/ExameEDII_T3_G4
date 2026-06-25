#ifndef MENU_H
#define MENU_H

#include "grafo.h"
#include "bst.h"
#include "avl.h"
#include "hash.h"

typedef struct {
    Grafo*     grafo;
    BST*       bst;
    AVL*       avl;
    HashTable* hash;
} Sistema;

Sistema* criarSistema();
void     destruirSistema(Sistema* s);

void menuPrincipal    (Sistema* s);
void menuPontos       (Sistema* s);
void menuLigacoes     (Sistema* s);
void menuOrdenacao    (Sistema* s);
void menuBusca        (Sistema* s);
void menuEstruturas   (Sistema* s);
void menuMST          (Sistema* s);
void menuEstatisticas (Sistema* s);
void menuFicheiros    (Sistema* s);

#endif
