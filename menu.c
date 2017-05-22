#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"

//Descrição: Protótipos das funções auxiliares.
int erro_string(char* palavra);
int erro_num(char *numero);
int le_inteiro_menor(void);

//Descrição: Vai definir o buffer de entrada como null para limpar algum lixo que contenha
void limpa_buff(void){
     setbuf(stdin, NULL);
}

//Descrição: Mostrará todas as opções do menu
void apresenta_menu(int n_itens, int menor_opcao, ...){
    va_list menu;
    int i;

    va_start(menu, menor_opcao);

    for(i = 0; i < n_itens; i++)
        printf("\n%d - %s", menor_opcao++, va_arg(menu, char*));

    va_end(menu);
}

//Descrição: Vai somente ler uma string
char* le_string(void){
    char *caracteres = (char*) malloc(86*sizeof(char));

    if(caracteres == NULL){
        printf("\nSem memoria.");
        exit(1);
    }

    limpa_buff();
    fgets(caracteres, 85, stdin);

    if(strlen(caracteres) != 1)
        caracteres[strlen(caracteres)-1] = '\0'; // como o fgets ler o '\n', com isso ele vai eliminar o '\n' da leitura e definir como o final da string

return caracteres;
}

//Descrição: Vai ler uma string e verificar se ela é valida como nome
char* le_nome(void){
    char *nome;

    do{
        free(nome);
        limpa_buff();
        nome = le_string();

        if(erro_string(nome)){
            printf("\nNome invalido, digite novamente: ");
        }
    }while(erro_string(nome));

return nome;
}

//Descrição: Vai ler uma string para validar como um número e depois retornará um inteiro
int le_inteiro(void){
    char *numero;

    do{
        free(numero);
        limpa_buff();
        numero = le_string();

        if(erro_num(numero)){
            printf("\nNumero invalido.\nDigite novamente: ");
        } else if(strlen(numero) != 8){
            printf("\nQuantidade de digitos errada."
                   "\nA quantidade e 8 digitos"
                   "\nDigite novamente: ");
            char a[] = "abc"; // como a quantidade de caracteres é invalida mas a leitura de um número deu certo
            numero = a; // é necessário modificar o valor contido no "numero" para invalidar no laço while logo abaixo
        }
    }while(erro_num(numero));

    int num = atoi(numero);
    free(numero);
    numero = NULL;

return num;
}

//Descrição: Vai ler um inteiro e ver se ele está de acordo com as regras
int le_opcao(int menor, int maior){
    int op;

    do{
        op = le_inteiro_menor();

        if(op < menor || op > maior)
            printf("\nOpcao invalida\nO numero tem que ser entre %d e %d\nDigite novamente: ", menor, maior);
    }while(op < menor || op > maior);

return op;
}

//Descrição: Verifica se a respota foi sim ou não, caso nenhum dos dois, quer dizer que está errado.
int le_escolha(char escolha){
    if(escolha == 's' || escolha == 'S')
        return 1;
    else if(escolha == 'n' || escolha == 'N')
        return 0;
    else
        return -1;
}

//Descrição: Irá "apagar" as informações que estão presentes na tela
void limpa_tela(void){
    system("cls");
}

/*...................................
...........funções auxiliares........
...................................*/

//Descrição: Verifica se possui algum caractere invalido
int erro_string(char* palavra){
    int i;

    for(i = 0; i < strlen(palavra); i++){
        if(!isalpha(palavra[i])){
            if(palavra[i] == ' ')
                continue;
            else
                return 1;
        }
    }

return 0;
}

//Descrição: Irá validar o numero
int erro_num(char* numero){
    int i;

    for(i = 0; i < strlen(numero); i++){
        if(!isdigit(numero[i])){
            if(i == 0 && numero[i] == '-')
                continue;
            else
                return 1;
        }
    }

return 0;
}

//Descrição: Vai ler um inteiro e validar a sua leitura.
int le_inteiro_menor(void){
    char *numero;

    do{
        free(numero);
        limpa_buff();
        numero = le_string();

        if(erro_num(numero)){
            printf("\nNumero invalido.\nDigite novamente: ");
        }
    }while(erro_num(numero));

    int num = atoi(numero);
    free(numero);
    numero = NULL;

return num;
}
