#pragma once

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

Node *createNode(Data data); // 创建节点时传入一个 Data 结构体

Node *searchNode(Node *head, char *name); // 按关键字搜索节点

void deleteNode(Node **head, char *name); // 按图书名删除节点

void deleteAllNodes(Node **head); // 删除所有节点

void appendNode(Node **head, Data data); // 在链表末尾添加一个包含给定 Data 的节点

void printList(Node *head); // 打印链表
