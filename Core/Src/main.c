/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#define HIGH GPIO_PIN_RESET
#define LOW GPIO_PIN_SET
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for GreenLedFlashin */
osThreadId_t GreenLedFlashinHandle;
const osThreadAttr_t GreenLedFlashin_attributes = {
  .name = "GreenLedFlashin",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RedLedFlashing */
osThreadId_t RedLedFlashingHandle;
const osThreadAttr_t RedLedFlashing_attributes = {
  .name = "RedLedFlashing",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for OrangeLedFlashi */
osThreadId_t OrangeLedFlashiHandle;
const osThreadAttr_t OrangeLedFlashi_attributes = {
  .name = "OrangeLedFlashi",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
uint8_t StartFlag;
volatile uint8_t RedFlag;
volatile uint8_t GreenFlag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartDefaultTask(void *argument);
void GreenLedTask(void *argument);
void RedLedTask(void *argument);
void OrangeLed(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	StartFlag = 1;
	GreenFlag = 1;
	RedFlag = 1;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, HIGH);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of GreenLedFlashin */
  GreenLedFlashinHandle = osThreadNew(GreenLedTask, NULL, &GreenLedFlashin_attributes);

  /* creation of RedLedFlashing */
  RedLedFlashingHandle = osThreadNew(RedLedTask, NULL, &RedLedFlashing_attributes);

  /* creation of OrangeLedFlashi */
  OrangeLedFlashiHandle = osThreadNew(OrangeLed, NULL, &OrangeLedFlashi_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, led1_Pin|led2_Pin|led3_Pin|led4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : led1_Pin led2_Pin led3_Pin led4_Pin */
  GPIO_InitStruct.Pin = led1_Pin|led2_Pin|led3_Pin|led4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void AccessSharedData(void) {
    if (StartFlag == 1) {
        // Set Start flag to Down to indicate resource is in use
        StartFlag = 0;
    } else {
        // Resource contention: Turn on Blue LED
        HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, HIGH);
    }

    // Simulate read/write operations with a delay of 500 milliseconds
    SimulateReadWriteOperation();

    // Set Start flag back to Up to indicate resource is free
    StartFlag = 1;

    // Turn off Blue LED (if it was turned on during contention)
    HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, LOW);
}

void SimulateReadWriteOperation(void) {
    volatile uint32_t delay_count = 0;
    const uint32_t delay_target = 2000000; // Adjust this value to approximate 500 ms

    // Dummy loop to simulate processing time
    for (delay_count = 0; delay_count < delay_target; delay_count++) {
        __asm("nop"); // No Operation: Keeps the processor busy without changing code behavior
    }
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_GreenLedTask */
/**
* @brief Function implementing the GreenLedFlashin thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GreenLedTask */
void GreenLedTask(void *argument)
{
  /* USER CODE BEGIN GreenLedTask */
  /* Infinite loop */
  for(;;)
  {
	GreenFlag = 1;
	// Turn on Green LED
	HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, HIGH);

	// Enter critical section
	taskENTER_CRITICAL();
	AccessSharedData();
	taskEXIT_CRITICAL(); // Corrected macro usage

	// Turn off Green LED
	osDelay(200);
	HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, LOW);

	GreenFlag = 0;
	// Delay for 500 milliseconds
	osDelay(200);
  }
  /* USER CODE END GreenLedTask */
}

/* USER CODE BEGIN Header_RedLedTask */
/**
* @brief Function implementing the RedLedFlashing thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RedLedTask */
void RedLedTask(void *argument)
{
  /* USER CODE BEGIN RedLedTask */
  /* Infinite loop */
 for(;;)
  {
	RedFlag = 1;
	// Turn on Red LED
	HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, HIGH);

	// Enter critical section
	taskENTER_CRITICAL();
	AccessSharedData();
	taskEXIT_CRITICAL(); // Corrected macro usage

	// Turn off Red LED
	osDelay(550);
	HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, LOW);

	RedFlag = 0;
	// Delay for 100 milliseconds
	osDelay(550);
  }
  /* USER CODE END RedLedTask */
}

/* USER CODE BEGIN Header_OrangeLed */
/**
* @brief Function implementing the OrangeLedFlashi thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OrangeLed */
void OrangeLed(void *argument)
{
  /* USER CODE BEGIN OrangeLed */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(led4_GPIO_Port, led4_Pin);
	  osDelay(50);
  }
  /* USER CODE END OrangeLed */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
