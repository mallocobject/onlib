#pragma once

#include <stdbool.h>

typedef struct Shell
{
    char *title;          // English title
    void *function;       // function pointer
    int selected;         // which item is selected
    int count;            // how many items
    struct Shell **items; // assets
    struct Shell *parent; // parent shell
} Shell;

void setTitle(Shell *self, char *title_en);

void setFunction(Shell *self, void *function);

void setSelected(Shell *self, int selected);

int getSelected(Shell *self);

void setCount(Shell *self, int count);

int getCount(Shell *self);

void setParent(Shell *self, Shell *parent);

Shell *getParent(Shell *self);

Shell *addOption(Shell *self, Shell *item);

void show(Shell *self);

void up(Shell *self);

void down(Shell *self);

Shell *enter(Shell *self);

Shell *back(Shell *self);

Shell *new_shell();

void free_shell(Shell *self);

Shell *new_shell_item(char *title_en, void *function);
