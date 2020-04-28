#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tui-utils.h"

// limpa o buffer
// use somente quando o buffer estiver cheio
#define cleanBuffer while(getchar() != '\n')

// limpa a tela
#define cleanScreen system("clear")

char **options;
int cont = 0;
void (**functions)(void);

void menuClear()
{
    cont = 0;
    options = (char**) calloc(cont, sizeof(char*));
    functions = calloc(cont, sizeof(void));
}

void menuAddItem(char *op, void (*func)())
{
    cont++;
    options = (char**) realloc(options, sizeof(char*) * cont);
    if (options == NULL) exit(0);
    options[cont-1] = op;
    functions = realloc(functions, sizeof(void) * cont);
    if (functions == NULL) exit(0);
    (functions[cont-1]) = func;
}

void menu() {
    // opção digiada pelo usuario
    int op;

    // limpa a tela
    // cleanScreen;

    do
    {
        // percorrer e imprimir todas as opções do menu
        for (int i = 0; i < cont; i++)
            printf("%d - %s\n", i+1, options[i]);
        
        // pede que o usuario digite uma opção
        printf("Digite a opção: ");
        scanf("%d", &op);

        cleanBuffer;

        // checa se a opção é valida se não 
        // exibe uma mensagem
        if(op <= 0 || op > cont)
        {
            cleanScreen;
            printf("Digite uma opção valida!!\n\n");
        }

    // não sai ate que seja digitada uma opção valida
    } while (op <= 0 || op > cont);
    
    // executa a função correspondente
    // a opção escolhida pelo usuario
    (functions[op-1])();
}

void menuCurses()
{

    /// inicia o suporte ao ncurses
    initCurses();
    curs_set(0);
    // Define o plano de fundo
#define BG 1
    init_pair(BG, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(BG));

    refresh();
    // cria uma janela com 30 linhas e 60 colunas 
    // e centraliza ela na tela
    WINDOW *winMenu;
    winMenu = createCentralizeWindow(15, 50);
    // cria uma borda na tela
    box(winMenu, ACS_VLINE, ACS_HLINE);

    printwcentralize(winMenu, 1, "MENU PRINCIPAL");

    // pega a entrada do teclado do usuario
    int key;
    // guarda a opção selecionada
    int selectOption = 0;
    while (1)
    {
        // loop para atualizar as opções do usuario
        for (int i = 0; i < cont; i++)
        {
            // checa qual opção esta setada
            if (i == selectOption)
            {
                wattron(winMenu, A_REVERSE);
            }
            // imprime as opções de novo 
            mvwprintw(winMenu, i+3, 3, options[i]);
            wattroff(winMenu, A_REVERSE);
            wrefresh(winMenu);
        }

        // pega a tecla digitada pelo usuario
        key = getch();
        switch (key)
        {
            // caso for seta pra baixo
            case KEY_DOWN:
                // checa se pode descer mais uma opção 
                // se não volta pra cima
                if (selectOption == cont-1)
                {
                    selectOption = 0;
                }
                else
                {
                    selectOption++;
                }            
                break;
            case KEY_UP:
                //  checa se pode subir mais uma opção 
                // se não volta pra baixo
                if (selectOption == 0)
                {
                    selectOption = cont-1;
                }
                else
                {
                    selectOption--;
                }
                break;
            default:
                break;
        }
        // se precionar enter sai do loop do while 
        if (key == ENTER)
        {
            break;
        }
    }

    // Fecha a jenla de menu e o suporte ao ncurses
    delwin(winMenu);
    endwin();

    (functions[selectOption])();
}
