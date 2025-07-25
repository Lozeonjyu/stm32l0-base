/**
  ******************************************************************************
  * @file    stm32c011_ll_config.h
  * @author  MCD Application Team
  * @brief   STM32C011 LL library configuration file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef STM32C011_LL_CONFIG_H
#define STM32C011_LL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the LL library
  * Comment or uncomment the modules you want to use
  */

/* STM32C011 specific definitions */
#define STM32C011xx

/* LL modules selection */
#define USE_FULL_LL_DRIVER

/* Uncomment the LL modules you want to use */
#define LL_ADC_MODULE_ENABLED
#define LL_BUS_MODULE_ENABLED
#define LL_CORTEX_MODULE_ENABLED
#define LL_CRC_MODULE_ENABLED
#define LL_DMA_MODULE_ENABLED
#define LL_DMAMUX_MODULE_ENABLED
#define LL_EXTI_MODULE_ENABLED
#define LL_GPIO_MODULE_ENABLED
#define LL_I2C_MODULE_ENABLED
#define LL_IWDG_MODULE_ENABLED
#define LL_PWR_MODULE_ENABLED
#define LL_RCC_MODULE_ENABLED
#define LL_RTC_MODULE_ENABLED
#define LL_SPI_MODULE_ENABLED
#define LL_SYSTEM_MODULE_ENABLED
#define LL_TIM_MODULE_ENABLED
#define LL_USART_MODULE_ENABLED
#define LL_UTILS_MODULE_ENABLED
#define LL_WWDG_MODULE_ENABLED

/* ########################## System Clock Source Selection ################## */
/**
  * @brief This is the system clock source selection
  */
#define USE_HSI_CLOCK        /* High Speed Internal clock (16 MHz) */
/* #define USE_HSE_CLOCK */  /* High Speed External clock */
/* #define USE_PLL_CLOCK */  /* Phase Locked Loop clock */

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        LL drivers code
  */
/* #define USE_FULL_ASSERT */

/* ########################## Register Callbacks ############################ */
/**
  * @brief This is the list of register callbacks to be used in the LL library
  * Set to 1 to use callbacks, 0 to disable
  */
#define  USE_LL_ADC_REGISTER_CALLBACKS      0U
#define  USE_LL_CRC_REGISTER_CALLBACKS      0U
#define  USE_LL_DMA_REGISTER_CALLBACKS      0U
#define  USE_LL_I2C_REGISTER_CALLBACKS      0U
#define  USE_LL_RTC_REGISTER_CALLBACKS      0U
#define  USE_LL_SPI_REGISTER_CALLBACKS      0U
#define  USE_LL_TIM_REGISTER_CALLBACKS      0U
#define  USE_LL_USART_REGISTER_CALLBACKS    0U

/* ########################## Oscillator Values adaptation ################## */
/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the RCC LL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).  
  */
#if !defined(HSE_VALUE)
  #define HSE_VALUE    8000000U /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the RCC LL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL). 
  */
#if !defined(HSI_VALUE)
  #define HSI_VALUE    16000000U /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

/**
  * @brief Internal Low Speed oscillator (LSI) value.
  */
#if !defined(LSI_VALUE) 
 #define LSI_VALUE  32000U       /*!< LSI Typical Value in Hz*/
#endif /* LSI_VALUE */                      /*!< Value of the Internal Low Speed oscillator in Hz
                                             The real value may vary depending on the variations
                                             in voltage and temperature.*/
/**
  * @brief External Low Speed oscillator (LSE) value.
  *        This value is used by the UART, RTC LL module to compute the system frequency
  */
#if !defined(LSE_VALUE)
  #define LSE_VALUE  32768U    /*!< Value of the External Low Speed oscillator in Hz */
#endif /* LSE_VALUE */

#ifdef __cplusplus
}
#endif

#endif /* STM32C011_LL_CONFIG_H */