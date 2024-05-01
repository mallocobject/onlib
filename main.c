#include "./src/logic.h"
#include "./src/shell.h"
#include <stdio.h>

Shell *shell; // only one anywhere

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