#ifndef __GAUSSIAN_BAYES__
#define __GAUSSIAN_BAYES__

#include "arm_math.h"

#define NB_OF_CLASSES 10
#define VECTOR_DIMENSION 81

#ifdef __cplusplus
extern "C" {
#endif
uint32_t arm_gaussian_db_predict_f32(const float32_t * in);

#ifdef __cplusplus
}	
#endif	 
#endif