#include "stdio.h"
#include "stdlib.h"
#include "arm_math.h"
#include "nrf_delay.h"
#include "FFT_instance.h"
#include "filtering_preprocessing.h"

#define BLOCK_SIZE 1 // Number of sampling points processed by a call to arm_biquad_cascade_df1_f32
#define num_stages 2 // Number of second-order filters

uint32_t blocksize = BLOCK_SIZE;
uint32_t numBlocks = FFT_LEN/BLOCK_SIZE;
float32_t IIR_StateCache[4 * num_stages]; // Status cache

const float32_t IIR_Coeffs_4_order_butterworth[5 * num_stages] = {
1.0f, -2.0f, 1.0f, 1.990271241661728529592778613732662051916f, -0.990428397520601744297152890794677659869f,
1.0f, -2.0f, 1.0f, 1.976891354287120039501246537838596850634f, -0.977047453642915675331437341810669749975f	
}; // The high-pass filter coefficient is obtained from the C language header file using MATLAB FADTOOL, and remember a1 and a2 are inverse

/**
 * @brief IIR_butterworth_high_pass_4_order
 * @param 
 * @retval  
 */
float32_t* IIR_butterworth_high_pass_4_order(float32_t *IIR_Filter_input, const float32_t *coeff)
{
  uint32_t i;
  arm_biquad_casd_df1_inst_f32 S;
	float32_t scale_values;
	static float32_t IIR_Filter_Output[FFT_LEN]; // Filtered output
	
  // Initialize structure S
  arm_biquad_cascade_df1_init_f32(&S, num_stages, &coeff[0], &IIR_StateCache[0]);

  // Implement FIR filtering, processing 1 point at a time
  for (i = 0; i < numBlocks; i++)
  {
    arm_biquad_cascade_df1_f32(&S, IIR_Filter_input + (i * blocksize), IIR_Filter_Output + (i * blocksize), blocksize);
  }
	
	scale_values = 0.995174909795582540716907260502921417356 * 0.988484701982508928708170969912316650152; // By MATLAB
  
	for (i = 0; i < FFT_LEN; i++)
  {
    IIR_Filter_Output[i] *= scale_values;
  }

	return IIR_Filter_Output;
}
			
/**
 * @brief data_preprocess
 * @param 
 * @retval
 */
float32_t* data_preprocess(const float32_t *signal)
{
	uint16_t i = 0;
	float32_t rcc_mean_result;
	float32_t input_remove_trend[FFT_LEN];
	// static float32_t output_after_filtering[FFT_LEN];
	
	// Remove trend
	arm_mean_f32(&signal[0], FFT_LEN, &rcc_mean_result);
	for (i = 0; i < FFT_LEN; i++)
	{
		input_remove_trend[i] = signal[i];
		input_remove_trend[i] -= rcc_mean_result;
	}
	
	float32_t *output_after_filtering = IIR_butterworth_high_pass_4_order(input_remove_trend, IIR_Coeffs_4_order_butterworth);
	
	/*
	for(i = 0; i < FFT_LEN; i++)
	{
		//printf("output_after_filtering: %f \n", output_after_filtering[i]);
		if (i%256 == 0)
		{
			printf("\n");
			nrf_delay_ms(25);		
		}
		printf("%f ", output_after_filtering[i]);
		nrf_delay_ms(25);
	}
	*/
	
	return output_after_filtering;
}