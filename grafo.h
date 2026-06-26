#ifndef GRAFO_H
#define GRAFO_H

#include "ponto.h"
#include "ligacao.h"

/* Numero maximo de ligacoes suportadas */
#define MAX_LIGACOES 500

/*
 * NoAdj - no da lista de adjacencia do grafo.
 * Cada no guarda o indice do vizinho e o peso da aresta.
 */
typedef struct NoAdj {
    int         destino;   /* indice do ponto vizinho       */
    float       custo;     /* custo da ligacao em Kz        */
    float       distancia; /* distancia da ligacao em m     */
    struct NoAdj* prox;    /* proximo no da lista           */
} NoAdj;

/*
 * Grafo - estrutura principal do sistema.
 * Representa a rede hidraulica como um grafo nao-dirigido
 * implementado com lista de adjacencia.
 *
 * Campos:
 *   pontos      - array de ponteiros para os nos
 *   adj         - cabecas das listas de adjacencia
 *   ligacoes    - array de todas as arestas (para Kruskal)
 *   numPontos   - numero actual de pontos
 *   numLigacoes - numero actual de ligacoes
 */
typedef struct {
    Ponto*   pontos[MAX_PONTOS];
    NoAdj*   adj[MAX_PONTOS];
    Ligacao  ligacoes[MAX_LIGACOES];
    int      numPontos;
    int      numLigacoes;
} Grafo;

/*
 * UnionFind - estrutura auxiliar para o algoritmo de Kruskal.
 * Implementada com compressao de caminho e uniao por rank
 * para garantir eficiencia O(alfa(n)) por operacao.
 */
typedef struct {
    int pai[MAX_PONTOS];
    int rank[MAX_PONTOS];
} UnionFind;

/* ---- Prototipos - Gestao do Grafo ---- */
Grafo* criarGrafo();
void   destruirGrafo(Grafo* g);
int    inserirPontoGrafo(Grafo* g, Ponto* p);
/* removerPontoGrafo: remove o ponto do grafo mas NAO liberta a memoria
   do Ponto - isso e responsabilidade do Sistema para evitar ponteiros
   invalidos na BST, AVL e Hash */
int    removerPontoGrafo(Grafo* g, int id);
int    adicionarLigacao(Grafo* g, int orig, int dest, float custo, float dist);
int    removerLigacao(Grafo* g, int orig, int dest);
void   listarPontos(const Grafo* g);
void   listarLigacoes(const Grafo* g);
void   visualizarGrafo(const Grafo* g);
int    buscarIndicePonto(const Grafo* g, int id);

/* ---- Prototipos - Algoritmos MST ---- */
void kruskal(Grafo* g);
void prim(Grafo* g, int idInicio);

/* ---- Prototipos - Union-Find ---- */
void ufInicializar(UnionFind* uf, int n);
int  ufEncontrar(UnionFind* uf, int x);
int  ufUnir(UnionFind* uf, int x, int y);

#endif /* GRAFO_H */
