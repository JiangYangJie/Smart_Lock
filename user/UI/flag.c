#include "flag.h"
#include "ui.h"
#include "oled.h"

int off_on=0,sensor_flag=0;
int main_flag=0;
int Determine_Cancel_Button_Flag=0,LockType;
int name[4]={0},password[4]={0},history[4][2]={{9999,15},{9999,15},{9999,15},{9999,15}};
int history_data[4][3]={{9999,9999,0},{9999,9999,0},{9999,9999,0},{9999,9999,0}};  //
int number_flag=100;  //记录密码和账号的数字
int last_flag=0;  //记录左右是否调换，调换则number从0开始
const int name_password[person][2] = {{0000,0000},{0000,100},{1234,1234},{1200,1}};
UI_main Ui_Main;
ADMIN_main Admin_Main;
login Login;

void all_init(void)
{
	ui_main_init();
	admin_main_init();
	login_init();
	for(int i=0;i<person;i++)
	{
		name[i]=0;
		password[i]=0;
	}
	number_flag=100;
	last_flag=0;
	LED1_ON;
}

void ui_main_init(void)
{
	Ui_Main.Determine_Cancel_Button_Flag=0;  //确定取消 0：无   1：确定  
	Ui_Main.mian_cursor_flag=100;
	Ui_Main.main_Determine_Cancel_flag=100;
	Determine_Cancel(0);
	Cursor_Position(0);
}
void admin_main_init(void)
{
	Admin_Main.Determine_Cancel_Button_Flag=0;  //确定取消 0：无   1：确定   
	Admin_Main.admin_cursor_flag=100;
	Admin_Main.admin_Determine_Cancel_flag=100;
	Determine_Cancel(0);
	Cursor_Position(0);
}

void login_init(void)
{
	off_on=0;       //无状态  1:on  -1:off
	Login.Determine_Cancel_Button_Flag=0;  //确定取消 0：无   1：确定   -1：取消
	Login.login_cursor_flag=102;
	Login.login_Determine_Cancel_flag=100;
	Determine_Cancel(0);
}


void Determine_Cancel(int flag)  //左右
{ 
	if(main_flag==1)  //登陆页面
	{
		flag%=4;
		
		if(Login.login_cursor_flag%3==0)   //账号
		{
			if(last_flag!=flag)
			{
				last_flag=flag;
				number_flag=name[flag];
			}
			switch(flag)
			{
				case 0:show_name_password(flag,12); break;
				case 1:show_name_password(flag,12); break;
				case 2:show_name_password(flag,12); break;
				case 3:show_name_password(flag,12); break;
			}
				
		}
		else if(Login.login_cursor_flag%3==1)   //  密码
		{
			if(last_flag!=flag+Login.login_cursor_flag%3)
			{
				last_flag=flag+Login.login_cursor_flag%3;
				number_flag=password[flag];
			}
			switch(flag)
			{
				case 0:show_name_password(flag,50); break;
				case 1:show_name_password(flag,50); break;
				case 2:show_name_password(flag,50); break;
				case 3:show_name_password(flag,50); break;
			}
		}
		return;
	}
	if(flag==0)  //确定
	{
		showhanzi32(95,130,14,WHITE,RED);  //确
		showhanzi32(95,100,15,WHITE,RED);  //定
		showhanzi32(95,30,16,WHITE,BLACK);   //取
		showhanzi32(95,0,17,WHITE,BLACK);   //消
	}
	else      //取消
	{
		showhanzi32(95,130,14,WHITE,BLACK);  //确
		showhanzi32(95,100,15,WHITE,BLACK);  //定
		showhanzi32(95,30,16,WHITE,RED);   //取
		showhanzi32(95,0,17,WHITE,RED);   //消
	}
}

void Cursor_Position(int flag)   //上下
{
	if(main_flag==1)
	{
			if(flag==2 )  //在确定一行
			{
				if(Login.login_Determine_Cancel_flag%2==0)  //左右
				{
					showhanzi32(95,130,14,WHITE,RED);  //确
					showhanzi32(95,100,15,WHITE,RED);  //定
					showhanzi32(95,30,16,WHITE,BLACK);   //取
					showhanzi32(95,0,17,WHITE,BLACK);   //消
				}
				else
				{
					showhanzi32(95,130,14,WHITE,BLACK);  //确
					showhanzi32(95,100,15,WHITE,BLACK);  //定
					showhanzi32(95,30,16,WHITE,RED);   //取
					showhanzi32(95,0,17,WHITE,RED);   //消
				}
			}
			else
			{
				showhanzi32(95,130,14,WHITE,BLACK);  //确
				showhanzi32(95,100,15,WHITE,BLACK);  //定
				showhanzi32(95,30,16,WHITE,BLACK);   //取
				showhanzi32(95,0,17,WHITE,BLACK);   //消
			}

		if(flag==0)  //登录界面
		{
			show_name_password(4,50);   //每次换行清0，保证在第一个
			showhanzi32(12,130,5,WHITE,RED);   //帐
			showhanzi32(12,98,6,WHITE,RED);    //号
			show(12,80,10,16,32,WHITE,BLACK,1);        //：
			showhanzi32(50,130,7,WHITE,BLACK);     //密
			showhanzi32(50,98,8,WHITE,BLACK);     //码
		}
		else if(flag==1)
		{
			show_name_password(4,12);   // 换行清理
			showhanzi32(12,130,5,WHITE,BLACK);   //帐
			showhanzi32(12,98,6,WHITE,BLACK);    //号
			showhanzi32(50,130,7,WHITE,RED);     //密
			showhanzi32(50,98,8,WHITE,RED);     //码
		}
		else
		{
			show_name_password(4,50);   // 换行清理
			show_name_password(4,12);   // 换行清理
			showhanzi32(12,130,5,WHITE,BLACK);   //帐
			showhanzi32(12,98,6,WHITE,BLACK);    //号
			showhanzi32(50,130,7,WHITE,BLACK);     //密
			showhanzi32(50,98,8,WHITE,BLACK);     //码
		}
		return;
	}
	if(flag==0)   //光标位置  上面
		{
			showhanzi32(22,10,13,WHITE,BLACK);
			showhanzi32(60,10,13,BLACK,BLACK);
		}
		else      //下面
		{
			showhanzi32(22,10,13,BLACK,BLACK);
			showhanzi32(60,10,13,WHITE,BLACK);
		}

}


int judge_password_name(void)
{
	int i=0,n=0,p=0,j=3,k=0;
	n=name[0]*1000+name[1]*100+name[2]*10+name[3];
	p=password[0]*1000+password[1]*100+password[2]*10+password[3];
	for(;i<person;i++)
	{
			if(n==name_password[i][0] && p==name_password[i][1])
			{
				for(j=3;j>0;j--)  //打开
				{
					for(k=0;k<2;k++)
						{
								history[j][k]=history[j-1][k];
//							OLED_ShowNum_int(0+50*k,j,history[j][k],1);
						}
				}
				history[0][0]=n;
				history[0][1]=14;
				//向云端发送的数据
				for(int a=3;a>0;a--)
				{
					for(int h=0;h<3;h++)
					{
						history_data[a][h]=history_data[a-1][h];
					}
				}
				history_data[0][0]=n;
				history_data[0][1]=p;
				history_data[0][2]=1;
				//qingling
				for(int K=0;K<4;K++)
				{
					name[K]=0;
					password[K]=0;
				}
				return 1;
			}
	}
	for(j=3;j>0;j--)    //没有打开
	{
		for(k=3;k<2;k++)
		{
					history[j][k]=history[j-1][k];
		}
	}
	history[0][0]=n;
	history[0][1]=15;
	
	//向云端发送的数据
	for(int a=3;a>0;a--)
	{
		for(int h=0;h<3;h++)
		{
			history_data[a][h]=history_data[a-1][h];
		}
	}
	history_data[0][0]=n;
	history_data[0][1]=p;
	history_data[0][2]=0;

				
	return 0;
}

void judge_flag(void)
{
	if(main_flag==0)  //主界面
	{
		while(1){
			int mian_cursor_flag=Ui_Main.mian_cursor_flag%2;
			int main_Determine_Cancel_flag=Ui_Main.main_Determine_Cancel_flag%2;
			Cursor_Position(mian_cursor_flag);  //光标
			Determine_Cancel(main_Determine_Cancel_flag);  //底部按钮
			if(Ui_Main.Determine_Cancel_Button_Flag==1 && main_Determine_Cancel_flag==0)  //按下确定键。且按钮在确定位置   主界面取消无任何意义
			{
				if(mian_cursor_flag==0)  //uaser——login
				{
					main_flag=1;
					break;
				}
				else   //admin
				{
					main_flag=-1;
					break;
				}
			}
			if(sensor_flag>1000)  //传感器数据上报
			{
				sensor_hex();
				sensor_flag=0;
			}
			do_command(get_comand());       //下发命令
		}
		return;
	}
	else if(main_flag==1)  //用户登陆界面
	{	int yes_no;
		while(1)
		{
			int login_cursor_flag=Login.login_cursor_flag%3;
			int login_Determine_Cancel_flag=Login.login_Determine_Cancel_flag%2;
			Cursor_Position(login_cursor_flag);  //光标
			Determine_Cancel(Login.login_Determine_Cancel_flag);  //左右按钮
			if(Login.Determine_Cancel_Button_Flag==1 && login_Determine_Cancel_flag==0 && login_cursor_flag==2)  //确定
			{
				LED1_OFF;
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
				yes_no=judge_password_name();   //还没写   2019年10月3日10:19:47  写了 2019年10月13日14:41:54
				
				if(yes_no==1)
				{
					LED6_ON;
					main_flag=0;   //主界面
					LockType=2;
					On_Off(1);
					name_data(history_data);
					break;
				}
				else
				{
					main_flag=0;   //主界面
					On_Off(-1);
					name_data(history_data);
					break;
				}
			}
			else if(Login.Determine_Cancel_Button_Flag==1 && login_Determine_Cancel_flag==1 && login_cursor_flag==2)  //取消
			{
				main_flag=0;  //回到主界面
				break;
			}
			if(sensor_flag>1000)  //传感器数据上报
			{
				
				sensor_hex();
				sensor_flag=0;
			}
			do_command(get_comand());       //下发命令
		}
		return;
	}
	else if(main_flag==-1)  //管理员界面
	{
		while(1)
		{
			int admin_cursor_flag=Admin_Main.admin_cursor_flag%2;
			int admin_Determine_Cancel_flag=Admin_Main.admin_Determine_Cancel_flag%2;
			Cursor_Position(admin_cursor_flag);  //光标
			Determine_Cancel(admin_Determine_Cancel_flag);  //底部按钮
			if(Admin_Main.Determine_Cancel_Button_Flag==1 && admin_Determine_Cancel_flag==0)  //确定
			{
				if(admin_cursor_flag==0)  //查找
				{
					LED1_OFF;
					find_history(1);
					HAL_Delay(5000);
					main_flag=-1;
					break;
				}
				else if(admin_cursor_flag==1)  //历史
				{
					LED1_OFF;
					find_history(2);
					HAL_Delay(5000);
					main_flag=-1;
					break;
				}
			}
			if(Admin_Main.Determine_Cancel_Button_Flag==1 && admin_Determine_Cancel_flag==1)  //取消
			{
				main_flag=0;
				break;
			}
			if(sensor_flag>1000)  //传感器数据上报
			{
				sensor_hex();
				sensor_flag=0;
			}
			do_command(get_comand());   //下发命令
		}
		return;
	}
}























