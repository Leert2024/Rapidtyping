#include <windows.h>
#include <stdio.h>
#include "stdprint.h"
#define COL 100

void set_color(int n){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),n);
}

void gotoxy(int x, int y){
    COORD pos = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

COORD GetConsoleCursorPosition(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD pos = {csbi.dwCursorPosition.X,csbi.dwCursorPosition.Y};
    return pos;
}

void backspace(){
    COORD pos = GetConsoleCursorPosition();
    if(pos.X == 0 && pos.Y>0){
        gotoxy(COL-1,pos.Y-1);
        return;
    }
    printf("\b");
}

void print_char(char ch){
    printf("%c",ch);
    COORD pos = GetConsoleCursorPosition();
    if(pos.X == COL){
        gotoxy(0,pos.Y+1);
        return;
    }
}
