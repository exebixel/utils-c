#include <stdio.h>
#include "tui-utils.h"
#include "menu.h"

void test()
{
    printf("Hello word!!\n");
}

void test2()
{
    printf("Teste2\n");
}

int main()
{
    menuAddItem("teste", test);
    menuAddItem("teste2", test2);
    menuCurses();

    return 0;
}
