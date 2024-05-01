#pragma once

#include <stdbool.h>
#include "node_list.h"

void block();

void printLog(const char *func, char *name);

// select Admin
void selectAdmin();

// select user
void selectuser();

// borrow
void mainMenu_1();

// return
void mainMenu_2();

// search
void mainMenu_3();

// search
void mainMenu_4();

// sort
void mainMenu_5();

bool cmpName(Node *a, Node *b);

bool cmpCategory(Node *a, Node *b);

bool cmpAuthor(Node *a, Node *b);

bool cmpQuantity(Node *a, Node *b);

bool cmpPrice(Node *a, Node *b);

// checkout
void mainMenu_6();

// list
void mainMenu_7();

// add
void mainMenu_8();

// delete
void mainMenu_9();

// borrowd
void mainMenu_10();

// log
void mainMenu_11();

// sign up
void signUp();

// sign in
void signIn();