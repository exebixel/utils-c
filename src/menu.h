#ifndef MENU_H
#define MENU_H

// Limpa as opç~oes do menu
void menuClear();

// mostra o menu criado
void menu();

// adiciona uma opção ao menu
void menuAddItem(char *op, void (*func)());

void menuCurses();

#endif
