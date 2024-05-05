#include "participant.h"
#include <string.h>
#include <stdio.h>
#include "node_list.h"

extern Node *node;

Participant *newParticipant(int id, bool isAdmin)
{
    Participant *participant = (Participant *)malloc(sizeof(Participant));
    participant->id = id;
    participant->numbooks = 0;
    participant->books = NULL;
    participant->total = 0;
    participant->isAdmin = isAdmin;
    return participant;
}

void addBook(Participant *participant, char *book)
{
    participant->numbooks++;
    participant->books = (char **)realloc(participant->books, participant->numbooks * sizeof(char *));
    participant->books[participant->numbooks - 1] = (char *)malloc(strlen(book) + 1);
    strcpy(participant->books[participant->numbooks - 1], book);
}

void returnBook(Participant *participant, char *book)
{
    for (int i = 0; i < participant->numbooks; i++)
    {
        if (strcmp(participant->books[i], book) == 0)
        {
            free(participant->books[i]);
            participant->books[i] = NULL;
            for (int j = i; j < participant->numbooks - 1; j++)
            {
                participant->books[j] = participant->books[j + 1];
            }
            participant->numbooks--;
            participant->books = (char **)realloc(participant->books, participant->numbooks * sizeof(char *));
            break;
        }
    }
}

void listBooks(Participant *participant)
{
    for (int i = 0; i < participant->numbooks; i++)
    {
        if (i == 0)
            printf("%s", participant->books[i]);
        else
            printf(" | %s", participant->books[i]);
    }
}

void checkout(Participant *participant)
{
    for (int i = 0; i < participant->numbooks; i++)
    {
        Node *temp = searchNode(node, participant->books[i]);
        if (temp != NULL)
            participant->total += temp->data.price;
        free(participant->books[i]);
        participant->books[i] = NULL;
    }
    printf("Total: %.2f", participant->total);
    free(participant->books);
    participant->books = NULL;
    participant->numbooks = 0;
    participant->total = 0;
}

void deleteParticipant(Participant *participant)
{
    if (participant == NULL)
        return;
    for (int i = 0; i < participant->numbooks; i++)
    {
        free(participant->books[i]);
        participant->books[i] = NULL;
    }
    free(participant->books);
    participant->books = NULL;
    free(participant);
    participant = NULL;
}
