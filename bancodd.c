#include <stdio.h>
#include <stdlib.h>
#include "bancodd.h"

//Descri��o: Prot�tipos das fun��es auxiliares.
void realocar(Hash* h);
int calcula_hash(Hash* h, int x);

//Descri��o: Estrutura de um Hash.
struct hash{
    int qtd; // Quantidade de pacientes atuais.
    int max; // Quantidade m�xima de pacientes.
    Paciente** v; // Vetor de ponteiros para o tipo Paciente.
};

//Descri��o: Alocar� a tabela hash e inicializar� ela
Hash* hash_cria(void){
    Hash* novo = (Hash*) malloc(7*sizeof(Hash));
    int i;

    if(novo == NULL){
        printf("\nERRO DE ALOCACAO DE MEMORIA.\n");
        exit(1);
    }

    novo->qtd = 0;
    novo->max = 7;
    novo->v = (Paciente**) malloc(novo->max*sizeof(Paciente*));

    if(novo->v == NULL){
        printf("\nERRO DE ALOCACAO DE MEMORIA.\n");
        exit(1);
    }

    for(i = 0; i < novo->max; i++)
        novo->v[i] = NULL;

return novo;
}

//Descri��o: Insere um novo paciente na tabela
void hash_insere(Hash* h, Paciente* p){
    if(h->qtd == h->max){
        printf("\nHouve um erro no nosso banco de dados."
               "\nNo momento nao e possivel armazenar novos dados.");
    } else {
        if(h->qtd > (h->max * 0.85)) // Ir� verificar se a tabela atingiu a capacidade m�xima de 85% de ocupa��o
            realocar(h); // Caso esteja no limite, a tabela aumentar� de tamanho.

        int i = calcula_hash(h, paciente_sus(p));

        while(h->v[i] != NULL) // Caso a posi��o calculada pelo hash j� esteja ocupada, ir� ocupar a pr�xima livre.
            i = (i+1) % h->max;

        h->v[i] = p;
        h->qtd++;
    }
}

//Descri��o: Ir� carregar o arquivo salvo com os dados dos pacientes
Hash* hash_carrega(void){
    FILE* arqv = fopen("pacientes.txt", "a+t");
    char* nome = (char*) malloc(86*sizeof(char));
    int tel, sus;

    if(arqv == NULL){
        printf("\nFALHA AO ABRIR ARQUIVO\n");
        exit(1);
    }

    if(nome == NULL){
        printf("\nFALHA NA MEMORIA\n");
        exit(1);
    }

    Hash* h = hash_cria();

    while(fscanf(arqv, "\n%*s %[^\n]s", nome) != EOF){
        fscanf(arqv, "\n%*s %d\n%*s %d", &tel, &sus);

        Paciente* p = paciente_cria(nome, tel, sus, 0, 1);
        hash_insere(h, p);
    }

    fclose(arqv);

return h;
}

//Descri��o: Vai buscar os dados do paciente de acordo com o seu n�mero do SUS
Paciente* hash_busca(Hash* h, int sus){
    int i = calcula_hash(h, sus);

    while(h->v[i] != NULL){
        if(paciente_sus(h->v[i]) == sus)
            return h->v[i];
        else
            i = (i + 1) % h->max;
    }

return NULL;
}

//Descri��o: Ir� salvar as informa��es do paciente em um arquivo
void banco_salva(Hash* h){
    FILE* arqv = fopen("pacientes.txt", "wt");
    int i;

    if(arqv == NULL){
        printf("\nFALHA AO ABRIR ARQUIVO\n");
        exit(1);
    }

    for(i = 0; i < h->max; i++){
        if(h->v[i] != NULL){
            if(paciente_salvar(h->v[i]) != 0){
                fprintf(arqv, "Nome: %s"
                              "\nTelefone: %d"
                              "\nSUS: %d\n", paciente_nome(h->v[i]), paciente_telefone(h->v[i]), paciente_sus(h->v[i]));
            }
        }
    }

    fclose(arqv);
}

/*...................................
...........fun��es auxiliares........
...................................*/

//Descri��o: Ir� aumentar o tamanho da tabela.
void realocar(Hash* h){
    Paciente** vetor_ant = h->v;
    int max_ant = h->max;
    int i;

    h->qtd = 0;
    h->max *= 1.947;
    h->v = (Paciente**) malloc(h->max*sizeof(Paciente*));

    if(h->v == NULL){
        printf("\nERRO DE ALOCACAO DE MEMORIA.\n");
        exit(1);
    }

    for(i = 0; i < h->max; i++)
        h->v[i] = NULL;

    for(i = 0; i < max_ant; i++)
        if(vetor_ant[i] != NULL)
            hash_insere(h, vetor_ant[i]);

    free(vetor_ant);
    vetor_ant = NULL;
}

//Descri��o: Ir� determinar o �ndice que o paciente ir� ocupar
int calcula_hash(Hash* h, int x){
return x%h->max;
}
