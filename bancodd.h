#ifndef BANCODD_H_INCLUDED
#define BANCODD_H_INCLUDED

#include "paciente.h"
typedef struct hash Hash;
Hash* hash_cria(void);
void hash_insere(Hash* h, Paciente* p);
Hash* hash_carrega(void);
Paciente* hash_busca(Hash* h, int sus);
void banco_salva(Hash* h);

#endif // BANCODD_H_INCLUDED
