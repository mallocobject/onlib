#include "./src/logic.h"
#include <stdio.h>

int main()
{
    initialize();

    setBaseShell();

    mainLoop();

    terminate();
    printf("\nPress \"Enter\" to exit...");
    getchar();
    return 0;
}