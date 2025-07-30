#include "nrf52840.h"
#include "nrf_gpio.h"
#include "led.h"
#include "exit.h"

void Delay(uint32_t temp)
{
	for(; temp != 0;)
	{
		temp--;
	}
}

void KEY_Init(void)
{
	nrf_gpio_cfg_input(11, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(12, NRF_GPIO_PIN_PULLUP);
}

void EXIT_KEY_Init(void)
{
	KEY_Init();
	
	NVIC_EnableIRQ(GPIOTE_IRQn);
	
	NRF_GPIOTE->CONFIG[0] =  (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos)
                           | (11 << GPIOTE_CONFIG_PSEL_Pos)  
                           | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);
	NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN0_Set << GPIOTE_INTENSET_IN0_Pos;
	NRF_GPIOTE->CONFIG[1] = (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos)
													 | (12 << GPIOTE_CONFIG_PSEL_Pos)
													 | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);
	NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN1_Set << GPIOTE_INTENSET_IN1_Pos;
}

void GPIOTE_IRQHandler(void)
{
	if(nrf_gpio_pin_read(KEY_1) == 0)
	{
		if((NRF_GPIOTE->EVENTS_IN[0] == 1) &&
			(NRF_GPIOTE->INTENSET & GPIOTE_INTENCLR_IN0_Msk))
		{
			NRF_GPIOTE->EVENTS_IN[0] = 0;
			Delay(1000);
			LED1_Toggle();
		}
	}
	if(nrf_gpio_pin_read(KEY_2) == 0)
	{
		if((NRF_GPIOTE->EVENTS_IN[1] == 1) &&
			(NRF_GPIOTE->INTENSET & GPIOTE_INTENCLR_IN1_Msk))
		{
			NRF_GPIOTE->EVENTS_IN[1] = 0;
			Delay(1000);
			LED2_Toggle();
		}
	}
}
