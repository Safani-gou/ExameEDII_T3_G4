#ifndef PONTO_H
#define PONTO_H

/* Numero maximo de pontos suportados pelo sistema */
#define MAX_NOME   100
#define MAX_PONTOS 200

/*
 * TipoPonto - enumeracao dos tipos de nos da rede hidraulica.
 * Cada ponto pode ser um reservatorio, casa, escola ou hospital.
 */
typedef enum {
    RESERVATORIO,
    CASA,
    ESCOLA,
    HOSPITAL
} TipoPonto;

/*
 * Ponto - TAD que representa um no da rede hidraulica.
 * Campos:
 *   id   - identificador unico inteiro
 *   nome - nome descritivo do ponto
 *   tipo - categoria do ponto (TipoPonto)
 */
typedef struct {
    int id;
    char nome[MAX_NOME];
    TipoPonto tipo;
} Ponto;

/* ---- Prototipos ---- */
Ponto*      criarPonto(int id, const char* nome, TipoPonto tipo);
void        imprimirPonto(const Ponto* p);
const char* tipoParaString(TipoPonto tipo);
TipoPonto   stringParaTipo(const char* str);
void        destruirPonto(Ponto* p);

#endif /* PONTO_H */
