/*
 *  Created on: Jul 27, 2014
 *      Author: yev
 */

#ifndef D16312_H_
#define D16312_H_

#include "D16312Defs.h"

class D16312
{
public:
	D16312(uint32_t port, uint32_t dataBit, uint32_t clkBit, uint32_t stbBit);
	~D16312();

	// General
	void EnableDispay(bool value);
	bool IsDisplayEnabled() const;
	void SetBrightness(uint8_t brightness);
	uint8_t GetBrightness() const;

	// VFD
	void ClearScreen();
	void WriteChar(char letter, uint8_t pos);
	void EnableMP3(bool value);
	void EnablePBC(bool value);
	void EnableCamera(bool value);
	void EnableDolby(bool value);
	void EnableCD(bool value);
	void EnableVCD(bool value);
	void EnableSVCD(bool value);
	void EnableDTS(bool value);
	void EnableDVD(bool value);
	void EnablePlay(bool value);
	void EnablePause(bool value);
	void EnableAll(bool value);
	void EnableRepeat(bool value);
	void EnableColon1st(bool value);
	void EnableColon2nd(bool value);
	void ShowSpinner(uint8_t startPercent = 0, uint8_t stopPercent = 100);
	// LED
	void EnableLED(uint8_t ledPos, bool value);
	// Key
	uint8_t ReadKey();

private:
	void BeginCommand(uint8_t cmd, bool isSingle = false);
	void EndCommand();
	void WriteData(uint8_t data);
	uint8_t ReadData();
	void Clock();


	void Delay(int32_t ticks);
	void SetBit(uint8_t& byte, uint8_t bitPos, bool value);

private:
	static const uint8_t s_StartAddr;
	static const uint8_t s_EndAddr;
	static const uint8_t s_DisplCmd;
	static const uint8_t s_LEDCmd;
	static const uint8_t s_KeyCmd;
	static const uint8_t s_MaxBrightness;

	uint32_t m_Port;
	uint32_t m_DataBit;
	uint32_t m_ClkBit;
	uint32_t m_StbBit;

	bool m_IsEnabled;
	uint8_t m_Brightness;

	uint8_t m_BufferVFD[11];
	uint8_t m_BufferLED;
};


#endif /* D16312_H_ */
