#include <stdlib.h>
#include <stdio.h>
#include "sistema.h"
#define pai(i) (((i)-1)/2)
#define esq(i) (2*(i)+1)
#define dir(i) (2*(i)+2)

//Descri��o: Prot�tipos das fun��es auxiliares.
void troca(Heap* h, int i, int j);
void sobe(Heap* h, int i);
void desce(Heap* h, int i);

//Descri��o: Estrutura da fila de prioridade.
struct heap{
    int qtd; // Quantidade de pacientes atuais.
    int max; // Quantidade m�xima de pacientes.
    Paciente** v; // Vetor de ponteiros para o tipo Paciente.
};

//Descri��o: Alocar� a fila e inicializar� os campos dela.
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
        h->v[i] = NULL; // Inicializar� com NULL para economizar mem�ria

return h;
}

//Descri��o: Ir� inserer um Paciente na fila
void fila_insere(Heap* h, Paciente* p){
        h->v[h->qtd++] = p;
        sobe(h, h->qtd-1);
}

//Descri��o: Ir� dizer se afila est� cheia
int fila_cheia(Heap* h){
    if(h->qtd == h->max)
        return 1;
    else
        return 0;
}

//Descri��o: Ir� retirar o paciente de maior prioridade da fila
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

//Descri��o: Verificar� se a fila est� vazia
int fila_vazia(Heap* h){
    if(h->qtd == 0)
        return 1;
    else
        return 0;
}

/*...................................
...........fun��es auxiliares........
...................................*/

//Descri��o: Trocar� as posi��es de duas informa��es do vetor
void troca(Heap* h, int i, int j){
    Paciente* ant = h->v[i];

    h->v[i] = h->v[j];
    h->v[j] = ant;
}

//Descri��o: Certificar� que a fila de prioridade mantenha a propriedade
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

//Descri��o: Certificar� que a fila de prioridade mantenha a propriedade
void desce(Heap* h, int i){
    int e = esq(i); //Representa o lado esquerdo do pai

    while(e < h->qtd){
        int d = dir(i); //Representa o lado direito do pai

        if(d < h->qtd && paciente_gravidade(h->v[d]) > paciente_gravidade(h->v[e])) //Verificar� quais dos filhos � maior, e trocar o valor de "e" caso necess�rio
                e = d;

        if(paciente_gravidade(h->v[e]) < paciente_gravidade(h->v[i])) //Se for atendida a condi��o, ent�o a propriedade da fila j� est� correta
            break;

        troca(h,i,e);
        i = e;
        e = esq(i);
    }
}
