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
void borrowSection();

// return
void returnSection();

// search
void searchSection();

// modify
void modifySection();

// sort
void sortSection();

bool cmpName(Node *a, Node *b);

bool cmpCategory(Node *a, Node *b);

bool cmpAuthor(Node *a, Node *b);

bool cmpQuantity(Node *a, Node *b);

bool cmpPrice(Node *a, Node *b);

// checkout
void checkoutSection();

// list
void listSection();

// add
void addSection();

// delete
void deleteSection();

// borrowd
void borrowedSection();

// log
void logSection();

// sign up
void signUp();

// sign in
void signIn();