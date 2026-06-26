/*
 * grafo.c - Implementacao do Grafo com Lista de Adjacencia
 *
 * O grafo representa a rede hidraulica como um grafo nao-dirigido.
 * Cada ponto e um no e cada tubagem e uma aresta com custo e distancia.
 *
 * NOTA IMPORTANTE sobre gestao de memoria:
 *   removerPontoGrafo() remove o ponto do grafo mas NAO chama free()
 *   no Ponto. Isso e feito pelo Sistema (menu.c) depois de remover
 *   tambem da BST, AVL e Hash, evitando ponteiros invalidos.
 *
 * Grupo: ExameEDII_T3_G4 | ISPTC 2025/2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "grafo.h"

/* ============================================================
   CRIACAO E DESTRUICAO
   ============================================================ */

/*
 * criarGrafo - aloca e inicializa um grafo vazio.
 * Todos os slots de pontos e listas de adjacencia sao NULL.
 */
Grafo* criarGrafo() {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    if (!g) { printf("[ERRO] Falha ao criar grafo.\n"); return NULL; }
    g->numPontos   = 0;
    g->numLigacoes = 0;
    int i;
    for (i = 0; i < MAX_PONTOS; i++) {
        g->pontos[i] = NULL;
        g->adj[i]    = NULL;
    }
    printf("[SUCESSO] Grafo criado.\n");
    return g;
}

/*
 * destruirGrafo - liberta toda a memoria do grafo.
 * Liberta os nos de adjacencia e os proprios Pontos.
 * Chamado apenas quando o sistema encerra.
 */
void destruirGrafo(Grafo* g) {
    if (!g) return;
    int i;
    for (i = 0; i < MAX_PONTOS; i++) {
        /* liberta a lista de adjacencia do ponto i */
        NoAdj* no = g->adj[i];
        while (no) {
            NoAdj* prox = no->prox;
            free(no);
            no = prox;
        }
        /* liberta o proprio Ponto (o grafo e dono da memoria aqui) */
        if (g->pontos[i]) destruirPonto(g->pontos[i]);
    }
    free(g);
}

/* ============================================================
   UTILITARIOS
   ============================================================ */

/*
 * buscarIndicePonto - procura o indice interno de um ponto pelo seu ID.
 * Retorna o indice no array pontos[], ou -1 se nao encontrado.
 */
int buscarIndicePonto(const Grafo* g, int id) {
    int i;
    for (i = 0; i < MAX_PONTOS; i++)
        if (g->pontos[i] && g->pontos[i]->id == id) return i;
    return -1;
}

/* ============================================================
   GESTAO DE PONTOS
   ============================================================ */

/*
 * inserirPontoGrafo - insere um Ponto no primeiro slot disponivel.
 * O grafo nao cria o Ponto - recebe um ponteiro ja alocado.
 */
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
    printf("[ERRO] Grafo cheio (max %d pontos).\n", MAX_PONTOS);
    return 0;
}

/*
 * removerPontoGrafo - remove o ponto do grafo e as suas ligacoes.
 *
 * IMPORTANTE: esta funcao NAO chama destruirPonto() nem free().
 * O ponteiro e removido do array mas a memoria continua valida.
 * Quem chama esta funcao (menu.c) e responsavel por depois
 * remover o ponto da BST, AVL e Hash, e so entao chamar free().
 *
 * Retorna 1 em sucesso, 0 em falha.
 */
int removerPontoGrafo(Grafo* g, int id) {
    int idx = buscarIndicePonto(g, id);
    if (idx < 0) {
        printf("[ERRO] Ponto ID %d nao encontrado.\n", id);
        return 0;
    }
    /* remove a lista de adjacencia do ponto */
    NoAdj* no = g->adj[idx];
    while (no) {
        NoAdj* prox = no->prox;
        free(no);
        no = prox;
    }
    g->adj[idx] = NULL;

    /* remove referencias a este ponto nas listas dos outros nos */
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
            ant = cur;
            cur = cur->prox;
        }
    }

    /* remove do array de ligacoes */
    int j = 0, k;
    for (k = 0; k < g->numLigacoes; k++)
        if (g->ligacoes[k].origem != idx && g->ligacoes[k].destino != idx)
            g->ligacoes[j++] = g->ligacoes[k];
    g->numLigacoes = j;

    /* remove o ponto do array SEM libertar a memoria */
    g->pontos[idx] = NULL;
    g->numPontos--;
    printf("[SUCESSO] Ponto ID %d removido do grafo.\n", id);
    return 1;
}

/*
 * listarPontos - imprime todos os pontos do grafo.
 */
void listarPontos(const Grafo* g) {
    if (!g || g->numPontos == 0) {
        printf("[INFO] Nenhum ponto cadastrado.\n");
        return;
    }
    printf("\n=== PONTOS DA REDE (%d) ===\n", g->numPontos);
    int i;
    for (i = 0; i < MAX_PONTOS; i++)
        if (g->pontos[i]) imprimirPonto(g->pontos[i]);
}

/* ============================================================
   GESTAO DE LIGACOES
   ============================================================ */

/*
 * adicionarLigacao - adiciona uma aresta nao-dirigida entre dois pontos.
 * Cria nos em ambas as listas de adjacencia e regista no array ligacoes[].
 */
int adicionarLigacao(Grafo* g, int orig, int dest, float custo, float dist) {
    int io = buscarIndicePonto(g, orig);
    int id = buscarIndicePonto(g, dest);
    if (io < 0 || id < 0) {
        printf("[ERRO] Um ou ambos os pontos nao existem.\n");
        return 0;
    }
    if (g->numLigacoes >= MAX_LIGACOES) {
        printf("[ERRO] Limite de ligacoes atingido (%d).\n", MAX_LIGACOES);
        return 0;
    }
    /* cria nos na lista de adjacencia (grafo nao-dirigido: dois sentidos) */
    NoAdj* n1 = (NoAdj*)malloc(sizeof(NoAdj));
    NoAdj* n2 = (NoAdj*)malloc(sizeof(NoAdj));
    if (!n1 || !n2) {
        printf("[ERRO] Falha de memoria ao criar ligacao.\n");
        free(n1); free(n2);
        return 0;
    }
    n1->destino = id;   n1->custo = custo; n1->distancia = dist;
    n1->prox = g->adj[io]; g->adj[io] = n1;

    n2->destino = io;   n2->custo = custo; n2->distancia = dist;
    n2->prox = g->adj[id]; g->adj[id] = n2;

    /* guarda no array de ligacoes para uso pelo Kruskal */
    g->ligacoes[g->numLigacoes].origem    = io;
    g->ligacoes[g->numLigacoes].destino   = id;
    g->ligacoes[g->numLigacoes].custo     = custo;
    g->ligacoes[g->numLigacoes].distancia = dist;
    g->numLigacoes++;

    printf("[SUCESSO] Ligacao %d <-> %d adicionada.\n", orig, dest);
    return 1;
}

/*
 * removerLigacao - remove a aresta entre dois pontos (ambos os sentidos).
 */
int removerLigacao(Grafo* g, int orig, int dest) {
    int io = buscarIndicePonto(g, orig);
    int id = buscarIndicePonto(g, dest);
    if (io < 0 || id < 0) {
        printf("[ERRO] Pontos nao encontrados.\n");
        return 0;
    }
    /* remove de adj[io] -> id */
    NoAdj* ant = NULL, *cur = g->adj[io];
    while (cur) {
        if (cur->destino == id) {
            if (ant) ant->prox = cur->prox;
            else     g->adj[io] = cur->prox;
            free(cur); break;
        }
        ant = cur; cur = cur->prox;
    }
    /* remove de adj[id] -> io */
    ant = NULL; cur = g->adj[id];
    while (cur) {
        if (cur->destino == io) {
            if (ant) ant->prox = cur->prox;
            else     g->adj[id] = cur->prox;
            free(cur); break;
        }
        ant = cur; cur = cur->prox;
    }
    /* remove do array de ligacoes */
    int j = 0, k;
    for (k = 0; k < g->numLigacoes; k++)
        if (!((g->ligacoes[k].origem==io && g->ligacoes[k].destino==id) ||
              (g->ligacoes[k].origem==id && g->ligacoes[k].destino==io)))
            g->ligacoes[j++] = g->ligacoes[k];
    g->numLigacoes = j;

    printf("[SUCESSO] Ligacao %d <-> %d removida.\n", orig, dest);
    return 1;
}

/*
 * listarLigacoes - imprime todas as ligacoes registadas.
 */
void listarLigacoes(const Grafo* g) {
    if (!g || g->numLigacoes == 0) {
        printf("[INFO] Nenhuma ligacao cadastrada.\n");
        return;
    }
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

/*
 * visualizarGrafo - imprime a lista de adjacencia do grafo.
 */
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
   UNION-FIND (auxiliar para Kruskal)
   ============================================================ */

/*
 * ufInicializar - inicializa o Union-Find com n elementos.
 * Cada elemento e o seu proprio pai (conjuntos unitarios).
 */
void ufInicializar(UnionFind* uf, int n) {
    int i;
    for (i = 0; i < n; i++) {
        uf->pai[i]  = i;
        uf->rank[i] = 0;
    }
}

/*
 * ufEncontrar - encontra o representante do conjunto de x.
 * Usa compressao de caminho para optimizar operacoes futuras.
 */
int ufEncontrar(UnionFind* uf, int x) {
    if (uf->pai[x] != x)
        uf->pai[x] = ufEncontrar(uf, uf->pai[x]); /* compressao */
    return uf->pai[x];
}

/*
 * ufUnir - une os conjuntos de x e y.
 * Usa uniao por rank para manter a arvore balanceada.
 * Retorna 1 se uniu (conjuntos diferentes), 0 se ja estavam unidos.
 */
int ufUnir(UnionFind* uf, int x, int y) {
    int rx = ufEncontrar(uf, x);
    int ry = ufEncontrar(uf, y);
    if (rx == ry) return 0; /* ja no mesmo conjunto - formaria ciclo */
    /* une pelo rank para manter arvore baixa */
    if (uf->rank[rx] < uf->rank[ry]) { int t = rx; rx = ry; ry = t; }
    uf->pai[ry] = rx;
    if (uf->rank[rx] == uf->rank[ry]) uf->rank[rx]++;
    return 1;
}

/* ============================================================
   KRUSKAL - Arvore Geradora Minima
   ============================================================ */

/*
 * kruskal - encontra a MST usando o algoritmo de Kruskal.
 *
 * Algoritmo:
 *   1. Ordena todas as arestas por custo crescente
 *   2. Para cada aresta: se nao forma ciclo (Union-Find), adiciona
 *   3. Para quando tiver V-1 arestas (MST completa)
 *
 * Complexidade: O(E log E) onde E = numero de arestas.
 */
void kruskal(Grafo* g) {
    if (!g || g->numLigacoes == 0) {
        printf("[ERRO] Sem ligacoes para executar Kruskal.\n");
        return;
    }
    /* copia o array de ligacoes para nao alterar o original */
    Ligacao arr[MAX_LIGACOES];
    int n = g->numLigacoes, i, j;
    for (i = 0; i < n; i++) arr[i] = g->ligacoes[i];

    /* ordena por custo crescente (bubble sort simples) */
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j].custo > arr[j+1].custo) {
                Ligacao tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }

    /* inicializa Union-Find com todos os pontos */
    UnionFind uf;
    ufInicializar(&uf, MAX_PONTOS);

    float custoTotal  = 0;
    int   contArestas = 0;

    printf("\n=== KRUSKAL - Arvore Geradora Minima ===\n");
    for (i = 0; i < n && contArestas < g->numPontos - 1; i++) {
        int u = arr[i].origem;
        int v = arr[i].destino;
        /* so adiciona se nao formar ciclo */
        if (ufUnir(&uf, u, v)) {
            const char* nu = g->pontos[u] ? g->pontos[u]->nome : "?";
            const char* nv = g->pontos[v] ? g->pontos[v]->nome : "?";
            printf("  Ligacao: %-20s <-> %-20s | Custo: %.2f Kz\n",
                   nu, nv, arr[i].custo);
            custoTotal += arr[i].custo;
            contArestas++;
        }
    }
    printf("  --------------------------------------------------\n");
    printf("  Custo total da rede (Kruskal): %.2f Kz\n", custoTotal);
}

/* ============================================================
   PRIM - Arvore Geradora Minima
   ============================================================ */

/*
 * prim - encontra a MST usando o algoritmo de Prim.
 *
 * Algoritmo:
 *   1. Comeca no no inicial com chave 0
 *   2. Repete: escolhe o no nao visitado com menor chave
 *   3. Actualiza as chaves dos vizinhos
 *
 * Complexidade: O(V^2) na implementacao com array simples.
 */
void prim(Grafo* g, int idInicio) {
    if (!g || g->numPontos == 0) {
        printf("[ERRO] Grafo vazio.\n");
        return;
    }
    int inicio = buscarIndicePonto(g, idInicio);
    if (inicio < 0) {
        printf("[ERRO] Ponto inicial nao encontrado.\n");
        return;
    }

    int   visitado[MAX_PONTOS]; /* 1 se o no ja foi incluido na MST */
    float chave[MAX_PONTOS];    /* menor custo para chegar ao no    */
    int   pai[MAX_PONTOS];      /* no anterior na MST               */
    int i;

    /* inicializa: todos com chave infinita, sem pai, nao visitados */
    for (i = 0; i < MAX_PONTOS; i++) {
        visitado[i] = 0;
        chave[i]    = FLT_MAX;
        pai[i]      = -1;
    }
    chave[inicio] = 0; /* no inicial tem custo 0 */

    float custoTotal = 0;
    printf("\n=== PRIM - Arvore Geradora Minima (inicio: %s) ===\n",
           g->pontos[inicio]->nome);

    int count;
    for (count = 0; count < g->numPontos; count++) {
        /* escolhe o no nao visitado com menor chave */
        int u = -1;
        for (i = 0; i < MAX_PONTOS; i++)
            if (g->pontos[i] && !visitado[i] &&
               (u == -1 || chave[i] < chave[u]))
                u = i;

        if (u == -1 || chave[u] == FLT_MAX) break; /* grafo desconexo */
        visitado[u] = 1;

        /* imprime a aresta adicionada (excepto o no inicial) */
        if (pai[u] != -1) {
            const char* nu = g->pontos[u]     ? g->pontos[u]->nome     : "?";
            const char* np = g->pontos[pai[u]]? g->pontos[pai[u]]->nome: "?";
            printf("  Ligacao: %-20s <-> %-20s | Custo: %.2f Kz\n",
                   np, nu, chave[u]);
            custoTotal += chave[u];
        }

        /* actualiza chaves dos vizinhos nao visitados */
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
    printf("  --------------------------------------------------\n");
    printf("  Custo total da rede (Prim): %.2f Kz\n", custoTotal);
}
