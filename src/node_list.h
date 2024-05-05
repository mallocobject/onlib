#pragma once

#include <stdbool.h>

typedef struct Data
{
    char *name;
    char *category;
    char *author;
    int quantity;
    float price;

} Data;

typedef struct Node
{
    Data data;
    struct Node *next;
} Node;

// 创建节点时传入一个 Data 结构体
Node *createNode(Data data);

// 按关键字搜索节点
Node *searchNode(Node *head, char *name);

// 按图书名删除节点
void deleteNode(Node **head, char *name);

// 删除所有节点
void deleteAllNodes(Node **head);

// 在链表末尾添加一个包含给定 Data 的节点
void appendNode(Node **head, Data data);

// 打印链表
void printList(Node *head);

// 将链表分成两半
void splitList(Node *head, Node **front, Node **back);

// 合并两个已排序的链表
Node *mergeLists(Node *a, Node *b, bool (*cmp)(Node *, Node *));

// 对链表进行归并排序
void mergeSort(Node **headRef, bool (*cmp)(Node *, Node *));