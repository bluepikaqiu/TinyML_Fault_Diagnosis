#ifndef __POLYFIT_H__
#define __POLYFIT_H__

#include "arm_const_structs.h"

#ifdef __cplusplus
extern "C" {
#endif
	
int polyfit(const float32_t* const dependentValues ,
            const float32_t* const independentValues ,
            unsigned int        countOfElements ,
            unsigned int        order ,
            float32_t* coefficients);
						
#ifdef __cplusplus
}	
#endif

#endif