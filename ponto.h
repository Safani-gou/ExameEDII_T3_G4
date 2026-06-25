#ifndef PONTO_H
#define PONTO_H

#define MAX_NOME 100
#define MAX_PONTOS 200

/* Tipos de ponto na rede hidraulica */
typedef enum {
    RESERVATORIO,
    CASA,
    ESCOLA,
    HOSPITAL
} TipoPonto;

/* Estrutura de um ponto da rede */
typedef struct {
    int id;
    char nome[MAX_NOME];
    TipoPonto tipo;
} Ponto;

/* Prototipos */
Ponto* criarPonto(int id, const char* nome, TipoPonto tipo);
void imprimirPonto(const Ponto* p);
void imprimirTipo(TipoPonto tipo);
const char* tipoParaString(TipoPonto tipo);
TipoPonto stringParaTipo(const char* str);
void destruirPonto(Ponto* p);

#endif
