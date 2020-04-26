#ifndef TUI_UTILS_H
#define TUI_UTILS_H

#include <ncurses.h>

// define o valor da tecla enter
#define ENTER 10

// Cria uma janela centralizada na tela 
// Recebe como parametro o número de linhas e colunas da janela
WINDOW *createCentralizeWindow(int lines, int columns);

// Imprime um texto centralizado na tela
// Recebe a janela em que deve ser impresso o texto
// A linha em que deve ser impresso 
// e o texto em si
void printwcentralize(WINDOW *window, int line, char *text);

// Cria uma caixa de dialogo 
// com o texto passado por parametro
void messageBox(char *message);

// Inicia o suporte ao ncurses
// a cores e aos defines de teclado
void initCurses();

#endif
