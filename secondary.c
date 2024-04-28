#include "secondary.h"
#include "terminal.h"
#include "menu.h"
#include <stdio.h>
#include <conio.h> // for _kbhit() and _getch()
#include <stdbool.h>
#include "node_list.h"
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

extern Menu *menu;
Node *node = NULL;

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
    deleteAllNodes(&node);
    terminal_showCursor();
    terminal_reset();
}

void setBaseMenu()
{
    setTitle(menu, "Main Menu");
    Menu *m0 = addItem(menu, new_menu_item("basic function", NULL));
    addItem(m0, new_menu_item("add", func_01));
    addItem(m0, new_menu_item("delete", func_02));
    addItem(m0, new_menu_item("modify", func_03));
    addItem(m0, new_menu_item("search", func_04));
    addItem(m0, new_menu_item("print", func_05));

    Menu *m1 = addItem(menu, new_menu_item("game function", NULL));
    addItem(m1, new_menu_item("tetris", func_11));
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

void func_01()
{
    int data;
    printf("\nEnter data: ");
    scanf("%d", &data);
    getchar();
    appendNode(&node, data);
    block();
}

void func_02()
{
    int data;
    printf("\nEnter data: ");
    scanf("%d", &data);
    getchar();
    deleteNode(&node, data);
    block();
}

void func_03()
{
    int data;
    printf("\nEnter data: ");
    scanf("%d", &data);
    getchar();
    Node *temp = searchNode(node, data);
    if (temp != NULL)
    {
        printf("\nEnter new data: ");
        scanf("%d", &temp->data);
        getchar();
    }
    else
        printf("\nData not found.");
    block();
}

void func_04()
{
    int data;
    printf("\nEnter data: ");
    scanf("%d", &data);
    getchar();
    Node *temp = searchNode(node, data);
    if (temp != NULL)
        printf("\nData found: %d", temp->data);
    else
        printf("\nData not found.");
    block();
}

void func_05()
{
    printList(node);
    block();
}

void func_11()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    wchar_t wcwd[1024];
    mbstowcs(wcwd, cwd, sizeof(wcwd) / sizeof(wchar_t));
    wchar_t wpath[] = L"/plus_tetris.exe";
    wcscat(wcwd, wpath);
    _wsystem(wcwd);
    terminal_hideCursor();
}
