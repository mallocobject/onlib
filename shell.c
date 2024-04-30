#include "shell.h"
#include <stdlib.h>
#include "m_queue.h"
#include "terminal.h"
#include <stdio.h>

void setTitle(Shell *self, char *title)
{
    if (self->title != NULL)
    {
        free(self->title);
        self->title = NULL;
    }
    self->title = malloc(strlen(title) + 1);

    strcpy(self->title, title);
}

void setFunction(Shell *self, void *function)
{
    self->function = function;
}

void setSelected(Shell *self, int selected)
{
    self->selected = selected;
}

int getSelected(Shell *self)
{
    return self->selected;
}

void setCount(Shell *self, int count)
{
    self->count = count;
}

int getCount(Shell *self)
{
    return self->count;
}

void setParent(Shell *self, Shell *parent)
{
    self->parent = parent;
}

Shell *getParent(Shell *self)
{
    return self->parent;
}

Shell *addOption(Shell *self, Shell *item)
{
    int index = getCount(self);
    self->items = realloc(self->items, (index + 1) * sizeof(Shell));
    self->items[index] = item;
    setParent(item, self);
    setCount(self, index + 1);
    return item;
}

void show(Shell *self)
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

void up(Shell *self)
{
    setSelected(self, getSelected(self) - 1);
    if (getSelected(self) < 0)
        setSelected(self, getCount(self) - 1);
    show(self);
}

void down(Shell *self)
{
    setSelected(self, getSelected(self) + 1);
    if (getSelected(self) >= getCount(self))
        setSelected(self, 0);
    show(self);
}

Shell *enter(Shell *self)
{
    Shell *item = self->items[getSelected(self)];
    if (item->function != NULL)
        ((void (*)(Shell *))item->function)(item);
    else
    {
        show(item);
        return item;
    }
    return self;
}

Shell *back(Shell *self)
{
    Shell *parent = getParent(self);
    if (parent != NULL)
    {
        show(parent);
        return parent;
    }
    return self;
}

Shell *new_shell()
{
    Shell *shell = malloc(sizeof(Shell));
    shell->title = NULL;
    shell->function = NULL;
    shell->selected = 0;
    shell->count = 0;
    shell->items = NULL;
    shell->parent = NULL;
    return shell;
}

void free_shell(Shell *self)
{
    Queue *q = new_queue();
    push(q, (void *)self);
    while (!is_empty(q))
    {
        Shell *shell = (Shell *)pop(q);
        for (int i = 0; i < getCount(shell); i++)
        {
            push(q, (void *)shell->items[i]);
        }
        free(shell->items);
        shell->items = NULL;
        free(shell->title);
        shell->title = NULL;
        free(shell);
        shell = NULL;
    }
    free_queue(q);
}

Shell *new_shell_item(char *title_en, void *function)
{
    Shell *shell = new_shell();
    setTitle(shell, title_en);
    setFunction(shell, function);
    return shell;
}
