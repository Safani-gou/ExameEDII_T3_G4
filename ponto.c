/*
 * ponto.c - Implementacao do TAD Ponto
 *
 * Cada ponto representa um no da rede hidraulica
 * (reservatorio, casa, escola ou hospital).
 *
 * Grupo: ExameEDII_T3_G4 | ISPTC 2025/2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"

/*
 * criarPonto - aloca e inicializa um novo Ponto na heap.
 * Parametros:
 *   id   - identificador unico
 *   nome - nome do ponto (max MAX_NOME-1 caracteres)
 *   tipo - tipo do ponto (TipoPonto)
 * Retorno: ponteiro para o novo Ponto, ou NULL em caso de falha.
 */
Ponto* criarPonto(int id, const char* nome, TipoPonto tipo) {
    Ponto* p = (Ponto*)malloc(sizeof(Ponto));
    if (!p) {
        printf("[ERRO] Falha ao alocar memoria para ponto.\n");
        return NULL;
    }
    p->id   = id;
    strncpy(p->nome, nome, MAX_NOME - 1);
    p->nome[MAX_NOME - 1] = '\0'; /* garante terminacao da string */
    p->tipo = tipo;
    printf("[SUCESSO] Ponto '%s' (ID %d) criado.\n", p->nome, p->id);
    return p;
}

/*
 * tipoParaString - converte TipoPonto para string legivel.
 */
const char* tipoParaString(TipoPonto tipo) {
    switch (tipo) {
        case RESERVATORIO: return "Reservatorio";
        case CASA:         return "Casa";
        case ESCOLA:       return "Escola";
        case HOSPITAL:     return "Hospital";
        default:           return "Desconhecido";
    }
}

/*
 * stringParaTipo - converte string para TipoPonto.
 * Usado na leitura do ficheiro de dados.
 */
TipoPonto stringParaTipo(const char* str) {
    if (strcmp(str, "Reservatorio") == 0) return RESERVATORIO;
    if (strcmp(str, "Casa")         == 0) return CASA;
    if (strcmp(str, "Escola")       == 0) return ESCOLA;
    if (strcmp(str, "Hospital")     == 0) return HOSPITAL;
    return CASA; /* valor por defeito */
}

/*
 * imprimirPonto - exibe os dados de um ponto no ecra.
 */
void imprimirPonto(const Ponto* p) {
    if (!p) {
        printf("[ERRO] Ponto invalido.\n");
        return;
    }
    printf("  ID: %d | Nome: %-25s | Tipo: %s\n",
           p->id, p->nome, tipoParaString(p->tipo));
}

/*
 * destruirPonto - liberta a memoria alocada para um Ponto.
 * ATENCAO: so deve ser chamada quando nenhuma outra estrutura
 *          (BST, AVL, Hash) referencia este ponteiro.
 */
void destruirPonto(Ponto* p) {
    if (p) free(p);
}
