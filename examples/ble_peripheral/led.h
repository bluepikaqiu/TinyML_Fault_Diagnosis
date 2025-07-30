#ifndef __LED_H
#define	__LED_H

#include "nrf52840.h"


#define BEEP           NRF_GPIO_PIN_MAP(0,27)


#ifdef __cplusplus
extern "C" {
#endif

void BEEP_Init(void);
void BEEP_Open(void);
void BEEP_Close(void);
void LED_Init(void);
void LED1_Open(void);
void LED1_Close(void);
void LED1_Toggle(void);
void LED2_Open(void);
void LED2_Close(void);
void LED2_Toggle(void);
void LED3_Open(void);
void LED3_Close(void);
void LED3_Toggle(void);
void LED4_Open(void);
void LED4_Close(void);
void LED4_Toggle(void);

#ifdef __cplusplus
}
#endif

#endif /* __LED_H */
