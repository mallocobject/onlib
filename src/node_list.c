#include "node_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Node *createNode(Data data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

Node *searchNode(Node *head, char *name)
{
    Node *cur_node = head;
    while (cur_node != NULL)
    {
        if (strstr(cur_node->data.name, name) != NULL || strstr(cur_node->data.category, name) != NULL || strstr(cur_node->data.author, name) != NULL)
            return cur_node;

        cur_node = cur_node->next;
    }
    return NULL;
}

void deleteNode(Node **head, char *name)
{
    if (*head == NULL)
        return;

    Node *dummy_head = createNode((Data){.name = "", .category = "", .author = "", .quantity = 0, .price = 0.0});

    dummy_head->next = *head;

    Node *temp = searchNode(*head, name);
    while (temp != NULL && strcmp(temp->data.name, name) != 0)
    {
        temp = searchNode(temp->next, name);
    }
    if (temp == NULL)
        printf("\nBook not found.");

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
            free(temp->data.name);
            temp->data.name = NULL;
            free(temp->data.category);
            temp->data.category = NULL;
            free(temp->data.author);
            temp->data.author = NULL;
            free(temp);
            temp = NULL;
        }
        printf("\nSuccessful delete.");
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
        free(temp->data.name);
        temp->data.name = NULL;
        free(temp->data.category);
        temp->data.category = NULL;
        free(temp->data.author);
        temp->data.author = NULL;
        free(temp);
        temp = NULL;
    }
    *head = NULL;
}

void appendNode(Node **head, Data data)
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
    while (cur_node != NULL)
    {
        printf("\nName: %s", cur_node->data.name);
        printf(" | Category: %s", cur_node->data.category);
        printf(" | Author: %s", cur_node->data.author);
        printf(" | Quantity: %d", cur_node->data.quantity);
        printf(" | Price: %.2f", cur_node->data.price);
        cur_node = cur_node->next;
    }
}