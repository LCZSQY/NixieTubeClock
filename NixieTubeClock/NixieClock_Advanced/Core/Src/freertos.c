/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Nixie_displayHandle;
osThreadId ReadRTCHandle;
osThreadId EntireHourBBjiaHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppNixie_display(void const * argument);
void AppReadRTC(void const * argument);
void AppEntireHourBBjiao(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Nixie_display */
  osThreadDef(Nixie_display, AppNixie_display, osPriorityNormal, 0, 128);
  Nixie_displayHandle = osThreadCreate(osThread(Nixie_display), NULL);

  /* definition and creation of ReadRTC */
  osThreadDef(ReadRTC, AppReadRTC, osPriorityAboveNormal, 0, 128);
  ReadRTCHandle = osThreadCreate(osThread(ReadRTC), NULL);

  /* definition and creation of EntireHourBBjia */
  osThreadDef(EntireHourBBjia, AppEntireHourBBjiao, osPriorityBelowNormal, 0, 128);
  EntireHourBBjiaHandle = osThreadCreate(osThread(EntireHourBBjia), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_AppNixie_display */
/**
  * @brief  Function implementing the Nixie_display thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_AppNixie_display */
__weak void AppNixie_display(void const * argument)
{
  /* USER CODE BEGIN AppNixie_display */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END AppNixie_display */
}

/* USER CODE BEGIN Header_AppReadRTC */
/**
* @brief Function implementing the ReadRTC thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppReadRTC */
__weak void AppReadRTC(void const * argument)
{
  /* USER CODE BEGIN AppReadRTC */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END AppReadRTC */
}

/* USER CODE BEGIN Header_AppEntireHourBBjiao */
/**
* @brief Function implementing the EntireHourBBjia thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppEntireHourBBjiao */
__weak void AppEntireHourBBjiao(void const * argument)
{
  /* USER CODE BEGIN AppEntireHourBBjiao */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END AppEntireHourBBjiao */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

