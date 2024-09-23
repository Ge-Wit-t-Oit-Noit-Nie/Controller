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
#include "pcu.h"

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
/* Definitions for PCU */
osThreadId_t PCUHandle;
const osThreadAttr_t PCU_attributes = {
  .name = "PCU",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void start_pcu(void *argument);

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
  /* creation of PCU */
  PCUHandle = osThreadNew(start_pcu, NULL, &PCU_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_start_pcu */
/**
 * @brief  Function implementing the PCU thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_start_pcu */
void start_pcu(void *argument)
{
  /* USER CODE BEGIN start_pcu */
	PCU pcu_controller;
	Instruction instruction[] = {
			{.opcode = OPCODE_NOOP},
			{.opcode = OPCODE_LED, .parameter0 = (void *)LD2_Pin, .parameter1 = (void *)LD2_GPIO_Port},
			{.opcode = OPCODE_LED, .parameter0 = (void *)LD1_Pin, .parameter1 = (void *)LD1_GPIO_Port},
			{.opcode = OPCODE_DELAY, .parameter0 = (void *)pdMS_TO_TICKS(1500)},
	};
	pcu_controller.instructions = instruction;
	pcu_controller.program_size = 4;

	PCU_Init(&pcu_controller);

	/* Infinite loop */
	for (;;) {
		PCU_Execute(&pcu_controller);
		PCU_Step(&pcu_controller);
		//osDelay(500);
	}
  /* USER CODE END start_pcu */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

