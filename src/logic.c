#include "logic.h"
#include "terminal.h"
#include "shell.h"
#include <stdio.h>
#include <conio.h> // for _kbhit() and _getch()
#include <stdbool.h>
#include "node_list.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "section.h"
#include "participant.h"

Shell *shell;
extern Node *node;
extern Participant *participant;

void initialize()
{
    terminal_clearScreen();
    terminal_hideCursor();
    shell = new_shell();
    import();
}

void terminate()
{
    free_shell(shell);
    export();
    deleteAllNodes(&node);
    deleteParticipant(participant);
    terminal_showCursor();
    terminal_reset();
}

// set base shell
void setBaseShell()
{
    setTitle(shell, "Online Library");
    Shell *admin = addOption(shell, new_shell_item("Admin", selectAdmin));
    Shell *user = addOption(shell, new_shell_item("user", selectuser));

    addOption(admin, new_shell_item("Add", mainMenu_8));
    addOption(admin, new_shell_item("Delete", mainMenu_9));
    addOption(admin, new_shell_item("Modify", mainMenu_4));
    addOption(admin, new_shell_item("Search", mainMenu_3));
    addOption(admin, new_shell_item("List", mainMenu_7));
    addOption(admin, new_shell_item("Sort", mainMenu_5));
    addOption(admin, new_shell_item("Borrow", mainMenu_1));
    addOption(admin, new_shell_item("Return", mainMenu_2));
    addOption(admin, new_shell_item("Borrowed", mainMenu_10));
    addOption(admin, new_shell_item("Checkout", mainMenu_6));

    addOption(user, new_shell_item("Borrow", mainMenu_1));
    addOption(user, new_shell_item("Return", mainMenu_2));
    addOption(user, new_shell_item("Search", mainMenu_3));
    addOption(user, new_shell_item("Borrowed", mainMenu_10));
    addOption(user, new_shell_item("Checkout", mainMenu_6));
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

// import
void import()
{
    FILE *file = fopen("../asset/data.txt", "r");
    if (file == NULL)
    {
        printf("\nError opening file.");
        return;
    }
    char name[100], category[100], author[100];
    int quantity;
    float price;
    while (fscanf(file, "%s | %s | %s | %d | %f\n", name, category, author, &quantity, &price) != EOF)
    {
        Data data;
        int len = strlen(name);
        data.name = (char *)malloc(len + 1);
        strcpy(data.name, name);

        len = strlen(category);
        data.category = (char *)malloc(len + 1);
        strcpy(data.category, category);

        len = strlen(author);
        data.author = (char *)malloc(len + 1);
        strcpy(data.author, author);

        data.quantity = quantity;
        data.price = price;

        appendNode(&node, data);
    }
    fclose(file);
}

// export
void export()
{
    FILE *file = fopen("../asset/data.txt", "w");
    if (file == NULL)
    {
        printf("\nError opening file.");
        return;
    }
    Node *cur_node = node;
    while (cur_node != NULL)
    {
        fprintf(file, "%s | %s | %s | %d | %.2f\n", cur_node->data.name, cur_node->data.category, cur_node->data.author, cur_node->data.quantity, cur_node->data.price);
        cur_node = cur_node->next;
    }
    fclose(file);
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
