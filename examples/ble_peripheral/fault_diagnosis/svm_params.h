#ifndef __SVM_H__
#define __SVM_H__

#include "arm_math.h"

#ifdef __cplusplus
extern "C" {
#endif
//float32_t *scaler_transform(const float32_t *input);
	
void arm_svm_polynomial_init_f32_ovr(arm_svm_polynomial_instance_f32 *S,
	uint32_t nbOfSupportVectors,
	uint32_t vectorDimension,
  float32_t intercept,
  const float32_t *dualCoefficients,
  const float32_t *supportVectors);
	
//void arm_svm_polynomial_predict_f32_ovr_2c(const float32_t * in, int32_t * pResult);
//uint8_t arm_svm_polynomial_predict_f32_ovr_4c(const float32_t * in);
uint8_t arm_svm_polynomial_predict_f32_ovr_10c(const float32_t * in);

#ifdef __cplusplus
}	
#endif	 
#endif
