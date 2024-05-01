#pragma once

#include <stdbool.h>

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

Queue *new_queue();

void free_queue(Queue *self);

void push(Queue *self, void *data);

void *pop(Queue *self);

bool is_empty(Queue *self);
