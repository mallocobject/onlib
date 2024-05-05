#pragma once

#include <stdbool.h>
#include <stdlib.h>

// 定义参与者结构体
typedef struct Participant
{
    int id;       // 参与者ID
    int numbooks; // 参与者借阅的书籍数量
    char **books; // 参与者借阅的书籍列表
    float total;  // 参与者借阅书籍的总价
    bool isAdmin; // 参与者是否为管理员
} Participant;

// 创建新的参与者
Participant *newParticipant(int id, bool isAdmin);

// 参与者添加书籍
void addBook(Participant *participant, char *book);

// 参与者归还书籍
void returnBook(Participant *participant, char *book);

// 列出参与者借阅的所有书籍
void listBooks(Participant *participant);

// 参与者结账
void checkout(Participant *participant);

// 删除参与者
void deleteParticipant(Participant *participant);