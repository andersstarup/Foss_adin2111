/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lwIP_adin2111_app.h"
#include "lwip/timeouts.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

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
  /* USER CODE BEGIN 2 */
  uint32_t       error;
  uint32_t       heartbeatCheckTime = 0;

  adin2111_DeviceStruct_t dev;
  adin2111_DeviceHandle_t hDevice = &dev;
  LwIP_ADIN2111_t myConn;
  board_t boardDetails;

  /****** System Init *****/
  error = BSP_InitSystem();
  DEBUG_RESULT("BSP_InitSystem", error, 0);

  BSP_HWReset(true);

  boardDetails.mac[0] =	0x00;
  boardDetails.mac[1] =	0xE0;
  boardDetails.mac[2] =	0x22;
  boardDetails.mac[3] =	0xFE;
  boardDetails.mac[4] =	0xDA;
  boardDetails.mac[5] =	0xC9;

  boardDetails.ip_addr[0] =   192;
  boardDetails.ip_addr[1] =   168;
  boardDetails.ip_addr[2] =   0;
  boardDetails.ip_addr[3] =   220;

  boardDetails.net_mask[0] =  255;
  boardDetails.net_mask[1] =  255;
  boardDetails.net_mask[2] =  255;
  boardDetails.net_mask[3] =  0;

  boardDetails.gateway[0] =   192;
  boardDetails.gateway[1] =   168;
  boardDetails.gateway[2] =   1;
  boardDetails.gateway[3] =   1;

  boardDetails.ip_addr_fixed = IP_FIXED;//IP_DYNAMIC;//

  error = discoveradin2111(&hDevice);
  DEBUG_RESULT("Failed to access ADIN2111", error, 0);

  LwIP_StructInit(&myConn, &hDevice, boardDetails.mac);
  LwIP_Init(&myConn, &boardDetails);
  LwIP_ADIN2111LinkInput(&myConn.netif);
  BSP_delayMs(500);

  netif_set_link_up(&myConn.netif);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
      uint32_t now  = BSP_SysNow();
      if (now - heartbeatCheckTime >= 250)
      {
        heartbeatCheckTime = now;

        BSP_HeartBeat();

        sys_check_timeouts();


      }
      LwIP_ADIN2111LinkInput(&myConn.netif);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


