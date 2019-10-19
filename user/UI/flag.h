#ifndef __FALG_H
#define __FALG_H
#include "main.h"
#include "func.h"
#include "command.h"

#define person 4

extern int main_flag;   //������       0:main_ui   1:user_ui    -1:admin_ui
extern int off_on, number_flag,LockType;  //�˺������Ƿ�ƥ���־  1:on  -1:off
extern int name[4],password[4],history[4][2],history_data[4][3];
extern const int name_password[person][2];
extern int wait_flag,sensor_flag;
//extern int Determine_Cancel_Button_Flag;  //ȷ��ȡ�� 0����   1��ȷ��   -1��ȡ��
 

typedef struct
{
	int Determine_Cancel_Button_Flag;  //ȷ��ȡ�� 0����   1��ȷ��   -1��ȡ��
	int mian_cursor_flag;  //���  0:user   1:admin
	int main_Determine_Cancel_flag;   // 1:ȡ��  0��ȷ��
} UI_main;

typedef struct
{
	int Determine_Cancel_Button_Flag;  //ȷ��ȡ�� 0����   1��ȷ��   -1��ȡ��
	int admin_cursor_flag;    //���  0:����   1:��ʷ
	int admin_Determine_Cancel_flag;
} ADMIN_main;

typedef struct
{
	int Determine_Cancel_Button_Flag;  //ȷ��ȡ�� 0����   1��ȷ��   -1��ȡ��
	int login_cursor_flag;              // 0: username 1:password
	int login_Determine_Cancel_flag;
} login;


extern UI_main Ui_Main;
extern ADMIN_main Admin_Main;
extern login Login;


void ui_main_init(void);
void admin_main_init(void);
void login_init(void);
void Determine_Cancel(int flag);  //ȷ����ȡ��1����ɫ
void Cursor_Position(int flag);
void all_init(void); //ȫ����ʼ��ÿ��һ�����棬�������棬�����Լ�����ó�ʼ��

int judge_password_name(void);   //�ж��û��� ����

void judge_flag(void);     //�жϸ���flag��״̬
























#endif
