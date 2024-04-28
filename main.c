#include "secondary.h"
#include "menu.h"
#include <stdio.h>

Menu *menu; // only one anywhere

int main()
{
    initialize();

    setBaseMenu();

    mainLoop();

    terminate();
    printf("\nPress \"Enter\" to exit...");
    getchar();
    return 0;
}