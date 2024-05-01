#include "m_queue.h"
#include <stdlib.h>

Queue *new_queue()
{
    Queue *q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void free_queue(Queue *self)
{
    Node *cur = self->front;
    while (cur != NULL)
    {
        Node *temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(self);
}

void push(Queue *self, void *data)
{
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    if (self->rear == NULL)
    {
        self->front = node;
        self->rear = node;
    }
    else
    {
        self->rear->next = node;
        self->rear = node;
    }
}

void *pop(Queue *self)
{
    if (self->front == NULL)
        return NULL;

    Node *node = self->front;
    void *ret = node->data;
    self->front = node->next;
    if (self->front == NULL)
        self->rear = NULL;
    free(node);
    return ret;
}

bool is_empty(Queue *self)
{
    return self->front == NULL;
}
