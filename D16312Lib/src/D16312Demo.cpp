/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
/*
 *  Created on: Jul 27, 2014
 *      Author: yev
 */

#include <cr_section_macros.h>
#include "D16312.h"

void ShowTextDemo(D16312* vfdController);
void ShowSymbolsDemo(D16312* vfdController);
void ShowSpinnerDemo(D16312* vfdController);
void ShowAllDemo(D16312* vfdController);
void ShowLEDDemo(D16312* vfdController);
void ShowBrightnessDemo(D16312* vfdController);

void delay(int ticks)
{
	volatile int i = ticks;
	while(i--);
}

int main(void)
{
	GPIOInit();

	// Controller connected to port 3, data bit is 3rd, clock - 0 and strobe bit is 1
	D16312 vfdController(PORT3, 2, 0, 1);
	vfdController.EnableDispay(true);

	ShowTextDemo(&vfdController);
    while(1)
    {
    	delay(300000);	// We need to use this delay because display is disabled during key scanning, it might made flickering

    	uint8_t key = vfdController.ReadKey();
    	switch(key)
    	{
    	case PlayKey:
    		ShowSymbolsDemo(&vfdController);
    	break;
    	case PauseKey:
    		ShowSpinnerDemo(&vfdController);
		break;
    	case StopKey:
    		ShowAllDemo(&vfdController);
		break;
    	case BackwardKey:
    		ShowLEDDemo(&vfdController);
		break;
    	case ForwardKey:
    		ShowBrightnessDemo(&vfdController);
    	break;
    	};
    }
    return 0 ;
}

// Shows "Hi HAbr" text on display
void ShowTextDemo(D16312* vfdController)
{
	vfdController->ClearScreen();

	vfdController->WriteChar('H', 0);
	vfdController->WriteChar('i', 1);
	vfdController->WriteChar(' ', 2);
	vfdController->WriteChar('H', 3);
	vfdController->WriteChar('A', 4);
	vfdController->WriteChar('b', 5);
	vfdController->WriteChar('r', 6);

	delay(2000000);
}

// Enables special signs one-by-one
void ShowSymbolsDemo(D16312* vfdController)
{
	vfdController->ClearScreen();

	vfdController->EnableMP3(true);
	delay(2000000);

	vfdController->EnablePBC(true);
	delay(2000000);

	vfdController->EnableCamera(true);
	delay(2000000);

	vfdController->EnableDolby(true);
	delay(2000000);

	vfdController->EnableCD(true);
	delay(2000000);

	vfdController->EnableVCD(true);
	delay(2000000);

	vfdController->EnableSVCD(true);
	delay(2000000);

	vfdController->EnableDTS(true);
	delay(2000000);

	vfdController->EnableDVD(true);
	delay(2000000);

	vfdController->EnablePlay(true);
	delay(2000000);

	vfdController->EnablePause(true);
	delay(2000000);

	vfdController->EnableRepeat(true);
	delay(2000000);

	vfdController->EnableAll(true);
	delay(2000000);

	vfdController->EnableColon1st(true);
	delay(2000000);

	vfdController->EnableColon2nd(true);
	delay(2000000);
}

// Fill spinner progress gradually
void ShowSpinnerDemo(D16312* vfdController)
{
	vfdController->ClearScreen();

	for (uint8_t i = 0; i <= 100; ++i)
	{
		vfdController->ShowSpinner(0, i);

		delay(200000);
	}
}

// Enables all information at one time
void ShowAllDemo(D16312* vfdController)
{
	vfdController->ClearScreen();

	for (uint8_t i = 0; i < 7; ++i)
	{
		if (i % 2 == 0)
		{
			ShowTextDemo(vfdController);

			vfdController->EnableMP3(true);
			vfdController->EnablePBC(true);
			vfdController->EnableCamera(true);
			vfdController->EnableDolby(true);
			vfdController->EnableCD(true);
			vfdController->EnableVCD(true);
			vfdController->EnableSVCD(true);
			vfdController->EnableDTS(true);
			vfdController->EnableDVD(true);
			vfdController->EnablePlay(true);
			vfdController->EnablePause(true);
			vfdController->EnableRepeat(true);
			vfdController->EnableAll(true);
			vfdController->EnableColon1st(true);
			vfdController->EnableColon2nd(true);

			vfdController->ShowSpinner(0, 100);
		}
		else
		{
			vfdController->ClearScreen();
		}

		delay(3000000);
	}
}

// Blinks LED
void ShowLEDDemo(D16312* vfdController)
{
	for (uint8_t i = 0; i < 7; ++i)
	{
		vfdController->EnableLED(1, (i % 2 == 0));
		delay(3000000);
	}
}

// Dynamically changes brightness
void ShowBrightnessDemo(D16312* vfdController)
{
	ShowTextDemo(vfdController);
	for (int8_t i = 7; i >= 0; --i)
	{
		vfdController->SetBrightness(i);
		delay(300000);
	}
	for (uint8_t i = 0; i < 8; ++i)
	{
		vfdController->SetBrightness(i);
		delay(300000);
	}
}
