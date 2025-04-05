/*
 * work.c
 *
 *  Created on: Feb 15, 2025
 *      Author: user
 */

#include <stdio.h>
#include <work_rfid_pn532.h>
#include "work.h"
#include "led.h"
#include "button.h"
#include "can.h"
#include "pn532.h"
#include "pn532_stm32f1.h"
#include "work_buzzer.h"
#include "work_test.h"

void InitWork()
{
	InitBasic();

	//InitCanWork();
	//InitRfidPn532Work();
	InitWorkBuzzer();
	//InitWorkTest();

	printf("Start\n");
}



void DoWork()
{
	DoLedWork();
	//DoButtonWork();
	//DoCanWork();
	//DoRfidPn532Work();
	DoWorkBuzzer();
	//DoWorkTest();
}





