#pragma once

#include <wchar.h>
#include <stdbool.h>

typedef struct Menu
{
    char *title;         // English title
    void *function;      // function pointer
    int selected;        // which item is selected
    int count;           // how many items
    struct Menu **items; // assets
    struct Menu *parent; // parent menu
} Menu;

void setTitle(Menu *self, char *title_en);

void setFunction(Menu *self, void *function);

void setSelected(Menu *self, int selected);

int getSelected(Menu *self);

void setCount(Menu *self, int count);

int getCount(Menu *self);

void setParent(Menu *self, Menu *parent);

Menu *getParent(Menu *self);

Menu *addItem(Menu *self, Menu *item);

void show(Menu *self);

void up(Menu *self);

void down(Menu *self);

Menu *enter(Menu *self);

Menu *back(Menu *self);

Menu *new_menu();

void free_menu(Menu *self);

Menu *new_menu_item(char *title_en, void *function);
