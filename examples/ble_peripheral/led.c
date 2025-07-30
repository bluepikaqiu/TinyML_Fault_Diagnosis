#include "nrf52840.h"
#include "nrf_gpio.h"
#include "pca10056.h"
#include "led.h"


void BEEP_Init(void)
{
    //Configure BEEP to drive GPIO
    nrf_gpio_cfg_output(BEEP);
	
}

void BEEP_Open(void)
{
    nrf_gpio_pin_set(BEEP);
}

void BEEP_Close(void)
{
    nrf_gpio_pin_clear(BEEP);
}

void LED_Init(void)
{
  // Configure LED-pins as outputs
  nrf_gpio_cfg_output(LED_1);
  nrf_gpio_cfg_output(LED_2);
  nrf_gpio_cfg_output(LED_3);
  nrf_gpio_cfg_output(LED_4);
  LED1_Close();
  LED2_Close();
  LED3_Close();
  LED4_Close();
}

void LED1_Open(void)
{
  nrf_gpio_pin_clear(LED_1);
}

void LED1_Close(void)
{
  nrf_gpio_pin_set(LED_1);	
}

void LED1_Toggle(void)
{
  nrf_gpio_pin_toggle(LED_1);
}

void LED2_Open(void)
{
  nrf_gpio_pin_clear(LED_2);
}

void LED2_Close(void)
{
  nrf_gpio_pin_set(LED_2);	
}

void LED2_Toggle(void)
{
  nrf_gpio_pin_toggle(LED_2);
}

void LED3_Open(void)
{
  nrf_gpio_pin_clear(LED_3);
}

void LED3_Close(void)
{
  nrf_gpio_pin_set(LED_3);
}

void LED3_Toggle(void)
{
  nrf_gpio_pin_toggle(LED_3);
}

void LED4_Open(void)
{
  nrf_gpio_pin_clear(LED_4);
}

void LED4_Close(void)
{
  nrf_gpio_pin_set(LED_4);
}

void LED4_Toggle(void)
{
  nrf_gpio_pin_toggle(LED_4);
}
