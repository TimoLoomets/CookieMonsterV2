/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
* and associated documentation files (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, publish, distribute, 
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all copies or 
* substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef CORE_TEENSY4X_CORE_H_
#define CORE_TEENSY4X_CORE_H_

#include "arm_math.h"
#include "avr_emulation.h"
#include "avr_functions.h"
#include "core_cmInstr.h"
#include "core_pins.h"
#include "DMAChannel.h"
#include "eeprom.h"
#include "elapsedMillis.h"
#include "HardwareSerial.h"
#include "IntervalTimer.h"
#include "imxrt.h"
#include "pgmspace.h"
#include "pins_arduino.h"
#include "Print.h"
#include "printf.h"
#include "Stream.h"
#include "usb_desc.h"
#include "usb_dev.h"
#include "usb_names.h"
#include "usb_serial.h"
#include "EEPROMclass.h"
#include "SPI.h"
#include "WireIMXRT.h"
#include "micros64.h"
#include "bits.h"

#define interrupts() __enable_irq()
#define noInterrupts() __disable_irq()

#endif // CORE_TEENSY3X_CORE_H_
