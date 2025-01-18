#include"bsp.h"

extern uint32_t TimerUART;
extern bool Timestate ;

extern    uint8_t date ;
extern    uint8_t month ;
extern    uint16_t year ;
extern    uint8_t dow ;
extern    uint8_t hour ;
extern    uint8_t minute ;
extern    uint8_t second ;
extern    int8_t zone_hr ;
extern    uint8_t zone_min ;

extern uint32_t hour_n;
extern uint32_t minute_n;
extern uint32_t second_n;
extern uint32_t hour_n1;
extern uint32_t hour_n2;
extern uint32_t minute_n1;
extern uint32_t minute_n2;
extern uint32_t second_n1;
extern uint32_t second_n2;

void OLED_Initial(void)
{
    OLED_Init();
    OLED_Display_On();
    OLED_On();
    OLED_Clear();
}

void Self_Test(void)
{
    for (int i = 0; i < 10; i++) {
        Nixie_display(1, i);
        Nixie_display(2, i);
        Nixie_display(3, i);
        Nixie_display(4, i);
        Nixie_display(5, i);
        Nixie_display(6, i);
        TimerUART = uwTick;

        while ((HAL_GetTick() - TimerUART) < 300);
    }
}

void Get_time(void)
{
    date = DS1307_GetDate();
    month = DS1307_GetMonth();
    year = DS1307_GetYear();
    dow = DS1307_GetDayOfWeek();
    hour = DS1307_GetHour();
    minute = DS1307_GetMinute();
    second = DS1307_GetSecond();
    zone_hr = DS1307_GetTimeZoneHour();
    zone_min = DS1307_GetTimeZoneMin();
}

void Get_display_time(void)
{
    uint8_t hour = DS1307_GetHour();
    uint8_t minute = DS1307_GetMinute();
    uint8_t second = DS1307_GetSecond();
    //    minute_n = atoi((uint8_t *)minute);
    //    hour_n = atoi((uint8_t *)hour);
    //    second_n = atoi((uint8_t *)second);
    //    second_n2 = second_n % 10;
    //    second_n1 = second_n / 10 % 10;
    //    minute_n2 = minute_n % 10;
    //    minute_n1 = minute_n / 10 % 10;
    //    hour_n2 = hour_n % 10; //个位
    //    hour_n1 = hour_n / 10 % 10;
}

void Mixie_display_time(void)
{
    minute_n = (uint32_t)minute;
    hour_n = (uint32_t)hour;
    second_n=(uint32_t)second;
    second_n2 = second_n % 10;
    second_n1 = second_n / 10 % 10;
    minute_n2 = minute_n % 10;
    minute_n1 = minute_n / 10 % 10;
    hour_n2 = hour_n % 10; //个位
    hour_n1 = hour_n / 10 % 10;
    Nixie_display(1, hour_n1);
    Nixie_display(2, hour_n2);
    Nixie_display(5, minute_n1);
    Nixie_display(6, minute_n2);
    Nixie_display(4, second_n1);
    Nixie_display(3, second_n2);
}

void TIMs_Start(void)
{
    HAL_TIM_Base_Init(&htim7);
    HAL_TIM_Base_Start_IT(&htim7);
    HAL_TIM_Base_Init(&htim6);
    HAL_TIM_Base_Start_IT(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim7) {
        HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
    }

    if (htim == &htim6) {
        //        Timestate = !Timestate;
       // Get_display_time();
    }
}


void Nixie_display(uint32_t xuhao, uint32_t value)
{
    switch (xuhao) {
    case 1:
        switch (value) {
        case 1:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_RESET);
            break;

        case 2:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_RESET);
            break;

        case 4:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_RESET);
            break;

        case 5:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_RESET);
            break;

        case 6:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_RESET);
            break;

        case 7:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_RESET);
            break;

        case 8:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_SET);
            break;

        case 9:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_SET);
            break;

        case 0:
            HAL_GPIO_WritePin(X1A_GPIO_Port, X1A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1B_GPIO_Port, X1B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1C_GPIO_Port, X1C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X1D_GPIO_Port, X1D_Pin, GPIO_PIN_RESET);
            break;
        }

        break;

    case 2:
        switch (value) {
        case 1:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_RESET);
            break;

        case 2:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_RESET);
            break;

        case 4:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_RESET);
            break;

        case 5:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_RESET);
            break;

        case 6:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_RESET);
            break;

        case 7:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_RESET);
            break;

        case 8:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_SET);
            break;

        case 9:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_SET);
            break;

        case 0:
            HAL_GPIO_WritePin(X2A_GPIO_Port, X2A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2B_GPIO_Port, X2B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2C_GPIO_Port, X2C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X2D_GPIO_Port, X2D_Pin, GPIO_PIN_RESET);
            break;
        }

        break;

    case 3:
        switch (value) {
        case 1:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_RESET);
            break;

        case 2:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_RESET);
            break;

        case 4:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_RESET);
            break;

        case 5:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_RESET);
            break;

        case 6:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_RESET);
            break;

        case 7:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_RESET);
            break;

        case 8:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_SET);
            break;

        case 9:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_SET);
            break;

        case 0:
            HAL_GPIO_WritePin(X3A_GPIO_Port, X3A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3B_GPIO_Port, X3B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3C_GPIO_Port, X3C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X3D_GPIO_Port, X3D_Pin, GPIO_PIN_RESET);
            break;
        }

        break;

    case 4:
        switch (value) {
        case 1:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_RESET);
            break;

        case 2:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_RESET);
            break;

        case 4:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_RESET);
            break;

        case 5:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_RESET);
            break;

        case 6:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_RESET);
            break;

        case 7:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_RESET);
            break;

        case 8:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_SET);
            break;

        case 9:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_SET);
            break;

        case 0:
            HAL_GPIO_WritePin(X4A_GPIO_Port, X4A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4B_GPIO_Port, X4B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4C_GPIO_Port, X4C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X4D_GPIO_Port, X4D_Pin, GPIO_PIN_RESET);
            break;
        }

        break;

    case 5:
        switch (value) {
        case 1:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_RESET);
            break;

        case 2:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_RESET);
            break;

        case 4:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_RESET);
            break;

        case 5:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_RESET);
            break;

        case 6:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_RESET);
            break;

        case 7:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_RESET);
            break;

        case 8:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_SET);
            break;

        case 9:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_SET);
            break;

        case 0:
            HAL_GPIO_WritePin(X5A_GPIO_Port, X5A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5B_GPIO_Port, X5B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5C_GPIO_Port, X5C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X5D_GPIO_Port, X5D_Pin, GPIO_PIN_RESET);
            break;
        }

        break;

    case 6:
        switch (value) {
        case 1:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_RESET);
            break;

        case 2:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_RESET);
            break;

        case 4:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_RESET);
            break;

        case 5:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_RESET);
            break;

        case 6:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_RESET);
            break;

        case 7:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_RESET);
            break;

        case 8:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_SET);
            break;

        case 9:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_SET);
            break;

        case 0:
            HAL_GPIO_WritePin(X6A_GPIO_Port, X6A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6B_GPIO_Port, X6B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6C_GPIO_Port, X6C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(X6D_GPIO_Port, X6D_Pin, GPIO_PIN_RESET);
            break;
        }

        break;
    }
}