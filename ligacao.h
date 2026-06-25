#ifndef LIGACAO_H
#define LIGACAO_H

/* Estrutura de uma ligacao (aresta do grafo) */
typedef struct {
    int origem;      /* ID do ponto de origem */
    int destino;     /* ID do ponto de destino */
    float custo;     /* Custo de instalacao em Kz */
    float distancia; /* Distancia em metros */
} Ligacao;

/* Prototipos */
Ligacao* criarLigacao(int origem, int destino, float custo, float distancia);
void imprimirLigacao(const Ligacao* l);
void destruirLigacao(Ligacao* l);
int compararPorCusto(const void* a, const void* b);
int compararPorDistancia(const void* a, const void* b);

#endif
