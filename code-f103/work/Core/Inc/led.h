/*
 * led.h
 *
 *  Created on: Mar 4, 2025
 *      Author: user
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "basic.h"

void DoLedWork();

void SetLedD1(uint8_t on);
void ToggleLedD1();
void SetLedD2(uint8_t on);
void ToggleLedD2();

#endif /* INC_LED_H_ */
