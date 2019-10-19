#ifndef FUNC_H
#include "stm32f1xx_hal.h"
#include "main.h"
#include "spi.h"
#define FUNC_H
//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

#define LCD_RST1  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,GPIO_PIN_SET);
#define LCD_RST0  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,GPIO_PIN_RESET);
//   LCD_DC  AO
#define LCD_DC1  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,GPIO_PIN_SET);
#define LCD_DC0  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,GPIO_PIN_RESET);
//  LCD_CS
#define LCD_CS1  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,GPIO_PIN_SET);
#define LCD_CS0  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,GPIO_PIN_RESET);
void lcd7735_senddata(unsigned char data);
void lcd7735_send16bData(unsigned char msb,unsigned char lsb);
void spi2_8b_init(void);
void spi2_16b_init(void);
//初始化
void lcd7735_ini(void);
//发送数据
void lcd7735_sendData(unsigned char data);
//发送命令
void lcd7735_sendCmd(unsigned char cmd); 
// 点亮指定区域
void lcd7735_fillrect(unsigned char startX, unsigned char startY, unsigned char stopX, unsigned char stopY, unsigned int color);
//点亮像素点
void lcd7735_putpix(unsigned char x, unsigned char y, unsigned int Color);
// 画线
void lcd7735_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned int color);
// 绘制矩形（未填充）  
void lcd7735_rect(char x1,char y1,char x2,char y2, unsigned int color);
//输出单个字符
void lcd7735_putchar(unsigned char x, unsigned char y, unsigned char chr, unsigned int charColor, unsigned int bkgColor);
//输出字符串	 
void lcd7735_putstr(unsigned char x, unsigned char y, const unsigned char str[], unsigned int charColor, unsigned int bkgColor);
// 计算指定屏幕区域
void lcd7735_at(unsigned char startX, unsigned char startY, unsigned char stopX, unsigned char stopY) ;
//输出32*32中文	//
void showhanzi32(unsigned int x,unsigned int y,unsigned char index, unsigned int charColor,unsigned int bkgColor);

void showimage(uint16_t x,uint16_t y);

//   显示任何大小字体
void show(unsigned int x,unsigned int y,unsigned char index, unsigned int high,unsigned int wide,unsigned int charColor,unsigned int bkgColor,unsigned int font);
#endif


