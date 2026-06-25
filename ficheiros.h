#ifndef FICHEIROS_H
#define FICHEIROS_H

#include "grafo.h"

int carregarDados   (Grafo* g, const char* ficheiro);
int salvarDados     (const Grafo* g, const char* ficheiro);
int salvarResultadoMST(const char* ficheiro, const char* conteudo);

#endif
