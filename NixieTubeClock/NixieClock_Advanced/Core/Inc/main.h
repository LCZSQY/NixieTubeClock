/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp.h"
#include "ds1307.h"
#include "oled.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define X1A_Pin GPIO_PIN_2
#define X1A_GPIO_Port GPIOE
#define X5A_Pin GPIO_PIN_3
#define X5A_GPIO_Port GPIOE
#define X1B_Pin GPIO_PIN_4
#define X1B_GPIO_Port GPIOE
#define X5B_Pin GPIO_PIN_5
#define X5B_GPIO_Port GPIOE
#define X1C_Pin GPIO_PIN_6
#define X1C_GPIO_Port GPIOE
#define X5C_Pin GPIO_PIN_13
#define X5C_GPIO_Port GPIOC
#define X1D_Pin GPIO_PIN_0
#define X1D_GPIO_Port GPIOC
#define X5D_Pin GPIO_PIN_1
#define X5D_GPIO_Port GPIOC
#define KEYB_Pin GPIO_PIN_0
#define KEYB_GPIO_Port GPIOA
#define X2A_Pin GPIO_PIN_4
#define X2A_GPIO_Port GPIOA
#define X6A_Pin GPIO_PIN_5
#define X6A_GPIO_Port GPIOA
#define X2B_Pin GPIO_PIN_6
#define X2B_GPIO_Port GPIOA
#define X6B_Pin GPIO_PIN_7
#define X6B_GPIO_Port GPIOA
#define X2C_Pin GPIO_PIN_4
#define X2C_GPIO_Port GPIOC
#define X2D_Pin GPIO_PIN_0
#define X2D_GPIO_Port GPIOB
#define X6C_Pin GPIO_PIN_1
#define X6C_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_2
#define LED_BLUE_GPIO_Port GPIOB
#define X6D_Pin GPIO_PIN_7
#define X6D_GPIO_Port GPIOE
#define X3A_Pin GPIO_PIN_8
#define X3A_GPIO_Port GPIOE
#define X3B_Pin GPIO_PIN_10
#define X3B_GPIO_Port GPIOE
#define X3C_Pin GPIO_PIN_12
#define X3C_GPIO_Port GPIOE
#define X3D_Pin GPIO_PIN_14
#define X3D_GPIO_Port GPIOE
#define X4A_Pin GPIO_PIN_10
#define X4A_GPIO_Port GPIOB
#define X4B_Pin GPIO_PIN_12
#define X4B_GPIO_Port GPIOB
#define X4C_Pin GPIO_PIN_14
#define X4C_GPIO_Port GPIOB
#define X4D_Pin GPIO_PIN_15
#define X4D_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_8
#define KEY2_GPIO_Port GPIOD
#define KEY1_Pin GPIO_PIN_10
#define KEY1_GPIO_Port GPIOD
#define BEEP_Pin GPIO_PIN_8
#define BEEP_GPIO_Port GPIOA
#define NG_Pin GPIO_PIN_11
#define NG_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
