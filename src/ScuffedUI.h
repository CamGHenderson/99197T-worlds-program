#pragma once

#include <stdint.h>

#define NONE 0

#define RED 1
#define BLUE 2

#define UI_CLOSE_AUTO 1
#define UI_FAR_AUTO 2
#define UI_AUTO_SKILLS 3

void displayTest();
void displayAutoMenu();
uint16_t getUISelection();
uint8_t getUIColor();
