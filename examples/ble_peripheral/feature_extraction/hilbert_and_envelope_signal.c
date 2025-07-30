#include "stdio.h"
#include "stdlib.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "nrf_delay.h"
#include "FFT_instance.h"
#include "hilbert_and_envelope_signal.h"

/**
  * @brief  Perform Hilbert transform on the acc signal to obtain envelope signal and the amplitude spectrum of the envelope signal
  * @param  
  * @retval 0
  */
float32_t* Hilbert_and_envelope_signal(const float32_t *signal)
{
	uint16_t i = 0;	
	float32_t c_input[2 * FFT_LEN];
	float32_t system_matrix[2 * FFT_LEN];
	static float32_t output[FFT_LEN];
	
	for (i = 0; i < FFT_LEN; i++)
	{
		c_input[i*2] = signal[i];
		c_input[i*2+1] = 0;
	}
	
	//arm_cfft_instance_f32 S;
	//arm_cfft_init_f32(&S, FFT_LEN); // Max:FFT_LEN
	const arm_cfft_instance_f32 *fftConfig = &arm_cfft_sR_f32_len1024;
	arm_cfft_f32(fftConfig, &c_input[0], 0, 1); // CFFT transform
	
	// Generate the frequency-domain representation of the Hilbert transform
	system_matrix[0] = 0; // DC component
	for (i = 1; i < FFT_LEN; i++)
	{
		system_matrix[i] = 2; // Positive frequency
	}
	for (i = FFT_LEN; i < 2 * FFT_LEN; i++)
	{
		system_matrix[i] = 0; // Negative frequency
	}
	
	// Obtain analytic signal to get envelope signal
	for (i = 0; i < 2 * FFT_LEN; i++)
	{
		system_matrix[i] = system_matrix[i] * c_input[i]; // Negative frequency
	}
	
	arm_cfft_f32(fftConfig, &system_matrix[0], 1, 1); // ICFFT transform
	arm_cmplx_mag_f32((const float32_t *)&system_matrix[0], &output[0], FFT_LEN);
	
	/*
	for(i = 0; i < FFT_LEN; i++)
	{
		//printf("Envelope Output: %f \n", output[i]);
		if (i%256 == 0)
		{
			printf("\n");
			nrf_delay_ms(25);		
		}
		printf("%f ", output[i]);
		nrf_delay_ms(25);
	}
	*/
	
	return output;
}