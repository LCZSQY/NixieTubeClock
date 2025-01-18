#ifndef BSP_H
#define BSP_H


#include"stdint.h"
#include"stdlib.h"
#include"stdio.h"
#include"math.h"
#include"string.h"
#include"oled.h"
#include"stm32f1xx_ll_tim.h"
#include"tim.h"
#include"main.h"
#include"usart.h"
#include "ds1307.h"
#include "stdbool.h"




void OLED_Initial(void);
void Nixie_display(uint32_t xuhao,uint32_t value);
void Self_Test(void);
void Get_time(void);
void Get_display_time(void);
void TIMs_Start(void);
void Mixie_display_time(void);
#endif