#line 1 "/Users/nitkonitkic/Documents/Code/Weather_Station_And_Clock/Helpers.h"
#include "OLED-Display-SOLDERED.h"
#include <EEPROM.h>

#pragma once

void drawPolarLine(OLED_Display &display, int x, int y, float phi, int from, int to, float a = 1.0f, float b = 1.0f)
{
    int x1 = x + (int)(cos(phi) * a * (float)from);
    int y1 = y + (int)(sin(phi) * b * (float)from);
    int x2 = x + (int)(cos(phi) * a * (float)to);
    int y2 = y + (int)(sin(phi) * b * (float)to);

    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
}

void resetText(OLED_Display &display)
{
    display.setFont();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setTextWrap(true);
}

uint8_t pattern[8] = {
    0b10001000,
    0b00000000,
    0b00100010,
    0b00000000,
    0b10001000,
    0b00000000,
    0b00100010,
    0b00000000,
};

const char week_0[] = "Sun";
const char week_1[] = "Mon";
const char week_2[] = "Tue";
const char week_3[] = "Wed";
const char week_4[] = "Thu";
const char week_5[] = "Fri";
const char week_6[] = "Sat";

const char *weekDays[] = {
    week_0,
    week_1,
    week_2,
    week_3,
    week_4,
    week_5,
    week_6,
};

void setTimeZone(uint8_t timeZone)
{
    uint32_t flag = 0xABCDEFED;
    int address = 0;

    EEPROM.put(address, flag);
    address += sizeof(flag);

    EEPROM.put(address, timeZone);

    EEPROM.commit();
}

int getTimeZone()
{
    uint32_t flag;
    int address = 0;

    EEPROM.get(address, flag);
    address += sizeof(flag);

    if (flag == 0xABCDEFED)
    {
        uint8_t r;
        EEPROM.get(address, r);
        return r;
    }

    setTimeZone(0);
    return 0;
}