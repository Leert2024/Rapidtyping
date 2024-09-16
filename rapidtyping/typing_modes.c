#include <stdio.h>
#include <time.h>
#include "stdprint.h"
#include "typing_modes.h"
DWORD start_time;

void init_speed(){
    gotoxy(40,1);
    set_color(0x0f);
    printf("��ǰ�����ٶȣ�--");
}

void show_speed(typed_num){
    float speed;
    DWORD time = GetTickCount();
    if(time-start_time<10000)return;
    speed = (float)typed_num/(time-start_time)*1000*60;
    COORD pos = GetConsoleCursorPosition();
    gotoxy(54,1);
    set_color(0x0f);
    printf("%.2f �ַ�/����",speed);
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

    init_speed(0);//��ʼ���ٶ���ʾ��

    gotoxy(0,1);
    set_color(0x0f);
    printf("���������ʼ����");
    _getch();
    gotoxy(0,1);
    set_color(0x07);
    printf("                ");

    start_time = GetTickCount();
    show_speed();//��ʼ��ʱ
    gotoxy(0,3);

    while((ch=fgetc(fp))!=EOF){
        char next = input();

        if(next == '\b'){//�û����»��˼�
            if(!typed_num){//��ֹ�ܾ��û�һ�����ͻ���
                fseek(fp,-1L,SEEK_CUR);
                continue;
            }
            typed_num--;
            fseek(fp,-2L,SEEK_CUR);
            ch=fgetc(fp);
            fseek(fp,-1L,SEEK_CUR);
            set_color(0x07);//Ĭ����ɫ
            //putchar('\b');
            //putchar(ch);
            //putchar('\b');
            backspace();
            print_char(ch);
            backspace();

        }else if(next != ch){//�������������
            typed_num++;
            set_color(0xc0);//��ӡ��ɫ����Ϊ��ɫ
            //putchar(ch);
            print_char(ch);
            error_num++;
            while(error_num > 0){//����ͣ���ڡ��д��׶Σ�ֱ��error_numΪ0
                char next = input();
                if(next=='\b'){//�û����»��˼�
                    error_num--;
                    fseek(fp,-1L,SEEK_CUR);
                    ch=fgetc(fp);
                    fseek(fp,-1L,SEEK_CUR);
                    set_color(0x07);//Ĭ����ɫ
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
                    printf("���ȸ���ǰ��Ĵ����ټ�����ϰ��");
                    set_color(0x07);
                    gotoxy(pos.X,pos.Y);
                    continue;
                }

                if(typed_num >= char_num)continue;
                ch=fgetc(fp);

                if(next==ch){
                    set_color(0xe0);//��ɫ
                }else{
                    set_color(0xc0);//��ɫ
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

        }else{//������ȷ
            typed_num++;
            show_speed(typed_num);//�����ٶ���ʾ
            set_color(0xa0);//��ɫ
            //putchar(ch);
            print_char(ch);
        }
    }
}

void mode_2(FILE* fp){
    char ch;
    int typed_num = 0;

    init_speed();//��ʼ���ٶ���ʾ��

    gotoxy(0,1);
    set_color(0x0f);
    printf("���������ʼ����");
    _getch();
    gotoxy(0,1);
    set_color(0x07);
    printf("                ");

    start_time = GetTickCount();
    show_speed(0);//��ʼ��ʱ
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
        set_color(0xa0);//��ɫ
        //putchar(ch);
        print_char(ch);
        show_speed(typed_num);
    }
}
