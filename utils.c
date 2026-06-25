#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    limparBuffer();
}

void limparEcra() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void imprimirSeparador(char c, int n) {
    int i;
    for (i = 0; i < n; i++) putchar(c);
    putchar('\n');
}

void imprimirTitulo(const char* titulo) {
    imprimirSeparador('=', 55);
    printf("  %s\n", titulo);
    imprimirSeparador('=', 55);
}

int lerInteiro(const char* mensagem, int min, int max) {
    int val; char buf[32];
    while (1) {
        printf("%s", mensagem);
        if (fgets(buf, sizeof(buf), stdin)) {
            if (sscanf(buf, "%d", &val) == 1 && val >= min && val <= max) return val;
        }
        printf("[ERRO] Valor invalido. Insira um numero entre %d e %d.\n", min, max);
    }
}

float lerFloat(const char* mensagem) {
    float val; char buf[32];
    while (1) {
        printf("%s", mensagem);
        if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%f", &val) == 1 && val >= 0) return val;
        printf("[ERRO] Valor invalido. Insira um numero positivo.\n");
    }
}

void lerString(const char* mensagem, char* destino, int maxLen) {
    printf("%s", mensagem);
    if (fgets(destino, maxLen, stdin)) {
        int len = strlen(destino);
        if (len > 0 && destino[len-1] == '\n') destino[len-1] = '\0';
    }
}
