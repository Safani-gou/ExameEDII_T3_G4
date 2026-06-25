#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"

/* Cria um novo ponto alocado na heap */
Ponto* criarPonto(int id, const char* nome, TipoPonto tipo) {
    Ponto* p = (Ponto*)malloc(sizeof(Ponto));
    if (!p) {
        printf("[ERRO] Falha ao alocar memoria para ponto.\n");
        return NULL;
    }
    p->id   = id;
    strncpy(p->nome, nome, MAX_NOME - 1);
    p->nome[MAX_NOME - 1] = '\0';
    p->tipo = tipo;
    printf("[SUCESSO] Ponto '%s' (ID %d) criado.\n", p->nome, p->id);
    return p;
}

/* Retorna string do tipo */
const char* tipoParaString(TipoPonto tipo) {
    switch (tipo) {
        case RESERVATORIO: return "Reservatorio";
        case CASA:         return "Casa";
        case ESCOLA:       return "Escola";
        case HOSPITAL:     return "Hospital";
        default:           return "Desconhecido";
    }
}

/* Converte string para TipoPonto */
TipoPonto stringParaTipo(const char* str) {
    if (strcmp(str, "Reservatorio") == 0) return RESERVATORIO;
    if (strcmp(str, "Casa")         == 0) return CASA;
    if (strcmp(str, "Escola")       == 0) return ESCOLA;
    if (strcmp(str, "Hospital")     == 0) return HOSPITAL;
    return CASA; /* default */
}

/* Imprime os dados de um ponto */
void imprimirPonto(const Ponto* p) {
    if (!p) { printf("[ERRO] Ponto invalido.\n"); return; }
    printf("  ID: %d | Nome: %-20s | Tipo: %s\n",
           p->id, p->nome, tipoParaString(p->tipo));
}

/* Libera a memoria de um ponto */
void destruirPonto(Ponto* p) {
    if (p) free(p);
}
