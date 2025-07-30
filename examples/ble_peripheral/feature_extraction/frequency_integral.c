/**
 ******************************************************************** 
 *  @filename	First/second integral in frequency domain
 *  @brief Implementation of frequency domain integration
 ********************************************************************
 */

#include "stdio.h"
#include "frequency_integral.h"
#include "nrf_delay.h"
#include "arm_const_structs.h"

float32_t		w_vec[FFT_LEN];	// Frequency vector
float32_t   w_vec_new[FFT_LEN]; // New frequency vector
float32_t 	fft_buf[FFT_LEN];	// Used to store temporary arrays during fft calculations

/** 
 *  @name	Frequency domain first/second integral initialization function
 *  @brief Initializes the structure used to store the function. The following part can be changed according to the actual situation
 *  @pram	len	len The length of the array used for quadratic integration is recommended to be greater than 16 and less than 4096 to the power of 2
 *  @retval	0	success
 *  
 */
void integ_init(uint16_t len)
{
    uint32_t i, j;
    
/* 	integ->frq_min    = FRQ_MIN;								// High-pass filter cut-off frequency
    integ->frq_max    = FRQ_MAX;								// Low-pass filter cut-off frequency (should be less than the sampling frequency)
    if(integ->frq_max>=integ->smple_frq)
            return -2; // The low-pass cutoff frequency cannot be greater than the high-pass filter cutoff frequency */    

    float32_t df = (float32_t)SMPLE_FRQ / (float32_t)FFT_LEN;			// Calculate frequency interval(Hz/s)
/* 	integ->high_pass = round(integ->frq_min/df);						// High-pass frequency cut-off point
    integ->low_pass  = round(integ->frq_max/df);  						// Low pass frequency cutoff point */
    
    float32_t dw = 2*PI*df; // PI's macro is defined in the arm_math.h header file, where dw stands for circular frequency interval (rad/s).
    
    // i = 0 ~ (integ->fft_len)/2 - 1
    for(i = 0; i < FFT_LEN/2; i++)
    {
        w_vec[i] = dw*i;	// Positive discrete circular frequency vector
        w_vec[i] = POW(w_vec[i], INTEG_TIME); // The vector of circular frequency variable is established by taking the number of integrations as exponent
    }
		
		for(i = 0, j = 0; j < FFT_LEN;)
		{
			w_vec_new[j] = w_vec[i];
			w_vec_new[j+1] = w_vec[i];
			i += 1;
			j += 2;
			printf("w_vec_new[%d]: %f\r\n", i, w_vec_new[i]);
			nrf_delay_ms(50);
		}
}

/** 
 *  @name	First/second integral function in frequency domain
 *  @brief	Calculate the first/second integral
 *  @pram	inputbuf	input array 
 *  		  outputbuf	output array (length greater than or equal to the input array and must be 2^(4~12))
 *  @retval	0	
 * 
 */
void frq_domain_integral(float32_t* temp_buffer, float32_t* outputbuf)
{
    uint32_t i;	
		arm_rfft_fast_instance_f32 S;
    // Store in the following order: {real[0],imag[0],real[1],imag[1],......}
		/*
		for(i = 0; i < FFT_LEN; i++){
			       // Generates an FFT array
             //integ->fft_buf[2*i]   = inputbuf[i]; // The real part is the acceleration value
             //integ->fft_buf[2*i+1] = 0; // The imaginary part is 0
    }
		*/
		
    // Cmsis-dsp library single precision FFT calculation
    // The first argument is a encapsulated floating-point FFT instance
    // The second argument is the complex address
    // The third parameter is the positive and inverse transformation, where 0 represents the FFT positive transformation
    // The fourth parameter is to set output bit inversion, with 1 indicating enable.
    arm_rfft_fast_init_f32(&S, FFT_LEN);
		arm_rfft_fast_f32(&S, temp_buffer, fft_buf, 0); // Calculate FFT and save the result in fft_buf

		//cancel the DC trend term
		fft_buf[0] = 0;
		fft_buf[1] = 0;
		fft_buf[FFT_LEN - 2] = 0;
		fft_buf[FFT_LEN - 1] = 0;
    for(i = 2; i < FFT_LEN - 2; i++){
            fft_buf[i] /= w_vec_new[i];
    }
		
    if(INTEG_TIME == 2){
            for(i = 0; i < FFT_LEN; i++){
							      // The integral frequency domain transform and phase transform were done together
                    // The real and imaginary parts of the fft array are divided by the circular frequency transform vector w_vec
                    // The second integral phase transformation is rotated 180 degrees, that is, the real and imaginary parts are added with a negative sign
										fft_buf[i] = -fft_buf[i];
						}
    }
    else{
            float32_t temp1, temp2;
            for(i = 0; i < FFT_LEN / 2; i++){
							      // The first integral phase transformation is rotated 90 degrees counterclockwise
								    // The real part is equal to the imaginary part and the imaginary part is equal to the negative real part
										temp1 = -fft_buf[2*i];							
                    temp2 = fft_buf[2*i+1]; 
                    fft_buf[2*i] = temp2;
                    fft_buf[2*i+1] = temp1;
            }
    }
		
		/*
    for(i = 0; i < high_pass; i++){
		        // Clear the low frequency portion of the frequency domain
            fft_buf[2*i  ] = 0;
            fft_buf[2*i+1] = 0;
    }
		*/
		
    arm_rfft_fast_f32(&S, fft_buf, outputbuf, 1); // Calculate IFFT and save the result in outputbuf			
}

