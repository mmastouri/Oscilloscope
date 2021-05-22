/**
  ******************************************************************************
  * @file    BSP/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SETTINGS__H
#define SETTINGS__H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_qspi.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PARAMS_BLOCK_NB       (10)

/* Private variables ---------------------------------------------------------*/
__packed typedef union 
{
  uint8_t data[512];
  __packed struct __item
  {
		uint32_t signature;
    uint32_t CH1_YOffset;
    uint32_t CH2_YOffset;
		
    uint32_t CH1_Trigger;
    uint32_t CH2_Trigger;
		uint32_t CH1_TriggerType;
    uint32_t CH2_TriggerType;
		uint32_t CH1_TriggerValue;
		uint32_t CH2_TriggerValue;
		
		uint32_t CH1_TimeScale;		
		uint32_t CH2_TimeScale;		
		uint32_t CH1_VoltageScale;		
		uint32_t CH2_VoltageScale;				

  } item;
}save_data_t;

void qsettings_init (void);
void qsettings_save (save_data_t *pdata);
void qsettings_restore (save_data_t *pdata);
#ifdef __cplusplus
}
#endif
#endif /* SETTINGS__H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
