#include "stdio.h"
#include "stdlib.h"
#include "arm_math.h"
#include "nrf_delay.h"
#include "FFT_instance.h"
#include "integration.h"

/**
 * @brief time_integration
 * @param 
 * @retval  
 */
float32_t* time_integration(const float32_t *signal)
{
	uint16_t i = 0;
	float32_t ts = 1.0f/SMPLE_FRQ; // Sampling period
	float32_t mean_result;
	static float32_t t_integral_output[FFT_LEN];
	
  // Trapezoidal value quadrature formula, it should be noted that if multiple segments of data are passed separately, there is a high probability that the subsequent velocity is not accurate, because the initial velocity is not 0 at this time
  t_integral_output[0] = 0;
	for (i = 1; i <= FFT_LEN - 1; i++)
  {
    t_integral_output[i] = t_integral_output[i-1] + (ts/2.0f) * (signal[i-1] + signal[i]); 
  }
	
	// Remove trend
	arm_mean_f32(&t_integral_output[0], FFT_LEN, &mean_result);
	for (i = 0; i < FFT_LEN; i++)
	{
		t_integral_output[i] -= mean_result;
		t_integral_output[i] = t_integral_output[i] * 1000; // Convert m/s to mm/s
	}
	
	/*
	for(i = 0; i < FFT_LEN; i++)
	{
		//printf("t_integral_output: %f \n", t_integral_output[i]);
		if (i%256 == 0)
		{
			printf("\n");
			nrf_delay_ms(25);		
		}
		printf("%f ", t_integral_output[i]);
		nrf_delay_ms(25);
	}
	*/
	
	return t_integral_output;
}