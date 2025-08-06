/**
 * Copyright (c) 2014 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_uart.h"
#include "boards.h"
#include "arm_math.h"
#include "raw_rcc_data_x_pre_process.h"
#include "fault_diagnosis/main_functions.h"
#include "fault_diagnosis/output_handler.h"
#include "led.h"
#include "nrf_gpio.h"
#include "GPIOE.h"
#include "FFT_instance.h"
//#include "fcm_method.h"
#include "features_extraction.h"
#include "filtering_preprocessing.h"
#include "integration.h"
#include "hilbert_and_envelope_signal.h"
#include "fault_diagnosis/confusion_matrix_and_metrics.h"
#include "fault_diagnosis/svm_params.h"
//#include "fault_diagnosis/Gaussian_bayes.h"

#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif

#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif

#define MAX_TEST_DATA_BYTES  (15U)
#define UART_TX_BUF_SIZE      256
#define UART_RX_BUF_SIZE      256
#define UART_HWFC APP_UART_FLOW_CONTROL_DISABLED

float32_t t_integral_output[FFT_LEN]; // The output of the time-domain integrating signal
float32_t f_integral_output[FFT_LEN]; // The output of the frequency-domain integrating signal
float32_t data_after_smooth[FFT_LEN]; // Data after smooth
uint8_t pred_label[100];
float features_data[100][81];
float32_t data_temp[FFT_LEN]; // Temporary array(Store final time-domain integrating signal after filtering and removing trend)
float32_t smooth_matrix_temp[FFT_LEN];
float32_t speed = 0; // Recording speed
extern float32_t Mag_N[FFT_LEN]; // magnitude
extern float32_t Phase_N[FFT_LEN]; // phase 

void DWT_Init(void) 
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // DWT was enabled
    DWT->CYCCNT = 0;  // Reset counter
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;  // The Cycle Counter was enabled
}

/* static void uart_loopback_test()
{
	uint8_t cr;
	while(true)
	{
		while(app_uart_get(&cr) != NRF_SUCCESS);
		while(app_uart_put(cr) != NRF_SUCCESS);
		if(cr == 'a')
		{
			printf("\r\n hello world!\r\n");
		}
	}
} 
*/

static void uart_error_handle(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}

/*
static void uart_Interrupt_handle(app_uart_evt_t * p_event)
{
	uint8_t RX;
	if(p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
	{
		APP_ERROR_HANDLER(p_event->data.error_communication);
	}
	else if(p_event->evt_type == APP_UART_FIFO_ERROR)
	{
		APP_ERROR_HANDLER(p_event->data.error_code);
	}
	else if(p_event->evt_type == APP_UART_DATA_READY)
	{
		app_uart_get(&RX);
		printf("%c", RX);
	}
	else if(p_event->evt_type == APP_UART_TX_EMPTY)
	{
		nrf_gpio_pin_toggle(LED_1);
	}
}
*/

int main(int argc, char* argv[])
{
/*
        // Enable UART
        // When UART disabled, the RTT will be enabled to log
	uint32_t err_code;
	const app_uart_comm_params_t comm_params = {
		RX_PIN_NUMBER,
		TX_PIN_NUMBER,
		RTS_PIN_NUMBER,
		CTS_PIN_NUMBER,
		UART_HWFC,
		false,
#if defined (UART_PRESENT)
		NRF_UART_BAUDRATE_115200
#else
		NRF_UARTE_BAUDRATE_115200
#endif
	};
	APP_UART_FIFO_INIT(&comm_params, 
                           UART_RX_BUF_SIZE, 
	                   UART_TX_BUF_SIZE,
	                   uart_error_handle,
                           APP_IRQ_PRIORITY_LOWEST,
                           err_code);
	APP_ERROR_CHECK(err_code);
*/

	
	/*
	// Five points three times smooth processing, there is a problem with serial port acceptance, the code should be correct
	int i, j, k;
	int m = 5; //Smoothing degree
	// May need subtract bias
	for (i = 0; i < FFT_LEN; i++)
  {
    data_temp[i] = test_data_1024[1][i];
  }
	
  for (k = 0; k < m; k++)
  {
    smooth_matrix_temp[0] = (69 * data_temp[0] + 4 * (data_temp[1] + data_temp[3]) - 6 * data_temp[2] - data_temp[4])/70.0f;
    smooth_matrix_temp[1] = (2 * (data_temp[0] + data_temp[4]) + 27 * data_temp[1] + 12 * data_temp[2] - 7*data_temp[3])/35.0f;
		//printf("%f\n", smooth_matrix_temp[1]);
		//nrf_delay_ms(500);
    for (i = 3; i <= (FFT_LEN - 2); i++)
    {
      smooth_matrix_temp[i-1] = (12 * (data_temp[i - 2] + data_temp[i]) + 17 * data_temp[i - 1] - 3 * (data_temp[i - 3]+data_temp[i + 1]))/35.0f;
    }
    smooth_matrix_temp[FFT_LEN - 2] = (2 * (data_temp[FFT_LEN - 1] + data_temp[FFT_LEN - 5]) + 27 * data_temp[FFT_LEN - 2] + 12 * data_temp[FFT_LEN - 3] - 7*data_temp[FFT_LEN - 4])/35.0f;
    smooth_matrix_temp[FFT_LEN - 1] = (69 * data_temp[FFT_LEN - 1] + 4 * (data_temp[FFT_LEN - 2] + data_temp[FFT_LEN - 4]) - 6 * data_temp[FFT_LEN - 3] - data_temp[FFT_LEN - 5])/70.0f;
    for (j = 0; j < FFT_LEN; j++)
    {
      data_temp[j] = smooth_matrix_temp[j];
    }
  }
	
  for (j = 0; j < FFT_LEN; j++)
  {
    data_after_smooth[j] = data_temp[j];
  }
	*/
	
	LED_Init();
	LED1_Open();
	
	static float32_t feature_matrix[81];
	//uint32_t index = 0;
	float32_t accuracy;
	uint32_t start, end, cycles;
	float32_t time_us, average_time_us;
		
	DWT_Init();  // Initialize DWT
	nrf_delay_ms(5000);
	average_time_us = 0;
	
	//int32_t ML_result;
	
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < FFT_LEN; j++)
		{
			data_after_smooth[j] = test_data_1024[i][j];
		}
		start = DWT->CYCCNT;  // Start of record time
		
		float32_t *data_after_preprocess = data_preprocess(data_after_smooth);
		float32_t *acc_TD_features = extract_time_domain_features((const float32_t*)data_after_preprocess);
		fft_example((const float32_t*)data_after_preprocess); // Enable FFT
		float32_t *acc_FD_features = extract_frequency_domain_features();
		
		memcpy(feature_matrix, acc_TD_features, 20 * sizeof(float32_t)); // Copy acceleration 20 time-domain features
		memcpy(feature_matrix + 20, acc_FD_features, 7 * sizeof(float32_t)); // Copy acceleration 7 frequency-domain features
		
		float32_t *vel = time_integration((const float32_t*)data_after_preprocess);
		float32_t *vel_TD_features = extract_time_domain_features((const float32_t*)vel);
		fft_example((const float32_t*)vel);
		float32_t *vel_FD_features = extract_frequency_domain_features();
		
		memcpy(feature_matrix + 20 + 7, vel_TD_features, 20 * sizeof(float32_t)); // Copy velocity 20 time-domain features
		memcpy(feature_matrix + 20 + 7 + 20, vel_FD_features, 7 * sizeof(float32_t)); // Copy velocity 7 frequency-domain features
		
		float32_t *env = Hilbert_and_envelope_signal((const float32_t*)data_after_preprocess);
		float32_t *env_TD_features = extract_time_domain_features((const float32_t*)env);
		fft_example((const float32_t*)env);
		float32_t *env_FD_features = extract_frequency_domain_features();
		
		memcpy(feature_matrix + 7 + 20 + 7 + 20, env_TD_features, 20 * sizeof(float32_t)); // Copy envelope 20 time-domain features
		memcpy(feature_matrix + 20 + 7 + 20 + 7 + 20, env_FD_features, 7 * sizeof(float32_t)); // Copy envelope 7 frequency-domain features
		
		/*
		for(int k = 0; k < 81; k++)
		{
			printf("feature matrix[%d]: %f \n", k, feature_matrix[k]);
			nrf_delay_ms(50);
		}
		printf("\n");
		nrf_delay_ms(25);
		*/
		
		//  TFLite Micro Testing
		//TfLiteStatus temp_tflite_status = TFLM_Inference(&data_after_smooth[0], &pred_label[0], i);
		
		// Gaussian DB Testing
		//ML_result = arm_gaussian_db_predict_f32((const float32_t*)feature_matrix);
		//pred_label[i] = ML_result;
		
		/*
		end = DWT->CYCCNT;  // End of record time
		cycles = end - start;  // Calculates the number of clock cycles consumed
		time_us = (cycles * 1.0f) / (64000000 / 1e6); // uS
		printf("time_us: %f\n", time_us);
		nrf_delay_ms(25);
		average_time_us = average_time_us + time_us;
		*/
		
		// Store the features matrix (For SVM standscaler)
		for (int g = 0; g < 81; g++)
		{
			features_data[i][g] = feature_matrix[g];
		}
		
	}
	
	//  SVM Testing
	arm_svm_polynomial_predict_f32_ovr_10c(features_data, &pred_label[0]);
	
	end = DWT->CYCCNT;  // End of record time
	cycles = end - start;  // Calculates the number of clock cycles consumed
	time_us = (cycles * 1.0f) / (64000000 / 1e6); // uS
	average_time_us = time_us;
	
	
	//accuracy = (float32_t)index / 100.0f;
	//printf("-----TEST ACCURACY: %f-----\n", accuracy);
	//nrf_delay_ms(25);
	
	average_time_us = average_time_us / 100.0f;
	printf("----Inference Time: %f----\n", average_time_us);
	nrf_delay_ms(25);
	
	for(int i = 0; i < 100; i++)
	{
		printf("%u, ", pred_label[i]);
		nrf_delay_ms(25);
	}
	
	ClassificationReport report;
	uint8_t test_label_1024_test[100];
	for (int i = 0; i < 100; i++)
	{
		test_label_1024_test[i] = test_label_1024[i];
	}

	fill_confusion_matrix(test_label_1024_test, pred_label, 100, &report);
  calculate_metrics(&report);
	
	//printf("----Precision Macro Average: %f----\n", report.macro_avg[0]);
	//nrf_delay_ms(25);
	//printf("----Recall Macro Average: %f----\n", report.macro_avg[1]);
	//nrf_delay_ms(25);
	//printf("----F1-Score Macro Average: %f----\n", report.macro_avg[2]);
	//nrf_delay_ms(25);
	printf("----Precision Weighted Average: %f----\n", report.weighted_avg[0]);
	nrf_delay_ms(25);
	printf("----Recall Weighted Average: %f----\n", report.weighted_avg[1]);
	nrf_delay_ms(25);
	printf("----F1-Score Weighted Average: %f----\n", report.weighted_avg[2]);
	nrf_delay_ms(25);
	printf("-----TEST ACCURACY: %f-----\n", report.accuracy);
	nrf_delay_ms(25);
	
	LED2_Open();
	
  // Frequency domain integration
	/*
  int flag = 0;
  uint32_t u = 0;
  integ_init(FFT_LEN);
  frq_domain_integral(data_after_smooth, f_integral_output);
	
	nrf_delay_ms(1000);
  for (i = 0; i < FFT_LEN; i++)
  {
    //printf("%f %f %f\n", Mag_N[i], Phase_N[i], t_integral_output[i]);
		printf("%f %f\n", data_temp[i] * 1000, f_integral_output[i] * 1000); // Convert m/s to mm/s
		nrf_delay_ms(50);
  }
	*/
	
	/*
	// FCM Method
	printf("----FCM Beginning----\n");
	nrf_delay_ms(50);
	FCM_Main();	
	printf("----FCM Ending----\n");
	nrf_delay_ms(50);
	*/
	
  /*
	BEEP_Init();
	BEEP_Open();
	nrf_delay_ms(2000);
	BEEP_Close();
  */

}
