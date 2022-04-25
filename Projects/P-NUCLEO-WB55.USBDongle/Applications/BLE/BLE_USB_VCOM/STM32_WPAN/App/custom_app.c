/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_app.c
  * @author  MCD Application Team
  * @brief   Custom Example Application (Server)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "custom_app.h"
#include "custom_stm.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"  //[JT]
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  /* My_BLE_VCOM */
  uint8_t               Notify_c_Notification_Status;
  /* USER CODE BEGIN CUSTOM_APP_Context_t */

  /* USER CODE END CUSTOM_APP_Context_t */

  uint16_t              ConnectionHandle;
} Custom_App_Context_t;

/* USER CODE BEGIN PTD */
uint8_t notify_size;  //[JT]
/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

PLACE_IN_SECTION("BLE_APP_CONTEXT") static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

/* USER CODE BEGIN PV */
uint8_t UpdateCharData[247];
uint8_t NotifyCharData[247];

uint8_t SecureReadData;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
  /* My_BLE_VCOM */
static void Custom_Notify_c_Update_Char(void);
static void Custom_Notify_c_Send_Notification(void);

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */

  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch(pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

  /* My_BLE_VCOM */
    case CUSTOM_STM_WRITE_C_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_WRITE_C_WRITE_NO_RESP_EVT */
      //[JT]
      APP_DBG_MSG("\r\n\r** CUSTOM_STM_NOTIFY_C_WRITE_NO_RESP_EVT \n");
      
      /* Copy the received configuration data into local buffer */
      usb_cdc_copy_data(pNotification->DataTransfered.pPayload,
                        pNotification->DataTransfered.Length);
      
      UTIL_SEQ_SetTask( 1<<CFG_TASK_USB_CDC_SEND_DATA_ID, CFG_SCH_PRIO_0);
      /* USER CODE END CUSTOM_STM_WRITE_C_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_NOTIFY_C_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_NOTIFY_C_NOTIFY_ENABLED_EVT */
      //[JT] - Notifications enabled
      APP_DBG_MSG("\r\n\r** CUSTOM_STM_NOTIFY_C_NOTIFY_ENABLED_EVT \n");
      Custom_App_Context.Notify_c_Notification_Status = 1;        /* notification status has been enabled */
      
      /* USER CODE END CUSTOM_STM_NOTIFY_C_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_NOTIFY_C_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_NOTIFY_C_NOTIFY_DISABLED_EVT */
       //[JT] - Notifications disabled
      APP_DBG_MSG("\r\n\r** CUSTOM_STM_NOTIFY_C_NOTIFY_DISABLED_EVT \n");
      Custom_App_Context.Notify_c_Notification_Status = 0;        /* notification status has been disabled */
      
      /* USER CODE END CUSTOM_STM_NOTIFY_C_NOTIFY_DISABLED_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */

      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */

  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */

  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch(pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */

      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */

      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */

      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */

  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}

void Custom_APP_Init(void)
{
  /* USER CODE BEGIN CUSTOM_APP_Init */
  
  /* Init flags, variables, and buffers */ 
  Custom_App_Context.Notify_c_Notification_Status=0;                  

  /* USER CODE END CUSTOM_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

  /* My_BLE_VCOM */
void Custom_Notify_c_Update_Char(void) /* Property Read */
{
  Custom_STM_App_Update_Char(CUSTOM_STM_NOTIFY_C, (uint8_t *)UpdateCharData);
  /* USER CODE BEGIN Notify_c_UC*/

  /* USER CODE END Notify_c_UC*/
  return;
}

void Custom_Notify_c_Send_Notification(void) /* Property Notification */
 {
  if(Custom_App_Context.Notify_c_Notification_Status)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_NOTIFY_C, (uint8_t *)NotifyCharData);
    /* USER CODE BEGIN Notify_c_NS*/

    /* USER CODE END Notify_c_NS*/
  }
  else
  {
    APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n ");
  }
  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/
//[JT]

void ble_send_data( void )
{
   Custom_Notify_c_Send_Notification();
}

void ble_notify_copy_data(uint8_t * p_data, uint8_t sz)
{
  notify_size = sz;
  memcpy(&NotifyCharData, p_data, sz);
}



/* USER CODE END FD_LOCAL_FUNCTIONS*/
