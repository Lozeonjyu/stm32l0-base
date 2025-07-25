/**
  ******************************************************************************
  * @file    main.c
  * @brief   STM32C011 LL GPIO Blink Example
  * @author  STM32 LL Example
  ******************************************************************************
  * @attention
  *
  * This example shows how to use STM32C011 LL drivers to blink an LED
  * connected to GPIO pin PA5.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx.h"
#include "stm32c011_ll_config.h"
#include "stm32c0xx_ll_bus.h"
#include "stm32c0xx_ll_gpio.h"
#include "stm32c0xx_ll_rcc.h"
#include "stm32c0xx_ll_utils.h"
#include "stm32c0xx_ll_system.h"
#include "stm32c0xx_ll_cortex.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LED_PIN                 LL_GPIO_PIN_5
#define LED_GPIO_PORT           GPIOA
#define LED_GPIO_CLK            LL_AHB1_GRP1_PERIPH_GPIOA

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Configure_GPIO(void);
void LED_Blinking(uint32_t Period);

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  Configure_GPIO();

  /* Infinite loop */
  while (1)
  {
    LED_Blinking(200);  /* 200ms blink period */
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured to use HSI as source
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Enable HSI */
  LL_RCC_HSI_Enable();
  while (!LL_RCC_HSI_IsReady());

  /* Set AHB prescaler */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the main HSI */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI);

  /* Set APB1 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

  /* Set systick to 1ms in using frequency set to SystemCoreClock */
  LL_Init1msTick(SystemCoreClock);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(SystemCoreClock);
}

/**
  * @brief  Configure GPIO for LED
  * @param  None
  * @retval None
  */
void Configure_GPIO(void)
{
  /* Enable GPIO Clock */
  LL_AHB1_GRP1_EnableClock(LED_GPIO_CLK);

  /* Configure GPIO */
  LL_GPIO_SetPinMode(LED_GPIO_PORT, LED_PIN, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinOutputType(LED_GPIO_PORT, LED_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinSpeed(LED_GPIO_PORT, LED_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinPull(LED_GPIO_PORT, LED_PIN, LL_GPIO_PULL_NO);
}

/**
  * @brief  LED blinking function
  * @param  Period: Period of blink in ms
  * @retval None
  */
void LED_Blinking(uint32_t Period)
{
  /* Toggle LED */
  LL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
  
  /* Wait for Period ms */
  LL_mDelay(Period);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */