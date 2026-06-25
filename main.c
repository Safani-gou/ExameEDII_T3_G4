/*
 * Sistema de Gestao de Rede Hidraulica
 * Disciplina: Estrutura de Dados II
 * Instituto Superior Politecnico de Tecnologias e Ciencias
 * Semestre: 2025/2 | Docente: Silvia Antonio
 *
 * Grupo: ExameEDII_T1_G16
 */

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "utils.h"

int main() {
    printf("\n  Iniciando Sistema de Rede Hidraulica...\n\n");

    Sistema* s = criarSistema();
    if (!s) {
        printf("[ERRO FATAL] Falha ao inicializar o sistema.\n");
        return EXIT_FAILURE;
    }

    menuPrincipal(s);

    destruirSistema(s);
    printf("[INFO] Memoria libertada. Sistema encerrado.\n");
    return EXIT_SUCCESS;
}
