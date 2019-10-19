#ifndef __KEY_H
#define __KEY_H
#include "main.h"
#include "flag.h"

#define shang HAL_GPIO_ReadPin(shang_GPIO_Port,shang_Pin)
#define zhong HAL_GPIO_ReadPin(zhong_GPIO_Port,zhong_Pin)
#define xia HAL_GPIO_ReadPin(xia_GPIO_Port,xia_Pin)
#define zuo HAL_GPIO_ReadPin(zuo_GPIO_Port,zuo_Pin)
#define you HAL_GPIO_ReadPin(you_GPIO_Port,you_Pin)
#define shushang HAL_GPIO_ReadPin(shushang_GPIO_Port,shushang_Pin)
#define shuxia HAL_GPIO_ReadPin(shuxia_GPIO_Port,shuxia_Pin)
#define zhiwen HAL_GPIO_ReadPin(zhiwen_GPIO_Port,zhiwen_Pin)
#define shuaka HAL_GPIO_ReadPin(shuaka_GPIO_Port,shuaka_Pin)
#define close HAL_GPIO_ReadPin(close_GPIO_Port,close_Pin)

#define ABS(x) ((x)>0?(x):-(x))

int key_scan(void);

void key_do(int flag);





#endif

