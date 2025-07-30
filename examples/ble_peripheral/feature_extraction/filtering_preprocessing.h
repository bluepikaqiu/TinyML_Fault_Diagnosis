#ifndef __FILTERING_PREPROCESSING_H__
#define __FILTERING_PREPROCESSING_H__

#include "arm_math.h"

#ifdef __cplusplus
extern "C" {
#endif
float32_t* IIR_butterworth_high_pass_4_order(float32_t *IIR_Filter_input, const float32_t *coeff);
float32_t* data_preprocess(const float32_t *signal);
#ifdef __cplusplus
}	
#endif

#endif