#include "section.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node_list.h"
#include "participant.h"

Node *node = NULL;
Participant *participant = NULL;

void block()
{
    printf("\nPress \"Enter\" to continue...");
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    };
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
    else
    {
        temp->data.quantity--;
        addBook(participant, name);
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

// sort
void mainMenu_5()
{
    if (participant->isAdmin == false)
    {
        printf("\nYou have no access.");
        block();
        return;
    }
    printList(node);

    // getchar();
    block();
}

// checkout
void mainMenu_6()
{
    checkout(participant);
    block();
}

// list
void mainMenu_7()
{
    printList(node);
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
        appendNode(&node, data);
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
    block();
}

// borrowed
void mainMenu_10()
{
    listBooks(participant);
    block();
}
