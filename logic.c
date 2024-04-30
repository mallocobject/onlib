#include "logic.h"
#include "terminal.h"
#include "shell.h"
#include <stdio.h>
#include <conio.h> // for _kbhit() and _getch()
#include <stdbool.h>
#include "./onlib/node_list.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "./src/mainmenu.h"

extern Shell *shell;
extern Node *node;

void initialize()
{
    terminal_clearScreen();
    terminal_hideCursor();
    shell = new_shell();
}

void terminate()
{
    free_shell(shell);
    deleteAllNodes(&node);
    terminal_showCursor();
    terminal_reset();
}

// set base shell
void setBaseShell()
{
    setTitle(shell, "Online Library");
    addOption(shell, new_shell_item("Borrow", mainMenu_1));
    addOption(shell, new_shell_item("Return", mainMenu_2));
    addOption(shell, new_shell_item("Search", mainMenu_3));
    addOption(shell, new_shell_item("Modify", mainMenu_4));
    addOption(shell, new_shell_item("Sort", mainMenu_5));
    addOption(shell, new_shell_item("Charge", mainMenu_6));
    addOption(shell, new_shell_item("List", mainMenu_7));
    addOption(shell, new_shell_item("Add", mainMenu_8));
    addOption(shell, new_shell_item("Delete", mainMenu_9));
}

void mainLoop()
{
    bool running = true;
    while (running)
    {
        show(shell);

        char ch = _getch();

        if (ch == -32) // 检测到转义字符
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // 上箭头键
                up(shell);
                break;
            case 80: // 下箭头键
                down(shell);
                break;
            case 75: // 左箭头键
                Shell *temp = back(shell);
                if (temp != shell)
                    shell = temp;
                else
                    running = false;
                break;
            case 77: // 右箭头键
                shell = enter(shell);
                break;
            default:
                break;
            }
        }
        else if (ch == 13) // 回车键
        {
            shell = enter(shell);
        }
        else if (ch == 27) // ESC键
        {
            running = false;
        }
    }
}

// void func_11()
// {
//     char cwd[1024];
//     getcwd(cwd, sizeof(cwd));
//     char path[] = "/plus_tetris.exe";
//     strcat(cwd, path);
//     system(cwd);
//     terminal_hideCursor();
// }
