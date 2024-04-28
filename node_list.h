#pragma once

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data);

void deleteNode(Node **head, int data);

void deleteAllNodes(Node **head);

void appendNode(Node **head, int data);

void printList(Node *head);
