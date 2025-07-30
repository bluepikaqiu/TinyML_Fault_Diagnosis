#ifndef __EXIT__H
#define __EXIT__H

#include "nrf52840.h"
#define KEY_1 NRF_GPIO_PIN_MAP(0,11)
#define KEY_2 NRF_GPIO_PIN_MAP(0,12)

void EXIT_KEY_Init(void);

#endif
