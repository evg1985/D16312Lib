/*
 *  Created on: Jul 27, 2014
 *      Author: yev
 */

#include "D16312.h"
#include <string.h>

const uint8_t D16312::s_StartAddr 		= 0xC0;
const uint8_t D16312::s_EndAddr 		= 0xCC;
const uint8_t D16312::s_DisplCmd 		= 0x44;	// Fixed address
const uint8_t D16312::s_LEDCmd 			= 0x45;
const uint8_t D16312::s_KeyCmd 			= 0x42;
const uint8_t D16312::s_MaxBrightness 	= 0x07;

D16312::D16312(uint32_t port, uint32_t dataBit, uint32_t clkBit, uint32_t stbBit)
: m_Port(port)
, m_DataBit(dataBit)
, m_ClkBit(clkBit)
, m_StbBit(stbBit)
, m_IsEnabled(false)
, m_Brightness(s_MaxBrightness)
{
	GPIOSetDir(m_Port, m_ClkBit, 1);
	GPIOSetDir(m_Port, m_StbBit, 1);
	GPIOSetDir(m_Port, m_DataBit, 1);

	memset(m_BufferVFD, 0, sizeof(m_BufferVFD));
	m_BufferLED = 0;
}

D16312::~D16312()
{
	GPIOSetDir(m_Port, m_ClkBit, 0);
	GPIOSetDir(m_Port, m_StbBit, 0);
	GPIOSetDir(m_Port, m_DataBit, 0);
}

void D16312::EnableDispay(bool value)
{
	m_IsEnabled = value;

	SetBrightness(m_Brightness);
}

bool D16312::IsDisplayEnabled() const
{
	return m_IsEnabled;
}

void D16312::SetBrightness(uint8_t brightness)
{
	if (brightness <= s_MaxBrightness)
	{
		m_Brightness = brightness;
	}

	uint8_t data = 0x80 | (0x07 & m_Brightness);
	SetBit(data, 3, m_IsEnabled);

	BeginCommand(data, true);
}

uint8_t D16312::GetBrightness() const
{
	return m_Brightness;
}

void D16312::ClearScreen()
{
	for (uint8_t i = s_StartAddr; i <= s_EndAddr; ++i)
	{
		BeginCommand(s_DisplCmd, true);
		BeginCommand(i);
		WriteData(0x00);
		EndCommand();

		memset(m_BufferVFD, 0, sizeof(m_BufferVFD));
	}
}

void D16312::WriteChar(char chr, uint8_t pos)
{
	if (pos > 6 || chr > 127)
	{
		return;
	}

	uint8_t decodedChar = D16312Chars[(uint8_t)chr];
	uint8_t realPos = 6 - pos;
	uint8_t addr = s_StartAddr + realPos;
	// We need this hack because 7th bit of 0xC0 character respond for first sign of 0xC1 char
	if (pos == 5)
	{
		m_BufferVFD[0] = (decodedChar & 0x01) ? (m_BufferVFD[0] | 0x80) : (m_BufferVFD[0] & 0x7F);
		decodedChar >>= 1;
		m_BufferVFD[realPos] = decodedChar;
	}
	else
	{
		m_BufferVFD[realPos] = (decodedChar & 0x7F) | (m_BufferVFD[realPos] & 0x80);
	}

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(m_BufferVFD[realPos]);
	EndCommand();
}

void D16312::EnableMP3(bool value)
{
	uint8_t pos = 1;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 6, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}


void D16312::EnablePBC(bool value)
{
	uint8_t pos = 1;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 7, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableCamera(bool value)
{
	uint8_t pos = 3;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 7, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableDolby(bool value)
{
	uint8_t pos = 5;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 7, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableCD(bool value)
{
	uint8_t pos = 7;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 4, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableVCD(bool value)
{
	uint8_t pos = 7;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 5, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableSVCD(bool value)
{
	uint8_t pos = 7;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 6, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableDTS(bool value)
{
	uint8_t pos = 7;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 7, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableDVD(bool value)
{
	uint8_t pos = 9;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 7, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnablePlay(bool value)
{
	uint8_t pos = 7;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 3, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnablePause(bool value)
{
	uint8_t pos = 7;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 2, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableAll(bool value)
{
	uint8_t pos = 7;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 1, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableRepeat(bool value)
{
	uint8_t pos = 7;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 0, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableColon1st(bool value)
{
	uint8_t pos = 2;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 7, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::EnableColon2nd(bool value)
{
	uint8_t pos = 4;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& data = m_BufferVFD[pos];

	SetBit(data, 7, value);

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(data);
	EndCommand();
}

void D16312::ShowSpinner(uint8_t startPercent, uint8_t stopPercent)
{
	if (stopPercent < startPercent)
	{
		return;
	}

	// Spinner use 15 segments, 16th uses for DVD sign
	uint8_t startBit = (int)(startPercent * 15 / 100.0f);
	uint8_t stopBit = (int)(stopPercent * 15 / 100.0f);

	uint8_t pos = 8;
	uint8_t addr = s_StartAddr + pos;
	uint8_t& left = m_BufferVFD[pos];

	left = 0;
	uint8_t size =  (stopBit < 8) ? stopBit : 8;
	for (int8_t i = startBit; i < size; ++i)
	{
		SetBit(left, i, true);
	}

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(left);
	EndCommand();

	pos = 9;
	addr = s_StartAddr + pos;
	uint8_t& right = m_BufferVFD[pos];

	right = 0;
	size = (stopBit < 8) ? 0 : stopBit - 8;
	for (int8_t i = 0; i < size; ++i)
	{
		SetBit(right, i, true);
	}

	BeginCommand(s_DisplCmd, true);
	BeginCommand(addr);
	WriteData(right);
	EndCommand();
}

void D16312::EnableLED(uint8_t ledPos, bool value)
{
	if (ledPos >= 0x10)
	{
		return;
	}

	SetBit(m_BufferLED, ledPos, value);

	BeginCommand(s_LEDCmd);
	WriteData(m_BufferLED);
	EndCommand();
}

uint8_t D16312::ReadKey()
{
	// Disable display for scanning keys
	bool isEnabled = IsDisplayEnabled();
	EnableDispay(false);

	BeginCommand(s_KeyCmd);
	uint8_t value = ReadData();
	EndCommand();

	// Scanning finished, restore previous state
	EnableDispay(isEnabled);

	return value;
}

void D16312::BeginCommand(uint8_t cmd, bool isSingle)
{
	GPIOSetValue(m_Port, m_ClkBit, 1);
	GPIOSetValue(m_Port, m_StbBit, 0);
	Delay(10);

	WriteData(cmd);

	if (isSingle)
	{
		EndCommand();
	}
}

void D16312::EndCommand()
{
	GPIOSetValue(m_Port, m_ClkBit, 1);
	GPIOSetValue(m_Port, m_StbBit, 1);
	Delay(10);
}

void D16312::WriteData(uint8_t data)
{
	GPIOSetDir(m_Port, m_DataBit, 1);

	for (uint8_t i = 0; i < 8; ++i)
	{
		bool isSet = (data & 0x01);
		GPIOSetValue(m_Port, m_DataBit, (int)isSet);

		Clock();

		data = data >> 1;
	}
}

uint8_t D16312::ReadData()
{
	GPIOSetDir(m_Port, m_DataBit, 0);

	uint8_t data = 0;
	for (uint8_t i = 0; i < 8; ++i)
	{
		Clock();

		bool isSet = 0;
		switch (m_Port)
		{
		case PORT0:
			isSet = (LPC_GPIO0->DATA & (1 << m_DataBit));
		break;
		case PORT1:
			isSet = (LPC_GPIO1->DATA & (1 << m_DataBit));
		break;
		case PORT2:
			isSet = (LPC_GPIO2->DATA & (1 << m_DataBit));
		break;
		case PORT3:
			isSet = (LPC_GPIO3->DATA & (1 << m_DataBit));
		break;
		default:
			break;
		}

		SetBit(data, i, isSet);
	}

	return data;
}

void D16312::Clock()
{
	Delay(10);
	GPIOSetValue(m_Port, m_ClkBit, 0);
	Delay(10);
	GPIOSetValue(m_Port, m_ClkBit, 1);
}

void D16312::Delay(int32_t ticks)
{
	volatile int32_t i = ticks;
	while(i--);
}

void D16312::SetBit(uint8_t& byte, uint8_t bitPos, bool value)
{
	if (value)
	{
		byte |= (1 << bitPos);
	}
	else
	{
		byte &= ~(1 << bitPos);
	}
}
