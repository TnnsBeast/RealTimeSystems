/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "MPU6050.h"


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
/* Definitions for MPU_Task */
osThreadId_t MPU_TaskHandle;
const osThreadAttr_t MPU_Task_attributes = {
  .name = "MPU_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LED_dummyTask */
osThreadId_t LED_dummyTaskHandle;
const osThreadAttr_t LED_dummyTask_attributes = {
  .name = "LED_dummyTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartMPUTask(void *argument);
void StartLEDDummyTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of MPU_Task */
  MPU_TaskHandle = osThreadNew(StartMPUTask, NULL, &MPU_Task_attributes);

  /* creation of LED_dummyTask */
  LED_dummyTaskHandle = osThreadNew(StartLEDDummyTask, NULL, &LED_dummyTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartMPUTask */
/**
  * @brief  Function implementing the MPU_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartMPUTask */
void StartMPUTask(void *argument)
{
  /* USER CODE BEGIN StartMPUTask */
  /* Infinite loop */
  for(;;)
  {
	  if(MPU6050_DataReady() == 1)
		{
			MPU6050_ProcessData(&MPU6050);
			//printf("%f, %f, %f\n", MPU6050.acc_x, MPU6050.acc_y, MPU6050.acc_z);
			//printf("%f, %f, %f\n", MPU6050.gyro_x, MPU6050.gyro_y, MPU6050.gyro_z);
			printf("%d, %d, %d\n", MPU6050.acc_x_raw, MPU6050.acc_y_raw, MPU6050.acc_z_raw);
		}
    osDelay(1);
  }
  /* USER CODE END StartMPUTask */
}

/* USER CODE BEGIN Header_StartLEDDummyTask */
/**
* @brief Function implementing the LED_dummyTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLEDDummyTask */
void StartLEDDummyTask(void *argument)
{
  /* USER CODE BEGIN StartLEDDummyTask */
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_3); // PB3 is the on board LED for Nucleo L432KC
    osDelay(500);
  }
  /* USER CODE END StartLEDDummyTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

