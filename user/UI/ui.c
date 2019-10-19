#include "ui.h"
#include "oled.h"
#include "math.h"



void ui_main(void)
{
		lcd7735_fillrect(0, 0, 128, 160, BLACK);  //清空
		showhanzi32(22,116,0,WHITE,BLACK);
		showhanzi32(22,65,1,WHITE,BLACK);
		showhanzi32(60,130,2,WHITE,BLACK);
		showhanzi32(60,95,3,WHITE,BLACK);
		showhanzi32(60,58,4,WHITE,BLACK);
		
}

void login_main(void)
{
		lcd7735_fillrect(0, 0, 128, 160, BLACK);  //清空
		showhanzi32(12,130,5,WHITE,RED);   //帐
		showhanzi32(12,98,6,WHITE,RED);    //号
		show(12,80,10,16,32,WHITE,BLACK,1);        //：
		showhanzi32(50,130,7,WHITE,BLACK);     //密
		showhanzi32(50,98,8,WHITE,BLACK);     //码
		show(50,80,10,16,32,WHITE,BLACK,1);       //：
		for(int i=1;i<5;i++)
		{
			show(50,80-18*i,11,16,32,WHITE,BLACK,1);
		}
		for(int i=1;i<5;i++)
		{
			show(12,80-18*i,11,16,32,WHITE,BLACK,1);
		}
}

void admin_main(void)
{
		lcd7735_fillrect(0, 0, 128, 160, BLACK);  //清空
		showhanzi32(22,116,20,WHITE,BLACK);     //查
		showhanzi32(22,65,21,WHITE,BLACK);      //找
		showhanzi32(60,116,18,WHITE,BLACK);     //历
		showhanzi32(60,65,19,WHITE,BLACK);    //史 
	
}

void find_history(int flag)   
{
		int a,b;
		lcd7735_fillrect(0, 0, 128, 160, BLACK);  //清空
		lcd7735_rect(5,10,110,150,WHITE);   
		for(int i=0;i<4;i++)
		{
			lcd7735_line(30+i*20,10,30+i*20,150,WHITE);    //横线
		}
		lcd7735_line(5,84,110,84,WHITE);
		show(10,130,10,16,16,WHITE,BLACK,2);       //账
		show(10,114,11,16,16,WHITE,BLACK,2);       //号
	if(flag==1)   //内容填充所有的
	{
		show(10,64,12,16,16,WHITE,BLACK,2);       //账
		show(10,48,13,16,16,WHITE,BLACK,2);       //号
		for(int i=0;i<person;i++)
		{
			for(int j=0;j<4;j++){
				a=name_password[i][0]/pow(10,3-j);
				b=name_password[i][1]/pow(10,3-j);
				show(32+20*i,134-16*j,a%10,16,16,WHITE,BLACK,2);    //账号
				show(32+20*i,68-16*j,b%10,16,16,WHITE,BLACK,2);  	//密码	
			}
		}
	}
	else if(flag==2)    //内容填充历史
	{
		show(10,64,14,16,16,WHITE,BLACK,2);       //kai
		show(10,48,16,16,16,WHITE,BLACK,2);
		show(10,32,15,16,16,WHITE,BLACK,2);       //关
		
		for(int i=0;i<person;i++)
		{
			b=history[i][1];
			show(32+20*i,48,b,16,16,WHITE,BLACK,2);  	//开/关
			for(int j=0;j<4;j++){
				a=history[i][0]/pow(10,3-j);
				show(32+20*i,134-16*j,a%10,16,16,WHITE,BLACK,2);    //账号
			}
		}
	}
}

void ui_welcom(void)
{
	lcd7735_fillrect(0, 0, 128, 160, BLACK);  //清空
	show(20,128,0,20,32,WHITE,BLACK,3);       //欢
	show(20,86,1,20,32,WHITE,BLACK,3);       //迎
	show(20,54,2,20,32,WHITE,BLACK,3);       //使
	show(20,22,3,20,32,WHITE,BLACK,3);       //用
	show(60,124,4,20,32,WHITE,BLACK,3);       //智
	show(60,104,5,20,32,WHITE,BLACK,3);       //能
	show(60,84,6,20,32,WHITE,BLACK,3);       //门
	show(60,64,7,20,32,WHITE,BLACK,3);       //禁
	show(60,44,8,20,32,WHITE,BLACK,3);       //系
	show(60,24,9,20,32,WHITE,BLACK,3);       //统
}

void ui_wait()
{
	lcd7735_fillrect(0, 0, 128, 160, BLACK);  //清空
	show(40,124,10,20,32,WHITE,BLACK,3);       //正
	show(40,104,11,20,32,WHITE,BLACK,3);       //在
	show(40,84,12,20,32,WHITE,BLACK,3);       //连
	show(40,64,13,20,32,WHITE,BLACK,3);       //接
	show(40,44,14,20,32,WHITE,BLACK,3);       //服
	show(40,24,15,20,32,WHITE,BLACK,3);       //务
	show(40,4,16,20,32,WHITE,BLACK,3);       //器
	
	lcd7735_rect(80,25,116,130,WHITE);	
}


void On_Off(int flag)
{
	lcd7735_fillrect(0, 0, 128, 160, BLACK);  //清空
	if(flag>0)  //开
	{
		showhanzi32(48,84,9,YELLOW,BLACK);
		showhanzi32(48,52,10,YELLOW,BLACK);
	}
	else if(flag<0)  //关
	{
		showhanzi32(48,84,11,RED,BLACK);
		showhanzi32(48,52,12,RED,BLACK);
	}
	else
	{}
}

void diaplay(void)
{
	
	if(main_flag==1)
	{
		login_main();
	}
	else if(main_flag==-1)
	{
		admin_main();
	}
	else
	{
		ui_main();
	}
	all_init();   //全部状态初始化
}


void show_name_password(int flag,int location)
{
	int i=0;
	i=number_flag%10;  //显示数字
	for(int i=1;i<5;i++)  //全部清空
	{
		if(location<20)  //用来保存
		{
			show(location,80-18*i,name[i-1],16,32,WHITE,BLACK,1);  //账号
		}
		else
		{
			show(location,80-18*i,password[i-1],16,32,WHITE,BLACK,1);  //密码
		}
	}
	if(flag==0)
	{
		show(location,62,i,16,32,WHITE,BLUE,1);
		
	}
	else if(flag==1)
	{
		show(location,44,i,16,32,WHITE,BLUE,1);
	}
	else if(flag==2)
	{
		show(location,26,i,16,32,WHITE,BLUE,1);
	}
	else if(flag==3)
	{
		show(location,8,i,16,32,WHITE,BLUE,1);
	}
	else if(flag==4)
	{
		return;  //清0，不记录
	}
	
	
	if(location<20)  //用来保存
	{
		name[flag]=i;
	}
	else
	{
		password[flag]=i;
	}
}

void show_error(void)
{
	lcd7735_fillrect(0, 0, 128, 160, BLACK);  //清空
	lcd7735_putstr(20,30,"error",RED,YELLOW);
}








