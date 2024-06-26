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

    Shell *admin = addOption(shell, new_shell_item("Admin", NULL));
    Shell *admin_si = addOption(admin, new_shell_item("Sign In", signIn));
    Shell *admin_sp = addOption(admin, new_shell_item("Sign Up", signUp));

    Shell *user = addOption(shell, new_shell_item("User", NULL));
    Shell *user_si = addOption(user, new_shell_item("Sign In", signIn));
    Shell *user_sp = addOption(user, new_shell_item("Sign Up", signUp));

    Shell *shell_arr[] = {admin_si, admin_sp, user_si, user_sp};

    for (int i = 0; i < sizeof(shell_arr) / sizeof(shell_arr[0]); i++)
    {
        if (i <= 1)
        {
            addOption(shell_arr[i], new_shell_item("Add", addSection));
            addOption(shell_arr[i], new_shell_item("Delete", deleteSection));
            addOption(shell_arr[i], new_shell_item("Modify", modifySection));
            addOption(shell_arr[i], new_shell_item("Log", logSection));

            Shell *sort = addOption(shell_arr[i], new_shell_item("Sort", NULL));

            addOption(sort, new_shell_item("Name", sortSection));
            addOption(sort, new_shell_item("Category", sortSection));
            addOption(sort, new_shell_item("Author", sortSection));
            addOption(sort, new_shell_item("Quantity", sortSection));
            addOption(sort, new_shell_item("Price", sortSection));
        }

        addOption(shell_arr[i], new_shell_item("Borrow", borrowSection));
        addOption(shell_arr[i], new_shell_item("Return", returnSection));
        addOption(shell_arr[i], new_shell_item("Search", searchSection));
        addOption(shell_arr[i], new_shell_item("List", listSection));
        addOption(shell_arr[i], new_shell_item("Borrowed", borrowedSection));
        addOption(shell_arr[i], new_shell_item("Checkout", checkoutSection));
    }
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
    char name[1024], category[1024], author[1024];
    int quantity;
    float price;
    while (fscanf(file, " %1023[^|]|%1023[^|]|%1023[^|]|%d|%f\n", name, category, author, &quantity, &price) == 5)
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
        fprintf(file, "%s|%s|%s|%d|%.2f\n", cur_node->data.name, cur_node->data.category, cur_node->data.author, cur_node->data.quantity, cur_node->data.price);
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
