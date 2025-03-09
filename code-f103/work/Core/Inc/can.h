/*
 * can.h
 *
 *  Created on: Mar 4, 2025
 *      Author: user
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

#include "basic.h"

void InitCanWork();
void DoCanWork();

int SendCanMessageButton1(uint8_t button);
int SendCanMessageButton2(uint8_t button);

#endif /* INC_CAN_H_ */
