#ifndef __FEATURES_EXTRACTION__
#define __FEATURES_EXTRACTION__

#include "arm_math.h"

#ifdef __cplusplus
extern "C" {
#endif
float32_t* extract_time_domain_features(const float32_t *signal);
float32_t* extract_frequency_domain_features();
#ifdef __cplusplus
}	
#endif

#endif