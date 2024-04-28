#include "menu.h"
#include <stdlib.h>
#include "m_queue.h"
#include "terminal.h"
#include <stdio.h>

void setTitle(Menu *self, char *title)
{
    self->title = title;
}

void setFunction(Menu *self, void *function)
{
    self->function = function;
}

void setSelected(Menu *self, int selected)
{
    self->selected = selected;
}

int getSelected(Menu *self)
{
    return self->selected;
}

void setCount(Menu *self, int count)
{
    self->count = count;
}

int getCount(Menu *self)
{
    return self->count;
}

void setParent(Menu *self, Menu *parent)
{
    self->parent = parent;
}

Menu *getParent(Menu *self)
{
    return self->parent;
}

Menu *addItem(Menu *self, Menu *item)
{
    int index = getCount(self);
    self->items = realloc(self->items, (index + 1) * sizeof(Menu));
    self->items[index] = item;
    setParent(item, self);
    setCount(self, index + 1);
    return item;
}

void show(Menu *self)
{
    if (self == NULL)
        return;
    terminal_clearScreen();
    terminal_setCursorPosition(1, 1);
    terminal_setColorAndStyle(Blue, Underline, true);
    terminal_printString(self->title);
    terminal_reset();
    for (int i = 0; i < getCount(self); i++)
    {
        terminal_setCursorPosition(1, i + 2);
        if (i == getSelected(self))
        {
            terminal_setColorAndStyle(Green, Bold, true);
            terminal_printString("> ");
            terminal_printString(self->items[i]->title);
        }
        else
        {
            terminal_printString("  ");
            terminal_setColor(White, true);
            terminal_printString(self->items[i]->title);
        }
        terminal_reset();
    }
}

void up(Menu *self)
{
    setSelected(self, getSelected(self) - 1);
    if (getSelected(self) < 0)
        setSelected(self, getCount(self) - 1);
    show(self);
}

void down(Menu *self)
{
    setSelected(self, getSelected(self) + 1);
    if (getSelected(self) >= getCount(self))
        setSelected(self, 0);
    show(self);
}

Menu *enter(Menu *self)
{
    Menu *item = self->items[getSelected(self)];
    if (item->function != NULL)
        ((void (*)(Menu *))item->function)(item);
    else
    {
        show(item);
        return item;
    }
    return self;
}

Menu *back(Menu *self)
{
    Menu *parent = getParent(self);
    if (parent != NULL)
    {
        show(parent);
        return parent;
    }
    return self;
}

Menu *new_menu()
{
    Menu *menu = malloc(sizeof(Menu));
    menu->title = NULL;
    menu->function = NULL;
    menu->selected = 0;
    menu->count = 0;
    menu->items = NULL;
    menu->parent = NULL;
    return menu;
}

void free_menu(Menu *self)
{
    Queue *q = new_queue();
    push(q, (void *)self);
    while (!is_empty(q))
    {
        Menu *menu = (Menu *)pop(q);
        for (int i = 0; i < getCount(menu); i++)
        {
            push(q, (void *)menu->items[i]);
        }
        free(menu->items);
        free(menu);
    }
    free_queue(q);
}

Menu *new_menu_item(char *title_en, void *function)
{
    Menu *menu = new_menu();
    setTitle(menu, title_en);
    setFunction(menu, function);
    return menu;
}
