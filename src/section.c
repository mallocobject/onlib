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
extern bool isAdmin;

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
    if (strcmp(func, "borrowSection") == 0)
        does = "borrowed";
    else if (strcmp(func, "returnSection") == 0)
        does = "returned";
    else if (strcmp(func, "modifySection") == 0)
        does = "modified";
    else if (strcmp(func, "addSection") == 0)
        does = "added";
    else if (strcmp(func, "deleteSection") == 0)
        does = "deleted";
    else if (strcmp(func, "checkoutSection") == 0)
        does = "checked out";
    else if (strcmp(func, "sortSection") == 0)
        does = "sorted";
    else if (strcmp(func, "listSection") == 0)
        does = "listed";
    else if (strcmp(func, "searchSection") == 0)
        does = "searched";
    else
        does = "unknown";

    fprintf(file, "[%s-%s] %s %s \"%s\"\n", __DATE__, __TIME__, who, does, name);
    fclose(file);
}

// // select Admin
// void selectAdmin()
// {
//     if (participant != NULL)
//         deleteParticipant(participant);
//     participant = newParticipant(0, true);
// }

// // select User
// void selectuser()
// {
//     if (participant != NULL)
//         deleteParticipant(participant);
//     participant = newParticipant(0, false);
// }

// borrow
void borrowSection()
{
    char name[100];
    printf("Enter name: ");
    scanf("%s", name);

    Node *temp = searchNode(node, name);
    if (temp == NULL || strcmp(temp->data.name, name) != 0)
        printf("\nBook not found.");
    else if (temp->data.quantity <= 0)
        printf("\nBook out of stock.");
    else
    {
        for (int i = 0; i < participant->numbooks; i++)
        {
            if (strcmp(participant->books[i], name) == 0)
            {
                printf("\nYou have already borrowed this book.");
                getchar();
                block();
                return;
            }
        }

        temp->data.quantity--;
        addBook(participant, name);
        printLog(__func__, name);
        printf("\nSuccessfully borrowed.");
    }

    getchar();
    block();
}

// return
void returnSection()
{
    char name[100];
    printf("Enter name: ");
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
void searchSection()
{
    char word[100];
    printf("Enter keywords: ");
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
void modifySection()
{
    char name[100];
    printf("Enter name: ");
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
void sortSection()
{
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
void checkoutSection()
{
    checkout(participant);
    printLog(__func__, "all");
    block();
}

// list
void listSection()
{
    printList(node);
    printLog(__func__, "all");
    block();
}

// add
void addSection()
{
    Data data;
    char name[100], category[100], author[100];
    int quantity;
    float price;

    printf("Enter name: ");
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
void deleteSection()
{
    char name[100];
    printf("Enter name: ");
    scanf("%s", name);

    getchar();
    deleteNode(&node, name);
    printLog(__func__, name);
    block();
}

// borrowed
void borrowedSection()
{
    listBooks(participant);
    printLog(__func__, "all");
    block();
}

// log
void logSection()
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

// sign up
void signUp()
{
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    FILE *file = fopen("../asset/participant.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char exist_username[100], exist_password[100], exist_role[100];
    while (fscanf(file, "%s %s %s", exist_username, exist_password, exist_role) == 3)
    {
        if (strcmp(exist_username, username) == 0)
        {
            getchar();
            printf("\nUsername already exists.");
            fclose(file);
            block();
            return;
        }
    }
    fclose(file);

    file = fopen("../asset/participant.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s %s %s\n", username, password, isAdmin ? "admin" : "user");
    fclose(file);
    getchar();
    printf("\nSuccessfully signed up.");
    block();
}

// sign in
void signIn()
{
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    FILE *file = fopen("../asset/participant.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char user[100], pass[100], role[100];
    while (fscanf(file, "%s %s %s", user, pass, role) == 3)
    {
        if (strcmp(user, username) == 0 && strcmp(pass, password) == 0)
        {
            if (isAdmin && strcmp(role, "admin") != 0)
            {
                getchar();
                printf("\nInvalid username or password.");
                fclose(file);
                block();
                return;
            }
            else if (!isAdmin && strcmp(role, "user") != 0)
            {
                getchar();
                printf("\nInvalid username or password.");
                fclose(file);
                block();
                return;
            }

            if (participant != NULL)
                deleteParticipant(participant);
            participant = newParticipant(0, strcmp(role, "admin") == 0);
            getchar();
            printf("\nSuccessfully signed in.");
            fclose(file);
            block();
            return;
        }
    }

    getchar();
    printf("\nInvalid username or password.");
    fclose(file);
    block();
}
