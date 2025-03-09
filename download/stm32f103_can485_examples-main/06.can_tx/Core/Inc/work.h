/*
 * work.h
 *
 *  Created on: Feb 15, 2025
 *      Author: user
 */

#ifndef INC_WORK_H_
#define INC_WORK_H_

#include "stm32f1xx_hal.h"

extern void InitWork();
extern void ReadButton();
extern void ToggleRunLed();
extern int SendCanFrame(uint32_t id, int data_len, uint8_t data[]);
extern int SendCanMessagePoll();
extern int SendCanMessageButton(uint8_t button);

#endif /* INC_WORK_H_ */
