#include "command.h"
#include "string.h"
#include "usart.h"
#include "Data_Processing.h"
#include "sht20.h"
#include "flag.h"
#include "bmp180.h"
#include "BH1750FVI.h"


Content contenT;
int wait_flag=0;
//const char number_command[]={'0','1','2','3','4','5','6','7','8','9'};
char *number_command[]={"open\":0","open\":1","open\":2","open\":3","open\":4","open\":5","open\":6","open\":7","open\":8","open\":9"};

/****************************************   ��ģ�鷢atָ����Է��������ж�  *************************************************************/
int mqtt_send(char data[],char *flag){
	HAL_UART_Transmit(&huart3,(uint8_t *)data,strlen(data),0xff);
	//printf("%d:%s\r\n",strlen(data),data);
	HAL_Delay(1000);
	if(UsartType.RX_flag)    	// Receive flag
    {
			//printf("UsartType.RX_pData:%s\r\n",UsartType.RX_pData);
			UsartType.RX_flag=0;	// clean flag
			
			//  find_command((char *)UsartType.RX_pData,"get","yes");                      //Ѱ��ƽ̨�·�����      
			if(strstr((char *)UsartType.RX_pData,flag)){
				memset(&UsartType.RX_pData,0,strlen((char *)UsartType.RX_pData)); //����ַ���
				return 1;
			}
			else{
				memset(&UsartType.RX_pData,0,strlen((char *)UsartType.RX_pData));   //����ַ���
				return 0;
			} 
    }
		return 0;

	
}

/****************************************   ��ԭʼ����ת����16����  *************************************************************/
void sensor_hex(void){
		nb_is_alive();  // ���NBģ���Ƿ�����
		char test1[200],test2[200],data[250];
		SHT20_GetValue(&contenT.temp,&contenT.hum);        //��ȡ�¶�ʪ��
		contenT.beam=bh_data_read();
		BMP_UncompemstatedToTrue();
		contenT.pressure=(float)bmp180.p/100.0;
//	//printf("%.2f",contenT.pressure);
		sprintf(test1,"{\"params\":{\"CurrentHumidity\":%d,\"CurrentTemperature\":%.2f}}"
	,(int)contenT.hum,contenT.temp); //ûת��Ϊ16���Ƶ�����
		strToHex(test1,test2);  //���ݰ�ת16����
		sprintf(data,"%s%d,%s\r\n",nb_mqttput,strlen(test1),test2);	
		send_command(data,"+MQTT",5);
	
	
		sprintf(test1,"{\"params\":{\"LightLux\":%.2f,\"Atmosphere\":%.2f}}"
	,contenT.beam,contenT.pressure); //ûת��Ϊ16���Ƶ�����
		strToHex(test1,test2);  //���ݰ�ת16����
		sprintf(data,"%s%d,%s\r\n",nb_mqttput,strlen(test1),test2);	
		send_command(data,"+MQTT",5);
}

/****************************************   ��ģ�鷢atָ�����onenet  *************************************************************/
int connect_onenet(void){
		LED1_ON;
		mqtt_send(nb_reseet,"OK");
		HAL_Delay(5000);
	
		show(83,110-wait_flag*20,17,20,32,RED,BLACK,3);       //>>
	
		if(send_command(nb_at,"OK",50)==0){return 0;}         //��atָ�50�δ����˳�
		
		wait_flag++;
		show(83,110-wait_flag*20,17,20,32,RED,BLACK,3);       //>>
		
		if(mqtt_send(nb_haeder,"OK")==0){    //����mqtt����
			HAL_Delay(300);
			mqtt_send(nb_haeder,"OK");
		}
		
		wait_flag++;
		show(83,110-wait_flag*20,17,20,32,RED,BLACK,3);       //>>
		
		HAL_Delay(3000);
		if(send_command(nb_net,"1",50)==0) { return 0;}   //û����
		
		wait_flag++;
		show(83,110-wait_flag*20,17,20,32,RED,BLACK,3);       //>>
		
		if(mqtt_send(nb_mqtt_key,"789")==1){  //�鿴mqtt��������
			
			wait_flag++;
			show(83,110-wait_flag*20,17,20,32,RED,BLACK,3);       //>>
			mqtt_send(nb_connect,"OK");      //���Ӱ�����
			return 1;
		}
		else{return 0;}
}

int reconnection(void){ //������
	int time=0;
	if(mqtt_send(nb_mqtt_state,"1")==1 || mqtt_send(nb_mqtt_state,"2")==1){    //1 �ѳ�ʼ��,δ����
			HAL_Delay(500);
			if(mqtt_send(nb_connect,"OK")==1)
				return 1;
			else return 0;
	}
	else if(mqtt_send(nb_mqtt_state,"3")==0 || mqtt_send(nb_mqtt_state,"4")==0){
			HAL_Delay(3000);
		while(mqtt_send(nb_mqtt_state,"5")==0){   //������ʱ���ã�����
			connect_onenet();
			HAL_Delay(500);
			time++;
			if(time>10){
				return 0;          //����ʧ��
			}
		}
		return 1;
	}
	return 0;
}


void find_command(char *raw_data,char *flag,char *find_flag){
		char *p=NULL;
		if(strstr((char *)UsartType.RX_pData,flag)){  //�ж��Ƿ����·�����
			p=strtok((char *)UsartType.RX_pData,",");
			while(p){
				if(strstr(p,find_flag)){
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
					HAL_Delay(500);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
					break;
				}
				else{
					p=strtok(NULL,",");
				}
			}	
		}
}	


int send_command(char data[],char *flag, int times){
	int i=0;  //�����ж�ѭ������
	while(i<times){
		if(mqtt_send(data,flag)==1){return 1;}
		else{i++;}
	}
	return 0;
}

int topic(char *topic_name,int qos,int flag){
		char test[100];
	if(flag==1){
		sprintf(test,"%s%s,%d\r\n",nb_get_topic,topic_name,qos);
	}
	else{
		sprintf(test,"%s%s\r\n",nb_get_topic,topic_name);
	}
	if(send_command(test,"OK",5)==0)
	{return 0;}
	return 1;
}

void name_data(int history[][3])
{
	nb_is_alive();  // ���NBģ���Ƿ�����
	char test1[200],test2[200], data[200];
	sprintf(test1,"{\"params\":{\"name0\":%d,\"password0\":%d,\"door0\":%d,\"door\":%d}}",
	history[0][0],history[0][1],history[0][2],history[0][2]);
	strToHex(test1,test2);  //���ݰ�ת16����
	sprintf(data,"%s%d,%s\r\n",nb_mqttput,strlen(test1),test2);
	send_command(data,"+MQTT",5);
	if(history[0][2]==1)
	{   //DoorOpenNotification
		//sprintf(test3,"%d",history[0][0]);
			sprintf(test1,"{\"params\":{\"KeyID\":\"%d\",\"LockType\":%d}}",
			history[0][0],LockType);
			strToHex(test1,test2);  //���ݰ�ת16����
			sprintf(data,"%s%d,%s\r\n",nb_event,strlen(test1),test2);
			send_command(data,"+MQTT",5);
	
	}
	if(history[1][0]!=9999)
	{
		sprintf(test1,"{\"params\":{\"name1\":%d,\"password1\":%d,\"door1\":%d}}",
		history[1][0],history[1][1],history[1][2]);
		strToHex(test1,test2);  //���ݰ�ת16����
		sprintf(data,"%s%d,%s\r\n",nb_mqttput,strlen(test1),test2);
		send_command(data,"+MQTT",5);
	}
	if(history[2][0]!=9999)
	{
		sprintf(test1,"{\"params\":{\"name2\":%d,\"password2\":%d,\"door2\":%d}}",
		history[2][0],history[2][1],history[2][2]);
		strToHex(test1,test2);  //���ݰ�ת16����
		sprintf(data,"%s%d,%s\r\n",nb_mqttput,strlen(test1),test2);
		send_command(data,"+MQTT",5);
	}
	
	if(history[3][0]!=9999)
	{
		sprintf(test1,"{\"params\":{\"name3\":%d,\"password3\":%d,\"door3\":%d}}",
		history[3][0],history[3][1],history[3][2]);
		strToHex(test1,test2);  //���ݰ�ת16����
		sprintf(data,"%s%d,%s\r\n",nb_mqttput,strlen(test1),test2);
		send_command(data,"+MQTT",5);
	}
}



//+MQTTPUBLISH:0,0,0,0,/sys/a1HWw6lLR9B/nb5310/thing/service/remoteOpen,93,{"method":"thing.service.remoteOpen","id":"1686632933","params":{"open":1},"version":"1.0.0"}
int get_comand(void)
{
	
	if(UsartType.RX_flag)   //�����б�־λ
	{
		if(strstr((char *)UsartType.RX_pData,"remoteOpen")){  //�ж��Ƿ����·�����
			
//			printf("%s\r\n",UsartType.RX_pData);
				char *p=NULL;
				p=strtok((char *)UsartType.RX_pData,",");   //  , �ָ���
				while(p){
//					printf("p:%s\r\n",p);
					
					for(int i=0;i<10;i++)
					{
//						printf("number_command:%s\r\n",number_command[i]);
						if(strstr(p,number_command[i])){
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
							HAL_Delay(500);
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
//							printf("i:%d\r\n",i);
							memset(&UsartType.RX_pData,0,strlen((char *)UsartType.RX_pData));   //����ַ���
							return i;
						}
						}
							p=strtok(NULL,",");     //  �� �����ԣ��ָ�
			}	
			memset(&UsartType.RX_pData,0,strlen((char *)UsartType.RX_pData));   //����ַ���
		}
	}
	return -1;
}

void do_command(int flag)
{
	//if(send_command("AT","OK",5)==0) connect_onenet();  //�޷���ָ�ģ��ʧЧ������ 
	if(flag==-1)  {LED1_ON; return;}
	switch(flag)
	{
		case 0:
		{
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==1)
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
			break;
		}
		case 1:
		{
			LED6_ON;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			break;
		}
		case 2:
		{
			LED2_ON;
			break;
		}
		case 3:
		{
			LED2_OFF;
			break;
		}
		case 4:
		{
			LED3_ON;
			break;
		}
		case 5:
		{
			LED3_OFF;
			break;
		}
		case 6:
		{
			LED4_ON;
			break;
		}
		case 7:
		{
			LED4_OFF;
			break;
		}
		case 8:
		{
			LED5_ON;
			break;
		}
		case 9:
		{
			LED5_OFF;
			break;
		}
		default:
		{
			break;
		}
	}
}

void zhiwen_shuaka(int flag)
{
	LED1_OFF;;
		char test1[100],test2[100],data[200];
		sprintf(test1,"{\"params\":{\"KeyID\":\"%d\",\"LockType\":%d}}",
		history[0][0],flag);
		strToHex(test1,test2);  //���ݰ�ת16����
		sprintf(data,"%s%d,%s\r\n",nb_event,strlen(test1),test2);
		send_command(data,"+MQTT",5);
}


void nb_is_alive(void)
{
	if(send_command(nb_at,"OK",5)==0)    //˵��ģ��������ˣ�������stm32
	{
		__set_FAULTMASK(1);//�ر����ж�
    NVIC_SystemReset();//����Ƭ������
	}
}




	
	
	
	
