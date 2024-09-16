#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "stdprint.h"
#include "welcome.h"
#include "typing_modes.h"
#define COL 100

char modes[2][10] = {"����ģʽ","����ģʽ"};
char names[6][10] = {"minecraft","hamlet","churchill","roosevelt","peppa","test"};
int lengths[6] = {321,196,328,381,101,300};

//��ӡ�ı�
int load_text(char* name){
    system("cls");
    gotoxy(0,3);
    FILE* fp;
    if((fp = fopen(name,"r"))==NULL){
        printf("�ļ���ʧ�ܣ�\n");
        return 0;
    }else{
        int char_num = 0;
        set_color(0x07);
        char ch;
        //����ַ��ض�ȡ�ļ����ݣ�ÿ��ȡһ���������һ������Ļ
        while((ch=fgetc(fp))!=EOF){
            putchar(ch);
            char_num++;
            if(char_num%COL == 0)printf("\n");
        }
    fclose(fp);
    return char_num;
    }
}

//���ֽ���
void typing(int mode, int name_choice, int char_num){
    char name[20] = "texts/";
    strcat(name,names[name_choice-1]);
    strcat(name,".txt");

    gotoxy(0,0);
    set_color(0x0f);
    printf("��ǰģʽ��%s ��ǰ�ı���%s �ı����ȣ�%d",modes[mode-1],name,lengths[name_choice-1]);
    gotoxy(0,1);
    set_color(0x07);

    FILE* fp;
    if((fp = fopen(name,"r"))==NULL){
        printf("�ļ�%s�޷��򿪣�����%s�Ƿ�����ɾ����\n",name,name);
        system("pause");
        exit(0);
    }else{
        switch(mode){
            case 1:{//����ģʽ
                mode_1(fp,char_num);
                break;
            }
            case 2:{//����ģʽ
                mode_2(fp);
                break;
            }
        }
    }
    fclose(fp);
}

//���ع��
void hide_cursor(){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
}

//������
int main(){
    system("title rapidtype");//�޸Ĵ�������
    hide_cursor();

    print_welcome();//��ʾ��ӭ����
    int mode = choose_mode(2);
    int name_choice = choose_text(6);

    char name[20] = "texts/";
    strcat(name,names[name_choice-1]);
    strcat(name,".txt");

    int char_num;
    if(!(char_num = load_text(name))){
        printf("�ļ�%s�޷��򿪻��ļ�Ϊ�գ�����%s�ĺϷ��ԡ�\n",name,name);
        system("pause");
        exit(0);
    };
    typing(mode,name_choice,char_num);
    set_color(0x07);
    printf("\n�� �� �� �� ��\n");
    system("pause");
    return 0;
}
