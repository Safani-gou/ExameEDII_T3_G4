#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "grafo.h"

/* ============================================================
   CRIACAO E DESTRUICAO
   ============================================================ */

Grafo* criarGrafo() {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    if (!g) { printf("[ERRO] Falha ao criar grafo.\n"); return NULL; }
    g->numPontos  = 0;
    g->numLigacoes = 0;
    int i;
    for (i = 0; i < MAX_PONTOS; i++) {
        g->pontos[i] = NULL;
        g->adj[i]    = NULL;
    }
    printf("[SUCESSO] Grafo criado.\n");
    return g;
}

void destruirGrafo(Grafo* g) {
    if (!g) return;
    int i;
    for (i = 0; i < MAX_PONTOS; i++) {
        if (g->pontos[i]) destruirPonto(g->pontos[i]);
        NoAdj* no = g->adj[i];
        while (no) {
            NoAdj* prox = no->prox;
            free(no);
            no = prox;
        }
    }
    free(g);
}

/* ============================================================
   BUSCA DE INDICE
   ============================================================ */

int buscarIndicePonto(const Grafo* g, int id) {
    int i;
    for (i = 0; i < MAX_PONTOS; i++)
        if (g->pontos[i] && g->pontos[i]->id == id) return i;
    return -1;
}

/* ============================================================
   GESTAO DE PONTOS
   ============================================================ */

int inserirPontoGrafo(Grafo* g, Ponto* p) {
    if (!g || !p) return 0;
    if (buscarIndicePonto(g, p->id) >= 0) {
        printf("[ERRO] Ponto com ID %d ja existe.\n", p->id);
        return 0;
    }
    int i;
    for (i = 0; i < MAX_PONTOS; i++) {
        if (!g->pontos[i]) {
            g->pontos[i] = p;
            g->numPontos++;
            printf("[SUCESSO] Ponto inserido no grafo.\n");
            return 1;
        }
    }
    printf("[ERRO] Grafo cheio.\n");
    return 0;
}

int removerPontoGrafo(Grafo* g, int id) {
    int idx = buscarIndicePonto(g, id);
    if (idx < 0) { printf("[ERRO] Ponto ID %d nao encontrado.\n", id); return 0; }
    /* Remove lista de adjacencia do ponto */
    NoAdj* no = g->adj[idx];
    while (no) { NoAdj* p = no->prox; free(no); no = p; }
    g->adj[idx] = NULL;
    /* Remove referencias a este ponto nas outras listas */
    int i;
    for (i = 0; i < MAX_PONTOS; i++) {
        NoAdj* ant = NULL;
        NoAdj* cur = g->adj[i];
        while (cur) {
            if (cur->destino == idx) {
                if (ant) ant->prox = cur->prox;
                else     g->adj[i] = cur->prox;
                free(cur);
                break;
            }
            ant = cur; cur = cur->prox;
        }
    }
    destruirPonto(g->pontos[idx]);
    g->pontos[idx] = NULL;
    g->numPontos--;
    printf("[SUCESSO] Ponto ID %d removido.\n", id);
    return 1;
}

void listarPontos(const Grafo* g) {
    if (!g || g->numPontos == 0) { printf("[INFO] Nenhum ponto cadastrado.\n"); return; }
    printf("\n=== PONTOS DA REDE (%d) ===\n", g->numPontos);
    int i;
    for (i = 0; i < MAX_PONTOS; i++)
        if (g->pontos[i]) imprimirPonto(g->pontos[i]);
}

/* ============================================================
   GESTAO DE LIGACOES
   ============================================================ */

int adicionarLigacao(Grafo* g, int orig, int dest, float custo, float dist) {
    int io = buscarIndicePonto(g, orig);
    int id = buscarIndicePonto(g, dest);
    if (io < 0 || id < 0) {
        printf("[ERRO] Um ou ambos os pontos nao existem.\n");
        return 0;
    }
    if (g->numLigacoes >= MAX_LIGACOES) {
        printf("[ERRO] Limite de ligacoes atingido.\n");
        return 0;
    }
    /* Adiciona na lista de adjacencia (nao-dirigido) */
    NoAdj* n1 = (NoAdj*)malloc(sizeof(NoAdj));
    NoAdj* n2 = (NoAdj*)malloc(sizeof(NoAdj));
    if (!n1 || !n2) { printf("[ERRO] Falha de memoria.\n"); return 0; }
    n1->destino   = id;   n1->custo = custo; n1->distancia = dist; n1->prox = g->adj[io]; g->adj[io] = n1;
    n2->destino   = io;   n2->custo = custo; n2->distancia = dist; n2->prox = g->adj[id]; g->adj[id] = n2;
    /* Salva no array de ligacoes para Kruskal */
    g->ligacoes[g->numLigacoes].origem    = io;
    g->ligacoes[g->numLigacoes].destino   = id;
    g->ligacoes[g->numLigacoes].custo     = custo;
    g->ligacoes[g->numLigacoes].distancia = dist;
    g->numLigacoes++;
    printf("[SUCESSO] Ligacao %d <-> %d adicionada.\n", orig, dest);
    return 1;
}

int removerLigacao(Grafo* g, int orig, int dest) {
    int io = buscarIndicePonto(g, orig);
    int id = buscarIndicePonto(g, dest);
    if (io < 0 || id < 0) { printf("[ERRO] Pontos nao encontrados.\n"); return 0; }
    /* Remove de adj[io] -> id */
    NoAdj* ant = NULL, *cur = g->adj[io];
    while (cur) {
        if (cur->destino == id) {
            if (ant) ant->prox = cur->prox; else g->adj[io] = cur->prox;
            free(cur); break;
        }
        ant = cur; cur = cur->prox;
    }
    /* Remove de adj[id] -> io */
    ant = NULL; cur = g->adj[id];
    while (cur) {
        if (cur->destino == io) {
            if (ant) ant->prox = cur->prox; else g->adj[id] = cur->prox;
            free(cur); break;
        }
        ant = cur; cur = cur->prox;
    }
    printf("[SUCESSO] Ligacao %d <-> %d removida.\n", orig, dest);
    return 1;
}

void listarLigacoes(const Grafo* g) {
    if (!g || g->numLigacoes == 0) { printf("[INFO] Nenhuma ligacao cadastrada.\n"); return; }
    printf("\n=== LIGACOES DA REDE (%d) ===\n", g->numLigacoes);
    int i;
    for (i = 0; i < g->numLigacoes; i++) {
        int io = g->ligacoes[i].origem;
        int id = g->ligacoes[i].destino;
        const char* no = g->pontos[io] ? g->pontos[io]->nome : "?";
        const char* nd = g->pontos[id] ? g->pontos[id]->nome : "?";
        printf("  %s <-> %s | Custo: %.2f Kz | Dist: %.2f m\n",
               no, nd, g->ligacoes[i].custo, g->ligacoes[i].distancia);
    }
}

void visualizarGrafo(const Grafo* g) {
    if (!g) return;
    printf("\n=== VISUALIZACAO DO GRAFO (Lista de Adjacencia) ===\n");
    int i;
    for (i = 0; i < MAX_PONTOS; i++) {
        if (!g->pontos[i]) continue;
        printf("  [%s]", g->pontos[i]->nome);
        NoAdj* no = g->adj[i];
        while (no) {
            if (g->pontos[no->destino])
                printf(" -> %s(%.0fKz)", g->pontos[no->destino]->nome, no->custo);
            no = no->prox;
        }
        printf("\n");
    }
}

/* ============================================================
   UNION-FIND (para Kruskal)
   ============================================================ */

void ufInicializar(UnionFind* uf, int n) {
    int i;
    for (i = 0; i < n; i++) { uf->pai[i] = i; uf->rank[i] = 0; }
}

int ufEncontrar(UnionFind* uf, int x) {
    if (uf->pai[x] != x) uf->pai[x] = ufEncontrar(uf, uf->pai[x]);
    return uf->pai[x];
}

int ufUnir(UnionFind* uf, int x, int y) {
    int rx = ufEncontrar(uf, x), ry = ufEncontrar(uf, y);
    if (rx == ry) return 0;
    if (uf->rank[rx] < uf->rank[ry]) { int t = rx; rx = ry; ry = t; }
    uf->pai[ry] = rx;
    if (uf->rank[rx] == uf->rank[ry]) uf->rank[rx]++;
    return 1;
}

/* ============================================================
   KRUSKAL - Arvore Geradora Minima
   ============================================================ */

void kruskal(Grafo* g) {
    if (!g || g->numLigacoes == 0) { printf("[ERRO] Sem ligacoes para Kruskal.\n"); return; }
    /* Copia e ordena ligacoes por custo */
    Ligacao arr[MAX_LIGACOES];
    int n = g->numLigacoes, i, j;
    for (i = 0; i < n; i++) arr[i] = g->ligacoes[i];
    /* Bubble sort por custo */
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j].custo > arr[j+1].custo) {
                Ligacao tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }

    UnionFind uf;
    ufInicializar(&uf, MAX_PONTOS);
    float custoTotal = 0;
    int   contArestas = 0;

    printf("\n=== KRUSKAL - Arvore Geradora Minima ===\n");
    for (i = 0; i < n && contArestas < g->numPontos - 1; i++) {
        int u = arr[i].origem, v = arr[i].destino;
        if (ufUnir(&uf, u, v)) {
            const char* nu = g->pontos[u] ? g->pontos[u]->nome : "?";
            const char* nv = g->pontos[v] ? g->pontos[v]->nome : "?";
            printf("  Ligacao: %s <-> %s | Custo: %.2f Kz\n", nu, nv, arr[i].custo);
            custoTotal += arr[i].custo;
            contArestas++;
        }
    }
    printf("  Custo total da rede (Kruskal): %.2f Kz\n", custoTotal);
}

/* ============================================================
   PRIM - Arvore Geradora Minima
   ============================================================ */

void prim(Grafo* g, int idInicio) {
    if (!g || g->numPontos == 0) { printf("[ERRO] Grafo vazio.\n"); return; }
    int inicio = buscarIndicePonto(g, idInicio);
    if (inicio < 0) { printf("[ERRO] Ponto inicial nao encontrado.\n"); return; }

    int     visitado[MAX_PONTOS];
    float   chave[MAX_PONTOS];
    int     pai[MAX_PONTOS];
    int i;

    for (i = 0; i < MAX_PONTOS; i++) {
        visitado[i] = 0;
        chave[i]    = FLT_MAX;
        pai[i]      = -1;
    }
    chave[inicio] = 0;

    float custoTotal = 0;
    printf("\n=== PRIM - Arvore Geradora Minima (inicio: %s) ===\n",
           g->pontos[inicio]->nome);

    int count;
    for (count = 0; count < g->numPontos; count++) {
        /* Encontra vertice nao visitado com menor chave */
        int u = -1;
        for (i = 0; i < MAX_PONTOS; i++)
            if (g->pontos[i] && !visitado[i] && (u == -1 || chave[i] < chave[u]))
                u = i;
        if (u == -1 || chave[u] == FLT_MAX) break;
        visitado[u] = 1;

        if (pai[u] != -1) {
            const char* nu = g->pontos[u]    ? g->pontos[u]->nome    : "?";
            const char* np = g->pontos[pai[u]]? g->pontos[pai[u]]->nome : "?";
            printf("  Ligacao: %s <-> %s | Custo: %.2f Kz\n", np, nu, chave[u]);
            custoTotal += chave[u];
        }

        /* Actualiza chaves dos vizinhos */
        NoAdj* no = g->adj[u];
        while (no) {
            int v = no->destino;
            if (g->pontos[v] && !visitado[v] && no->custo < chave[v]) {
                chave[v] = no->custo;
                pai[v]   = u;
            }
            no = no->prox;
        }
    }
    printf("  Custo total da rede (Prim): %.2f Kz\n", custoTotal);
}
