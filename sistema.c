#include <stdlib.h>
#include <stdio.h>
#include "sistema.h"
#define pai(i) (((i)-1)/2)
#define esq(i) (2*(i)+1)
#define dir(i) (2*(i)+2)

//Descrição: Protótipos das funções auxiliares.
void troca(Heap* h, int i, int j);
void sobe(Heap* h, int i);
void desce(Heap* h, int i);

//Descrição: Estrutura da fila de prioridade.
struct heap{
    int qtd; // Quantidade de pacientes atuais.
    int max; // Quantidade máxima de pacientes.
    Paciente** v; // Vetor de ponteiros para o tipo Paciente.
};

//Descrição: Alocará a fila e inicializará os campos dela.
Heap* fila_cria(int max){
    Heap* h = (Heap*) malloc(sizeof(Heap));
    int i;

    if(h == NULL){
        printf("\nERRO DE ALOCACAO DE MEMORIA.\n");
        exit(1);
    }

    h->qtd = 0;
    h->max = max;
    h->v = (Paciente**) malloc(max*sizeof(Paciente*));

    if(h->v == NULL){
        printf("\nERRO DE ALOCACAO DE MEMORIA.\n");
        exit(1);
    }

    for(i = 0; i < max; i++)
        h->v[i] = NULL; // Inicializará com NULL para economizar memória

return h;
}

//Descrição: Irá inserer um Paciente na fila
void fila_insere(Heap* h, Paciente* p){
        h->v[h->qtd++] = p;
        sobe(h, h->qtd-1);
}

//Descrição: Irá dizer se afila está cheia
int fila_cheia(Heap* h){
    if(h->qtd == h->max)
        return 1;
    else
        return 0;
}

//Descrição: Irá retirar o paciente de maior prioridade da fila
void fila_atende(Heap* h){
    if(h->qtd == 0){
        printf("\nA fila de pacientes a serem atendidos esta vazia no momento.");
    } else {
        char* nome = paciente_nome(h->v[0]);

        h->v[0] = h->v[--h->qtd];
        desce(h, 0);

        printf("\nO(A) paciente \" %s \" foi atendido(a)", nome);

        h->v[h->qtd] = NULL;
        nome = NULL;
    }
}

//Descrição: Verificará se a fila está vazia
int fila_vazia(Heap* h){
    if(h->qtd == 0)
        return 1;
    else
        return 0;
}

/*...................................
...........funções auxiliares........
...................................*/

//Descrição: Trocará as posições de duas informações do vetor
void troca(Heap* h, int i, int j){
    Paciente* ant = h->v[i];

    h->v[i] = h->v[j];
    h->v[j] = ant;
}

//Descrição: Certificará que a fila de prioridade mantenha a propriedade
void sobe(Heap* h, int i){
    while(i>0){
        int p = pai(i);

        if(paciente_gravidade(h->v[p]) < paciente_gravidade(h->v[i])){
            troca(h, p, i);
            i = p;
        }
        else
            break;
    }
}

//Descrição: Certificará que a fila de prioridade mantenha a propriedade
void desce(Heap* h, int i){
    int e = esq(i); //Representa o lado esquerdo do pai

    while(e < h->qtd){
        int d = dir(i); //Representa o lado direito do pai

        if(d < h->qtd && paciente_gravidade(h->v[d]) > paciente_gravidade(h->v[e])) //Verificará quais dos filhos é maior, e trocar o valor de "e" caso necessário
                e = d;

        if(paciente_gravidade(h->v[e]) < paciente_gravidade(h->v[i])) //Se for atendida a condição, então a propriedade da fila já está correta
            break;

        troca(h,i,e);
        i = e;
        e = esq(i);
    }
}
