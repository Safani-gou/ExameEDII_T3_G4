#ifndef UTILS_H
#define UTILS_H

void limparBuffer();
void pausar();
void limparEcra();
void imprimirSeparador(char c, int n);
void imprimirTitulo(const char* titulo);
int  lerInteiro(const char* mensagem, int min, int max);
float lerFloat(const char* mensagem);
void lerString(const char* mensagem, char* destino, int maxLen);

#endif
