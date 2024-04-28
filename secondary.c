#include "secondary.h"
#include "terminal.h"
#include "menu.h"
#include <stdio.h>
#include <conio.h> // for _kbhit() and _getch()
#include <stdbool.h>
#include "node_list.h"
#include <wchar.h>
#include <locale.h>

extern Menu *menu;

void initialize()
{
    setlocale(LC_ALL, "");
    terminal_clearScreen();
    terminal_hideCursor();
    menu = new_menu();
}

void terminate()
{
    free_menu(menu);
    terminal_showCursor();
    terminal_reset();
}

void setBaseMenu()
{
    setTitle(menu, "Main Menu");
    addItem(menu, new_menu_item("Item 1", func1));
    Menu *m2 = addItem(menu, new_menu_item("Item 2", NULL));
    addItem(m2, new_menu_item("Item 2.1", func2));

    addItem(menu, new_menu_item("Item 3", func3));
}

void mainLoop()
{
    bool running = true;
    while (running)
    {
        show(menu);

        char ch = _getch();

        if (ch == -32) // 检测到转义字符
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // 上箭头键
                up(menu);
                break;
            case 80: // 下箭头键
                down(menu);
                break;
            default:
                break;
            }
        }
        else
        {
            switch (ch)
            {
            case 13: // Enter键
                menu = enter(menu);
                break;
            case 27: // Escape键
                Menu *temp = back(menu);
                if (temp != menu)
                    menu = temp;
                else
                    running = false;
                break;
            default:
                break;
            }
        }
    }
}

void block()
{
    printf("\nPress \"Enter\" to continue...");
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void func1()
{
    printf("\nFunction 1 called");
    block();
}

void func2()
{
    printf("\nFunction 2 called");
    block();
}

void func3()
{
    Node *node = NULL;
    appendNode(&node, 1);
    appendNode(&node, 2);
    appendNode(&node, 3);
    appendNode(&node, 4);
    appendNode(&node, 5);
    printList(node);
    deleteAllNodes(&node);
    block();
}
