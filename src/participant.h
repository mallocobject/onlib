#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct Participant
{
    int id;
    int numbooks;
    char **books;
    float total;
    bool isAdmin;
} Participant;

Participant *newParticipant(int id, bool isAdmin);

void addBook(Participant *participant, char *book);

void returnBook(Participant *participant, char *book);

void listBooks(Participant *participant);

void checkout(Participant *participant);

void deleteParticipant(Participant *participant);
