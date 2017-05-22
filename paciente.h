#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED

typedef struct paciente Paciente;
Paciente* paciente_cria(char* nome, int telefone, int nsus, int gravidade, int salvar);
int paciente_gravidade(Paciente* p);
char* paciente_nome(Paciente* p);
int paciente_sus(Paciente* p);
int paciente_telefone(Paciente* p);
int paciente_salvar(Paciente* p);
void paciente_modifica_salvar(Paciente* p, int salvar_dado);
void paciente_modifica_gravidade(Paciente* p, int gravidade);
void paciente_modifica_info(Paciente* p, char* nome, int tel);

#endif // PACIENTE_H_INCLUDED
