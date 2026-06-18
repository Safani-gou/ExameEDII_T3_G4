#ifndef AVL_H
#define AVL_H

typedef struct no AVL;
AVL *creatNo(int root);
AVL *insertNo(AVL *root, int chave);
AVL *removeNo(AVL *root, int chave);
AVL *updateNo(AVL *root);
AVL *listNo(AVL *root);

#endif