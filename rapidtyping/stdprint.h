#include <windows.h>
#ifndef STDPRINT_H_INCLUDED
#define STDPRINT_H_INCLUDED

void set_color(int n);
void gotoxy(int x, int y);
COORD GetConsoleCursorPosition();
void backspace();
void print_char(char ch);

#endif // STDPRINT_H_INCLUDED
