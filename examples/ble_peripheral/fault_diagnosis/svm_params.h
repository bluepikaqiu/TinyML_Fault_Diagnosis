#ifndef __SVM_H__
#define __SVM_H__

#include "arm_math.h"

#ifdef __cplusplus
extern "C" {
#endif
void arm_svm_polynomial_init_f32_ovr(arm_svm_polynomial_instance_f32 *S,
	uint32_t nbOfSupportVectors,
	uint32_t vectorDimension,
  float32_t intercept,
  const float32_t *dualCoefficients,
  const float32_t *supportVectors);
	
//void arm_svm_polynomial_predict_f32_ovr_2c(const float32_t input[100][81], uint8_t *predicted_class);
//void arm_svm_polynomial_predict_f32_ovr_4c(const float32_t input[100][81], uint8_t *predicted_class);
void arm_svm_polynomial_predict_f32_ovr_10c(const float32_t input[100][81], uint8_t *predicted_class);

#ifdef __cplusplus
}	
#endif	 
#endif
