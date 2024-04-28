#include "node_list.h"
#include <stdlib.h>
#include <stdio.h>

Node *createNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

Node *searchNode(Node *head, int data)
{
    Node *cur_node = head;
    while (cur_node != NULL)
    {
        if (cur_node->data == data)
        {
            return cur_node;
        }
        cur_node = cur_node->next;
    }
    return NULL;
}

void deleteNode(Node **head, int data)
{
    if (*head == NULL)
        return;

    Node *dummy_head = createNode(0);

    dummy_head->next = *head;
    Node *temp = searchNode(*head, data);

    if (temp != NULL)
    {
        if (temp == *head)
        {
            dummy_head->next = (*head)->next;
            free(temp);
        }
        else
        {
            Node *cur_node = dummy_head;
            while (cur_node->next != temp)
            {
                cur_node = cur_node->next;
            }
            cur_node->next = temp->next;
            free(temp);
        }
    }

    *head = dummy_head->next;
    free(dummy_head);
}

void deleteAllNodes(Node **head)
{
    Node *cur_node = *head;
    while (cur_node != NULL)
    {
        Node *temp = cur_node;
        cur_node = cur_node->next;
        free(temp);
    }
    *head = NULL;
}

void appendNode(Node **head, int data)
{
    if (*head == NULL)
    {
        *head = createNode(data);
        return;
    }
    Node *cur_node = *head;
    while (cur_node->next != NULL)
    {
        cur_node = cur_node->next;
    }
    cur_node->next = createNode(data);
}

void printList(Node *head)
{
    Node *cur_node = head;
    printf("\n");
    while (cur_node != NULL)
    {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
}
