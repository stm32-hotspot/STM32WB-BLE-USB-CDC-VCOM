/**
  @page BLE_USB_VCOM      
  @verbatim
  ******************************************************************************
  * @file    BLE/BLE_USB_VCOM/readme.txt 
  * @author  MCD Application Team
  * @brief   Server implementation for max Data transfer via notification to client.
  *          
  ******************************************************************************
  *
  * Copyright (c) 2019-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim

@par Example Description

This examle demonstrates how to use the BLE component alongside the USB peripheral for point-to-point communications. The application runs the BLE component as a GAP Peripheral and GATT Server, and the USB as a Device Communication Class (CDC), this is a typical application on how to use the STM32WBxx USB Device peripheral where the STM32WB MCU behaves as a USB-to-RS232 bridge following the Virtual COM Port (VCP) implementation.
 - On one side, the STM32 exchanges data with a PC host through USB interface in Device mode.
 - On the other side, the STM32 exchanges data with other devices through the BLE interface (GATT Server).

When the VCP application is started, the STM32 MCU is enumerated as serial communication port and is
configured in the same way (baudrate, data format, parity, stop bit) as it would configure a standard 
COM port. 

  
@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Connectivity, BLE, IPCC, HSEM, RTC, UART, PWR, BLE protocol, BLE pairing, BLE profile, Dual core

@par Directory contents 
  
  - BLE/BLE_USB_VCOM/Core/Inc/stm32wbxx_hal_conf.h		HAL configuration file
  - BLE/BLE_USB_VCOM/Core/Inc/stm32wbxx_it.h          	Interrupt handlers header file
  - BLE/BLE_USB_VCOM/Core/Inc/main.h                  	Header for main.c module
  - BLE/BLE_USB_VCOM/STM32_WPAN/App/app_ble.h           Header for app_ble.c module
  - BLE/BLE_USB_VCOM/Core/Inc/app_common.h            	Header for all modules with common definition
  - BLE/BLE_USB_VCOM/Core/Inc/app_conf.h              	Parameters configuration file of the application
  - BLE/BLE_USB_VCOM/Core/Inc/app_entry.h               Parameters configuration file of the application
  - BLE/BLE_USB_VCOM/STM32_WPAN/App/ble_conf.h          BLE Services configuration
  - BLE/BLE_USB_VCOM/STM32_WPAN/App/ble_dbg_conf.h      BLE Traces configuration of the BLE services
  - BLE/BLE_USB_VCOM/Core/Inc/hw_conf.h           		Configuration file of the HW
  - BLE/BLE_USB_VCOM/Core/Inc/utilities_conf.h    		Configuration file of the utilities
  - BLE/BLE_USB_VCOM/STM32_WPAN/App/custom_app.h        Header for Data Throughput Server Application implementation
  - BLE/BLE_USB_VCOM/STM32_WPAN/App/custom_stm.h		Header for Data Throughput Service  implementation
  - BLE/BLE_USB_VCOM/Core/Src/stm32wbxx_it.c          	Interrupt handlers
  - BLE/BLE_USB_VCOM/Core/Src/main.c                  	Main program
  - BLE/BLE_USB_VCOM/Core/Src/system_stm32wbxx.c      	stm32wbxx system source file
  - BLE/BLE_USB_VCOM/STM32_WPAN/App/app_ble.c      	    BLE Profile implementation
  - BLE/BLE_USB_VCOM/Core/Src/app_entry.c      		    Initialization of the application
  - BLE/BLE_USB_VCOM/STM32_WPAN/Target/hw_ipcc.c      	IPCC Driver
  - BLE/BLE_USB_VCOM/Core/Src/stm32_lpm_if.c			Low Power Manager Interface
  - BLE/BLE_USB_VCOM/Core/Src/hw_timerserver.c 		    Timer Server based on RTC
  - BLE/BLE_USB_VCOM/Core/Src/hw_uart.c 			    UART Driver
  - BLE/BLE_USB_VCOM/STM32_WPAN/App/custom_app.c        Data Throughput Server Application implementation
  - BLE/BLE_USB_VCOM/STM32_WPAN/App/custom_stm.c		Data Throughput Service implementation
   
     
@par Hardware and Software environment

  - This example runs on STM32WB55xx devices.
  
  - This example has been tested with an STMicroelectronics STM32WB55xx-Nucleo-Dongle
    board and can be easily tailored to any other supported device 
    and development board.

@par How to use it ? 

This application requires having the stm32wb5x_BLE_Stack_full_fw.bin binary flashed on the Wireless Coprocessor.
If it is not the case, you need to use STM32CubeProgrammer to load the appropriate binary.
All available binaries are located under /Projects/STM32_Copro_Wireless_Binaries directory of the official STM32CubeWB v1.13.3 
package (https://github.com/STMicroelectronics/STM32CubeWB/releases/tag/v1.13.3).
Refer to UM2237 to learn how to use/install STM32CubeProgrammer.
Refer to /Projects/STM32_Copro_Wireless_Binaries/ReleaseNote.html for the detailed procedure to change the
Wireless Coprocessor binary.  

In order to make the program work, you must do the following:
 - Open your preferred toolchain (IAR EWARM or STM32CubeIDE) 
 - Rebuild all files and load your image into target memory


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 
