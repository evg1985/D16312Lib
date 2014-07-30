================================================================================
NEC D16312 VFD controller display library for LPCXpresso board
--------------------------------------------------------------------------------
A small library that allow to connect LPCXpresso board with D16312 NEC VFD 
display controller and manipulate it. In particular, it was tested with display 
from Daewoo DV-500 DVD player

Supporting features:
- Show text
- Enable/disable special signs
- Animate spinner
- Enable/disable LED
- Read keys

================================================================================
Usage
--------------------------------------------------------------------------------
- Install LPCXpresso ide
- Switch workspace to a project location and build D16312Lib

The project has already consist LPC11xx_cmsis2_Lib and CMSIS_CORE_LPC11xx 
libraries for LPC11xx microcontrollers inside the workspace. If you want to use 
another microcontroller you have to use appropriate libraries versions

D16312Demo.cpp source contain examples of use this library with lpc1114
controller

================================================================================
The MIT License
--------------------------------------------------------------------------------
Copyright (c) 2014 Yevgeniy Logachev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.