/**
  ******************************************************************************
  * @file STM32F10x_DSP_Lib/inc/table_fft.h 
  * @author  MCD Application Team
  * @version  V2.0.0
  * @date  04/27/2009
  * @brief  Contains the coefficients required for FFT computation.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TABLE_FFT_H
#define __TABLE_FFT_H

#include "stdint.h"

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
uint16_t TableFFT[]= {0x4000,0x0000, 0x4000,0x0000, 0x4000,0x0000,
                 0xdd5d,0x3b21, 0x22a3,0x187e, 0x0000,0x2d41,
                 0xa57e,0x2d41, 0x0000,0x2d41, 0xc000,0x4000,
                 0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41,
                 0x4000,0x0000, 0x4000,0x0000, 0x4000,0x0000,  /* N=64 */
                 0x2aaa,0x1294, 0x396b,0x0646, 0x3249,0x0c7c,
                 0x11a8,0x238e, 0x3249,0x0c7c, 0x22a3,0x187e,
                 0xf721,0x3179, 0x2aaa,0x1294, 0x11a8,0x238e,
                 0xdd5d,0x3b21, 0x22a3,0x187e, 0x0000,0x2d41,
                 0xc695,0x3fb1, 0x1a46,0x1e2b, 0xee58,0x3537,
                 0xb4be,0x3ec5, 0x11a8,0x238e, 0xdd5d,0x3b21,
                 0xa963,0x3871, 0x08df,0x289a, 0xcdb7,0x3ec5,
                 0xa57e,0x2d41, 0x0000,0x2d41, 0xc000,0x4000,
                 0xa963,0x1e2b, 0xf721,0x3179, 0xb4be,0x3ec5,
                 0xb4be,0x0c7c, 0xee58,0x3537, 0xac61,0x3b21,
                 0xc695,0xf9ba, 0xe5ba,0x3871, 0xa73b,0x3537,
                 0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41,
                 0xf721,0xd766, 0xd556,0x3d3f, 0xa73b,0x238e,
                 0x11a8,0xcac9, 0xcdb7,0x3ec5, 0xac61,0x187e,
                 0x2aaa,0xc2c1, 0xc695,0x3fb1, 0xb4be,0x0c7c,
                 0x4000,0x0000, 0x4000,0x0000, 0x4000,0x0000,  /* N=256 */
                 0x3b1e,0x04b5, 0x3e69,0x0192, 0x3cc8,0x0324,
                 0x35eb,0x0964, 0x3cc8,0x0324, 0x396b,0x0646,
                 0x306c,0x0e06, 0x3b1e,0x04b5, 0x35eb,0x0964,
                 0x2aaa,0x1294, 0x396b,0x0646, 0x3249,0x0c7c,
                 0x24ae,0x1709, 0x37af,0x07d6, 0x2e88,0x0f8d,
                 0x1e7e,0x1b5d, 0x35eb,0x0964, 0x2aaa,0x1294,
                 0x1824,0x1f8c, 0x341e,0x0af1, 0x26b3,0x1590,
                 0x11a8,0x238e, 0x3249,0x0c7c, 0x22a3,0x187e,
                 0x0b14,0x2760, 0x306c,0x0e06, 0x1e7e,0x1b5d,
                 0x0471,0x2afb, 0x2e88,0x0f8d, 0x1a46,0x1e2b,
                 0xfdc7,0x2e5a, 0x2c9d,0x1112, 0x15fe,0x20e7,
                 0xf721,0x3179, 0x2aaa,0x1294, 0x11a8,0x238e,
                 0xf087,0x3453, 0x28b2,0x1413, 0x0d48,0x2620,
                 0xea02,0x36e5, 0x26b3,0x1590, 0x08df,0x289a,
                 0xe39c,0x392b, 0x24ae,0x1709, 0x0471,0x2afb,
                 0xdd5d,0x3b21, 0x22a3,0x187e, 0x0000,0x2d41,
                 0xd74e,0x3cc5, 0x2093,0x19ef, 0xfb8f,0x2f6c,
                 0xd178,0x3e15, 0x1e7e,0x1b5d, 0xf721,0x3179,
                 0xcbe2,0x3f0f, 0x1c64,0x1cc6, 0xf2b8,0x3368,
                 0xc695,0x3fb1, 0x1a46,0x1e2b, 0xee58,0x3537,
                 0xc197,0x3ffb, 0x1824,0x1f8c, 0xea02,0x36e5,
                 0xbcf0,0x3fec, 0x15fe,0x20e7, 0xe5ba,0x3871,
                 0xb8a6,0x3f85, 0x13d5,0x223d, 0xe182,0x39db,
                 0xb4be,0x3ec5, 0x11a8,0x238e, 0xdd5d,0x3b21,
                 0xb140,0x3daf, 0x0f79,0x24da, 0xd94d,0x3c42,
                 0xae2e,0x3c42, 0x0d48,0x2620, 0xd556,0x3d3f,
                 0xab8e,0x3a82, 0x0b14,0x2760, 0xd178,0x3e15,
                 0xa963,0x3871, 0x08df,0x289a, 0xcdb7,0x3ec5,
                 0xa7b1,0x3612, 0x06a9,0x29ce, 0xca15,0x3f4f,
                 0xa678,0x3368, 0x0471,0x2afb, 0xc695,0x3fb1,
                 0xa5bc,0x3076, 0x0239,0x2c21, 0xc338,0x3fec,
                 0xa57e,0x2d41, 0x0000,0x2d41, 0xc000,0x4000,
                 0xa5bc,0x29ce, 0xfdc7,0x2e5a, 0xbcf0,0x3fec,
                 0xa678,0x2620, 0xfb8f,0x2f6c, 0xba09,0x3fb1,
                 0xa7b1,0x223d, 0xf957,0x3076, 0xb74d,0x3f4f,
                 0xa963,0x1e2b, 0xf721,0x3179, 0xb4be,0x3ec5,
                 0xab8e,0x19ef, 0xf4ec,0x3274, 0xb25e,0x3e15,
                 0xae2e,0x1590, 0xf2b8,0x3368, 0xb02d,0x3d3f,
                 0xb140,0x1112, 0xf087,0x3453, 0xae2e,0x3c42,
                 0xb4be,0x0c7c, 0xee58,0x3537, 0xac61,0x3b21,
                 0xb8a6,0x07d6, 0xec2b,0x3612, 0xaac8,0x39db,
                 0xbcf0,0x0324, 0xea02,0x36e5, 0xa963,0x3871,
                 0xc197,0xfe6e, 0xe7dc,0x37b0, 0xa834,0x36e5,
                 0xc695,0xf9ba, 0xe5ba,0x3871, 0xa73b,0x3537,
                 0xcbe2,0xf50f, 0xe39c,0x392b, 0xa678,0x3368,
                 0xd178,0xf073, 0xe182,0x39db, 0xa5ed,0x3179,
                 0xd74e,0xebed, 0xdf6d,0x3a82, 0xa599,0x2f6c,
                 0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41,
                 0xe39c,0xe33a, 0xdb52,0x3bb6, 0xa599,0x2afb,
                 0xea02,0xdf19, 0xd94d,0x3c42, 0xa5ed,0x289a,
                 0xf087,0xdb26, 0xd74e,0x3cc5, 0xa678,0x2620,
                 0xf721,0xd766, 0xd556,0x3d3f, 0xa73b,0x238e,
                 0xfdc7,0xd3df, 0xd363,0x3daf, 0xa834,0x20e7,
                 0x0471,0xd094, 0xd178,0x3e15, 0xa963,0x1e2b,
                 0x0b14,0xcd8c, 0xcf94,0x3e72, 0xaac8,0x1b5d,
                 0x11a8,0xcac9, 0xcdb7,0x3ec5, 0xac61,0x187e,
                 0x1824,0xc850, 0xcbe2,0x3f0f, 0xae2e,0x1590,
                 0x1e7e,0xc625, 0xca15,0x3f4f, 0xb02d,0x1294,
                 0x24ae,0xc44a, 0xc851,0x3f85, 0xb25e,0x0f8d,
                 0x2aaa,0xc2c1, 0xc695,0x3fb1, 0xb4be,0x0c7c,
                 0x306c,0xc18e, 0xc4e2,0x3fd4, 0xb74d,0x0964,
                 0x35eb,0xc0b1, 0xc338,0x3fec, 0xba09,0x0646,
                 0x3b1e,0xc02c, 0xc197,0x3ffb, 0xbcf0,0x0324,
                 0x4000,0x0000, 0x4000,0x0000, 0x4000,0x0000, /* N=1024*/
                 0x3ed0,0x012e, 0x3f9b,0x0065, 0x3f36,0x00c9,
                 0x3d9a,0x025b, 0x3f36,0x00c9, 0x3e69,0x0192,
                 0x3c5f,0x0388, 0x3ed0,0x012e, 0x3d9a,0x025b,
                 0x3b1e,0x04b5, 0x3e69,0x0192, 0x3cc8,0x0324,
                 0x39d9,0x05e2, 0x3e02,0x01f7, 0x3bf4,0x03ed,
                 0x388e,0x070e, 0x3d9a,0x025b, 0x3b1e,0x04b5,
                 0x373f,0x0839, 0x3d31,0x02c0, 0x3a46,0x057e,
                 0x35eb,0x0964, 0x3cc8,0x0324, 0x396b,0x0646,
                 0x3492,0x0a8e, 0x3c5f,0x0388, 0x388e,0x070e,
                 0x3334,0x0bb7, 0x3bf4,0x03ed, 0x37af,0x07d6,
                 0x31d2,0x0cdf, 0x3b8a,0x0451, 0x36ce,0x089d,
                 0x306c,0x0e06, 0x3b1e,0x04b5, 0x35eb,0x0964,
                 0x2f02,0x0f2b, 0x3ab2,0x051a, 0x3505,0x0a2b,
                 0x2d93,0x1050, 0x3a46,0x057e, 0x341e,0x0af1,
                 0x2c21,0x1173, 0x39d9,0x05e2, 0x3334,0x0bb7,
                 0x2aaa,0x1294, 0x396b,0x0646, 0x3249,0x0c7c,
                 0x2931,0x13b4, 0x38fd,0x06aa, 0x315b,0x0d41,
                 0x27b3,0x14d2, 0x388e,0x070e, 0x306c,0x0e06,
                 0x2632,0x15ee, 0x381f,0x0772, 0x2f7b,0x0eca,
                 0x24ae,0x1709, 0x37af,0x07d6, 0x2e88,0x0f8d,
                 0x2326,0x1821, 0x373f,0x0839, 0x2d93,0x1050,
                 0x219c,0x1937, 0x36ce,0x089d, 0x2c9d,0x1112,
                 0x200e,0x1a4b, 0x365d,0x0901, 0x2ba4,0x11d3,
                 0x1e7e,0x1b5d, 0x35eb,0x0964, 0x2aaa,0x1294,
                 0x1ceb,0x1c6c, 0x3578,0x09c7, 0x29af,0x1354,
                 0x1b56,0x1d79, 0x3505,0x0a2b, 0x28b2,0x1413,
                 0x19be,0x1e84, 0x3492,0x0a8e, 0x27b3,0x14d2,
                 0x1824,0x1f8c, 0x341e,0x0af1, 0x26b3,0x1590,
                 0x1688,0x2091, 0x33a9,0x0b54, 0x25b1,0x164c,
                 0x14ea,0x2193, 0x3334,0x0bb7, 0x24ae,0x1709,
                 0x134a,0x2292, 0x32bf,0x0c1a, 0x23a9,0x17c4,
                 0x11a8,0x238e, 0x3249,0x0c7c, 0x22a3,0x187e,
                 0x1005,0x2488, 0x31d2,0x0cdf, 0x219c,0x1937,
                 0x0e61,0x257e, 0x315b,0x0d41, 0x2093,0x19ef,
                 0x0cbb,0x2671, 0x30e4,0x0da4, 0x1f89,0x1aa7,
                 0x0b14,0x2760, 0x306c,0x0e06, 0x1e7e,0x1b5d,
                 0x096d,0x284c, 0x2ff4,0x0e68, 0x1d72,0x1c12,
                 0x07c4,0x2935, 0x2f7b,0x0eca, 0x1c64,0x1cc6,
                 0x061b,0x2a1a, 0x2f02,0x0f2b, 0x1b56,0x1d79,
                 0x0471,0x2afb, 0x2e88,0x0f8d, 0x1a46,0x1e2b,
                 0x02c7,0x2bd8, 0x2e0e,0x0fee, 0x1935,0x1edc,
                 0x011c,0x2cb2, 0x2d93,0x1050, 0x1824,0x1f8c,
                 0xff72,0x2d88, 0x2d18,0x10b1, 0x1711,0x203a,
                 0xfdc7,0x2e5a, 0x2c9d,0x1112, 0x15fe,0x20e7,
                 0xfc1d,0x2f28, 0x2c21,0x1173, 0x14ea,0x2193,
                 0xfa73,0x2ff2, 0x2ba4,0x11d3, 0x13d5,0x223d,
                 0xf8ca,0x30b8, 0x2b28,0x1234, 0x12bf,0x22e7,
                 0xf721,0x3179, 0x2aaa,0x1294, 0x11a8,0x238e,
                 0xf579,0x3236, 0x2a2d,0x12f4, 0x1091,0x2435,
                 0xf3d2,0x32ef, 0x29af,0x1354, 0x0f79,0x24da,
                 0xf22c,0x33a3, 0x2931,0x13b4, 0x0e61,0x257e,
                 0xf087,0x3453, 0x28b2,0x1413, 0x0d48,0x2620,
                 0xeee3,0x34ff, 0x2833,0x1473, 0x0c2e,0x26c1,
                 0xed41,0x35a5, 0x27b3,0x14d2, 0x0b14,0x2760,
                 0xeba1,0x3648, 0x2733,0x1531, 0x09fa,0x27fe,
                 0xea02,0x36e5, 0x26b3,0x1590, 0x08df,0x289a,
                 0xe865,0x377e, 0x2632,0x15ee, 0x07c4,0x2935,
                 0xe6cb,0x3812, 0x25b1,0x164c, 0x06a9,0x29ce,
                 0xe532,0x38a1, 0x252f,0x16ab, 0x058d,0x2a65,
                 0xe39c,0x392b, 0x24ae,0x1709, 0x0471,0x2afb,
                 0xe208,0x39b0, 0x242b,0x1766, 0x0355,0x2b8f,
                 0xe077,0x3a30, 0x23a9,0x17c4, 0x0239,0x2c21,
                 0xdee9,0x3aab, 0x2326,0x1821, 0x011c,0x2cb2,
                 0xdd5d,0x3b21, 0x22a3,0x187e, 0x0000,0x2d41,
                 0xdbd5,0x3b92, 0x221f,0x18db, 0xfee4,0x2dcf,
                 0xda4f,0x3bfd, 0x219c,0x1937, 0xfdc7,0x2e5a,
                 0xd8cd,0x3c64, 0x2117,0x1993, 0xfcab,0x2ee4,
                 0xd74e,0x3cc5, 0x2093,0x19ef, 0xfb8f,0x2f6c,
                 0xd5d3,0x3d21, 0x200e,0x1a4b, 0xfa73,0x2ff2,
                 0xd45c,0x3d78, 0x1f89,0x1aa7, 0xf957,0x3076,
                 0xd2e8,0x3dc9, 0x1f04,0x1b02, 0xf83c,0x30f9,
                 0xd178,0x3e15, 0x1e7e,0x1b5d, 0xf721,0x3179,
                 0xd00c,0x3e5c, 0x1df8,0x1bb8, 0xf606,0x31f8,
                 0xcea5,0x3e9d, 0x1d72,0x1c12, 0xf4ec,0x3274,
                 0xcd41,0x3ed8, 0x1ceb,0x1c6c, 0xf3d2,0x32ef,
                 0xcbe2,0x3f0f, 0x1c64,0x1cc6, 0xf2b8,0x3368,
                 0xca88,0x3f40, 0x1bdd,0x1d20, 0xf19f,0x33df,
                 0xc932,0x3f6b, 0x1b56,0x1d79, 0xf087,0x3453,
                 0xc7e1,0x3f91, 0x1ace,0x1dd3, 0xef6f,0x34c6,
                 0xc695,0x3fb1, 0x1a46,0x1e2b, 0xee58,0x3537,
                 0xc54e,0x3fcc, 0x19be,0x1e84, 0xed41,0x35a5,
                 0xc40c,0x3fe1, 0x1935,0x1edc, 0xec2b,0x3612,
                 0xc2cf,0x3ff1, 0x18ad,0x1f34, 0xeb16,0x367d,
                 0xc197,0x3ffb, 0x1824,0x1f8c, 0xea02,0x36e5,
                 0xc065,0x4000, 0x179b,0x1fe3, 0xe8ef,0x374b,
                 0xbf38,0x3fff, 0x1711,0x203a, 0xe7dc,0x37b0,
                 0xbe11,0x3ff8, 0x1688,0x2091, 0xe6cb,0x3812,
                 0xbcf0,0x3fec, 0x15fe,0x20e7, 0xe5ba,0x3871,
                 0xbbd4,0x3fdb, 0x1574,0x213d, 0xe4aa,0x38cf,
                 0xbabf,0x3fc4, 0x14ea,0x2193, 0xe39c,0x392b,
                 0xb9af,0x3fa7, 0x145f,0x21e8, 0xe28e,0x3984,
                 0xb8a6,0x3f85, 0x13d5,0x223d, 0xe182,0x39db,
                 0xb7a2,0x3f5d, 0x134a,0x2292, 0xe077,0x3a30,
                 0xb6a5,0x3f30, 0x12bf,0x22e7, 0xdf6d,0x3a82,
                 0xb5af,0x3efd, 0x1234,0x233b, 0xde64,0x3ad3,
                 0xb4be,0x3ec5, 0x11a8,0x238e, 0xdd5d,0x3b21,
                 0xb3d5,0x3e88, 0x111d,0x23e2, 0xdc57,0x3b6d,
                 0xb2f2,0x3e45, 0x1091,0x2435, 0xdb52,0x3bb6,
                 0xb215,0x3dfc, 0x1005,0x2488, 0xda4f,0x3bfd,
                 0xb140,0x3daf, 0x0f79,0x24da, 0xd94d,0x3c42,
                 0xb071,0x3d5b, 0x0eed,0x252c, 0xd84d,0x3c85,
                 0xafa9,0x3d03, 0x0e61,0x257e, 0xd74e,0x3cc5,
                 0xaee8,0x3ca5, 0x0dd4,0x25cf, 0xd651,0x3d03,
                 0xae2e,0x3c42, 0x0d48,0x2620, 0xd556,0x3d3f,
                 0xad7b,0x3bda, 0x0cbb,0x2671, 0xd45c,0x3d78,
                 0xacd0,0x3b6d, 0x0c2e,0x26c1, 0xd363,0x3daf,
                 0xac2b,0x3afa, 0x0ba1,0x2711, 0xd26d,0x3de3,
                 0xab8e,0x3a82, 0x0b14,0x2760, 0xd178,0x3e15,
                 0xaaf8,0x3a06, 0x0a87,0x27af, 0xd085,0x3e45,
                 0xaa6a,0x3984, 0x09fa,0x27fe, 0xcf94,0x3e72,
                 0xa9e3,0x38fd, 0x096d,0x284c, 0xcea5,0x3e9d,
                 0xa963,0x3871, 0x08df,0x289a, 0xcdb7,0x3ec5,
                 0xa8eb,0x37e1, 0x0852,0x28e7, 0xcccc,0x3eeb,
                 0xa87b,0x374b, 0x07c4,0x2935, 0xcbe2,0x3f0f,
                 0xa812,0x36b1, 0x0736,0x2981, 0xcafb,0x3f30,
                 0xa7b1,0x3612, 0x06a9,0x29ce, 0xca15,0x3f4f,
                 0xa757,0x356e, 0x061b,0x2a1a, 0xc932,0x3f6b,
                 0xa705,0x34c6, 0x058d,0x2a65, 0xc851,0x3f85,
                 0xa6bb,0x3419, 0x04ff,0x2ab0, 0xc772,0x3f9c,
                 0xa678,0x3368, 0x0471,0x2afb, 0xc695,0x3fb1,
                 0xa63e,0x32b2, 0x03e3,0x2b45, 0xc5ba,0x3fc4,
                 0xa60b,0x31f8, 0x0355,0x2b8f, 0xc4e2,0x3fd4,
                 0xa5e0,0x3139, 0x02c7,0x2bd8, 0xc40c,0x3fe1,
                 0xa5bc,0x3076, 0x0239,0x2c21, 0xc338,0x3fec,
                 0xa5a1,0x2faf, 0x01aa,0x2c6a, 0xc266,0x3ff5,
                 0xa58d,0x2ee4, 0x011c,0x2cb2, 0xc197,0x3ffb,
                 0xa581,0x2e15, 0x008e,0x2cfa, 0xc0ca,0x3fff,
                 0xa57e,0x2d41, 0x0000,0x2d41, 0xc000,0x4000,
                 0xa581,0x2c6a, 0xff72,0x2d88, 0xbf38,0x3fff,
                 0xa58d,0x2b8f, 0xfee4,0x2dcf, 0xbe73,0x3ffb,
                 0xa5a1,0x2ab0, 0xfe56,0x2e15, 0xbdb0,0x3ff5,
                 0xa5bc,0x29ce, 0xfdc7,0x2e5a, 0xbcf0,0x3fec,
                 0xa5e0,0x28e7, 0xfd39,0x2e9f, 0xbc32,0x3fe1,
                 0xa60b,0x27fe, 0xfcab,0x2ee4, 0xbb77,0x3fd4,
                 0xa63e,0x2711, 0xfc1d,0x2f28, 0xbabf,0x3fc4,
                 0xa678,0x2620, 0xfb8f,0x2f6c, 0xba09,0x3fb1,
                 0xa6bb,0x252c, 0xfb01,0x2faf, 0xb956,0x3f9c,
                 0xa705,0x2435, 0xfa73,0x2ff2, 0xb8a6,0x3f85,
                 0xa757,0x233b, 0xf9e5,0x3034, 0xb7f8,0x3f6b,
                 0xa7b1,0x223d, 0xf957,0x3076, 0xb74d,0x3f4f,
                 0xa812,0x213d, 0xf8ca,0x30b8, 0xb6a5,0x3f30,
                 0xa87b,0x203a, 0xf83c,0x30f9, 0xb600,0x3f0f,
                 0xa8eb,0x1f34, 0xf7ae,0x3139, 0xb55e,0x3eeb,
                 0xa963,0x1e2b, 0xf721,0x3179, 0xb4be,0x3ec5,
                 0xa9e3,0x1d20, 0xf693,0x31b9, 0xb422,0x3e9d,
                 0xaa6a,0x1c12, 0xf606,0x31f8, 0xb388,0x3e72,
                 0xaaf8,0x1b02, 0xf579,0x3236, 0xb2f2,0x3e45,
                 0xab8e,0x19ef, 0xf4ec,0x3274, 0xb25e,0x3e15,
                 0xac2b,0x18db, 0xf45f,0x32b2, 0xb1cd,0x3de3,
                 0xacd0,0x17c4, 0xf3d2,0x32ef, 0xb140,0x3daf,
                 0xad7b,0x16ab, 0xf345,0x332c, 0xb0b5,0x3d78,
                 0xae2e,0x1590, 0xf2b8,0x3368, 0xb02d,0x3d3f,
                 0xaee8,0x1473, 0xf22c,0x33a3, 0xafa9,0x3d03,
                 0xafa9,0x1354, 0xf19f,0x33df, 0xaf28,0x3cc5,
                 0xb071,0x1234, 0xf113,0x3419, 0xaea9,0x3c85,
                 0xb140,0x1112, 0xf087,0x3453, 0xae2e,0x3c42,
                 0xb215,0x0fee, 0xeffb,0x348d, 0xadb6,0x3bfd,
                 0xb2f2,0x0eca, 0xef6f,0x34c6, 0xad41,0x3bb6,
                 0xb3d5,0x0da4, 0xeee3,0x34ff, 0xacd0,0x3b6d,
                 0xb4be,0x0c7c, 0xee58,0x3537, 0xac61,0x3b21,
                 0xb5af,0x0b54, 0xedcc,0x356e, 0xabf6,0x3ad3,
                 0xb6a5,0x0a2b, 0xed41,0x35a5, 0xab8e,0x3a82,
                 0xb7a2,0x0901, 0xecb6,0x35dc, 0xab29,0x3a30,
                 0xb8a6,0x07d6, 0xec2b,0x3612, 0xaac8,0x39db,
                 0xb9af,0x06aa, 0xeba1,0x3648, 0xaa6a,0x3984,
                 0xbabf,0x057e, 0xeb16,0x367d, 0xaa0f,0x392b,
                 0xbbd4,0x0451, 0xea8c,0x36b1, 0xa9b7,0x38cf,
                 0xbcf0,0x0324, 0xea02,0x36e5, 0xa963,0x3871,
                 0xbe11,0x01f7, 0xe978,0x3718, 0xa912,0x3812,
                 0xbf38,0x00c9, 0xe8ef,0x374b, 0xa8c5,0x37b0,
                 0xc065,0xff9b, 0xe865,0x377e, 0xa87b,0x374b,
                 0xc197,0xfe6e, 0xe7dc,0x37b0, 0xa834,0x36e5,
                 0xc2cf,0xfd40, 0xe753,0x37e1, 0xa7f1,0x367d,
                 0xc40c,0xfc13, 0xe6cb,0x3812, 0xa7b1,0x3612,
                 0xc54e,0xfae6, 0xe642,0x3842, 0xa774,0x35a5,
                 0xc695,0xf9ba, 0xe5ba,0x3871, 0xa73b,0x3537,
                 0xc7e1,0xf88e, 0xe532,0x38a1, 0xa705,0x34c6,
                 0xc932,0xf763, 0xe4aa,0x38cf, 0xa6d3,0x3453,
                 0xca88,0xf639, 0xe423,0x38fd, 0xa6a4,0x33df,
                 0xcbe2,0xf50f, 0xe39c,0x392b, 0xa678,0x3368,
                 0xcd41,0xf3e6, 0xe315,0x3958, 0xa650,0x32ef,
                 0xcea5,0xf2bf, 0xe28e,0x3984, 0xa62c,0x3274,
                 0xd00c,0xf198, 0xe208,0x39b0, 0xa60b,0x31f8,
                 0xd178,0xf073, 0xe182,0x39db, 0xa5ed,0x3179,
                 0xd2e8,0xef4f, 0xe0fc,0x3a06, 0xa5d3,0x30f9,
                 0xd45c,0xee2d, 0xe077,0x3a30, 0xa5bc,0x3076,
                 0xd5d3,0xed0c, 0xdff2,0x3a59, 0xa5a9,0x2ff2,
                 0xd74e,0xebed, 0xdf6d,0x3a82, 0xa599,0x2f6c,
                 0xd8cd,0xeacf, 0xdee9,0x3aab, 0xa58d,0x2ee4,
                 0xda4f,0xe9b4, 0xde64,0x3ad3, 0xa585,0x2e5a,
                 0xdbd5,0xe89a, 0xdde1,0x3afa, 0xa57f,0x2dcf,
                 0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41,
                 0xdee9,0xe66d, 0xdcda,0x3b47, 0xa57f,0x2cb2,
                 0xe077,0xe559, 0xdc57,0x3b6d, 0xa585,0x2c21,
                 0xe208,0xe448, 0xdbd5,0x3b92, 0xa58d,0x2b8f,
                 0xe39c,0xe33a, 0xdb52,0x3bb6, 0xa599,0x2afb,
                 0xe532,0xe22d, 0xdad1,0x3bda, 0xa5a9,0x2a65,
                 0xe6cb,0xe124, 0xda4f,0x3bfd, 0xa5bc,0x29ce,
                 0xe865,0xe01d, 0xd9ce,0x3c20, 0xa5d3,0x2935,
                 0xea02,0xdf19, 0xd94d,0x3c42, 0xa5ed,0x289a,
                 0xeba1,0xde18, 0xd8cd,0x3c64, 0xa60b,0x27fe,
                 0xed41,0xdd19, 0xd84d,0x3c85, 0xa62c,0x2760,
                 0xeee3,0xdc1e, 0xd7cd,0x3ca5, 0xa650,0x26c1,
                 0xf087,0xdb26, 0xd74e,0x3cc5, 0xa678,0x2620,
                 0xf22c,0xda31, 0xd6cf,0x3ce4, 0xa6a4,0x257e,
                 0xf3d2,0xd93f, 0xd651,0x3d03, 0xa6d3,0x24da,
                 0xf579,0xd851, 0xd5d3,0x3d21, 0xa705,0x2435,
                 0xf721,0xd766, 0xd556,0x3d3f, 0xa73b,0x238e,
                 0xf8ca,0xd67f, 0xd4d8,0x3d5b, 0xa774,0x22e7,
                 0xfa73,0xd59b, 0xd45c,0x3d78, 0xa7b1,0x223d,
                 0xfc1d,0xd4bb, 0xd3df,0x3d93, 0xa7f1,0x2193,
                 0xfdc7,0xd3df, 0xd363,0x3daf, 0xa834,0x20e7,
                 0xff72,0xd306, 0xd2e8,0x3dc9, 0xa87b,0x203a,
                 0x011c,0xd231, 0xd26d,0x3de3, 0xa8c5,0x1f8c,
                 0x02c7,0xd161, 0xd1f2,0x3dfc, 0xa912,0x1edc,
                 0x0471,0xd094, 0xd178,0x3e15, 0xa963,0x1e2b,
                 0x061b,0xcfcc, 0xd0fe,0x3e2d, 0xa9b7,0x1d79,
                 0x07c4,0xcf07, 0xd085,0x3e45, 0xaa0f,0x1cc6,
                 0x096d,0xce47, 0xd00c,0x3e5c, 0xaa6a,0x1c12,
                 0x0b14,0xcd8c, 0xcf94,0x3e72, 0xaac8,0x1b5d,
                 0x0cbb,0xccd4, 0xcf1c,0x3e88, 0xab29,0x1aa7,
                 0x0e61,0xcc21, 0xcea5,0x3e9d, 0xab8e,0x19ef,
                 0x1005,0xcb73, 0xce2e,0x3eb1, 0xabf6,0x1937,
                 0x11a8,0xcac9, 0xcdb7,0x3ec5, 0xac61,0x187e,
                 0x134a,0xca24, 0xcd41,0x3ed8, 0xacd0,0x17c4,
                 0x14ea,0xc983, 0xcccc,0x3eeb, 0xad41,0x1709,
                 0x1688,0xc8e8, 0xcc57,0x3efd, 0xadb6,0x164c,
                 0x1824,0xc850, 0xcbe2,0x3f0f, 0xae2e,0x1590,
                 0x19be,0xc7be, 0xcb6e,0x3f20, 0xaea9,0x14d2,
                 0x1b56,0xc731, 0xcafb,0x3f30, 0xaf28,0x1413,
                 0x1ceb,0xc6a8, 0xca88,0x3f40, 0xafa9,0x1354,
                 0x1e7e,0xc625, 0xca15,0x3f4f, 0xb02d,0x1294,
                 0x200e,0xc5a7, 0xc9a3,0x3f5d, 0xb0b5,0x11d3,
                 0x219c,0xc52d, 0xc932,0x3f6b, 0xb140,0x1112,
                 0x2326,0xc4b9, 0xc8c1,0x3f78, 0xb1cd,0x1050,
                 0x24ae,0xc44a, 0xc851,0x3f85, 0xb25e,0x0f8d,
                 0x2632,0xc3e0, 0xc7e1,0x3f91, 0xb2f2,0x0eca,
                 0x27b3,0xc37b, 0xc772,0x3f9c, 0xb388,0x0e06,
                 0x2931,0xc31c, 0xc703,0x3fa7, 0xb422,0x0d41,
                 0x2aaa,0xc2c1, 0xc695,0x3fb1, 0xb4be,0x0c7c,
                 0x2c21,0xc26d, 0xc627,0x3fbb, 0xb55e,0x0bb7,
                 0x2d93,0xc21d, 0xc5ba,0x3fc4, 0xb600,0x0af1,
                 0x2f02,0xc1d3, 0xc54e,0x3fcc, 0xb6a5,0x0a2b,
                 0x306c,0xc18e, 0xc4e2,0x3fd4, 0xb74d,0x0964,
                 0x31d2,0xc14f, 0xc476,0x3fdb, 0xb7f8,0x089d,
                 0x3334,0xc115, 0xc40c,0x3fe1, 0xb8a6,0x07d6,
                 0x3492,0xc0e0, 0xc3a1,0x3fe7, 0xb956,0x070e,
                 0x35eb,0xc0b1, 0xc338,0x3fec, 0xba09,0x0646,
                 0x373f,0xc088, 0xc2cf,0x3ff1, 0xbabf,0x057e,
                 0x388e,0xc064, 0xc266,0x3ff5, 0xbb77,0x04b5,
                 0x39d9,0xc045, 0xc1fe,0x3ff8, 0xbc32,0x03ed,
                 0x3b1e,0xc02c, 0xc197,0x3ffb, 0xbcf0,0x0324,
                 0x3c5f,0xc019, 0xc130,0x3ffd, 0xbdb0,0x025b,
                 0x3d9a,0xc00b, 0xc0ca,0x3fff, 0xbe73,0x0192,
                 0x3ed0,0xc003, 0xc065,0x4000, 0xbf38,0x00c9
};

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __TABLE_FFT_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
