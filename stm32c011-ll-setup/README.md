# STM32C011 Low-Level (LL) Library Setup

This directory contains the STM32C011 Low-Level (LL) drivers and configuration files for developing applications with the STM32C011 microcontroller.

## Overview

The STM32C011 is part of STMicroelectronics' STM32C0 series, which is the most cost-effective ARM Cortex-M0+ microcontroller family. The LL (Low-Level) drivers provide register-level access with optimized performance and minimal code footprint.

## Directory Structure

```
stm32c011-ll-setup/
├── STM32C0xx_HAL_Driver/          # HAL and LL drivers
│   ├── Inc/                       # Header files
│   │   ├── stm32c0xx_ll_*.h      # LL driver headers
│   │   └── stm32c0xx_hal_*.h     # HAL driver headers
│   └── Src/                       # Source files
│       ├── stm32c0xx_ll_*.c      # LL driver source
│       └── stm32c0xx_hal_*.c     # HAL driver source
├── CMSIS/                         # CMSIS headers and device support
│   ├── Core/Include/              # ARM Cortex-M0+ core headers
│   └── Device/ST/STM32C0xx/       # STM32C0 device specific headers
├── stm32c011_ll_config.h         # LL library configuration
└── README.md                      # This file
```

## Available STM32C011 LL Modules

The following LL modules are available for STM32C011:

- **LL_ADC**: Analog-to-Digital Converter
- **LL_BUS**: Bus matrix and AHB/APB peripherals
- **LL_CORTEX**: ARM Cortex-M0+ core functions
- **LL_CRC**: Cyclic Redundancy Check
- **LL_DMA**: Direct Memory Access
- **LL_DMAMUX**: DMA request multiplexer
- **LL_EXTI**: External interrupt/event controller
- **LL_GPIO**: General Purpose Input/Output
- **LL_I2C**: Inter-Integrated Circuit
- **LL_IWDG**: Independent Watchdog
- **LL_PWR**: Power management
- **LL_RCC**: Reset and Clock Control
- **LL_RTC**: Real-Time Clock
- **LL_SPI**: Serial Peripheral Interface
- **LL_SYSTEM**: System configuration
- **LL_TIM**: Timer/Counter
- **LL_USART**: Universal Synchronous/Asynchronous Receiver/Transmitter
- **LL_UTILS**: Utility functions
- **LL_WWDG**: Window Watchdog

## How to Use STM32C011 LL Libraries

### 1. Include Required Headers

In your main application file, include the necessary headers:

```c
#include "stm32c0xx.h"           // Device header
#include "stm32c011_ll_config.h" // LL configuration
#include "stm32c0xx_ll_bus.h"    // Bus control
#include "stm32c0xx_ll_gpio.h"   // GPIO functions
#include "stm32c0xx_ll_rcc.h"    // Clock control
// Add other LL modules as needed
```

### 2. Configure Compiler Defines

Add these preprocessor defines to your compiler settings:
```
-DSTM32C011xx
-DUSE_FULL_LL_DRIVER
```

### 3. Configure Include Paths

Add these directories to your compiler include paths:
```
stm32c011-ll-setup/STM32C0xx_HAL_Driver/Inc
stm32c011-ll-setup/CMSIS/Core/Include
stm32c011-ll-setup/CMSIS/Device/ST/STM32C0xx/Include
stm32c011-ll-setup/
```

### 4. Basic Example: GPIO LED Blink

```c
#include "stm32c0xx.h"
#include "stm32c011_ll_config.h"
#include "stm32c0xx_ll_bus.h"
#include "stm32c0xx_ll_gpio.h"
#include "stm32c0xx_ll_rcc.h"
#include "stm32c0xx_ll_utils.h"

int main(void)
{
    // Enable GPIO port clock
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    
    // Configure PA5 as output (LED pin on many development boards)
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_5, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_5, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_5, LL_GPIO_PULL_NO);
    
    while (1)
    {
        // Toggle LED
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
        
        // Simple delay (not precise)
        for (volatile uint32_t i = 0; i < 100000; i++);
    }
}
```

### 5. Clock Configuration Example

```c
void SystemClock_Config(void)
{
    // Configure the system clock to use HSI (16 MHz)
    LL_RCC_HSI_Enable();
    while (!LL_RCC_HSI_IsReady());
    
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI);
    
    // Configure HCLK and PCLK1
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    
    // Update system core clock variable
    SystemCoreClockUpdate();
}
```

## Advantages of LL Drivers

1. **Performance**: Direct register access with minimal overhead
2. **Code Size**: Smaller footprint compared to HAL drivers
3. **Real-time**: Predictable execution time
4. **Flexibility**: Full control over peripheral configuration
5. **Efficiency**: No unnecessary abstraction layers

## Comparison: LL vs HAL

| Feature | LL Drivers | HAL Drivers |
|---------|------------|-------------|
| Code Size | Smaller | Larger |
| Performance | Faster | Slower |
| Learning Curve | Steeper | Easier |
| Abstraction | Low | High |
| Flexibility | High | Medium |
| Real-time | Better | Good |

## Building with GCC

Example Makefile snippet:
```makefile
# Compiler
CC = arm-none-eabi-gcc

# Defines
DEFS = -DSTM32C011xx -DUSE_FULL_LL_DRIVER

# Include paths
INCLUDES = -Istm32c011-ll-setup/STM32C0xx_HAL_Driver/Inc \
           -Istm32c011-ll-setup/CMSIS/Core/Include \
           -Istm32c011-ll-setup/CMSIS/Device/ST/STM32C0xx/Include \
           -Istm32c011-ll-setup/

# Compiler flags
CFLAGS = -mcpu=cortex-m0plus -mthumb $(DEFS) $(INCLUDES) -Os -Wall

# Linker flags
LDFLAGS = -mcpu=cortex-m0plus -mthumb -specs=nano.specs -Wl,--gc-sections
```

## Debugging and Development Tools

- **STM32CubeIDE**: Integrated development environment
- **STM32CubeMX**: Graphical configuration tool
- **STM32CubeProgrammer**: Programming and debugging tool
- **STLink**: Hardware debugger interface

## Resources

- [STM32C0 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0490-stm32c0x1-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [STM32C011 Datasheet](https://www.st.com/resource/en/datasheet/stm32c011d6.pdf)
- [LL Driver Documentation](https://www.st.com/resource/en/user_manual/um2319-description-of-stm32l0-hal-and-lowlayer-drivers-stmicroelectronics.pdf)

## STM32C011 Key Features

- **Core**: ARM Cortex-M0+ up to 48 MHz
- **Flash**: Up to 32 KB
- **SRAM**: Up to 12 KB
- **GPIO**: Up to 15 I/Os
- **Timers**: 1x 16-bit advanced, 1x 16-bit general purpose
- **Communication**: USART, I2C, SPI
- **ADC**: 12-bit, up to 8 channels
- **Package**: SOIC8, SOIC14, TSSOP20, WLCSP12
- **Operating Voltage**: 1.7V to 3.6V
- **Temperature Range**: -40°C to +85°C (125°C for some variants)

## License

This setup uses STMicroelectronics' STM32CubeC0 package, which is subject to ST's software license agreement.