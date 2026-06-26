#ifndef LIGACAO_H
#define LIGACAO_H

/*
 * Ligacao - TAD que representa uma aresta do grafo.
 * Cada ligacao conecta dois pontos da rede com um
 * custo de instalacao (Kz) e uma distancia (metros).
 */
typedef struct {
    int   origem;    /* indice interno do ponto de origem  */
    int   destino;   /* indice interno do ponto de destino */
    float custo;     /* custo de instalacao em Kwanzas     */
    float distancia; /* comprimento da tubagem em metros   */
} Ligacao;

/* ---- Prototipos ---- */
Ligacao* criarLigacao(int origem, int destino, float custo, float distancia);
void     imprimirLigacao(const Ligacao* l);
void     destruirLigacao(Ligacao* l);
int      compararPorCusto(const void* a, const void* b);
int      compararPorDistancia(const void* a, const void* b);

#endif /* LIGACAO_H */
