#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "ordenacao.h"
#include "busca.h"
#include "ficheiros.h"
#include "utils.h"

/* ============================================================
   SISTEMA
   ============================================================ */

Sistema* criarSistema() {
    Sistema* s = (Sistema*)malloc(sizeof(Sistema));
    if (!s) return NULL;
    s->grafo = criarGrafo();
    s->bst   = criarBST();
    s->avl   = criarAVL();
    s->hash  = criarHashTable();
    return s;
}

void destruirSistema(Sistema* s) {
    if (!s) return;
    destruirGrafo(s->grafo);
    destruirBST(s->bst);
    destruirAVL(s->avl);
    destruirHash(s->hash);
    free(s);
}

/* ============================================================
   MENU PRINCIPAL
   ============================================================ */

void menuPrincipal(Sistema* s) {
    int opcao;
    do {
        limparEcra();
        imprimirTitulo("SISTEMA DE GESTAO DE REDE HIDRAULICA");
        printf("  1. Gerir Pontos da Rede\n");
        printf("  2. Gerir Ligacoes\n");
        printf("  3. Visualizar Grafo\n");
        printf("  4. Algoritmos de Ordenacao\n");
        printf("  5. Algoritmos de Busca\n");
        printf("  6. Estruturas de Dados\n");
        printf("  7. Rede de Menor Custo (MST)\n");
        printf("  8. Estatisticas\n");
        printf("  9. Ficheiros (Carregar/Salvar)\n");
        printf("  0. Sair\n");
        imprimirSeparador('-', 55);
        opcao = lerInteiro("  Opcao: ", 0, 9);

        switch (opcao) {
            case 1: menuPontos(s);        break;
            case 2: menuLigacoes(s);      break;
            case 3:
                limparEcra();
                visualizarGrafo(s->grafo);
                pausar(); break;
            case 4: menuOrdenacao(s);     break;
            case 5: menuBusca(s);         break;
            case 6: menuEstruturas(s);    break;
            case 7: menuMST(s);           break;
            case 8: menuEstatisticas(s);  break;
            case 9: menuFicheiros(s);     break;
            case 0: printf("\n  Encerrando o sistema. Ate logo!\n\n"); break;
        }
    } while (opcao != 0);
}

/* ============================================================
   MENU PONTOS
   ============================================================ */

void menuPontos(Sistema* s) {
    int opcao;
    do {
        limparEcra();
        imprimirTitulo("GESTAO DE PONTOS");
        printf("  1. Inserir ponto\n");
        printf("  2. Remover ponto\n");
        printf("  3. Listar pontos\n");
        printf("  0. Voltar\n");
        imprimirSeparador('-', 55);
        opcao = lerInteiro("  Opcao: ", 0, 3);

        if (opcao == 1) {
            int id = lerInteiro("  ID do ponto: ", 1, 9999);
            char nome[MAX_NOME]; lerString("  Nome: ", nome, MAX_NOME);
            printf("  Tipo (0=Reservatorio 1=Casa 2=Escola 3=Hospital): ");
            int t = lerInteiro("", 0, 3);
            Ponto* p = criarPonto(id, nome, (TipoPonto)t);
            if (p) {
                inserirPontoGrafo(s->grafo, p);
                s->bst->raiz = inserirBST(s->bst->raiz, p);
                s->avl->raiz = inserirAVL(s->avl->raiz, p);
                inserirHash(s->hash, p);
            }
            pausar();
        } else if (opcao == 2) {
            int id = lerInteiro("  ID a remover: ", 1, 9999);
            /*
             * GESTAO DE MEMORIA SEGURA:
             * O Ponto e partilhado pelo grafo, BST, AVL e Hash.
             * Ordem correcta:
             *   1. Guardar o ponteiro antes de remover
             *   2. Remover de todas as estruturas (sem free)
             *   3. Chamar free() UMA unica vez no final
             * Assim evitamos ponteiros invalidos (dangling pointers).
             */
            /* passo 1: guardar ponteiro antes de qualquer remocao */
            int idx = buscarIndicePonto(s->grafo, id);
            Ponto* pRemover = (idx >= 0) ? s->grafo->pontos[idx] : NULL;

            /* passo 2: remover de todas as estruturas (sem libertar memoria) */
            removerPontoGrafo(s->grafo, id);   /* NAO chama free() */
            s->bst->raiz = removerBST(s->bst->raiz, id);
            s->avl->raiz = removerAVL(s->avl->raiz, id);
            removerHash(s->hash, id);

            /* passo 3: libertar a memoria uma unica vez */
            if (pRemover) {
                free(pRemover);
                printf("[SUCESSO] Memoria do ponto ID %d libertada.\n", id);
            }
            pausar();
        } else if (opcao == 3) {
            limparEcra();
            listarPontos(s->grafo);
            pausar();
        }
    } while (opcao != 0);
}

/* ============================================================
   MENU LIGACOES
   ============================================================ */

void menuLigacoes(Sistema* s) {
    int opcao;
    do {
        limparEcra();
        imprimirTitulo("GESTAO DE LIGACOES");
        printf("  1. Adicionar ligacao\n");
        printf("  2. Remover ligacao\n");
        printf("  3. Listar ligacoes\n");
        printf("  0. Voltar\n");
        imprimirSeparador('-', 55);
        opcao = lerInteiro("  Opcao: ", 0, 3);

        if (opcao == 1) {
            int o = lerInteiro("  ID origem: ", 1, 9999);
            int d = lerInteiro("  ID destino: ", 1, 9999);
            float c = lerFloat("  Custo (Kz): ");
            float dist = lerFloat("  Distancia (m): ");
            adicionarLigacao(s->grafo, o, d, c, dist);
            pausar();
        } else if (opcao == 2) {
            int o = lerInteiro("  ID origem: ", 1, 9999);
            int d = lerInteiro("  ID destino: ", 1, 9999);
            removerLigacao(s->grafo, o, d);
            pausar();
        } else if (opcao == 3) {
            limparEcra();
            listarLigacoes(s->grafo);
            pausar();
        }
    } while (opcao != 0);
}

/* ============================================================
   MENU ORDENACAO
   ============================================================ */

void menuOrdenacao(Sistema* s) {
    int opcao;
    do {
        limparEcra();
        imprimirTitulo("ALGORITMOS DE ORDENACAO");
        printf("  1. Ordenar ligacoes por custo\n");
        printf("  2. Ordenar ligacoes por distancia\n");
        printf("  3. Comparar todos os algoritmos\n");
        printf("  0. Voltar\n");
        imprimirSeparador('-', 55);
        opcao = lerInteiro("  Opcao: ", 0, 3);

        if (opcao >= 1 && opcao <= 3) {
            int n = s->grafo->numLigacoes;
            if (n == 0) { printf("[ERRO] Sem ligacoes.\n"); pausar(); continue; }
            Ligacao* copia = (Ligacao*)malloc(n * sizeof(Ligacao));
            int i; for (i = 0; i < n; i++) copia[i] = s->grafo->ligacoes[i];

            if (opcao == 1) {
                printf("\n  Escolha: 1=Insertion 2=Selection 3=Shell 4=Merge 5=Quick 6=Heap\n");
                int alg = lerInteiro("  Algoritmo: ", 1, 6);
                CriterioOrdem c = POR_CUSTO;
                switch(alg) {
                    case 1: insertionSort(copia, n, c); break;
                    case 2: selectionSort(copia, n, c); break;
                    case 3: shellSort(copia, n, c);     break;
                    case 4: mergeSort(copia, n, c);     break;
                    case 5: quickSort(copia, 0, n-1, c);break;
                    case 6: heapSort(copia, n, c);      break;
                }
                printf("\n  Ligacoes ordenadas por custo:\n");
                for (i = 0; i < n; i++) imprimirLigacao(&copia[i]);
            } else if (opcao == 2) {
                mergeSort(copia, n, POR_DISTANCIA);
                printf("\n  Ligacoes ordenadas por distancia:\n");
                for (i = 0; i < n; i++) imprimirLigacao(&copia[i]);
            } else {
                compararTodosAlgoritmos(s->grafo->ligacoes, n);
            }
            free(copia);
            pausar();
        }
    } while (opcao != 0);
}

/* ============================================================
   MENU BUSCA
   ============================================================ */

void menuBusca(Sistema* s) {
    int opcao;
    do {
        limparEcra();
        imprimirTitulo("ALGORITMOS DE BUSCA");
        printf("  1. Busca linear por ID\n");
        printf("  2. Busca binaria por ID\n");
        printf("  3. Busca em AVL por ID\n");
        printf("  4. Busca em Hash por ID\n");
        printf("  5. Busca por nome\n");
        printf("  0. Voltar\n");
        imprimirSeparador('-', 55);
        opcao = lerInteiro("  Opcao: ", 0, 5);

        if (opcao >= 1 && opcao <= 5) {
            /* Monta array de ponteiros de pontos */
            Ponto* arr[MAX_PONTOS]; int n = 0, i;
            for (i = 0; i < MAX_PONTOS; i++)
                if (s->grafo->pontos[i]) arr[n++] = s->grafo->pontos[i];

            Ponto* resultado = NULL;
            if (opcao == 5) {
                char nome[MAX_NOME]; lerString("  Nome: ", nome, MAX_NOME);
                resultado = buscaPorNome(arr, n, nome);
            } else {
                int id = lerInteiro("  ID a buscar: ", 1, 9999);
                if (opcao == 1) resultado = buscaLinear(arr, n, id);
                else if (opcao == 2) { ordenarPontosPorID(arr, n); resultado = buscaBinaria(arr, n, id); }
                else if (opcao == 3) resultado = buscaEmAVL(s->avl, id);
                else if (opcao == 4) resultado = buscaEmHash(s->hash, id);
            }
            if (resultado) imprimirPonto(resultado);
            pausar();
        }
    } while (opcao != 0);
}

/* ============================================================
   MENU ESTRUTURAS
   ============================================================ */

void menuEstruturas(Sistema* s) {
    int opcao;
    do {
        limparEcra();
        imprimirTitulo("ESTRUTURAS DE DADOS");
        printf("  1. Listar BST (em ordem)\n");
        printf("  2. Listar AVL (em ordem)\n");
        printf("  3. Listar Tabela Hash\n");
        printf("  0. Voltar\n");
        imprimirSeparador('-', 55);
        opcao = lerInteiro("  Opcao: ", 0, 3);

        limparEcra();
        if (opcao == 1) { printf("\n=== BST em ordem ===\n"); emOrdemBST(s->bst->raiz); }
        else if (opcao == 2) { printf("\n=== AVL em ordem ===\n"); emOrdemAVL(s->avl->raiz); }
        else if (opcao == 3) listarHash(s->hash);
        if (opcao >= 1 && opcao <= 3) pausar();
    } while (opcao != 0);
}

/* ============================================================
   MENU MST
   ============================================================ */

void menuMST(Sistema* s) {
    int opcao;
    do {
        limparEcra();
        imprimirTitulo("REDE DE MENOR CUSTO (MST)");
        printf("  1. Kruskal\n");
        printf("  2. Prim\n");
        printf("  0. Voltar\n");
        imprimirSeparador('-', 55);
        opcao = lerInteiro("  Opcao: ", 0, 2);

        if (opcao == 1) { kruskal(s->grafo); pausar(); }
        else if (opcao == 2) {
            int id = lerInteiro("  ID do ponto inicial: ", 1, 9999);
            prim(s->grafo, id);
            pausar();
        }
    } while (opcao != 0);
}

/* ============================================================
   MENU ESTATISTICAS
   ============================================================ */

void menuEstatisticas(Sistema* s) {
    limparEcra();
    imprimirTitulo("ESTATISTICAS DA REDE");
    printf("  Total de pontos  : %d\n", s->grafo->numPontos);
    printf("  Total de ligacoes: %d\n", s->grafo->numLigacoes);

    float custoTotal = 0, distTotal = 0;
    int i;
    for (i = 0; i < s->grafo->numLigacoes; i++) {
        custoTotal += s->grafo->ligacoes[i].custo;
        distTotal  += s->grafo->ligacoes[i].distancia;
    }
    printf("  Custo total      : %.2f Kz\n", custoTotal);
    printf("  Distancia total  : %.2f m\n",  distTotal);
    printf("  Elementos na BST : (percorra em ordem para contar)\n");
    printf("  Elementos na Hash: %d\n", s->hash->tamanho);

    if (s->grafo->numLigacoes > 0)
        compararTodosAlgoritmos(s->grafo->ligacoes, s->grafo->numLigacoes);

    pausar();
}

/* ============================================================
   MENU FICHEIROS
   ============================================================ */

void menuFicheiros(Sistema* s) {
    int opcao;
    do {
        limparEcra();
        imprimirTitulo("FICHEIROS");
        printf("  1. Carregar dados de 'dados_entrada.txt'\n");
        printf("  2. Salvar dados em 'dados_saida.txt'\n");
        printf("  0. Voltar\n");
        imprimirSeparador('-', 55);
        opcao = lerInteiro("  Opcao: ", 0, 2);

        if (opcao == 1) {
            carregarDados(s->grafo, "dados_entrada.txt");
            /* Sincroniza BST, AVL e Hash com os dados carregados */
            int i;
            for (i = 0; i < MAX_PONTOS; i++) {
                if (!s->grafo->pontos[i]) continue;
                Ponto* p = s->grafo->pontos[i];
                s->bst->raiz = inserirBST(s->bst->raiz, p);
                s->avl->raiz = inserirAVL(s->avl->raiz, p);
                inserirHash(s->hash, p);
            }
            pausar();
        } else if (opcao == 2) {
            salvarDados(s->grafo, "dados_saida.txt");
            pausar();
        }
    } while (opcao != 0);
}
