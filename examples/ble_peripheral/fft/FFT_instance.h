#ifndef __FFT_1024_H__
#define __FFT_1024_H__

#include "stdint.h"
#include "arm_math.h"

#define SMPLE_FRQ				12000				//����Ƶ��
#define FFT_LEN         1024			//FFT���鳤�ȣ�Ϊ2�������ݴ�

#ifdef __cplusplus
extern "C" {
#endif
void fft_example(const float *signal);
void PowerMag(uint16_t _usFFTPoints);
void Power_Phase_Radians(uint16_t _usFFTPoints);
#ifdef __cplusplus
}	
#endif

#endif