/*
 * Sistema de Gestao de Rede Hidraulica
 * Disciplina: Estrutura de Dados II
 * Instituto Superior Politecnico de Tecnologias e Ciencias
 * Semestre: 2025/2 | Docente: Silvia Antonio
 *
 * Grupo: ExameEDII_T3_G4
 */

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "ficheiros.h"
#include "utils.h"

int main() {
    printf("\n  Iniciando Sistema de Rede Hidraulica...\n\n");

    Sistema* s = criarSistema();
    if (!s) {
        printf("[ERRO FATAL] Falha ao inicializar o sistema.\n");
        return EXIT_FAILURE;
    }

    /* ── Carrega dados automaticamente ao arrancar ── */
    FILE* teste = fopen("dados_entrada.txt", "r");
    if (teste) {
        fclose(teste);
        printf("[INFO] Ficheiro 'dados_entrada.txt' encontrado. A carregar dados...\n\n");
        carregarDados(s->grafo, "dados_entrada.txt");

        /* Sincroniza BST, AVL e Hash com os pontos carregados */
        int i;
        for (i = 0; i < MAX_PONTOS; i++) {
            if (!s->grafo->pontos[i]) continue;
            Ponto* p = s->grafo->pontos[i];
            s->bst->raiz = inserirBST(s->bst->raiz, p);
            s->avl->raiz = inserirAVL(s->avl->raiz, p);
            inserirHash(s->hash, p);
        }
        printf("\n[SUCESSO] Grafo construido automaticamente a partir do ficheiro.\n");
        printf("          Pontos: %d | Ligacoes: %d\n\n",
               s->grafo->numPontos, s->grafo->numLigacoes);
    } else {
        printf("[INFO] Ficheiro 'dados_entrada.txt' nao encontrado. Iniciando com grafo vazio.\n\n");
    }

    menuPrincipal(s);

    destruirSistema(s);
    printf("[INFO] Memoria libertada. Sistema encerrado.\n");
    return EXIT_SUCCESS;
}
