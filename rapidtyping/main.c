#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "stdprint.h"
#include "welcome.h"
#include "typing_modes.h"
#define COL 100

char modes[2][10] = {"仿真模式","快速模式"};
char names[6][10] = {"minecraft","hamlet","churchill","roosevelt","peppa","test"};
int lengths[6] = {321,196,328,381,101,300};

//打印文本
int load_text(char* name){
    system("cls");
    gotoxy(0,3);
    FILE* fp;
    if((fp = fopen(name,"r"))==NULL){
        printf("文件打开失败！\n");
        return 0;
    }else{
        int char_num = 0;
        set_color(0x07);
        char ch;
        //逐个字符地读取文件内容，每读取一个，即输出一个到屏幕
        while((ch=fgetc(fp))!=EOF){
            putchar(ch);
            char_num++;
            if(char_num%COL == 0)printf("\n");
        }
    fclose(fp);
    return char_num;
    }
}

//打字界面
void typing(int mode, int name_choice, int char_num){
    char name[20] = "texts/";
    strcat(name,names[name_choice-1]);
    strcat(name,".txt");

    gotoxy(0,0);
    set_color(0x0f);
    printf("当前模式：%s 当前文本：%s 文本长度：%d",modes[mode-1],name,lengths[name_choice-1]);
    gotoxy(0,1);
    set_color(0x07);

    FILE* fp;
    if((fp = fopen(name,"r"))==NULL){
        printf("文件%s无法打开！请检查%s是否被意外删除。\n",name,name);
        system("pause");
        exit(0);
    }else{
        switch(mode){
            case 1:{//仿真模式
                mode_1(fp,char_num);
                break;
            }
            case 2:{//快速模式
                mode_2(fp);
                break;
            }
        }
    }
    fclose(fp);
}

//隐藏光标
void hide_cursor(){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
}

//主函数
int main(){
    system("title rapidtype");//修改窗口名称
    hide_cursor();

    print_welcome();//显示欢迎界面
    int mode = choose_mode(2);
    int name_choice = choose_text(6);

    char name[20] = "texts/";
    strcat(name,names[name_choice-1]);
    strcat(name,".txt");

    int char_num;
    if(!(char_num = load_text(name))){
        printf("文件%s无法打开或文件为空，请检查%s的合法性。\n",name,name);
        system("pause");
        exit(0);
    };
    typing(mode,name_choice,char_num);
    set_color(0x07);
    printf("\n你 成 功 了 ！\n");
    system("pause");
    return 0;
}
