/**
  ******************************************************************************
  * @file    settings.c 
  * @author  MCD Application Team
  * @brief   This example code shows how to use the QSPI Driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "settings.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static QSPI_Info pQSPI_Info;
static uint32_t address;


/* Private functions ---------------------------------------------------------*/

/**
* @brief  QSPI Demo
* @param  None
* @retval None
*/
void qsettings_init (void)
{ 
  BSP_QSPI_DeInit();
  BSP_QSPI_Init();
  
  BSP_QSPI_GetInfo(&pQSPI_Info);
  address = pQSPI_Info.FlashSize - PARAMS_BLOCK_NB * pQSPI_Info.EraseSectorSize;

  BSP_QSPI_EnableMemoryMappedMode();  
}

/**
* @brief  QSPI Demo
* @param  None
* @retval None
*/
void qsettings_save (save_data_t *pdata)
{ 
  BSP_QSPI_DeInit();
  BSP_QSPI_Init();  
	
	BSP_QSPI_Erase_Block(address);  
  BSP_QSPI_Write ( (uint8_t *)pdata->data, address, 512);
  BSP_QSPI_EnableMemoryMappedMode();
}

void qsettings_restore (save_data_t *pdata)
{
  BSP_QSPI_DeInit();
  BSP_QSPI_Init();  

  BSP_QSPI_Read ( (uint8_t *)pdata->data, address, 512);
  BSP_QSPI_EnableMemoryMappedMode();
}
/**
* @}
*/ 

/**
* @}
*/ 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
