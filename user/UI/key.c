#include "key.h"
#include "string.h"


int key_scan(void)
{
	if(shang==0) return 0;
	if(zhong==0) return 1;
	if(zuo==0) return 2;
	if(xia==0) return 3;
	if(you==0) return 4;
	if(shushang==0) return 5;
	if(shuxia==0) return 6;
	if(shuaka==0) return 7;
	if(zhiwen==0) return 8;
	if(close==0) return 9;
	return -1;
}


void key_do(int flag)
{
	if(flag==-1) return;
	if(flag==0)  //ÉÏ¼ü
	{
		if(main_flag==0)  {Ui_Main.mian_cursor_flag++;     }
		else if(main_flag==1)   {Login.login_cursor_flag++;          }
		else if(main_flag==-1)   {Admin_Main.admin_cursor_flag++;          }
		return;
	}
	if(flag==1)  //ÖÐ¼ü
	{
		if(main_flag==0)  {Ui_Main.Determine_Cancel_Button_Flag=1;}
		else if(main_flag==1)   {if(Login.login_cursor_flag%3==2)  Login.Determine_Cancel_Button_Flag=1;}
		else if(main_flag==-1)   {Admin_Main.Determine_Cancel_Button_Flag=1;}
		return;
	}
	if(flag==2)  //×ó¼ü
	{
		if(main_flag==0)  {Ui_Main.main_Determine_Cancel_flag++;     }
		else if(main_flag==1)   {Login.login_Determine_Cancel_flag++;  }  //Login.login_Determine_Cancel_flag%=2;
		else if(main_flag==-1)   {Admin_Main.admin_Determine_Cancel_flag++;         }
		return;
	}
	if(flag==3)  //ÏÂ¼ü
	{
		if(main_flag==0)  {Ui_Main.mian_cursor_flag--;    Ui_Main.mian_cursor_flag=ABS(Ui_Main.mian_cursor_flag); }
		else if(main_flag==1)   {Login.login_cursor_flag--;     Login.login_cursor_flag=ABS(Login.login_cursor_flag);      }
		else if(main_flag==-1)   {Admin_Main.admin_cursor_flag--;     Admin_Main.admin_cursor_flag=ABS(Admin_Main.admin_cursor_flag);      }
		return;
	}
	if(flag==4)  //ÓÒ¼ü
	{
	//	if(Ui_Main.main_Determine_Cancel_flag>1000 || Login.login_Determine_Cancel_flag>1000 || Admin_Main.admin_Determine_Cancel_flag>1000)
		
		if(main_flag==0)  {Ui_Main.main_Determine_Cancel_flag--;  Ui_Main.main_Determine_Cancel_flag=ABS(Ui_Main.main_Determine_Cancel_flag);   }
		else if(main_flag==1)   {Login.login_Determine_Cancel_flag--;    Login.login_Determine_Cancel_flag=ABS(Login.login_Determine_Cancel_flag); if(Login.login_Determine_Cancel_flag>300) Login.login_Determine_Cancel_flag=100;}  //Login.login_Determine_Cancel_flag%=2;
		else if(main_flag==-1)   {Admin_Main.admin_Determine_Cancel_flag--;     Admin_Main.admin_Determine_Cancel_flag=ABS(Admin_Main.admin_Determine_Cancel_flag);    }
		return;
	}
	if(flag==5)  //Êý×ÖÉÏ¼ü
	{
		number_flag++;
		return;
	}
	if(flag==6)  //Êý×ÖÏÂ¼ü
	{
		number_flag--;
		number_flag=ABS(number_flag);
		return;
	}
	if(flag==7)  //Ë¢¿¨¼ü   3
	{
		zhiwen_shuaka(3);
		return;
	}
	if(flag==8)  //Ö¸ÎÆ¼ü  1
	{
		zhiwen_shuaka(1);
		return;
	}
	if(flag==9)  //close 
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==1)
		{
			LED1_OFF;
			char data[100];
			char test1[]="{\"params\":{\"door\":0}}";
			sprintf(data,"%s%d,%s\r\n",nb_mqttput,0,test1);
			send_command(data,"+MQTT",5);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			LED6_OFF;
		}
		return;
	}
	return;
}

