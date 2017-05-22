#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void apresenta_menu(int n_itens, int menor_opcao, ...);
char* le_nome(void);
int le_inteiro(void);
void limpa_buff(void);
int le_opcao(int menor, int maior);
void limpa_tela(void);
int le_escolha(char escolha);

#endif // MENU_H_INCLUDED
