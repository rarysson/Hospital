#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include "bancodd.h"
#include "menu.h"
#define OP1 "Receber paciente"
#define OP2 "Modificar dados do paciente"
#define OP3 "Atender paciente"
#define OP4 "Finalizar atendimento"
#define G1 "AZUL - Atendimento ate 4 horas."
#define G2 "VERDE - Atendimento ate 3 horas."
#define G3 "AMARELO - Atendimento ate 30 minutos."
#define G4 "LARANJA - Atendimento ate 20 minutos."
#define G5 "VERMELHO - Atendimento imediato."
#define M1 "Mudar dados pessoais"
#define M2 "Retirar os dados do banco de dados"

int main(){
    Hash* tabela_pacientes;
    Heap* fila_pacientes;
    char* nome, esc;
    int telefone, sus, gravidade, opcao, salvar_dados, op_aux, interrompido, escolha;
    Paciente* paciente;

    tabela_pacientes = hash_carrega();
    fila_pacientes = fila_cria(15);
    interrompido = 0;

    printf("\n..........Iniciando sistema hospitalar.............\n");

    do{
        apresenta_menu(4, 1, OP1, OP2, OP3, OP4);
        printf("\nOpcao: ");
        opcao = le_opcao(1, 4);

        switch(opcao){
            case 1:
                if(interrompido){
                    printf("\nDesculpe, mas o sistema de atendimento ja foi fechado");
                } else {
                    if(fila_cheia(fila_pacientes)){
                        printf("\nA fila de atendimento no momento esta cheia."
                                "\nPor favor aguarde um momento ate que o proximo paciente seja atendido.");
                    } else {
                            printf("\nDigite o numero do cartao do SUS: ");
                            sus = le_inteiro();

                            printf("\n........Procurando o(a) paciente no banco de dados........\n");
                            paciente = hash_busca(tabela_pacientes, sus);

                            if(paciente == NULL){
                                printf("\nPaciente nao encontrado(a) no banco de dados");
                                printf("\n.......Cadastrando paciente.......\n");

                                printf("\nDigite o nome: ");
                                limpa_buff();
                                nome = le_nome();

                                printf("\nDigite o numero de telefone: ");
                                limpa_buff();
                                telefone = le_inteiro();

                                printf("\nQual o nivel da gravidade?");
                                apresenta_menu(5, 1, G1, G2, G3, G4, G5);
                                printf("\nGravidade: ");
                                limpa_buff();
                                gravidade = le_opcao(1, 5);

                                printf("\nDeseja salvar seus dados no nosso sistema? <S/N>: ");

                                do{
                                    limpa_buff();
                                    scanf("%1s", &esc);
                                    escolha = le_escolha(esc);

                                    if(escolha == -1)
                                        printf("\nDigitacao invalida.\nSo e aceito 's'/'S' ou 'n'/'N'\nDigite sua escolha: ");
                                }while(escolha == -1);

                                if(escolha)
                                    salvar_dados = 1;
                                else
                                    salvar_dados = 0;

                                paciente = paciente_cria(nome, telefone, sus, gravidade, salvar_dados);

                                hash_insere(tabela_pacientes, paciente);
                            } else {
                                printf("\n..........Paciente encontrado...........\n");
                                printf("\nOla %s seja bem-vindo(a) de volta.", paciente_nome(paciente));

                                printf("\nQual o nivel da gravidade?");
                                apresenta_menu(5, 1, G1, G2, G3, G4, G5);
                                printf("\nGravidade: ");
                                gravidade = le_opcao(1, 5);

                                paciente_modifica_gravidade(paciente, gravidade);
                            }

                            fila_insere(fila_pacientes, paciente);
                    }
                }
            break;
            case 2:
                printf("\nDigite o numero do cartao do SUS: ");
                sus = le_inteiro();

                paciente = hash_busca(tabela_pacientes, sus);

                if(paciente == NULL){
                    printf("\nDesculpe, mas voce nao esta presente no nosso banco de dados");
                } else {
                    printf("\nOla %s", paciente_nome(paciente));
                    printf("\nO que voce deseja modificar?");
                    apresenta_menu(2, 1, M1, M2);

                    printf("\nOpcao: ");
                    op_aux = le_opcao(1, 2);

                    if(op_aux == 1){
                        printf("\nDigite o novo nome: ");
                        nome = le_nome();

                        printf("\nDigite o novo telefone: ");
                        telefone = le_inteiro();

                        paciente_modifica_info(paciente, nome, telefone);
                    } else {
                        printf("\nLamentamos se aconteceu algum problema, esperamos que volte ao nosso hospital.");
                        printf("\n..........Retirando os dados do nosso banco de dados.........\n");
                        paciente_modifica_salvar(paciente, 0);
                    }
                }
            break;
            case 3:
                printf("\n.......Atendendo paciente.......\n");

                fila_atende(fila_pacientes);

            break;
            case 4:
                printf("\nDeseja realmente encerrar o atendimento? <S/N>: ");

                do{
                    limpa_buff();
                    scanf("%1s", &esc);
                    escolha = le_escolha(esc);

                    if(escolha == -1)
                        printf("\nDigitacao invalida.\nSo e aceito 's'/'S' ou 'n'/'N'\nDigite sua escolha: ");
                }while(escolha == -1);

                if(escolha){
                   printf("\nFechando sistema hospitalar.........\n");

                   interrompido = 1;

                   if(!fila_vazia(fila_pacientes)){
                        printf("\nAinda falta pacientes a serem atendidos."
                                "\nNao sera aceito novos pacientes, mas sera necessario atender o restante dos pacientes.");
                        opcao = 3;
                   } else {
                        printf("\nObrigado por utilizar o nosso sistema.");
                   }
                } else {
                    printf("\n........O sistema ainda esta em funcionamento........\n");
                    opcao = 3;
                }
            break;
        }

        limpa_buff();
        printf("\nAperte ENTER para continuar.........");
        scanf("%*c");

        limpa_tela();

    } while(opcao != 4);

    printf("\n.........Salvando os dados dos clientes no banco de dados.........\n");

    banco_salva(tabela_pacientes);

    printf("\n.........Pacientes salvos no banco de dados com sucesso............\n");

return 0;
}
