# 0 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
# 64 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
        .syntax unified
# 80 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
.macro VECTOR Name=
        .section .vectors, "a"
        .word \Name
.endm



.macro ISR_HANDLER Name=



        .section .vectors, "a"
        .word \Name



        .section .init.\Name, "ax"
        .thumb_func
        .weak \Name
        .balign 2
\Name:
        1: b 1b
        END_FUNC \Name
.endm




.macro ISR_RESERVED
        .section .vectors, "a"
        .word 0
.endm




.macro END_FUNC name
        .size \name,.-\name
.endm
# 132 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
        .section .vectors, "a"
        .code 16
        .balign 4
        .global _vectors
_vectors:
        VECTOR __stack_end__
        VECTOR Reset_Handler
        ISR_HANDLER NMI_Handler
        VECTOR HardFault_Handler
        ISR_HANDLER MemManage_Handler
        ISR_HANDLER BusFault_Handler
        ISR_HANDLER UsageFault_Handler
        ISR_RESERVED
        ISR_RESERVED
        ISR_RESERVED
        ISR_RESERVED
        ISR_HANDLER SVC_Handler
        ISR_HANDLER DebugMon_Handler
        ISR_RESERVED
        ISR_HANDLER PendSV_Handler
        ISR_HANDLER SysTick_Handler
# 162 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
        .section .vectors, "a"
        .size _vectors, .-_vectors
_vectors_end:
# 187 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
        .global reset_handler
        .global Reset_Handler
        .equ reset_handler, Reset_Handler
        .section .init.Reset_Handler, "ax"
        .balign 2
        .thumb_func
Reset_Handler:






        movs R0, #8
        ldr R0, [R0]
        nop
        nop
# 218 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
        bl SystemInit
# 233 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
        bl _start
END_FUNC Reset_Handler





        .weak SystemInit
# 262 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
        .weak HardFault_Handler
        .section .init.HardFault_Handler, "ax"
        .balign 2
        .thumb_func
HardFault_Handler:



        ldr R1, =0xE000ED2C
        ldr R2, [R1]
        cmp R2, #0

.LHardFault_Handler_hfLoop:
        bmi .LHardFault_Handler_hfLoop
# 290 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
        tst LR, #4
        ite eq
        mrseq R0, MSP
        mrsne R0, PSP
# 304 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/samples/Cortex_M_Startup.s"
        orr R2, R2, #0x80000000
        str R2, [R1]




        ldr R1, [R0, #24]
        adds R1, #2
        str R1, [R0, #24]

        bx LR
END_FUNC HardFault_Handler
