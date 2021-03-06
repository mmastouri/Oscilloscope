/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.7.0 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * Copyright (C) 2014-2016 Draupner Graphics A/S <http://www.touchgfx.com>.
 * All rights reserved.
 *
 * TouchGFX is protected by international copyright laws and the knowledge of
 * this source code may not be used to write a similar product. This file may
 * only be used in accordance with a license and should not be re-
 * distributed in any way without the prior permission of Draupner Graphics.
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/
#include <bsp/ResistiveTouchController.hpp>
#include <touchgfx/transforms/TouchCalibration.hpp>

#include "stm324x9i_eval_lcd.h"
#include "stm324x9i_eval_ioe8.h"

using namespace touchgfx;

static volatile int32_t _lastX = 0;
static volatile int32_t _lastY = 0;
static volatile bool lastState = false;
static volatile int touch_delay = 1;

//volatile uint32_t cc_begin = 0;
//volatile uint32_t mcu_load_pct = 0;
//extern volatile uint32_t cc_consumed;

void ResistiveTouchController::init()
{
    IOE_Config();
}

bool ResistiveTouchController::sampleTouch(int32_t& x, int32_t& y)
{
    static int cnt = touch_delay;
    cnt--;
    if (!cnt)
    {
        cnt = touch_delay;
        TS_STATE*  ts;
        ts = IOE_TS_GetState();

        if (ts->TouchDetected == 0x80)
        {
            x = ts->X;
            y = ts->Y;

            x -= 10;
            y = 271 - y;

            _lastX = x;
            _lastY = y;
            lastState = true;
            return true;
        }
        lastState = false;
        return false;
    }
    else
    {
        x = _lastX;
        y = _lastY;
        return lastState;
    }
}
