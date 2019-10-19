
#include "gpio_iic.h"

#include "BH1750FVI.h"

void BH1750_start(void){
	Single_Write_BH1750(0x01);
}

void Single_Write_BH1750(uchar REG_Address)
{
   iic_start();                  //��ʼ�ź�
   iic_sendbyte(BHAddWrite);   //�����豸��ַ+д�ź�
   iic_sendbyte(REG_Address);    //�ڲ��Ĵ�����ַ��
  //  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
   iic_stop();                   //����ֹͣ�ź�
		bh_data_send(BHPowOn);   
		bh_data_send(BHReset);
		bh_data_send(BHModeL); //ѡ����Ƿֱ�����4lx������ʱ����16ms��
}


void bh_data_send(uint8_t command)
{
    do{
		iic_start();                      //iic��ʼ�ź�
    iic_sendbyte(BHAddWrite);       //����������ַ
    }
		while(iic_wait_ack());           //�ȴ��ӻ�Ӧ��
    iic_sendbyte(command);          //����ָ��
    iic_wait_ack();                   //�ȴ��ӻ�Ӧ��
    iic_stop();                       //iicֹͣ�ź�
}

uint16_t bh_data_read(void)
{
	uint16_t buf;
	iic_start();                       //iic��ʼ�ź�
	iic_sendbyte(BHAddRead);         //����������ַ+����־λ
	iic_wait_ack();                     //�ȴ��ӻ�Ӧ��
	buf=iic_readbyte(1);              //��ȡ����
	buf=buf<<8;                        //��ȡ������߰�λ����
	buf+=0x00ff&iic_readbyte(0);      //��ȡ������ڰ�λ����
	iic_stop();                        //����ֹͣ�ź� 
	return buf; 
}

