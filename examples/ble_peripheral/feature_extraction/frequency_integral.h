/**
 **************************************************************************
 *  @filename	Ƶ��һ��/���λ���
 *  @brief   	���ļ���Ҫ����ʵ�ּ��ٶ���Ƶ���һ�λ���λ��ֵõ��ٶȻ�λ�ƣ�
 * 				�д�ͨ�˲����ܣ����ֺ�Ư�ƽ�С�������Ƶ��1kHz���ϣ�Ч����Ϊ����
 * 
 *  @example	integ_init(1024);
 *				float data_buf[1000];		//��Ҫ���л��ֵ���������
 *				float integ_buf[1024];		//���ڴ�����ֽ��������
 *				frq_domain_integral(data_buf, integ_buf);

 *  @attention	����mallocʧ�ܽ���hardfaultʱ�����԰�starup_stm32f40_41xxx.s
 * 				�е�Stack_Size��Heap_Size����Ĭ�ϵĶ�ջ�Ƚ�С������̫��ʱ��
 * 				����ʧ��
 * 				���ļ���Ҫ�õ�STM32F4��DSP��
 * 
 * 	@other		�������񶯻�������λ��Ϊ0����λ�Ƽ��㣬�������ڵ���λ�ƵĲ���
 **************************************************************************
 */

#ifndef __FREQUENCY_INTEGRAL_H__
#define __FREQUENCY_INTEGRAL_H__

#include <stdlib.h>
#include "math.h"
#include "arm_math.h"								//stm32f4xx DSP�⣬��FPU��Ӳ������FFT

//�����ӿ�
#define MALLOC(size)			malloc(size)
#define MEMSET(addr,val,len)	memset(addr,val,len)
#define	POW(n,x)				pow(n,x)

#define SMPLE_FRQ				12000				//����Ƶ��
//#define GRAVITY					9.8				//��λ�仯ϵ���������ֽ�����ϸ�ϵ���������������ٶȵõ���
#define INTEG_TIME				1					//���ִ���
#define FRQ_MIN					SMPLE_FRQ * 0.002	  //��ͨ�˲���ֹƵ��
#define FRQ_MAX					200					//��ͨ�˲���ֹƵ�ʣ�ӦС�ڲ���Ƶ�ʣ�
#define FFT_LEN         1024			//FFT���鳤�ȣ�Ϊ2�������ݴ�
#define	high_pass			round((float32_t)FRQ_MIN / ((float32_t)SMPLE_FRQ / (float32_t)FFT_LEN))	//��ͨƵ����ʼ��
#define	low_pass				100 			//��ͨƵ�ʽ�ֹ��

#ifdef __cplusplus
extern "C" {
#endif

/** 
 *  @name	Ƶ��һ��/���λ��ֳ�ʼ������
 *  @brief  ��ʼ�����ڴ洢�����Ľṹ�壬�·��ɸ��Ĳ��ָ���ʵ���������
 *  @pram	len	���ڶ��λ��ֵ����鳤�ȣ��������16С��4096��2���ݴ�
 *  @retval	��
 *  
 */
void integ_init(uint16_t len);

/** 
 *  @name	Ƶ��һ��/���λ��ֺ���
 *  @brief	����һ��/���λ���
 *  @pram	inputbuf	��������
 *  		outputbuf	������飨���ȴ��ڵ���������������Ϊ2^(4~12)��
 *  @retval	��
 */
void frq_domain_integral(float* inputbuf, float* outputbuf);

#ifdef __cplusplus
}	
#endif

#endif

