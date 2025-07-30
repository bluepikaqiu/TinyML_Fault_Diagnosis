#ifndef __KEY_H
#define __KEY_H

#include "nrf52840.h"
#include "nrf_gpio.h"

#define KEY_1 NRF_GPIO_PIN_MAP(0,11)
#define KEY_2 NRF_GPIO_PIN_MAP(0,12)
#define KEY_3 NRF_GPIO_PIN_MAP(0,24)
#define KEY_4 NRF_GPIO_PIN_MAP(0,25)
#define TCH   NRF_GPIO_PIN_MAP(0,26)

void KEY_Init(void);
uint8_t KEY1_Down(void);
uint8_t KEY2_Down(void);
uint8_t KEY3_Down(void);
uint8_t KEY4_Down(void);
uint8_t TCH_Down(void);

#endif
