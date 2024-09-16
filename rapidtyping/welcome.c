#include <stdio.h>
#include <conio.h>
#include "welcome.h"
#include "stdprint.h"
extern char names[6][10];
extern int lengths[6];

void print_welcome(){
    gotoxy(0,0);
    set_color(0x07);
    printf("欢迎来到rapidtyping打字练习软件！\n");
}

void print_text_choice(int choice){
    gotoxy(0,6);
    for(int i=1;i<=6;i++){
        if(i != choice){
            set_color(0x0f);
            printf("%s(%d)",names[i-1],lengths[i-1]);
        }else{
            set_color(0xf0);
            printf("%s(%d)",names[i-1],lengths[i-1]);
            set_color(0x0f);
        }
        printf(" ");
    }
}

int choose_text(int num){
    gotoxy(0,5);
    printf("请选择文本：\n");
    int choice = 1;
    print_text_choice(choice);
    char move = 'a';
    while(move != 's'){
        move = _getch();
        switch(move){
            case 'a':{
                if(choice > 1){choice--;}else{choice = num;}
                break;
            }
            case 'd':{
                if(choice < num){choice++;}else{choice = 1;}
                break;
            }
        }
        print_text_choice(choice);
    }
    return choice;
}

void print_mode_choice(int choice){
    gotoxy(0,3);
    switch(choice){
        case 1:{
            set_color(0xf0);
            printf("仿真模式");
            set_color(0x0f);
            printf(" 快速模式");
            break;
        }
        case 2:{
            set_color(0x0f);
            printf("仿真模式 ");
            set_color(0xf0);
            printf("快速模式");
            set_color(0x0f);
        }
    }
}

int choose_mode(int num){
    gotoxy(0,2);
    printf("请选择模式：\n");
    int choice = 1;
    print_mode_choice(choice);
    char move = 'a';
    while(move != 's'){
        move = _getch();
        switch(move){
            case 'a':{
                if(choice > 1){choice--;}else{choice = num;}
                break;
            }
            case 'd':{
                if(choice < num){choice++;}else{choice = 1;}
                break;
            }
        }
        print_mode_choice(choice);
    }
    return choice;
}
