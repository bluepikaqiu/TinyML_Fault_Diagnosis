	.cpu cortex-m4
	.arch armv7e-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 38, 1
	.eabi_attribute 18, 4
	.file	"SupportFunctionsF16.c"
	.text
.Ltext0:
	.file 1 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/SupportFunctionsF16.c"
	.section	.text.arm_copy_f16,"ax",%progbits
	.align	1
	.global	arm_copy_f16
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_copy_f16, %function
arm_copy_f16:
.LFB134:
	.file 2 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_copy_f16.c"
	.loc 2 80 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	sub	sp, sp, #24
.LCFI0:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	.loc 2 108 10
	ldr	r3, [sp, #4]
	str	r3, [sp, #20]
	.loc 2 112 9
	b	.L2
.L3:
	.loc 2 117 20
	ldr	r2, [sp, #12]
	adds	r3, r2, #2
	str	r3, [sp, #12]
	.loc 2 117 10
	ldr	r3, [sp, #8]
	adds	r1, r3, #2
	str	r1, [sp, #8]
	.loc 2 117 15
	ldrh	r2, [r2]	@ __fp16
	.loc 2 117 13
	strh	r2, [r3]	@ __fp16
	.loc 2 120 11
	ldr	r3, [sp, #20]
	subs	r3, r3, #1
	str	r3, [sp, #20]
.L2:
	.loc 2 112 17
	ldr	r3, [sp, #20]
	cmp	r3, #0
	bne	.L3
	.loc 2 122 1
	nop
	nop
	add	sp, sp, #24
.LCFI1:
	@ sp needed
	bx	lr
.LFE134:
	.size	arm_copy_f16, .-arm_copy_f16
	.section	.text.arm_fill_f16,"ax",%progbits
	.align	1
	.global	arm_fill_f16
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_fill_f16, %function
arm_fill_f16:
.LFB135:
	.file 3 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_fill_f16.c"
	.loc 3 77 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	sub	sp, sp, #24
.LCFI2:
	strh	r0, [sp, #14]	@ __fp16
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	.loc 3 105 10
	ldr	r3, [sp, #4]
	str	r3, [sp, #20]
	.loc 3 109 9
	b	.L5
.L6:
	.loc 3 114 10
	ldr	r3, [sp, #8]
	adds	r2, r3, #2
	str	r2, [sp, #8]
	.loc 3 114 13
	ldrh	r2, [sp, #14]	@ __fp16
	strh	r2, [r3]	@ __fp16
	.loc 3 117 11
	ldr	r3, [sp, #20]
	subs	r3, r3, #1
	str	r3, [sp, #20]
.L5:
	.loc 3 109 17
	ldr	r3, [sp, #20]
	cmp	r3, #0
	bne	.L6
	.loc 3 119 1
	nop
	nop
	add	sp, sp, #24
.LCFI3:
	@ sp needed
	bx	lr
.LFE135:
	.size	arm_fill_f16, .-arm_fill_f16
	.global	__gnu_h2f_ieee
	.global	__aeabi_fmul
	.global	__aeabi_f2iz
	.section	.text.arm_f16_to_q15,"ax",%progbits
	.align	1
	.global	arm_f16_to_q15
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_f16_to_q15, %function
arm_f16_to_q15:
.LFB136:
	.file 4 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_f16_to_q15.c"
	.loc 4 103 1
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{lr}
.LCFI4:
	sub	sp, sp, #36
.LCFI5:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	.loc 4 104 22
	ldr	r3, [sp, #12]
	str	r3, [sp, #28]
	.loc 4 113 12
	ldr	r3, [sp, #4]
	str	r3, [sp, #24]
	.loc 4 115 11
	b	.L8
.L12:
	.loc 4 139 58
	ldr	r3, [sp, #28]
	adds	r2, r3, #2
	str	r2, [sp, #28]
	.loc 4 139 54
	ldrh	r3, [r3]	@ __fp16
	.loc 4 139 44
	mov	r0, r3	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	.loc 4 139 61
	mov	r1, #1191182336
	mov	r0, r3
	bl	__aeabi_fmul
	mov	r3, r0
	.loc 4 139 19
	mov	r0, r3
	bl	__aeabi_f2iz
	mov	r1, r0
	.loc 4 139 14
	ldr	r2, [sp, #8]
	adds	r3, r2, #2
	str	r3, [sp, #8]
	str	r1, [sp, #20]
.LBB4:
.LBB5:
	.file 5 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Include/dsp/none.h"
	.loc 5 169 24
	ldr	r3, [sp, #20]
	asrs	r1, r3, #16
	.loc 5 169 45
	ldr	r3, [sp, #20]
	asrs	r3, r3, #15
	.loc 5 170 40
	cmp	r1, r3
	beq	.L9
	.loc 5 170 30
	ldr	r3, [sp, #20]
	asrs	r3, r3, #31
	.loc 5 170 19
	sxth	r3, r3
	.loc 5 170 40
	eor	r3, r3, #32640
	eor	r3, r3, #127
	sxth	r3, r3
	b	.L13
.L9:
	ldr	r3, [sp, #20]
	sxth	r3, r3
.L13:
.LBE5:
.LBE4:
	.loc 4 139 17
	strh	r3, [r2]	@ movhi
	.loc 4 146 15
	ldr	r3, [sp, #24]
	subs	r3, r3, #1
	str	r3, [sp, #24]
.L8:
	.loc 4 115 19
	ldr	r3, [sp, #24]
	cmp	r3, #0
	bne	.L12
	.loc 4 149 1
	nop
	nop
	add	sp, sp, #36
.LCFI6:
	@ sp needed
	ldr	pc, [sp], #4
.LFE136:
	.size	arm_f16_to_q15, .-arm_f16_to_q15
	.section	.text.arm_f16_to_float,"ax",%progbits
	.align	1
	.global	arm_f16_to_float
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_f16_to_float, %function
arm_f16_to_float:
.LFB137:
	.file 6 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_f16_to_float.c"
	.loc 6 108 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI7:
	sub	sp, sp, #24
.LCFI8:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	.loc 6 109 22
	ldr	r3, [sp, #12]
	str	r3, [sp, #20]
	.loc 6 115 12
	ldr	r3, [sp, #4]
	str	r3, [sp, #16]
	.loc 6 117 11
	b	.L15
.L16:
	.loc 6 120 36
	ldr	r3, [sp, #20]
	adds	r2, r3, #2
	str	r2, [sp, #20]
	.loc 6 120 31
	ldrh	r2, [r3]	@ __fp16
	.loc 6 120 14
	ldr	r4, [sp, #8]
	adds	r3, r4, #4
	str	r3, [sp, #8]
	.loc 6 120 19
	mov	r0, r2	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	.loc 6 120 17
	str	r3, [r4]	@ float
	.loc 6 124 15
	ldr	r3, [sp, #16]
	subs	r3, r3, #1
	str	r3, [sp, #16]
.L15:
	.loc 6 117 19
	ldr	r3, [sp, #16]
	cmp	r3, #0
	bne	.L16
	.loc 6 126 1
	nop
	nop
	add	sp, sp, #24
.LCFI9:
	@ sp needed
	pop	{r4, pc}
.LFE137:
	.size	arm_f16_to_float, .-arm_f16_to_float
	.global	__aeabi_f2d
	.section	.text.arm_f16_to_f64,"ax",%progbits
	.align	1
	.global	arm_f16_to_f64
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_f16_to_f64, %function
arm_f16_to_f64:
.LFB138:
	.file 7 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_f16_to_f64.c"
	.loc 7 56 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI10:
	sub	sp, sp, #24
.LCFI11:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	.loc 7 57 22
	ldr	r3, [sp, #12]
	str	r3, [sp, #20]
	.loc 7 63 12
	ldr	r3, [sp, #4]
	str	r3, [sp, #16]
	.loc 7 65 11
	b	.L18
.L19:
	.loc 7 68 36
	ldr	r3, [sp, #20]
	adds	r2, r3, #2
	str	r2, [sp, #20]
	.loc 7 68 31
	ldrh	r2, [r3]	@ __fp16
	.loc 7 68 14
	ldr	r4, [sp, #8]
	add	r3, r4, #8
	str	r3, [sp, #8]
	.loc 7 68 19
	mov	r0, r2	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	mov	r0, r3
	bl	__aeabi_f2d
	mov	r2, r0
	mov	r3, r1
	.loc 7 68 17
	strd	r2, [r4]
	.loc 7 72 15
	ldr	r3, [sp, #16]
	subs	r3, r3, #1
	str	r3, [sp, #16]
.L18:
	.loc 7 65 19
	ldr	r3, [sp, #16]
	cmp	r3, #0
	bne	.L19
	.loc 7 74 1
	nop
	nop
	add	sp, sp, #24
.LCFI12:
	@ sp needed
	pop	{r4, pc}
.LFE138:
	.size	arm_f16_to_f64, .-arm_f16_to_f64
	.global	__gnu_d2h_ieee
	.section	.text.arm_f64_to_f16,"ax",%progbits
	.align	1
	.global	arm_f64_to_f16
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_f64_to_f16, %function
arm_f64_to_f16:
.LFB139:
	.file 8 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_f64_to_f16.c"
	.loc 8 60 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI13:
	sub	sp, sp, #24
.LCFI14:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	.loc 8 61 22
	ldr	r3, [sp, #12]
	str	r3, [sp, #20]
	.loc 8 67 12
	ldr	r3, [sp, #4]
	str	r3, [sp, #16]
	.loc 8 69 11
	b	.L21
.L22:
	.loc 8 72 36
	ldr	r3, [sp, #20]
	add	r2, r3, #8
	str	r2, [sp, #20]
	.loc 8 72 31
	ldrd	r2, [r3]
	.loc 8 72 14
	ldr	r4, [sp, #8]
	adds	r1, r4, #2
	str	r1, [sp, #8]
	.loc 8 72 19
	mov	r0, r2
	mov	r1, r3
	bl	__gnu_d2h_ieee
	mov	r3, r0	@ __fp16
	.loc 8 72 17
	strh	r3, [r4]	@ __fp16
	.loc 8 76 15
	ldr	r3, [sp, #16]
	subs	r3, r3, #1
	str	r3, [sp, #16]
.L21:
	.loc 8 69 19
	ldr	r3, [sp, #16]
	cmp	r3, #0
	bne	.L22
	.loc 8 78 1
	nop
	nop
	add	sp, sp, #24
.LCFI15:
	@ sp needed
	pop	{r4, pc}
.LFE139:
	.size	arm_f64_to_f16, .-arm_f64_to_f16
	.global	__aeabi_i2f
	.global	__gnu_f2h_ieee
	.global	__aeabi_fdiv
	.section	.text.arm_q15_to_f16,"ax",%progbits
	.align	1
	.global	arm_q15_to_f16
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_q15_to_f16, %function
arm_q15_to_f16:
.LFB140:
	.file 9 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_q15_to_f16.c"
	.loc 9 103 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI16:
	sub	sp, sp, #24
.LCFI17:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	.loc 9 105 16
	ldr	r3, [sp, #12]
	str	r3, [sp, #16]
	.loc 9 132 10
	ldr	r3, [sp, #4]
	str	r3, [sp, #20]
	.loc 9 136 9
	b	.L24
.L25:
	.loc 9 141 31
	ldr	r3, [sp, #16]
	adds	r2, r3, #2
	str	r2, [sp, #16]
	.loc 9 141 27
	ldrsh	r3, [r3]
	.loc 9 141 16
	mov	r0, r3
	bl	__aeabi_i2f
	mov	r3, r0
	mov	r0, r3
	bl	__gnu_f2h_ieee
	mov	r3, r0	@ __fp16
	mov	r0, r3	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	.loc 9 141 34
	mov	r1, #1191182336
	mov	r0, r3
	bl	__aeabi_fdiv
	mov	r3, r0
	mov	r2, r3
	.loc 9 141 10
	ldr	r4, [sp, #8]
	adds	r3, r4, #2
	str	r3, [sp, #8]
	.loc 9 141 34
	mov	r0, r2
	bl	__gnu_f2h_ieee
	mov	r3, r0	@ __fp16
	.loc 9 141 13
	strh	r3, [r4]	@ __fp16
	.loc 9 144 11
	ldr	r3, [sp, #20]
	subs	r3, r3, #1
	str	r3, [sp, #20]
.L24:
	.loc 9 136 17
	ldr	r3, [sp, #20]
	cmp	r3, #0
	bne	.L25
	.loc 9 147 1
	nop
	nop
	add	sp, sp, #24
.LCFI18:
	@ sp needed
	pop	{r4, pc}
.LFE140:
	.size	arm_q15_to_f16, .-arm_q15_to_f16
	.section	.text.arm_float_to_f16,"ax",%progbits
	.align	1
	.global	arm_float_to_f16
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_float_to_f16, %function
arm_float_to_f16:
.LFB141:
	.file 10 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_float_to_f16.c"
	.loc 10 105 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI19:
	sub	sp, sp, #24
.LCFI20:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	.loc 10 106 22
	ldr	r3, [sp, #12]
	str	r3, [sp, #20]
	.loc 10 112 12
	ldr	r3, [sp, #4]
	str	r3, [sp, #16]
	.loc 10 114 11
	b	.L27
.L28:
	.loc 10 117 36
	ldr	r3, [sp, #20]
	adds	r2, r3, #4
	str	r2, [sp, #20]
	.loc 10 117 31
	ldr	r2, [r3]	@ float
	.loc 10 117 14
	ldr	r4, [sp, #8]
	adds	r3, r4, #2
	str	r3, [sp, #8]
	.loc 10 117 19
	mov	r0, r2
	bl	__gnu_f2h_ieee
	mov	r3, r0	@ __fp16
	.loc 10 117 17
	strh	r3, [r4]	@ __fp16
	.loc 10 121 15
	ldr	r3, [sp, #16]
	subs	r3, r3, #1
	str	r3, [sp, #16]
.L27:
	.loc 10 114 19
	ldr	r3, [sp, #16]
	cmp	r3, #0
	bne	.L28
	.loc 10 123 1
	nop
	nop
	add	sp, sp, #24
.LCFI21:
	@ sp needed
	pop	{r4, pc}
.LFE141:
	.size	arm_float_to_f16, .-arm_float_to_f16
	.global	__aeabi_fadd
	.section	.text.arm_weighted_sum_f16,"ax",%progbits
	.align	1
	.global	arm_weighted_sum_f16
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_weighted_sum_f16, %function
arm_weighted_sum_f16:
.LFB142:
	.file 11 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_weighted_sum_f16.c"
	.loc 11 116 1
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
.LCFI22:
	sub	sp, sp, #36
.LCFI23:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	.loc 11 123 9
	ldr	r3, [sp, #12]
	str	r3, [sp, #24]
	.loc 11 124 8
	ldr	r3, [sp, #8]
	str	r3, [sp, #20]
	.loc 11 126 11
	movw	r3, #0
	strh	r3, [sp, #30]	@ __fp16
	.loc 11 127 11
	movw	r3, #0
	strh	r3, [sp, #28]	@ __fp16
	.loc 11 129 12
	ldr	r3, [sp, #4]
	str	r3, [sp, #16]
	.loc 11 130 10
	b	.L30
.L31:
	.loc 11 132 33
	ldr	r3, [sp, #24]
	adds	r2, r3, #2
	str	r2, [sp, #24]
	.loc 11 132 29
	ldrh	r3, [r3]	@ __fp16
	.loc 11 132 19
	mov	r0, r3	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r4, r0
	.loc 11 132 48
	ldr	r3, [sp, #20]
	ldrh	r3, [r3]	@ __fp16
	.loc 11 132 38
	mov	r0, r3	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	.loc 11 132 36
	mov	r1, r3
	mov	r0, r4
	bl	__aeabi_fmul
	mov	r3, r0
	mov	r4, r3
	.loc 11 132 16
	ldrh	r0, [sp, #30]	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	mov	r1, r3
	mov	r0, r4
	bl	__aeabi_fadd
	mov	r3, r0
	mov	r0, r3
	bl	__gnu_f2h_ieee
	mov	r3, r0	@ __fp16
	strh	r3, [sp, #30]	@ __fp16
	.loc 11 133 32
	ldr	r3, [sp, #20]
	adds	r2, r3, #2
	str	r2, [sp, #20]
	.loc 11 133 19
	ldrh	r4, [r3]	@ __fp16
	.loc 11 133 16
	ldrh	r0, [sp, #28]	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r5, r0
	.loc 11 133 19
	mov	r0, r4	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	.loc 11 133 16
	mov	r1, r3
	mov	r0, r5
	bl	__aeabi_fadd
	mov	r3, r0
	mov	r0, r3
	bl	__gnu_f2h_ieee
	mov	r3, r0	@ __fp16
	strh	r3, [sp, #28]	@ __fp16
	.loc 11 134 15
	ldr	r3, [sp, #16]
	subs	r3, r3, #1
	str	r3, [sp, #16]
.L30:
	.loc 11 130 18
	ldr	r3, [sp, #16]
	cmp	r3, #0
	bne	.L31
	.loc 11 137 19
	ldrh	r0, [sp, #30]	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r4, r0
	ldrh	r0, [sp, #28]	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	mov	r1, r3
	mov	r0, r4
	bl	__aeabi_fdiv
	mov	r3, r0
	mov	r0, r3
	bl	__gnu_f2h_ieee
	mov	r3, r0	@ __fp16
	.loc 11 138 1
	mov	r0, r3	@ __fp16
	add	sp, sp, #36
.LCFI24:
	@ sp needed
	pop	{r4, r5, pc}
.LFE142:
	.size	arm_weighted_sum_f16, .-arm_weighted_sum_f16
	.section	.text.arm_barycenter_f16,"ax",%progbits
	.align	1
	.global	arm_barycenter_f16
	.syntax unified
	.thumb
	.thumb_func
	.type	arm_barycenter_f16, %function
arm_barycenter_f16:
.LFB143:
	.file 12 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/SupportFunctions/arm_barycenter_f16.c"
	.loc 12 211 1
	@ args = 4, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
.LCFI25:
	sub	sp, sp, #44
.LCFI26:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	str	r3, [sp]
	.loc 12 218 17
	ldr	r3, [sp]
	str	r3, [sp, #24]
	.loc 12 219 17
	ldr	r3, [sp, #56]
	str	r3, [sp, #20]
	.loc 12 221 10
	movw	r3, #0
	strh	r3, [sp, #18]	@ __fp16
	.loc 12 223 7
	ldr	r3, [sp, #8]
	str	r3, [sp, #32]
	.loc 12 224 8
	ldr	r3, [sp, #12]
	str	r3, [sp, #36]
	.loc 12 227 17
	ldr	r3, [sp, #56]
	str	r3, [sp, #20]
	.loc 12 228 9
	ldr	r3, [sp, #4]
	str	r3, [sp, #28]
	.loc 12 230 9
	b	.L34
.L35:
	.loc 12 232 16
	ldr	r3, [sp, #28]
	movw	r2, #0
	strh	r2, [r3]	@ __fp16
	.loc 12 233 14
	ldr	r3, [sp, #28]
	adds	r3, r3, #2
	str	r3, [sp, #28]
	.loc 12 234 22
	ldr	r3, [sp, #20]
	subs	r3, r3, #1
	str	r3, [sp, #20]
.L34:
	.loc 12 230 23
	ldr	r3, [sp, #20]
	cmp	r3, #0
	bne	.L35
	.loc 12 238 9
	b	.L36
.L39:
	.loc 12 240 12
	ldr	r3, [sp, #4]
	str	r3, [sp, #28]
	.loc 12 241 14
	ldr	r3, [sp, #32]
	adds	r2, r3, #2
	str	r2, [sp, #32]
	.loc 12 241 9
	ldrh	r3, [r3]	@ __fp16
	strh	r3, [sp, #16]	@ __fp16
	.loc 12 242 13
	ldrh	r0, [sp, #18]	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r4, r0
	ldrh	r0, [sp, #16]	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	mov	r1, r3
	mov	r0, r4
	bl	__aeabi_fadd
	mov	r3, r0
	mov	r0, r3
	bl	__gnu_f2h_ieee
	mov	r3, r0	@ __fp16
	strh	r3, [sp, #18]	@ __fp16
	.loc 12 244 20
	ldr	r3, [sp, #56]
	str	r3, [sp, #20]
	.loc 12 245 12
	b	.L37
.L38:
	.loc 12 247 29
	ldr	r3, [sp, #28]
	ldrh	r3, [r3]	@ __fp16
	.loc 12 247 19
	mov	r0, r3	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r4, r0
	.loc 12 247 51
	ldr	r3, [sp, #36]
	adds	r2, r3, #2
	str	r2, [sp, #36]
	.loc 12 247 47
	ldrh	r3, [r3]	@ __fp16
	.loc 12 247 37
	mov	r0, r3	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r5, r0
	.loc 12 247 56
	ldrh	r0, [sp, #16]	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	.loc 12 247 54
	mov	r1, r3
	mov	r0, r5
	bl	__aeabi_fmul
	mov	r3, r0
	.loc 12 247 35
	mov	r1, r3
	mov	r0, r4
	bl	__aeabi_fadd
	mov	r3, r0
	mov	r0, r3
	bl	__gnu_f2h_ieee
	mov	r2, r0	@ __fp16
	.loc 12 247 17
	ldr	r3, [sp, #28]
	strh	r2, [r3]	@ __fp16
	.loc 12 248 15
	ldr	r3, [sp, #28]
	adds	r3, r3, #2
	str	r3, [sp, #28]
	.loc 12 249 23
	ldr	r3, [sp, #20]
	subs	r3, r3, #1
	str	r3, [sp, #20]
.L37:
	.loc 12 245 26
	ldr	r3, [sp, #20]
	cmp	r3, #0
	bne	.L38
	.loc 12 252 19
	ldr	r3, [sp, #24]
	subs	r3, r3, #1
	str	r3, [sp, #24]
.L36:
	.loc 12 238 23
	ldr	r3, [sp, #24]
	cmp	r3, #0
	bne	.L39
	.loc 12 256 17
	ldr	r3, [sp, #56]
	str	r3, [sp, #20]
	.loc 12 257 9
	ldr	r3, [sp, #4]
	str	r3, [sp, #28]
	.loc 12 259 9
	b	.L40
.L41:
	.loc 12 261 28
	ldr	r3, [sp, #28]
	ldrh	r3, [r3]	@ __fp16
	.loc 12 261 34
	mov	r0, r3	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r4, r0
	ldrh	r0, [sp, #18]	@ __fp16
	bl	__gnu_h2f_ieee
	mov	r3, r0
	mov	r1, r3
	mov	r0, r4
	bl	__aeabi_fdiv
	mov	r3, r0
	mov	r0, r3
	bl	__gnu_f2h_ieee
	mov	r2, r0	@ __fp16
	.loc 12 261 16
	ldr	r3, [sp, #28]
	strh	r2, [r3]	@ __fp16
	.loc 12 262 14
	ldr	r3, [sp, #28]
	adds	r3, r3, #2
	str	r3, [sp, #28]
	.loc 12 263 22
	ldr	r3, [sp, #20]
	subs	r3, r3, #1
	str	r3, [sp, #20]
.L40:
	.loc 12 259 23
	ldr	r3, [sp, #20]
	cmp	r3, #0
	bne	.L41
	.loc 12 266 1
	nop
	nop
	add	sp, sp, #44
.LCFI27:
	@ sp needed
	pop	{r4, r5, pc}
.LFE143:
	.size	arm_barycenter_f16, .-arm_barycenter_f16
	.section	.debug_frame,"",%progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x3
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB134
	.4byte	.LFE134-.LFB134
	.byte	0x4
	.4byte	.LCFI0-.LFB134
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0xe
	.uleb128 0
	.align	2
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB135
	.4byte	.LFE135-.LFB135
	.byte	0x4
	.4byte	.LCFI2-.LFB135
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0xe
	.uleb128 0
	.align	2
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB136
	.4byte	.LFE136-.LFB136
	.byte	0x4
	.4byte	.LCFI4-.LFB136
	.byte	0xe
	.uleb128 0x4
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI5-.LCFI4
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	.LCFI6-.LCFI5
	.byte	0xe
	.uleb128 0x4
	.align	2
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB137
	.4byte	.LFE137-.LFB137
	.byte	0x4
	.4byte	.LCFI7-.LFB137
	.byte	0xe
	.uleb128 0x8
	.byte	0x84
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI8-.LCFI7
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI9-.LCFI8
	.byte	0xe
	.uleb128 0x8
	.align	2
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB138
	.4byte	.LFE138-.LFB138
	.byte	0x4
	.4byte	.LCFI10-.LFB138
	.byte	0xe
	.uleb128 0x8
	.byte	0x84
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI11-.LCFI10
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI12-.LCFI11
	.byte	0xe
	.uleb128 0x8
	.align	2
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB139
	.4byte	.LFE139-.LFB139
	.byte	0x4
	.4byte	.LCFI13-.LFB139
	.byte	0xe
	.uleb128 0x8
	.byte	0x84
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI14-.LCFI13
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI15-.LCFI14
	.byte	0xe
	.uleb128 0x8
	.align	2
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB140
	.4byte	.LFE140-.LFB140
	.byte	0x4
	.4byte	.LCFI16-.LFB140
	.byte	0xe
	.uleb128 0x8
	.byte	0x84
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI17-.LCFI16
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI18-.LCFI17
	.byte	0xe
	.uleb128 0x8
	.align	2
.LEFDE12:
.LSFDE14:
	.4byte	.LEFDE14-.LASFDE14
.LASFDE14:
	.4byte	.Lframe0
	.4byte	.LFB141
	.4byte	.LFE141-.LFB141
	.byte	0x4
	.4byte	.LCFI19-.LFB141
	.byte	0xe
	.uleb128 0x8
	.byte	0x84
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI20-.LCFI19
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI21-.LCFI20
	.byte	0xe
	.uleb128 0x8
	.align	2
.LEFDE14:
.LSFDE16:
	.4byte	.LEFDE16-.LASFDE16
.LASFDE16:
	.4byte	.Lframe0
	.4byte	.LFB142
	.4byte	.LFE142-.LFB142
	.byte	0x4
	.4byte	.LCFI22-.LFB142
	.byte	0xe
	.uleb128 0xc
	.byte	0x84
	.uleb128 0x3
	.byte	0x85
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI23-.LCFI22
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.4byte	.LCFI24-.LCFI23
	.byte	0xe
	.uleb128 0xc
	.align	2
.LEFDE16:
.LSFDE18:
	.4byte	.LEFDE18-.LASFDE18
.LASFDE18:
	.4byte	.Lframe0
	.4byte	.LFB143
	.4byte	.LFE143-.LFB143
	.byte	0x4
	.4byte	.LCFI25-.LFB143
	.byte	0xe
	.uleb128 0xc
	.byte	0x84
	.uleb128 0x3
	.byte	0x85
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI26-.LCFI25
	.byte	0xe
	.uleb128 0x38
	.byte	0x4
	.4byte	.LCFI27-.LCFI26
	.byte	0xe
	.uleb128 0xc
	.align	2
.LEFDE18:
	.text
.Letext0:
	.file 13 "C:/SEGGER/SEGGER Embedded Studio for ARM 7.30/include/stdint.h"
	.file 14 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Include/arm_math_types.h"
	.file 15 "C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Include/arm_math_types_f16.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x5cd
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0xc
	.4byte	.LASF51
	.4byte	.LASF52
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF2
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.uleb128 0x4
	.4byte	.LASF6
	.byte	0xd
	.2byte	0x112
	.byte	0x29
	.4byte	0x55
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x4
	.4byte	.LASF7
	.byte	0xd
	.2byte	0x114
	.byte	0x29
	.4byte	0x70
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x4
	.4byte	.LASF9
	.byte	0xd
	.2byte	0x115
	.byte	0x29
	.4byte	0x84
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF11
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF12
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.4byte	.LASF13
	.uleb128 0x3
	.byte	0x8
	.byte	0x3
	.4byte	.LASF14
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.4byte	.LASF15
	.uleb128 0x3
	.byte	0x10
	.byte	0x3
	.4byte	.LASF16
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.4byte	.LASF17
	.uleb128 0x3
	.byte	0x10
	.byte	0x3
	.4byte	.LASF18
	.uleb128 0x4
	.4byte	.LASF19
	.byte	0xe
	.2byte	0x11f
	.byte	0x13
	.4byte	0x48
	.uleb128 0x5
	.4byte	0xc3
	.uleb128 0x4
	.4byte	.LASF20
	.byte	0xe
	.2byte	0x124
	.byte	0x13
	.4byte	0x63
	.uleb128 0x4
	.4byte	.LASF21
	.byte	0xe
	.2byte	0x12f
	.byte	0x11
	.4byte	0x99
	.uleb128 0x5
	.4byte	0xe2
	.uleb128 0x4
	.4byte	.LASF22
	.byte	0xe
	.2byte	0x135
	.byte	0x12
	.4byte	0xa7
	.uleb128 0x5
	.4byte	0xf4
	.uleb128 0x6
	.4byte	.LASF23
	.byte	0xf
	.byte	0x37
	.byte	0x16
	.4byte	0x117
	.uleb128 0x5
	.4byte	0x106
	.uleb128 0x3
	.byte	0x2
	.byte	0x4
	.4byte	.LASF24
	.uleb128 0x7
	.4byte	.LASF38
	.byte	0xc
	.byte	0xd2
	.byte	0x6
	.4byte	.LFB143
	.4byte	.LFE143-.LFB143
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1e5
	.uleb128 0x8
	.ascii	"in\000"
	.byte	0xc
	.byte	0xd2
	.byte	0x2a
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x9
	.4byte	.LASF25
	.byte	0xc
	.byte	0xd2
	.byte	0x3f
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x8
	.ascii	"out\000"
	.byte	0xc
	.byte	0xd2
	.byte	0x53
	.4byte	0x1eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x9
	.4byte	.LASF26
	.byte	0xc
	.byte	0xd2
	.byte	0x61
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x9
	.4byte	.LASF27
	.byte	0xc
	.byte	0xd2
	.byte	0x74
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xa
	.ascii	"pIn\000"
	.byte	0xc
	.byte	0xd5
	.byte	0x15
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xa
	.ascii	"pW\000"
	.byte	0xc
	.byte	0xd5
	.byte	0x1a
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xb
	.4byte	.LASF28
	.byte	0xc
	.byte	0xd6
	.byte	0xf
	.4byte	0x1eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xb
	.4byte	.LASF29
	.byte	0xc
	.byte	0xd7
	.byte	0xd
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xb
	.4byte	.LASF30
	.byte	0xc
	.byte	0xd7
	.byte	0x1a
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xb
	.4byte	.LASF31
	.byte	0xc
	.byte	0xd8
	.byte	0xe
	.4byte	0x106
	.uleb128 0x2
	.byte	0x91
	.sleb128 -38
	.uleb128 0xa
	.ascii	"w\000"
	.byte	0xc
	.byte	0xd8
	.byte	0x15
	.4byte	0x106
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.4byte	0x112
	.uleb128 0xc
	.byte	0x4
	.4byte	0x106
	.uleb128 0xd
	.4byte	.LASF53
	.byte	0xb
	.byte	0x73
	.byte	0xb
	.4byte	0x106
	.4byte	.LFB142
	.4byte	.LFE142-.LFB142
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x282
	.uleb128 0x8
	.ascii	"in\000"
	.byte	0xb
	.byte	0x73
	.byte	0x31
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x9
	.4byte	.LASF32
	.byte	0xb
	.byte	0x73
	.byte	0x46
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0xb
	.byte	0x73
	.byte	0x58
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0xb
	.4byte	.LASF34
	.byte	0xb
	.byte	0x76
	.byte	0xe
	.4byte	0x282
	.uleb128 0x2
	.byte	0x91
	.sleb128 -18
	.uleb128 0xb
	.4byte	.LASF35
	.byte	0xb
	.byte	0x76
	.byte	0x16
	.4byte	0x282
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xa
	.ascii	"pIn\000"
	.byte	0xb
	.byte	0x77
	.byte	0x16
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xa
	.ascii	"pW\000"
	.byte	0xb
	.byte	0x77
	.byte	0x1c
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0xb
	.byte	0x78
	.byte	0xe
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.byte	0x2
	.byte	0x4
	.4byte	.LASF37
	.uleb128 0x7
	.4byte	.LASF39
	.byte	0xa
	.byte	0x65
	.byte	0x6
	.4byte	.LFB141
	.4byte	.LFE141-.LFB141
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2eb
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0xa
	.byte	0x66
	.byte	0x15
	.4byte	0x2eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0xa
	.byte	0x67
	.byte	0x15
	.4byte	0x1eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0xa
	.byte	0x68
	.byte	0x12
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xa
	.ascii	"pIn\000"
	.byte	0xa
	.byte	0x6a
	.byte	0x16
	.4byte	0x2eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0xa
	.byte	0x6b
	.byte	0xf
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.4byte	0xef
	.uleb128 0x7
	.4byte	.LASF42
	.byte	0x9
	.byte	0x63
	.byte	0x6
	.4byte	.LFB140
	.4byte	.LFE140-.LFB140
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x353
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x9
	.byte	0x64
	.byte	0x11
	.4byte	0x353
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x9
	.byte	0x65
	.byte	0x15
	.4byte	0x1eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x9
	.byte	0x66
	.byte	0x12
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x9
	.byte	0x68
	.byte	0x12
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xa
	.ascii	"pIn\000"
	.byte	0x9
	.byte	0x69
	.byte	0x10
	.4byte	0x353
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.4byte	0xd0
	.uleb128 0x7
	.4byte	.LASF43
	.byte	0x8
	.byte	0x38
	.byte	0x6
	.4byte	.LFB139
	.4byte	.LFE139-.LFB139
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x3bb
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x8
	.byte	0x39
	.byte	0x15
	.4byte	0x3bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x8
	.byte	0x3a
	.byte	0x15
	.4byte	0x1eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x8
	.byte	0x3b
	.byte	0x12
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xa
	.ascii	"pIn\000"
	.byte	0x8
	.byte	0x3d
	.byte	0x16
	.4byte	0x3bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x8
	.byte	0x3e
	.byte	0xf
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.4byte	0x101
	.uleb128 0x7
	.4byte	.LASF44
	.byte	0x7
	.byte	0x33
	.byte	0x6
	.4byte	.LFB138
	.4byte	.LFE138-.LFB138
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x423
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x7
	.byte	0x34
	.byte	0x15
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x7
	.byte	0x35
	.byte	0x15
	.4byte	0x423
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x7
	.byte	0x36
	.byte	0x12
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xa
	.ascii	"pIn\000"
	.byte	0x7
	.byte	0x39
	.byte	0x16
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x7
	.byte	0x3a
	.byte	0xf
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.4byte	0xf4
	.uleb128 0x7
	.4byte	.LASF45
	.byte	0x6
	.byte	0x68
	.byte	0x6
	.4byte	.LFB137
	.4byte	.LFE137-.LFB137
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x48b
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x6
	.byte	0x69
	.byte	0x15
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x6
	.byte	0x6a
	.byte	0x15
	.4byte	0x48b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x6
	.byte	0x6b
	.byte	0x12
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xa
	.ascii	"pIn\000"
	.byte	0x6
	.byte	0x6d
	.byte	0x16
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x6
	.byte	0x6e
	.byte	0xf
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.4byte	0xe2
	.uleb128 0x7
	.4byte	.LASF46
	.byte	0x4
	.byte	0x63
	.byte	0x6
	.4byte	.LFB136
	.4byte	.LFE136-.LFB136
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x50c
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x4
	.byte	0x64
	.byte	0x15
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x4
	.byte	0x65
	.byte	0x11
	.4byte	0x50c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x4
	.byte	0x66
	.byte	0x12
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xa
	.ascii	"pIn\000"
	.byte	0x4
	.byte	0x68
	.byte	0x16
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x4
	.byte	0x69
	.byte	0xf
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xe
	.4byte	0x5b8
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.byte	0x4
	.byte	0x8b
	.byte	0x13
	.uleb128 0xf
	.4byte	0x5c5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.4byte	0xc3
	.uleb128 0x10
	.4byte	.LASF47
	.byte	0x3
	.byte	0x49
	.byte	0x6
	.4byte	.LFB135
	.4byte	.LFE135-.LFB135
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x565
	.uleb128 0x9
	.4byte	.LASF48
	.byte	0x3
	.byte	0x4a
	.byte	0xd
	.4byte	0x106
	.uleb128 0x2
	.byte	0x91
	.sleb128 -10
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x3
	.byte	0x4b
	.byte	0xf
	.4byte	0x1eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x3
	.byte	0x4c
	.byte	0xc
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x3
	.byte	0x4e
	.byte	0xc
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x10
	.4byte	.LASF49
	.byte	0x2
	.byte	0x4c
	.byte	0x6
	.4byte	.LFB134
	.4byte	.LFE134-.LFB134
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5b8
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x2
	.byte	0x4d
	.byte	0x15
	.4byte	0x1e5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x2
	.byte	0x4e
	.byte	0x15
	.4byte	0x1eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x2
	.byte	0x4f
	.byte	0x12
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x2
	.byte	0x51
	.byte	0xc
	.4byte	0x77
	.uleb128 0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x11
	.4byte	.LASF54
	.byte	0x5
	.byte	0xa6
	.byte	0x1e
	.4byte	0xc3
	.byte	0x3
	.uleb128 0x12
	.ascii	"x\000"
	.byte	0x5
	.byte	0xa7
	.byte	0x9
	.4byte	0xd5
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x2134
	.uleb128 0x19
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_pubnames,"",%progbits
	.4byte	0xea
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x5d1
	.4byte	0x11e
	.ascii	"arm_barycenter_f16\000"
	.4byte	0x1f1
	.ascii	"arm_weighted_sum_f16\000"
	.4byte	0x289
	.ascii	"arm_float_to_f16\000"
	.4byte	0x2f1
	.ascii	"arm_q15_to_f16\000"
	.4byte	0x359
	.ascii	"arm_f64_to_f16\000"
	.4byte	0x3c1
	.ascii	"arm_f16_to_f64\000"
	.4byte	0x429
	.ascii	"arm_f16_to_float\000"
	.4byte	0x491
	.ascii	"arm_f16_to_q15\000"
	.4byte	0x512
	.ascii	"arm_fill_f16\000"
	.4byte	0x565
	.ascii	"arm_copy_f16\000"
	.4byte	0x5b8
	.ascii	"clip_q31_to_q15\000"
	.4byte	0
	.section	.debug_pubtypes,"",%progbits
	.4byte	0x1a4
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x5d1
	.4byte	0x25
	.ascii	"int\000"
	.4byte	0x2c
	.ascii	"char\000"
	.4byte	0x33
	.ascii	"unsigned int\000"
	.4byte	0x3a
	.ascii	"signed char\000"
	.4byte	0x41
	.ascii	"unsigned char\000"
	.4byte	0x55
	.ascii	"short int\000"
	.4byte	0x48
	.ascii	"int16_t\000"
	.4byte	0x5c
	.ascii	"short unsigned int\000"
	.4byte	0x70
	.ascii	"long int\000"
	.4byte	0x63
	.ascii	"int32_t\000"
	.4byte	0x84
	.ascii	"long unsigned int\000"
	.4byte	0x77
	.ascii	"uint32_t\000"
	.4byte	0x8b
	.ascii	"long long int\000"
	.4byte	0x92
	.ascii	"long long unsigned int\000"
	.4byte	0x99
	.ascii	"float\000"
	.4byte	0xa0
	.ascii	"complex float\000"
	.4byte	0xa7
	.ascii	"double\000"
	.4byte	0xae
	.ascii	"complex double\000"
	.4byte	0xb5
	.ascii	"long double\000"
	.4byte	0xbc
	.ascii	"complex long double\000"
	.4byte	0xc3
	.ascii	"q15_t\000"
	.4byte	0xd5
	.ascii	"q31_t\000"
	.4byte	0xe2
	.ascii	"float32_t\000"
	.4byte	0xf4
	.ascii	"float64_t\000"
	.4byte	0x117
	.ascii	"__fp16\000"
	.4byte	0x106
	.ascii	"float16_t\000"
	.4byte	0x282
	.ascii	"_Float16\000"
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x64
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB134
	.4byte	.LFE134-.LFB134
	.4byte	.LFB135
	.4byte	.LFE135-.LFB135
	.4byte	.LFB136
	.4byte	.LFE136-.LFB136
	.4byte	.LFB137
	.4byte	.LFE137-.LFB137
	.4byte	.LFB138
	.4byte	.LFE138-.LFB138
	.4byte	.LFB139
	.4byte	.LFE139-.LFB139
	.4byte	.LFB140
	.4byte	.LFE140-.LFB140
	.4byte	.LFB141
	.4byte	.LFE141-.LFB141
	.4byte	.LFB142
	.4byte	.LFE142-.LFB142
	.4byte	.LFB143
	.4byte	.LFE143-.LFB143
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB134
	.4byte	.LFE134
	.4byte	.LFB135
	.4byte	.LFE135
	.4byte	.LFB136
	.4byte	.LFE136
	.4byte	.LFB137
	.4byte	.LFE137
	.4byte	.LFB138
	.4byte	.LFE138
	.4byte	.LFB139
	.4byte	.LFE139
	.4byte	.LFB140
	.4byte	.LFE140
	.4byte	.LFB141
	.4byte	.LFE141
	.4byte	.LFB142
	.4byte	.LFE142
	.4byte	.LFB143
	.4byte	.LFE143
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF47:
	.ascii	"arm_fill_f16\000"
.LASF52:
	.ascii	"C:\\nrf52840\\my_demo\\examples\\ble_peripheral\000"
.LASF2:
	.ascii	"signed char\000"
.LASF24:
	.ascii	"__fp16\000"
.LASF37:
	.ascii	"_Float16\000"
.LASF48:
	.ascii	"value\000"
.LASF32:
	.ascii	"weigths\000"
.LASF43:
	.ascii	"arm_f64_to_f16\000"
.LASF39:
	.ascii	"arm_float_to_f16\000"
.LASF29:
	.ascii	"blkCntVector\000"
.LASF25:
	.ascii	"weights\000"
.LASF7:
	.ascii	"int32_t\000"
.LASF19:
	.ascii	"q15_t\000"
.LASF13:
	.ascii	"float\000"
.LASF11:
	.ascii	"long long int\000"
.LASF20:
	.ascii	"q31_t\000"
.LASF3:
	.ascii	"unsigned char\000"
.LASF36:
	.ascii	"blkCnt\000"
.LASF10:
	.ascii	"long unsigned int\000"
.LASF5:
	.ascii	"short unsigned int\000"
.LASF27:
	.ascii	"vecDim\000"
.LASF41:
	.ascii	"pDst\000"
.LASF50:
	.ascii	"GNU C99 12.2.1 20221205 -fmessage-length=0 -std=c99"
	.ascii	" -mcpu=cortex-m4 -mlittle-endian -mfloat-abi=soft -"
	.ascii	"mthumb -munaligned-access -mtp=soft -mfp16-format=i"
	.ascii	"eee -gdwarf-4 -g2 -gpubnames -fomit-frame-pointer -"
	.ascii	"fno-dwarf2-cfi-asm -ffunction-sections -fdata-secti"
	.ascii	"ons -fshort-enums -fno-common\000"
.LASF53:
	.ascii	"arm_weighted_sum_f16\000"
.LASF15:
	.ascii	"double\000"
.LASF34:
	.ascii	"accum1\000"
.LASF31:
	.ascii	"accum\000"
.LASF44:
	.ascii	"arm_f16_to_f64\000"
.LASF18:
	.ascii	"complex long double\000"
.LASF49:
	.ascii	"arm_copy_f16\000"
.LASF51:
	.ascii	"C:/Keil_V5/ARM/PACK/ARM/CMSIS-DSP/1.14.4/Source/Sup"
	.ascii	"portFunctions/SupportFunctionsF16.c\000"
.LASF1:
	.ascii	"unsigned int\000"
.LASF30:
	.ascii	"blkCntSample\000"
.LASF12:
	.ascii	"long long unsigned int\000"
.LASF6:
	.ascii	"int16_t\000"
.LASF45:
	.ascii	"arm_f16_to_float\000"
.LASF46:
	.ascii	"arm_f16_to_q15\000"
.LASF17:
	.ascii	"long double\000"
.LASF28:
	.ascii	"pOut\000"
.LASF26:
	.ascii	"nbVectors\000"
.LASF33:
	.ascii	"blockSize\000"
.LASF23:
	.ascii	"float16_t\000"
.LASF0:
	.ascii	"char\000"
.LASF21:
	.ascii	"float32_t\000"
.LASF42:
	.ascii	"arm_q15_to_f16\000"
.LASF4:
	.ascii	"short int\000"
.LASF16:
	.ascii	"complex double\000"
.LASF38:
	.ascii	"arm_barycenter_f16\000"
.LASF9:
	.ascii	"uint32_t\000"
.LASF8:
	.ascii	"long int\000"
.LASF54:
	.ascii	"clip_q31_to_q15\000"
.LASF14:
	.ascii	"complex float\000"
.LASF40:
	.ascii	"pSrc\000"
.LASF22:
	.ascii	"float64_t\000"
.LASF35:
	.ascii	"accum2\000"
	.ident	"GCC: (based on arm-12.2.Rel1 source release) 12.2.1 20221205"
