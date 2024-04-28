#include "terminal.h"
#include <stdio.h>

static void terminal_setAttribute(const char *attribute, int value)
{
	printf("\033[%s;%dm", attribute, value);
}

void terminal_setColor(terminal_Color color, bool isForeground)
{
	if (color < 0 || color > 255)
	{
		return;
	}
	terminal_setAttribute(isForeground ? "38;5" : "48;5", (int)(color));
}

void terminal_setStyle(terminal_Style style)
{
	if (style < 0 || style > 8)
	{
		return;
	}
	terminal_setAttribute("", (int)(style));
}

void terminal_setColorAndStyle(terminal_Color color, terminal_Style style, bool isForeground)
{
	if (color < 0 || color > 255 || style < 0 || style > 8)
	{
		return;
	}
	printf("\033[%d;5;%dm\033[%dm", isForeground ? 38 : 48, (int)(color), (int)(style));
}

void terminal_setCursorPosition(int x, int y)
{
	printf("\033[%d;%dH", y, x);
}

void terminal_hideCursor()
{
	printf("\033[?25l");
}

void terminal_showCursor()
{
	printf("\033[?25h");
}

void terminal_clearScreen()
{
	printf("\033[H\033[2J");
}

void terminal_reset()
{
	printf("\033[0m");
}

void terminal_printUnicode(const wchar_t lc)
{
	wprintf(L"%lc", lc);
}

void terminal_printUnicodeString(const wchar_t *str)
{
	wprintf(L"%ls", str);
}

void terminal_printChar(const char c)
{
	printf("%c", c);
}

void terminal_printString(const char *str)
{
	printf("%s", str);
}
