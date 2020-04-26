#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tui-utils.h"

void initCurses()
{
    // Inicia a lib ncurses
    initscr();
    // Abilita o uso dos defines do teclado, por exemplo a referencia da tecla F1 por KEY_F1
    keypad(stdscr, TRUE);
    // Inicia suporte a cores
    start_color();

    refresh();
}

WINDOW *createCentralizeWindow(int lines, int columns)
{
    int windowSizeColum = COLS;
    int windowSizeLine = LINES; 

    // if para limitar tamanho maxino da janela ao tamanho do terminal
    if (lines > windowSizeLine)
    {
        lines = windowSizeLine;
    }
    if (columns > windowSizeColum)
    {
        columns = windowSizeColum;
    }    

    // calculo para centralizar janela 
    windowSizeColum/=2;
    windowSizeLine/=2;
    windowSizeColum -= columns/2;
    windowSizeLine -= lines/2;

    // criação da janela
    WINDOW *window;
    window = newwin(lines, // número de linhas da janela
                    columns, // número de colunas 
                    windowSizeLine, // linha que inicia a janela
                    windowSizeColum); // coluna que inicia a janela

    return window;
}

void printwcentralize(WINDOW *window, int line, char *text)
{
    int maxColumns = getmaxx(window);
    int column;
    // pega o tamanho do texto a ser "imprimido"
    int sizeText = strlen(text);
    // calcula a coluna inicial do texto (onde ele começa)
    column = (maxColumns/2)-(sizeText/2);
    // imprime na tela
    mvwprintw(window, line, column, text);
}

void messageBox(char *message)
{
    int num = strlen(message);
    WINDOW *winbox;
    // cria uma janela centralizada
    winbox = createCentralizeWindow(5, num + 5);
    // cria uma linha ao redor da janela
    box(winbox, ACS_VLINE, ACS_HLINE);
    printwcentralize(winbox, 1, message);

    // cria um "botão de OK"
    wattron(winbox, A_REVERSE);
    printwcentralize(winbox, 3, "| OK |");
    wattroff(winbox, A_REVERSE);

    // atualiza a janela, sem isso não mostra a janela
    wrefresh(winbox);

    // não fecha a janela até o usuario digitar enter
    int key;
    do
    {
        key = getch();
    } while (key != ENTER);
    
    // deleta a janela
    delwin(winbox);

}
