/**
 * Copyright (c) 2014 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "sdk_common.h"
/** @file
 *
 * @defgroup retarget Retarget layer for stdio functions
 * @{
 * @ingroup app_common
 * @} */
#if NRF_MODULE_ENABLED(RETARGET)
#if !defined(NRF_LOG_USES_RTT) || NRF_LOG_USES_RTT != 1
#if !defined(HAS_SIMPLE_UART_RETARGET)


#include <stdio.h>
#include <stdint.h>
#include "app_uart.h"
#include "nrf_error.h"

#undef __IS_COMPILER_ARM_COMPILER_5__
#if ((__ARMCC_VERSION >= 5000000) && (__ARMCC_VERSION < 6000000))
#define __IS_COMPILER_ARM_COMPILER_5__ 1
#endif

#undef __IS_COMPILER_ARM_COMPILER_6__
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define __IS_COMPILER_ARM_COMPILER_6__ 1
#endif

#undef __IS_COMPILER_ARM_COMPILER__
#if defined(__IS_COMPILER_ARM_COMPILER_5__) && __IS_COMPILER_ARM_COMPILER_5__ \
|| defined(__IS_COMPILER_ARM_COMPILER_6__) && __IS_COMPILER_ARM_COMPILER_6__
#define __IS_COMPILER_ARM_COMPILER__ 1
#endif

#undef __IS_COMPILER_LLVM__
#if defined(__clang__) && !__IS_COMPILER_ARM_COMPILER_6__
#define __IS_COMPILER_LLVM__ 1
#endif

#undef __IS_COMPILER_GCC__
#if defined(__GNUC__) && !(  defined(__IS_COMPILER_ARM_COMPILER__) \
|| defined(__IS_COMPILER_LLVM__) || defined(__IS_COMPILER_IAR__))
#define __IS_COMPILER_GCC__ 1
#endif

#if __IS_COMPILER_ARM_COMPILER_6__
__asm(".global __ARM_use_no_argv\n\t");
#endif

#if __IS_COMPILER_ARM_COMPILER_6__
#ifndef __MICROLIB
__asm(".global __ARM_use_no_argv\n\t");
#endif
#endif

#if defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

// This part is taken from MDK-ARM template file and is required here to prevent
// linker from selecting libraries functions that use semihosting and failing
// because of multiple definitions of fgetc() and fputc().
// Refer to: http://www.keil.com/support/man/docs/gsac/gsac_retargetcortex.htm
// -- BEGIN --
//struct __FILE { int handle; /* Add whatever you need here */ };
//FILE __stdout;
//FILE __stdin;
// --- END ---

int fgetc(FILE * p_file)
{
    uint8_t input;
    while (app_uart_get(&input) == NRF_ERROR_NOT_FOUND)
    {
        // No implementation needed.
    }
    return input;
}

int fputc(int ch, FILE * p_file)
{
    UNUSED_PARAMETER(p_file);

    UNUSED_VARIABLE(app_uart_put((uint8_t)ch));
    return ch;
}

#elif defined(__GNUC__) && defined(__SES_ARM)

int __getchar(FILE * p_file)
{
    uint8_t input;
    while (app_uart_get(&input) == NRF_ERROR_NOT_FOUND)
    {
        // No implementation needed.
    }
    return input;
}

#if defined(__SES_VERSION) && (__SES_VERSION >= 34000)
int __putchar(int ch, FILE * tag_ptr)
{
    UNUSED_PARAMETER(tag_ptr);

    UNUSED_VARIABLE(app_uart_put((uint8_t)ch));
    return ch;
}
#else
int __putchar(int ch, FILE * p_file)
{
    UNUSED_PARAMETER(p_file);

    UNUSED_VARIABLE(app_uart_put((uint8_t)ch));
    return ch;
}
#endif

#elif defined(__GNUC__) && !defined(__SES_ARM)

int _write(int file, const char * p_char, int len)
{
    int i;

    UNUSED_PARAMETER(file);

    for (i = 0; i < len; i++)
    {
        UNUSED_VARIABLE(app_uart_put(*p_char++));
    }

    return len;
}

int _read(int file, char * p_char, int len)
{
    UNUSED_PARAMETER(file);
    while (app_uart_get((uint8_t *)p_char) == NRF_ERROR_NOT_FOUND)
    {
        // No implementation needed.
    }

    return 1;
}
#elif defined(__ICCARM__)

size_t __write(int handle, const unsigned char * buffer, size_t size)
{
    int i;
    UNUSED_PARAMETER(handle);
    for (i = 0; i < size; i++)
    {
        UNUSED_VARIABLE(app_uart_put(*buffer++));
    }
    return size;
}

size_t __read(int handle, unsigned char * buffer, size_t size)
{
    UNUSED_PARAMETER(handle);
    UNUSED_PARAMETER(size);
    while (app_uart_get((uint8_t *)buffer) == NRF_ERROR_NOT_FOUND)
    {
        // No implementation needed.
    }

    return 1;
}

long __lseek(int handle, long offset, int whence)
{
    return -1;
}
int __close(int handle)
{
    return 0;
}
int remove(const char * filename)
{
    return 0;
}

#endif

#endif // !defined(HAS_SIMPLE_UART_RETARGET)
#endif // NRF_LOG_USES_RTT != 1
#endif //NRF_MODULE_ENABLED(RETARGET)
