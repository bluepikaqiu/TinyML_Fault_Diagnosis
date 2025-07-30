/**
 **************************************************************************
 *  @filename	频域一次/二次积分
 *  @brief   	该文件主要用于实现加速度在频域的一次或二次积分得到速度或位移，
 * 				有带通滤波功能，积分后漂移较小建议采样频率1kHz以上，效果较为理想
 * 
 *  @example	integ_init(1024);
 *				float data_buf[1000];		//需要进行积分的数据数组
 *				float integ_buf[1024];		//用于储存积分结果的数组
 *				frq_domain_integral(data_buf, integ_buf);

 *  @attention	遇到malloc失败进入hardfault时，尝试把starup_stm32f40_41xxx.s
 * 				中的Stack_Size和Heap_Size调大，默认的堆栈比较小，数组太长时会
 * 				分配失败
 * 				该文件需要用到STM32F4的DSP库
 * 
 * 	@other		适用于振动环境（总位移为0）的位移计算，不适用于单次位移的测量
 **************************************************************************
 */

#ifndef __FREQUENCY_INTEGRAL_H__
#define __FREQUENCY_INTEGRAL_H__

#include <stdlib.h>
#include "math.h"
#include "arm_math.h"								//stm32f4xx DSP库，带FPU，硬件加速FFT

//函数接口
#define MALLOC(size)			malloc(size)
#define MEMSET(addr,val,len)	memset(addr,val,len)
#define	POW(n,x)				pow(n,x)

#define SMPLE_FRQ				12000				//采样频率
//#define GRAVITY					9.8				//单位变化系数（最后积分结果乘上该系数，根据重力加速度得到）
#define INTEG_TIME				1					//积分次数
#define FRQ_MIN					SMPLE_FRQ * 0.002	  //高通滤波截止频率
#define FRQ_MAX					200					//低通滤波截止频率（应小于采样频率）
#define FFT_LEN         1024			//FFT数组长度，为2的整数幂次
#define	high_pass			round((float32_t)FRQ_MIN / ((float32_t)SMPLE_FRQ / (float32_t)FFT_LEN))	//高通频率起始点
#define	low_pass				100 			//低通频率截止点

#ifdef __cplusplus
extern "C" {
#endif

/** 
 *  @name	频域一次/二次积分初始化函数
 *  @brief  初始化用于存储函数的结构体，下方可更改部分根据实际情况更改
 *  @pram	len	用于二次积分的数组长度，建议大于16小于4096，2的幂次
 *  @retval	无
 *  
 */
void integ_init(uint16_t len);

/** 
 *  @name	频域一次/二次积分函数
 *  @brief	计算一次/二次积分
 *  @pram	inputbuf	输入数组
 *  		outputbuf	输出数组（长度大于等于输入数组且需为2^(4~12)）
 *  @retval	无
 */
void frq_domain_integral(float* inputbuf, float* outputbuf);

#ifdef __cplusplus
}	
#endif

#endif

