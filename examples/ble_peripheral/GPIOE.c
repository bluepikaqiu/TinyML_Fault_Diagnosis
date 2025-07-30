#include "nrf52840.h"
#include "nrf_gpio.h"
#include "GPIOE.h"


void GPIOE_TASK_Init(void)
{
	NVIC_EnableIRQ(GPIOTE_IRQn);
	NRF_GPIOTE->CONFIG[0] = (GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos)
													| (LED_0 << GPIOTE_CONFIG_PSEL_Pos)
													| (GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos);
	NRF_GPIOTE->CONFIG[1] = (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos)
													| (LED_1 << GPIOTE_CONFIG_PSEL_Pos)
													| (GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos);
}