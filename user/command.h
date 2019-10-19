#ifndef __COMMAND_H
#define __COMMAND_H


#define nb_at "AT\r\n"   //AT
#define nb_reseet "AT+NRB\r\n"   //软复位
#define nb_haeder "AT+MQTTCFG=\"a1HWw6lLR9B.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,\"JiangYangJie|securemode=3,signmethod=hmacsha1,timestamp=789|\",120,\"nb5310&a1HWw6lLR9B\",\"7ad766779cb68e318c7bbc36d2f8570fc0f367c4\",1\r\n"    //onenet用户接入点
#define nb_mqtt_key "AT+MQTTCFG?\r\n"
#define nb_connect "AT+MQTTOPEN=1,1,0,0,0,\"\",\"\"\r\n"           //连接aliyun
#define nb_mqttput "AT+MQTTPUB=\"/sys/a1HWw6lLR9B/nb5310/thing/event/property/post\",1,0,0,"             //mqtt跟新数据流的header
#define nb_event "AT+MQTTPUB=\"/sys/a1HWw6lLR9B/nb5310/thing/event/DoorOpenNotification/post\",1,0,0,"   //时间上报
/*	0 未初始化
	1 已初始化
	2 已断开
	3 发送 Connect 包
	4 正在重连服务器
	5 已连接
	6 socket 连接服务器中
*/
/*
*      a1HWw6lLR9B/nb5310/user/get   订阅
*      订阅之后服务器会发送消息并以get开头 以，分割
*/
#define nb_mqtt_state "AT+MQTTSTAT?\r\n"               //mqtt状态  
#define nb_get_topic "AT+MQTTSUB="   //mqtt订阅主题   topic-主题 qos- 订阅的消息交付质量等级，0-2
#define nb_cancel_topic "AT+MQTTUNSUB="             //取消订阅
#define nb_disconnect "AT+MQTTDISC\r\n"            //主动断开连接
#define nb_ack "AT+MQTTPING\r\n"                 //该命令设置运行心跳包 ACK 显示，当未检测到服务器 ACK 时会引起重连  
#define nb_csq "AT+CSQ\r\n"                   //信号质量
#define nb_imei "AT+CGSN=1\r\n"              //查询IMEI编号
#define nb_net "AT+CGATT?\r\n"               // 查询是否zhu网

#define LED1_ON HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
#define LED1_OFF HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);

#define LED2_ON HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
#define LED2_OFF HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);

#define LED3_ON HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
#define LED3_OFF HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);

#define LED4_ON HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
#define LED4_OFF HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);

#define LED5_ON HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
#define LED5_OFF HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);

#define LED6_ON HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
#define LED6_OFF HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);


typedef struct {
	float temp;
	float hum;
	float pressure;   //压强
	float beam;   //光照
} Content;

extern Content contenT;

extern float temperature;
extern float humidity;

/********************************* 函数  ****************************************/
int mqtt_send( char data[],char *flag);

/****************************  将数据转换成16进制    ********************************/
void sensor_hex(void);
/****************************  连接onenet    ********************************/
int connect_onenet(void);
/****************************  重连    ********************************/
int reconnection(void);
/****************************  找下发命令    ********************************/
void find_command(char *raw_data,char *flag,char *find_flag);
/******************************* 发送规定次数的命令 ************************************/
int send_command(char data[],char *flag, int times);
/*******************订阅或取消订阅*****************************/
int topic(char *topic_name,int qos,int flag);      //falg=1订阅  flag=0取消订阅  qos消息质量0或1


int get_comand(void);
void do_command(int flag);

void name_data(int history[][3]);

void zhiwen_shuaka(int flag);

void nb_is_alive(void);
#endif

