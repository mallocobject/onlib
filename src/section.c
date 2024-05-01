#include "section.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node_list.h"
#include "participant.h"
#include "logic.h"
#include "shell.h"

Node *node = NULL;
Participant *participant = NULL;
extern Shell *shell;

void block()
{
    printf("\nPress \"Enter\" to continue...");
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    };
}

void printLog(const char *func, char *name)
{
    FILE *file = fopen("../asset/log.log", "a");
    if (file == NULL)
    {
        printf("\nError opening file.");
        return;
    }
    char *who = participant->isAdmin ? "Admin" : "User";
    char *does = NULL;
    if (strcmp(func, "mainMenu_1") == 0)
        does = "borrowed";
    else if (strcmp(func, "mainMenu_2") == 0)
        does = "returned";
    else if (strcmp(func, "mainMenu_4") == 0)
        does = "modified";
    else if (strcmp(func, "mainMenu_8") == 0)
        does = "added";
    else if (strcmp(func, "mainMenu_9") == 0)
        does = "deleted";
    else if (strcmp(func, "mainMenu_6") == 0)
        does = "checked out";
    else if (strcmp(func, "mainMenu_10") == 0)
        does = "viewed borrowed books";
    else if (strcmp(func, "mainMenu_5") == 0)
        does = "sorted";
    else if (strcmp(func, "mainMenu_7") == 0)
        does = "listed";
    else if (strcmp(func, "mainMenu_3") == 0)
        does = "searched";
    else
        does = "unknown";

    fprintf(file, "[%s-%s] %s %s \"%s\"\n", __DATE__, __TIME__, who, does, name);
    fclose(file);
}

// select Admin
void selectAdmin()
{
    if (participant != NULL)
        deleteParticipant(participant);
    participant = newParticipant(0, true);
}

// select User
void selectuser()
{
    if (participant != NULL)
        deleteParticipant(participant);
    participant = newParticipant(0, false);
}

// borrow
void mainMenu_1()
{
    char name[100];
    printf("\nEnter name: ");
    scanf("%s", name);

    Node *temp = searchNode(node, name);
    if (temp == NULL || strcmp(temp->data.name, name) != 0)
        printf("\nBook not found.");
    else if (temp->data.quantity <= 0)
        printf("\nBook out of stock.");
    else
    {
        temp->data.quantity--;
        addBook(participant, name);
        printLog(__func__, name);
        printf("\nSuccessfully borrowed.");
    }

    getchar();
    block();
}

// return
void mainMenu_2()
{
    char name[100];
    printf("\nEnter name: ");
    scanf("%s", name);

    Node *temp = searchNode(node, name);
    if (temp == NULL || strcmp(temp->data.name, name) != 0)
        printf("\nBook not found.");
    else
    {
        temp->data.quantity++;
        returnBook(participant, name);
        printLog(__func__, name);
        printf("\nSuccessfully returned.");
    }

    getchar();
    block();
}

// search
void mainMenu_3()
{
    char word[100];
    printf("\nEnter keywords: ");
    scanf("%s", word);
    Node *cur_node = node;
    while (cur_node != NULL)
    {
        if (strstr(cur_node->data.name, word) != NULL || strstr(cur_node->data.category, word) != NULL || strstr(cur_node->data.author, word) != NULL)
        {
            printf("\nName: %s", cur_node->data.name);
            printf(" | Category: %s", cur_node->data.category);
            printf(" | Author: %s", cur_node->data.author);
            printf(" | Quantity: %d", cur_node->data.quantity);
            printf(" | Price: %.2f", cur_node->data.price);
        }
        cur_node = cur_node->next;
    }
    printLog(__func__, word);

    getchar();
    block();
}

// modify
void mainMenu_4()
{
    if (participant->isAdmin == false)
    {
        printf("\nYou have no access.");
        block();
        return;
    }
    char name[100];
    printf("\nEnter name: ");
    scanf("%s", name);

    Node *temp = searchNode(node, name);
    if (temp == NULL || strcmp(temp->data.name, name) != 0)
        printf("\nBook not found.");

    else if (strcmp(temp->data.name, name) == 0)
    {
        printf("\nEnter new name: ");
        scanf("%s", name);
        int len = strlen(name);
        temp->data.name = (char *)malloc(len + 1);
        strcpy(temp->data.name, name);

        printf("Enter new category: ");
        scanf("%s", name);
        len = strlen(name);
        temp->data.category = (char *)malloc(len + 1);
        strcpy(temp->data.category, name);

        printf("Enter new author: ");
        scanf("%s", name);
        len = strlen(name);
        temp->data.author = (char *)malloc(len + 1);
        strcpy(temp->data.author, name);

        printf("Enter new quantity: ");
        scanf("%d", &temp->data.quantity);

        printf("Enter new price: ");
        scanf("%f", &temp->data.price);

        printLog(__func__, name);

        char *book = participant->books[0];
        for (int i = 0; i < participant->numbooks; i++)
        {
            if (strcmp(participant->books[i], name) == 0)
            {
                participant->books[i] = realloc(participant->books[i], strlen(name) + 1);
                strcpy(participant->books[i], name);
            }
        }
    }
    else
        printf("\nBook not found.");

    getchar();
    block();
}

bool cmpName(Node *a, Node *b)
{
    return strcmp(a->data.name, b->data.name) <= 0;
}

bool cmpCategory(Node *a, Node *b)
{
    return strcmp(a->data.category, b->data.category) <= 0;
}

bool cmpAuthor(Node *a, Node *b)
{
    return strcmp(a->data.author, b->data.author) <= 0;
}

bool cmpQuantity(Node *a, Node *b)
{
    return a->data.quantity <= b->data.quantity;
}

bool cmpPrice(Node *a, Node *b)
{
    return a->data.price <= b->data.price;
}

// sort
void mainMenu_5()
{
    if (participant->isAdmin == false)
    {
        printf("\nYou have no access.");
        block();
        return;
    }

    bool (*cmp)(Node *, Node *);

    if (shell->selected == 0)
        cmp = cmpName;
    else if (shell->selected == 1)
        cmp = cmpCategory;
    else if (shell->selected == 2)
        cmp = cmpAuthor;
    else if (shell->selected == 3)
        cmp = cmpQuantity;
    else if (shell->selected == 4)
        cmp = cmpPrice;

    mergeSort(&node, cmp);

    printLog(__func__, "all");

    printf("\nSuccessfully sorted.");

    // getchar();
    block();
}

// checkout
void mainMenu_6()
{
    checkout(participant);
    printLog(__func__, "all");
    block();
}

// list
void mainMenu_7()
{
    printList(node);
    printLog(__func__, "all");
    block();
}

// add
void mainMenu_8()
{
    if (participant->isAdmin == false)
    {
        printf("\nYou have no access.");
        block();
        return;
    }
    Data data;
    char name[100], category[100], author[100];
    int quantity;
    float price;

    printf("\nEnter name: ");
    scanf("%s", name);
    int len = strlen(name);
    data.name = (char *)malloc(len + 1);
    strcpy(data.name, name);

    printf("Enter category: ");
    scanf("%s", category);
    len = strlen(category);
    data.category = (char *)malloc(len + 1);
    strcpy(data.category, category);

    printf("Enter author: ");
    scanf("%s", author);
    len = strlen(author);
    data.author = (char *)malloc(len + 1);
    strcpy(data.author, author);

    printf("Enter quantity: ");
    scanf("%d", &quantity);
    data.quantity = quantity;

    printf("Enter price: ");
    scanf("%f", &price);
    data.price = price;

    getchar();
    Node *temp = searchNode(node, name);
    while (temp != NULL && strcmp(temp->data.name, name) != 0)
    {
        temp = searchNode(temp->next, name);
    }

    if (temp != NULL)
        printf("\nBook already exists.");
    else
    {
        printLog(__func__, name);
        appendNode(&node, data);
    }

    block();
}

// delete
void mainMenu_9()
{
    if (participant->isAdmin == false)
    {
        printf("\nYou have no access.");
        block();
        return;
    }
    char name[100];
    printf("\nEnter name: ");
    scanf("%s", name);

    getchar();
    deleteNode(&node, name);
    printLog(__func__, name);
    block();
}

// borrowed
void mainMenu_10()
{
    listBooks(participant);
    printLog(__func__, "all");
    block();
}

// log
void mainMenu_11()
{
    FILE *file = fopen("../asset/log.log", "r");
    if (file == NULL)
    {
        printf("\nError opening file.");
        return;
    }
    char ch;
    printf("\n");
    while ((ch = fgetc(file)) != EOF)
        printf("%c", ch);
    fclose(file);
    block();
}
