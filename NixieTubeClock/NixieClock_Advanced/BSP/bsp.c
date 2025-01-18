#include"bsp.h"


uint8_t date ;
uint8_t month ;
uint16_t year ;
uint8_t dow ;
uint8_t hour ;
uint8_t minute ;
uint8_t second ;
int8_t zone_hr ;
uint8_t zone_min ;
uint32_t hour_n;
uint32_t minute_n;
uint32_t second_n;
uint32_t hour_n1;
uint32_t hour_n2;
uint32_t minute_n1;
uint32_t minute_n2;
uint32_t second_n1;
uint32_t second_n2;
uint32_t TestHighWater[2] = {0};

extern osThreadId Nixie_displayHandle;
extern osThreadId ReadRTCHandle;
extern osThreadId EntireHourBBjiaHandle;


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
        osDelay(200);
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
    hour = DS1307_GetHour();
    minute = DS1307_GetMinute();
    second = DS1307_GetSecond();
}

void Mixie_display_time(void)
{
    minute_n = (uint32_t)minute;
    hour_n = (uint32_t)hour;
    second_n = (uint32_t)second;
    second_n2 = second_n % 10;
    second_n1 = second_n / 10 % 10;
    minute_n2 = minute_n % 10;
    minute_n1 = minute_n / 10 % 10;
    hour_n2 = hour_n % 10; //¸öÎ»
    hour_n1 = hour_n / 10 % 10;
    Nixie_display(1, hour_n1);
    Nixie_display(2, hour_n2);
    Nixie_display(5, minute_n1);
    Nixie_display(6, minute_n2);
    Nixie_display(4, second_n1);
    Nixie_display(3, second_n2);
}
void AppEntireHourBBjiao(void const *argument)
{
    osDelay(2000);

    while (1) {
        
            if (second_n == 0 && minute_n == 0) {
            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
                osDelay(500);
                HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
                portYIELD();
            }
        

        osDelay(1);
    }
}



void AppNixie_display(void const *argument)
{
    //    TestHighWater[0] = uxTaskGetStackHighWaterMark(Nixie_displayHandle);
    Self_Test();

    while (1) {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != pdFALSE) {
            Mixie_display_time();
        }

        osDelay(1);
    }
}
void AppReadRTC(void const *argument)
{
    //    TestHighWater[1] = uxTaskGetStackHighWaterMark(ReadRTCHandle);
    while (1) {
        Get_display_time();

        if (Nixie_displayHandle != NULL) {
            xTaskNotifyGive(Nixie_displayHandle);
        }

       

        osDelay(500);
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