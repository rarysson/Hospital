#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

//Descri��o: Estrutura do Paciente
struct paciente{
    char nome[86];
    int telefone;
    int sus;
    int gravidade;
    int salvar;
};

//Descri��o: Ir� alocar um novo paciente e defenir as suas informa��es
Paciente* paciente_cria(char* nome, int telefone, int nsus, int gravidade, int salvar){
    Paciente* novo = (Paciente*) malloc(sizeof(Paciente));

    if(novo == NULL){
        printf("\nERRO DE ALOCACAO DE MEMORIA.\n");
        exit(1);
    }

    strcpy(novo->nome, nome);
    novo->telefone = telefone;
    novo->sus = nsus;
    novo->gravidade = gravidade;
    novo->salvar = salvar;

return novo;
}

//Descri��o: Retornar� o n�vel da gravidade do paciente
int paciente_gravidade(Paciente* p){
return p->gravidade;
}

//Descri��o: Retornar� o nome do paciente
char* paciente_nome(Paciente* p){
return p->nome;
}

//Descri��o: Retornar� o n�mero do SUS do paciente
int paciente_sus(Paciente* p){
return p->sus;
}

//Descri��o: Retornar� o n�mero do telefone do paciente
int paciente_telefone(Paciente* p){
return p->telefone;
}

//Descri��o: Retornar� se o paciente quis salvar os dados ou n�o
int paciente_salvar(Paciente* p){
return p->salvar;
}

//Descri��o: Modifica o valor de salvar
void paciente_modifica_salvar(Paciente* p, int salvar_dado){
    p->salvar = salvar_dado;
}

//Descri��o: Modifica o n�vel da gravidade
void paciente_modifica_gravidade(Paciente* p, int gravidade){
    p->gravidade = gravidade;
}

//Descri��o: Modificar� o nome e o telefone do paciente
void paciente_modifica_info(Paciente* p, char* nome, int tel){
    strcpy(p->nome, nome);
    p->telefone = tel;
}
