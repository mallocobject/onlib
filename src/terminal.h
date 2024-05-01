#pragma once

#include <stdbool.h>

typedef enum
{
	White = 231,
	Black = 0,
	Cyan = 48,
	Blue = 21,
	Orange = 208,
	Yellow = 226,
	Green = 46,
	Purple = 93,
	Red = 196
} terminal_Color;

typedef enum
{
	Reset = 0,
	Bold,
	Dim,
	Italic,
	Underline,
	Blink,
	Invert,
	Hidden
} terminal_Style;

void terminal_setColor(terminal_Color color, bool isForeground);

void terminal_setStyle(terminal_Style style);

void terminal_setColorAndStyle(terminal_Color color, terminal_Style style, bool isForeground);

void terminal_setCursorPosition(int x, int y);

void terminal_hideCursor();

void terminal_showCursor();

void terminal_clearScreen();

void terminal_reset();

void terminal_printChar(const char c);

void terminal_printString(const char *str);