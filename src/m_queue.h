#pragma once

#include <stdbool.h>

// 定义节点结构体
typedef struct Node
{
    void *data;        // 节点数据
    struct Node *next; // 下一个节点
} Node;

// 定义队列结构体
typedef struct Queue
{
    Node *front; // 队列前端
    Node *rear;  // 队列后端
} Queue;

// 创建新的队列
Queue *new_queue();

// 释放队列
void free_queue(Queue *self);

// 向队列中添加数据
void push(Queue *self, void *data);

// 从队列中取出数据
void *pop(Queue *self);

// 检查队列是否为空
bool is_empty(Queue *self);