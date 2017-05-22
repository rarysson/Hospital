#ifndef SISTEMA_H_INCLUDED
#define SISTEMA_H_INCLUDED

#include "paciente.h"
typedef struct heap Heap;
Heap* fila_cria(int max);
void fila_atende(Heap* h);
void fila_insere(Heap* h, Paciente* p);
int fila_vazia(Heap* h);
int fila_cheia(Heap* h);

#endif // SISTEMA_H_INCLUDED
