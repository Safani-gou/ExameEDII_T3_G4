#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiros.h"

/*
  Formato do ficheiro de entrada (dados_entrada.txt):
  PONTO id nome tipo
  LIGACAO orig dest custo distancia
*/
int carregarDados(Grafo* g, const char* ficheiro) {
    FILE* f = fopen(ficheiro, "r");
    if (!f) { printf("[ERRO] Nao foi possivel abrir '%s'.\n", ficheiro); return 0; }

    char linha[256], tipo_str[32];
    int  carregados = 0;

    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#' || linha[0] == '\n') continue; /* comentarios */

        if (strncmp(linha, "PONTO", 5) == 0) {
            int id; char nome[MAX_NOME];
            sscanf(linha, "PONTO %d %99s %31s", &id, nome, tipo_str);
            Ponto* p = criarPonto(id, nome, stringParaTipo(tipo_str));
            if (p) { inserirPontoGrafo(g, p); carregados++; }

        } else if (strncmp(linha, "LIGACAO", 7) == 0) {
            int orig, dest; float custo, dist;
            sscanf(linha, "LIGACAO %d %d %f %f", &orig, &dest, &custo, &dist);
            adicionarLigacao(g, orig, dest, custo, dist);
            carregados++;
        }
    }
    fclose(f);
    printf("[SUCESSO] Ficheiro '%s' carregado (%d registos).\n", ficheiro, carregados);
    return 1;
}

int salvarDados(const Grafo* g, const char* ficheiro) {
    FILE* f = fopen(ficheiro, "w");
    if (!f) { printf("[ERRO] Nao foi possivel escrever em '%s'.\n", ficheiro); return 0; }

    fprintf(f, "# Sistema de Gestao de Rede Hidraulica\n");
    fprintf(f, "# Formato: PONTO id nome tipo\n");
    fprintf(f, "# Formato: LIGACAO orig dest custo distancia\n\n");

    int i;
    for (i = 0; i < MAX_PONTOS; i++) {
        if (!g->pontos[i]) continue;
        fprintf(f, "PONTO %d %s %s\n",
                g->pontos[i]->id,
                g->pontos[i]->nome,
                tipoParaString(g->pontos[i]->tipo));
    }
    for (i = 0; i < g->numLigacoes; i++) {
        int io = g->ligacoes[i].origem, id = g->ligacoes[i].destino;
        int origID = g->pontos[io] ? g->pontos[io]->id : io;
        int destID = g->pontos[id] ? g->pontos[id]->id : id;
        fprintf(f, "LIGACAO %d %d %.2f %.2f\n",
                origID, destID,
                g->ligacoes[i].custo, g->ligacoes[i].distancia);
    }
    fclose(f);
    printf("[SUCESSO] Dados salvos em '%s'.\n", ficheiro);
    return 1;
}

int salvarResultadoMST(const char* ficheiro, const char* conteudo) {
    FILE* f = fopen(ficheiro, "a");
    if (!f) { printf("[ERRO] Nao foi possivel escrever resultados MST.\n"); return 0; }
    fprintf(f, "%s\n", conteudo);
    fclose(f);
    return 1;
}
