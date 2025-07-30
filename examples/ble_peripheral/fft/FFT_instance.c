#include "stdio.h"
#include "stdlib.h"
#include "arm_math.h"
#include "dsp/window_functions.h"
#include "nrf_delay.h"
#include "FFT_instance.h"
#include "raw_rcc_data_x_pre_process.h"

float32_t time_domain_input[FFT_LEN], frequency_domain_output[FFT_LEN];
float32_t Mag[FFT_LEN/2]; // magnitude 2/N
float32_t Phase[FFT_LEN/2]; // phase 2/N
//float32_t Mag_N[FFT_LEN/2]; // magnitude N
//float32_t Phase_N[FFT_LEN/2]; // phase N

/**
 * @brief reverse
 * @param a[] len
 * @retval 
 */
void reverse(float32_t a[], int len)
{
    int left = 0;
    int right = len - 1;
    float32_t b;
    while (left < right)
    {
            b = a[right];
            a[right] = a[left];
            a[left] = b;
            left++;
            right--;
    }
}

/**
 * @brief PowerMag 
 * @param _usFFTPoints FFT
 * @retval 
 */
//void PowerMag(uint16_t _usFFTPoints)
//{
//  int16_t x, y;
//  uint16_t i;
//  float32_t mag;

//  // 
//  for (i = 0; i < _usFFTPoints; i++)
//  {
//    // Small-endian mode: The high 16 bits store the virtual part and the low 16 bits store the real part
//    x = (frequency_domain_output[i] << 16) >> 16; // real component
//    y = (frequency_domain_output[i] >> 16); // imaginary part
//    arm_sqrt_f32((float32_t)(x*x + y*y), &mag); // amplitude
//    Mag[i] = mag*2; // The actual modulus value is multiplied by 2 after modulo, and the DC component does not need to be multiplied by 2
//  }
//  // Since we're multiplying by 2, we're going to divide the DC component by 2
//  Mag[0] = Mag[0] >> 1;
//}

/**
 * @brief Power_Phase_Radians 
 * @param _usFFTPoints FFT
 * @retval 
 */
void Power_Phase_Radians(uint16_t _usFFTPoints)
{
    uint16_t i, j;
    float32_t x, y;
    float32_t phase;
    float32_t mag;
	
    i = 0;
    j = 0;
    for (; i < _usFFTPoints; )
    {
  //    x = (frequency_domain_output[i] << 16) >> 16; // real component
  //    y = (frequency_domain_output[i] >> 16); // imaginary part
      x = frequency_domain_output[i];
      y = frequency_domain_output[i+1];
      phase = atan2(y,x); // The range of results is (-pi, pi] in radians
      Phase[j] = phase * 180.0f/3.1415926f; // Convert radians to angles

      i+=2;
      j++;
    }
}

/**
  * @brief  fft_example FFT
  * @param  
  * @retval 0
  */
void fft_example(const float *signal)
{	
    uint16_t i, flag;
		float32_t hanning_result[FFT_LEN];
		arm_hanning_f32(&hanning_result[0], FFT_LEN);
    for(i = 0; i < FFT_LEN; i++)
    {
      time_domain_input[i] = signal[i];
			time_domain_input[i] = time_domain_input[i] * hanning_result[i];
    }
  	//For integer FFT
      // Calculate (FFT_LEN/2)-point FF
      // output: Indicates the output result. The higher 16 bits are the imaginary part and the lower 16 bits are the real part
      // input: indicates the input data. The upper 16 bits are the imaginary part and the lower 16 bits are the real part
      // The third parameter must be FFT_LEN/2
      // cr4_fft_1024_stm32(frequency_domain_output, time_domain_input, FFT_LEN/2);

  	  // amplitude
      // PowerMag(8000);

      // Phase frequency determination
      // Power_Phase_Radians(8000);
	
  	//For float FFT
  	arm_rfft_fast_instance_f32 S;
  	arm_rfft_fast_init_f32(&S, FFT_LEN); //Max:FFT_LEN
  	//0 means positive transformation
  	arm_rfft_fast_f32(&S, time_domain_input, frequency_domain_output, 0);
		//amplitude and normalized FFT
		for(i = 0; i < FFT_LEN; i++)
		{
			frequency_domain_output[i] = frequency_domain_output[i] / (float32_t)(FFT_LEN / 2);
		}
  	arm_cmplx_mag_f32(frequency_domain_output, Mag, FFT_LEN/2); //{real,imaginary},half frequency domain
		Mag[0] = 0; //eliminate DC component bias
		// real amplitude
		for (i = 1; i < FFT_LEN/2; i++)
		{
			Mag[i] *= 2;
		}
		
  	Power_Phase_Radians(FFT_LEN);	
	
    // USART  115200 8-N-1
    // Debug_USART_Config();
/*
  	//Extend the N/2 spectrum into N
  	float32_t mag_temp[FFT_LEN/2];
  	float32_t phase_temp[FFT_LEN/2];
  	for (i = 0; i < FFT_LEN/2; i++)
  	{
  		mag_temp[i] = Mag[i];
  		phase_temp[i] = Phase[i];
  	}
  	reverse(Mag, sizeof(Mag) / sizeof(Mag[0]));
  	reverse(Phase, sizeof(Phase) / sizeof(Phase[0]));
	
  	flag = 0;
  	for (i = 0; i < (sizeof(mag_temp)/sizeof(mag_temp[0])); i++)
  	{
  		Mag_N[flag] = mag_temp[i];
  		flag++;
  	}
  	for (i = 0; i < (sizeof(Mag)/sizeof(Mag[0])); i++)
  	{
  		Mag_N[flag] = Mag[i];
  		flag++;
  	}
  	flag = 0;
  	for (i = 0; i < (sizeof(phase_temp)/sizeof(phase_temp[0])); i++)
  	{
  		Phase_N[flag] = phase_temp[i];
  		flag++;
  	}
  	for (i = 0; i < (sizeof(Phase)/sizeof(Phase[0])); i++)
  	{
  		Phase_N[flag] = Phase[i];
  		flag++;
  	}
	
  //	printf("Print the magnitude and the phase!\n");
  //	for (i = 0; i < FFT_LEN; i++)
  //  {
  //    printf("%f %f\r\n", Mag_N[i], Phase_N[i]);
  //		nrf_delay_ms(50);
  //  }
*/
}