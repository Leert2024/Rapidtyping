#include <stdio.h>
#include <time.h>
#include "stdprint.h"
#include "typing_modes.h"
DWORD start_time;

void init_speed(){
    gotoxy(40,1);
    set_color(0x0f);
    printf("当前打字速度：--");
}

void show_speed(typed_num){
    float speed;
    DWORD time = GetTickCount();
    if(time-start_time<10000)return;
    speed = (float)typed_num/(time-start_time)*1000*60;
    COORD pos = GetConsoleCursorPosition();
    gotoxy(54,1);
    set_color(0x0f);
    printf("%.2f 字符/分钟",speed);
    gotoxy(pos.X,pos.Y);
}

char input(){
    char ch = _getch();
    if(ch == '#')exit(0);
    return ch;
}

void mode_1(FILE* fp,int char_num){
    char ch;
    int error_num = 0;
    int typed_num = 0;

    init_speed(0);//初始化速度显示栏

    gotoxy(0,1);
    set_color(0x0f);
    printf("按任意键开始……");
    _getch();
    gotoxy(0,1);
    set_color(0x07);
    printf("                ");

    start_time = GetTickCount();
    show_speed();//开始计时
    gotoxy(0,3);

    while((ch=fgetc(fp))!=EOF){
        char next = input();

        if(next == '\b'){//用户按下回退键
            if(!typed_num){//防止杠精用户一上来就回退
                fseek(fp,-1L,SEEK_CUR);
                continue;
            }
            typed_num--;
            fseek(fp,-2L,SEEK_CUR);
            ch=fgetc(fp);
            fseek(fp,-1L,SEEK_CUR);
            set_color(0x07);//默认颜色
            //putchar('\b');
            //putchar(ch);
            //putchar('\b');
            backspace();
            print_char(ch);
            backspace();

        }else if(next != ch){//当出现输入错误
            typed_num++;
            set_color(0xc0);//打印颜色设置为红色
            //putchar(ch);
            print_char(ch);
            error_num++;
            while(error_num > 0){//程序停留在“有错”阶段，直至error_num为0
                char next = input();
                if(next=='\b'){//用户按下回退键
                    error_num--;
                    fseek(fp,-1L,SEEK_CUR);
                    ch=fgetc(fp);
                    fseek(fp,-1L,SEEK_CUR);
                    set_color(0x07);//默认颜色
                    //putchar('\b');
                    //putchar(ch);
                    //putchar('\b');
                    backspace();
                    print_char(ch);
                    backspace();
                    typed_num--;
                    continue;
                }

                if(error_num >= 10){
                    COORD pos = GetConsoleCursorPosition();
                    gotoxy(0,1);
                    set_color(0x0c);
                    printf("请先改正前面的错误再继续练习！");
                    set_color(0x07);
                    gotoxy(pos.X,pos.Y);
                    continue;
                }

                if(typed_num >= char_num)continue;
                ch=fgetc(fp);

                if(next==ch){
                    set_color(0xe0);//黄色
                }else{
                    set_color(0xc0);//红色
                }
                //putchar(ch);
                print_char(ch);
                error_num++;
                typed_num++;
            }
            COORD pos = GetConsoleCursorPosition();
            gotoxy(0,1);
            set_color(0x07);
            printf("                              ");
            gotoxy(pos.X,pos.Y);

        }else{//输入正确
            typed_num++;
            show_speed(typed_num);//更新速度显示
            set_color(0xa0);//绿色
            //putchar(ch);
            print_char(ch);
        }
    }
}

void mode_2(FILE* fp){
    char ch;
    int typed_num = 0;

    init_speed();//初始化速度显示栏

    gotoxy(0,1);
    set_color(0x0f);
    printf("按任意键开始……");
    _getch();
    gotoxy(0,1);
    set_color(0x07);
    printf("                ");

    start_time = GetTickCount();
    show_speed(0);//开始计时
    gotoxy(0,3);

    while((ch=fgetc(fp))!=EOF){
        while(input()!=ch){
            set_color(0xc0);
            //putchar(ch);
            print_char(ch);
            //printf("\b");
            backspace();
        }
        typed_num++;
        set_color(0xa0);//绿色
        //putchar(ch);
        print_char(ch);
        show_speed(typed_num);
    }
}
