#ifndef __FALG_H
#define __FALG_H
#include "main.h"
#include "func.h"
#include "command.h"

#define person 4

extern int main_flag;   //主界面       0:main_ui   1:user_ui    -1:admin_ui
extern int off_on, number_flag,LockType;  //账号密码是否匹配标志  1:on  -1:off
extern int name[4],password[4],history[4][2],history_data[4][3];
extern const int name_password[person][2];
extern int wait_flag,sensor_flag;
//extern int Determine_Cancel_Button_Flag;  //确定取消 0：无   1：确定   -1：取消
 

typedef struct
{
	int Determine_Cancel_Button_Flag;  //确定取消 0：无   1：确定   -1：取消
	int mian_cursor_flag;  //光标  0:user   1:admin
	int main_Determine_Cancel_flag;   // 1:取消  0：确定
} UI_main;

typedef struct
{
	int Determine_Cancel_Button_Flag;  //确定取消 0：无   1：确定   -1：取消
	int admin_cursor_flag;    //光标  0:查找   1:历史
	int admin_Determine_Cancel_flag;
} ADMIN_main;

typedef struct
{
	int Determine_Cancel_Button_Flag;  //确定取消 0：无   1：确定   -1：取消
	int login_cursor_flag;              // 0: username 1:password
	int login_Determine_Cancel_flag;
} login;


extern UI_main Ui_Main;
extern ADMIN_main Admin_Main;
extern login Login;


void ui_main_init(void);
void admin_main_init(void);
void login_init(void);
void Determine_Cancel(int flag);  //确定或取消1的颜色
void Cursor_Position(int flag);
void all_init(void); //全部初始，每打开一个界面，其他界面，包括自己都因该初始化

int judge_password_name(void);   //判断用户名 密码

void judge_flag(void);     //判断各个flag的状态
























#endif
