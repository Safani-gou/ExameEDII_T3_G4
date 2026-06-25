#ifndef GRAFO_H
#define GRAFO_H

#include "ponto.h"
#include "ligacao.h"

#define MAX_LIGACOES 500

/* No da lista de adjacencia */
typedef struct NoAdj {
    int destino;
    float custo;
    float distancia;
    struct NoAdj* prox;
} NoAdj;

/* Grafo principal */
typedef struct {
    Ponto*   pontos[MAX_PONTOS];   /* Array de ponteiros para pontos */
    NoAdj*   adj[MAX_PONTOS];      /* Lista de adjacencia */
    Ligacao  ligacoes[MAX_LIGACOES]; /* Array de todas as ligacoes (para Kruskal) */
    int      numPontos;
    int      numLigacoes;
} Grafo;

/* Union-Find para Kruskal */
typedef struct {
    int pai[MAX_PONTOS];
    int rank[MAX_PONTOS];
} UnionFind;

/* Prototipos - Grafo */
Grafo* criarGrafo();
void   destruirGrafo(Grafo* g);
int    inserirPontoGrafo(Grafo* g, Ponto* p);
int    removerPontoGrafo(Grafo* g, int id);
int    adicionarLigacao(Grafo* g, int orig, int dest, float custo, float dist);
int    removerLigacao(Grafo* g, int orig, int dest);
void   listarPontos(const Grafo* g);
void   listarLigacoes(const Grafo* g);
void   visualizarGrafo(const Grafo* g);
int    buscarIndicePonto(const Grafo* g, int id);

/* Prototipos - MST */
void kruskal(Grafo* g);
void prim(Grafo* g, int idInicio);

/* Union-Find */
void ufInicializar(UnionFind* uf, int n);
int  ufEncontrar(UnionFind* uf, int x);
int  ufUnir(UnionFind* uf, int x, int y);

#endif
