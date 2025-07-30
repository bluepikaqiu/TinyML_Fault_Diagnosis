#include "stdio.h"
#include "stdlib.h"
#include "arm_math.h"
#include "nrf_delay.h"
#include "FFT_instance.h"
#include "features_extraction.h"

extern float32_t Mag[FFT_LEN/2];

/**
 * @brief compute the positive frequency component array(0 ~ Fs/2 - Fs/(2N_ps))
 * @param N_ps number of positive frequency components
 * @param Fs sample frequency
 * @return float32_t* returns a frequency array pointer
 */
float32_t* compute_positive_frequencies(int N_ps, float32_t Fs) {
    //allocate memory to store frequency arrays
    float32_t* freqs = (float32_t*)malloc(N_ps * sizeof(float32_t));
    if (freqs == NULL) {
        return NULL;
    }

    //total sampling points
    int N_total = 2 * N_ps;

    //f = Fs / N_total
    float32_t delta_f = Fs / (float32_t)N_total;

    //(0, ?f, 2?f, ..., (N_ps-1)f)
    for (int k = 0; k < N_ps; k++) {
        freqs[k] = k * delta_f;
    }
    return freqs;
}

/**
 * @brief extract time-domain features
 * @param 
 * @retval  
 */
float32_t* extract_time_domain_features(const float32_t *signal)
{	
	//initializes the features variables
	uint16_t i = 0;
	uint32_t pIndex;
	float32_t p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20; //total 19-dimensional time-domain features
	float32_t temp1[FFT_LEN], temp2[FFT_LEN], temp4[FFT_LEN], temp5[FFT_LEN], temp6[FFT_LEN]; 
	float32_t temp3;
	static float32_t feature_matrix[20];
	
	arm_absmax_f32(&signal[0], FFT_LEN, &p1, &pIndex); //p1, max absolute value
	arm_absmin_f32(&signal[0], FFT_LEN, &p2, &pIndex); //p2, min absolute value
	arm_abs_f32(&signal[0], &temp1[0], FFT_LEN);
	arm_mean_f32((const float32_t *)&temp1[0], FFT_LEN, &p3); //p3, absolute mean value/average amplitude
	p4 = p1 - p2; //p4, peak to peak value
	arm_mean_f32(&signal[0], FFT_LEN, &p5); //p5, mean value
	arm_rms_f32(&signal[0], FFT_LEN, &p6); //p6, root mean square
	
	for (i = 0; i < FFT_LEN; i++) {
		arm_sqrt_f32(temp1[i], &temp2[i]);
	}
	
	arm_mean_f32((const float32_t *)&temp2[0], FFT_LEN, &temp3);
	p7 = temp3 * temp3; //p7, square root amplitude
	arm_std_f32(&signal[0], FFT_LEN, &p8); //p8, standard deviation
	
	for (i = 0; i < FFT_LEN; i++) {
		temp6[i] = (signal[i] - p5) / p8;
	}
	
	/*
	arm_mult_f32(&signal[0], &signal[0], &temp2[0], FFT_LEN);
	arm_mult_f32((const float32_t *)&temp2[0], &signal[0], &temp5[0], FFT_LEN);
	arm_mean_f32((const float32_t *)&temp5[0], FFT_LEN, &p9); //p9, skewness
	arm_mult_f32((const float32_t *)&temp2[0], (const float32_t *)&temp2[0], &temp5[0], FFT_LEN);
	arm_mean_f32((const float32_t *)&temp5[0], FFT_LEN, &p10); //p10, kurtosis
	*/
	arm_mult_f32(&temp6[0], &temp6[0], &temp2[0], FFT_LEN);
	arm_mult_f32((const float32_t *)&temp2[0], &temp6[0], &temp5[0], FFT_LEN);
	arm_mean_f32((const float32_t *)&temp5[0], FFT_LEN, &p9); //p9, skewness
	arm_mult_f32((const float32_t *)&temp2[0], (const float32_t *)&temp2[0], &temp5[0], FFT_LEN);
	arm_mean_f32((const float32_t *)&temp5[0], FFT_LEN, &p10); //p10, kurtosis	
	arm_var_f32(&signal[0], FFT_LEN, &p11); //p11, variance
	p12 = p1 / p7; //p12, margin/clearance factor
	p13 = p8 / p3; //p13, Waveform Factor
	p14 = p6 / p3; //p14, wave/shape factor
	p15 = p1 / p6; //p15, crest/peak factor
	p16 = p1 / p3; //p16, impulse factor
	/*
	arm_sqrt_f32(p11, &temp3);
	arm_mult_f32((const float32_t *)&temp3, (const float32_t *)&temp3, &temp4, 1);
	arm_mult_f32((const float32_t *)&temp4, (const float32_t *)&temp3, &temp3, 1);
	
	p17 = p9 / temp3; //p17, skewness coefficient
	p18 = p10 / temp4; //p18, kurtosis coefficient
	p19 = arm_entropy_f32((const float32_t *)&temp1[0], FFT_LEN); //p19, entropy
	*/
	for (i = 0; i < FFT_LEN; i++) {
		temp6[i] = signal[i] - p5;
	}
	arm_mult_f32(&temp6[0], &temp6[0], &temp2[0], FFT_LEN);
	arm_mult_f32((const float32_t *)&temp2[0], &temp6[0], &temp5[0], FFT_LEN);
  arm_accumulate_f32((const float32_t *)&temp5[0], FFT_LEN, &p17);
	p17 = p17 / (FFT_LEN-1); //p17, 3th central moment
	arm_mult_f32((const float32_t *)&temp2[0], &temp2[0], &temp4[0], FFT_LEN);
  arm_accumulate_f32((const float32_t *)&temp4[0], FFT_LEN, &p18);
	p18 = p18 / (FFT_LEN-1); //p18, 4th central moment
	arm_mult_f32((const float32_t *)&temp4[0], &temp6[0], &temp5[0], FFT_LEN);
  arm_accumulate_f32((const float32_t *)&temp5[0], FFT_LEN, &p19);
	p19 = p19 / (FFT_LEN-1); //p19, 5th central moment
	p20 = arm_entropy_f32((const float32_t *)&temp1[0], FFT_LEN); //p20, entropy
	
	feature_matrix[0] = p1;
	feature_matrix[1] = p2;
	feature_matrix[2] = p3;
	feature_matrix[3] = p4;
	feature_matrix[4] = p5;
	feature_matrix[5] = p6;
	feature_matrix[6] = p7;
	feature_matrix[7] = p8;
	feature_matrix[8] = p9;
	feature_matrix[9] = p10;
	feature_matrix[10] = p11;
	feature_matrix[11] = p12;
	feature_matrix[12] = p13;
	feature_matrix[13] = p14;
	feature_matrix[14] = p15;
	feature_matrix[15] = p16;
	feature_matrix[16] = p17;
	feature_matrix[17] = p18;
	feature_matrix[18] = p19;
	feature_matrix[19] = p20;
	
	/*
	for(int i = 0; i < 20; i++)
	{
		printf("(time-domain)feature matrix: %f \n", feature_matrix[i]);
		nrf_delay_ms(300);
	}
	*/
	
	return feature_matrix;
}

/**
 * @brief extract frequency-domain features
 * @param 
 * @retval  
 */
float32_t* extract_frequency_domain_features()
{	
	//initializes the features variables
	uint32_t pIndex;
	uint16_t i = 0;
	uint16_t N_ps = FFT_LEN / 2; //length of power spectrum, len(rfft_mag)
	float32_t P21, P22, P23, P24, P25, P25_temp, P26, P26_temp, P27, P27_temp; //total 8-dimensional frequency-domain features
	float32_t rfft_ps[N_ps], temp1[N_ps], temp2[N_ps], temp3[N_ps];
	float32_t *freqs = compute_positive_frequencies(N_ps, SMPLE_FRQ); //only positive frequency component
	static float32_t feature_matrix[7];
	
	arm_mult_f32(&Mag[0], &Mag[0], &rfft_ps[0], N_ps);
	for (i = 0; i < N_ps; i++) {
		rfft_ps[i] = rfft_ps[i] / (float32_t)N_ps;
	}    
	arm_mean_f32((const float32_t *)&rfft_ps[0], N_ps, &P21); //P21, mean of power spectrum
	arm_std_f32((const float32_t *)&rfft_ps[0], N_ps, &P22); //P22, standard deviation of power spectrum
	for (i = 0; i < N_ps; i++) {
		temp1[i] = rfft_ps[i] - P21;
	}  
	arm_mult_f32(&temp1[0], &temp1[0], &temp2[0], N_ps);
	arm_mult_f32(&temp2[0], &temp1[0], &temp3[0], N_ps);
	arm_accumulate_f32((const float32_t *)&temp3[0], N_ps, &P23);
	P23 = P23 / (float32_t)(N_ps * pow(P22, 3)); //P23, skewness of power spectrum
	arm_mult_f32(&temp2[0], &temp2[0], &temp3[0], N_ps);
	arm_accumulate_f32((const float32_t *)&temp3[0], N_ps, &P24);
	P24 = P24 / (float32_t)(N_ps * pow(P22, 4)); //P24, kurtosis of power spectrum	
	arm_mult_f32(&freqs[0], &rfft_ps[0], &temp1[0], N_ps);
	arm_accumulate_f32((const float32_t *)&temp1[0], N_ps, &P25_temp);
	arm_accumulate_f32((const float32_t *)&rfft_ps[0], N_ps, &P25);
	P25 = P25_temp / P25; //P25, frequency center
	for (i = 0; i < N_ps; i++) {
		temp1[i] = freqs[i] - P25;
	}
	arm_mult_f32(&temp1[0], &temp1[0], &temp2[0], N_ps);
	arm_mult_f32(&temp2[0], &rfft_ps[0], &temp3[0], N_ps);
	arm_accumulate_f32((const float32_t *)&temp3[0], N_ps, &P26_temp);
	arm_accumulate_f32((const float32_t *)&rfft_ps[0], N_ps, &P26);
	//P26 = P26_temp / P26; //P26, frequency deviation
	arm_sqrt_f32((P26_temp / P26), &P26); //P26, frequency standard deviation
	arm_mult_f32(&freqs[0], &freqs[0], &temp1[0], N_ps);
	arm_mult_f32(&temp1[0], &rfft_ps[0], &temp2[0], N_ps);
	arm_accumulate_f32((const float32_t *)&temp2[0], N_ps, &P27_temp);
	arm_accumulate_f32((const float32_t *)&rfft_ps[0], N_ps, &P27);
	P27_temp = P27_temp / P27;
	arm_sqrt_f32(P27_temp, &P27); //P27, frequency root mean square
	
	feature_matrix[0] = P21;
	feature_matrix[1] = P22;
	feature_matrix[2] = P23;
	feature_matrix[3] = P24;
	feature_matrix[4] = P25;
	//feature_matrix[5] = P26;
	feature_matrix[5] = P26;
	feature_matrix[6] = P27;
	free(freqs);
	freqs = NULL;

	/*
	for(int i = 0; i < 7; i++)
	{
		printf("(frequency-domain)feature matrix: %f \n", feature_matrix[i]);
		nrf_delay_ms(300);
	}
	*/
	
	return feature_matrix;
}