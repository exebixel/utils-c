#include <stdio.h>
#include "tui-utils.h"
#include "menu.h"
#include "test.c"

int main()
{
    menuAddItem("teste", test);
    menuAddItem("teste2", test2);
    menuCurses();

    return 0;
}
