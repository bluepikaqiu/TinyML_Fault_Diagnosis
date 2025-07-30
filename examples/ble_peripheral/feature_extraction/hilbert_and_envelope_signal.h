#ifndef __HILBERT_AND_ENVELOPE_SIGNAL_H__
#define __HILBERT_AND_ENVELOPE_SIGNAL_H__

#include "arm_math.h"

#ifdef __cplusplus
extern "C" {
#endif
float32_t* Hilbert_and_envelope_signal(const float32_t *signal);
#ifdef __cplusplus
}	
#endif

#endif