/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/********************************************************************************
 * @file     dwin_lcd.h
 * @author   LEO / Creality3D
 * @date     2019/07/18
 * @version  2.0.1
 * @brief    迪文屏控制操作函数
 ********************************************************************************/

#include <stdint.h>
#include "../common/dwin_api.h"

#define RECEIVED_NO_DATA         0x00
#define RECEIVED_SHAKE_HAND_ACK  0x01

#define FHONE                    0xAA

#define DWIN_SCROLL_UP   2
#define DWIN_SCROLL_DOWN 3

#define DWIN_WIDTH  272
#define DWIN_HEIGHT 480

/*-------------------------------------- System variable function --------------------------------------*/

// Common DWIN startup
void DWIN_Startup(void);

/*---------------------------------------- Drawing functions ----------------------------------------*/

//Color: color
//x: upper left point
//y: bottom right point
void DWIN_Draw_DegreeSymbol(uint16_t Color, uint16_t x, uint16_t y);

void DWIN_Save_JPEG_in_SRAM(uint8_t *data, uint16_t size, uint16_t dest_addr);

void DWIN_SRAM_Memory_Icon_Display(uint16_t x, uint16_t y, uint16_t source_addr); 

/*---------------------------------------- Text related functions ----------------------------------------*/

// Draw a string
//  widthAdjust: true=self-adjust character width; false=no adjustment
//  bShow: true=display background color; false=don't display background color
//  size: Font size
//  color: Character color
//  bColor: Background color
//  x/y: Upper-left coordinate of the string
//  *string: The string
void DWIN_Draw_String(bool widthAdjust, bool bShow, uint8_t size,
                      uint16_t color, uint16_t bColor, uint16_t x, uint16_t y, const char * string);

class __FlashStringHelper;

inline void DWIN_Draw_String(bool widthAdjust, bool bShow, uint8_t size, uint16_t color, uint16_t bColor, uint16_t x, uint16_t y, const __FlashStringHelper *title) {
  // Note that this won't work on AVR. This is for 32-bit systems only!
  // Are __FlashStringHelper versions worth keeping?
  DWIN_Draw_String(widthAdjust, bShow, size, color, bColor, x, y, reinterpret_cast<const char*>(title));
}

// Draw a floating point number
//  bShow: true=display background color; false=don't display background color
//  zeroFill: true=zero fill; false=no zero fill
//  zeroMode: 1=leading 0 displayed as 0; 0=leading 0 displayed as a space
//  size: Font size
//  color: Character color
//  bColor: Background color
//  iNum: Number of whole digits
//  fNum: Number of decimal digits
//  x/y: Upper-left point
//  value: Long value
void DWIN_Draw_FloatValue(uint8_t bShow, bool zeroFill, uint8_t zeroMode, uint8_t size, uint16_t color,
                          uint16_t bColor, uint8_t iNum, uint8_t fNum, uint16_t x, uint16_t y, long value);

/*---------------------------------------- Picture related functions ----------------------------------------*/

// Draw an Icon
//  libID: Icon library ID
//  picID: Icon ID
//  x/y: Upper-left point
void DWIN_ICON_Show(uint8_t libID, uint8_t picID, uint16_t x, uint16_t y);

// Copy area from virtual display area to current screen
//  cacheID: virtual area number
//  xStart/yStart: Upper-left of virtual area
//  xEnd/yEnd: Lower-right of virtual area
//  x/y: Screen paste point
void DWIN_Frame_AreaCopy(uint8_t cacheID, uint16_t xStart, uint16_t yStart,
                         uint16_t xEnd, uint16_t yEnd, uint16_t x, uint16_t y);