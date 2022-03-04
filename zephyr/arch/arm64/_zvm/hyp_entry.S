/*
 * Copyright (c) 2022 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

_ASM_FILE_PROLOGUE


#include <toolchain.h>
#include <linker/sections.h>
#include <_zvm/zvm.h>
#include <_zvm/struct_offset.h>
#include <arch/arm64/_zvm/zvm_arm.h>

/* declare the offset of context */
#define REGS_OFFSET(x)  (CTXT_CPU_USER_PTR + 8*x)

#define SP_EL0_OFFSET   (REGS_OFFSET(30) + 8)


/* smp related process for get current cpu context */
.macro this_cpu_address, dst, sym, tmp
    adrp    \tmp,   \sym
    add     \dst,   \tmp, #:lo12:\sym
    mrs     \tmp,   tpidr_el2
    add     \dst,   \dst, \tmp
.endm


/* _guest_vm_entry point here
 * x0   --  vcpu struct
 */
GTEXT(_guest_vm_entry)
SECTION_SUBSEC_FUNC(TEXT, __hyp_section, _guest_vm_entry)
    /* we should find a address to place the register that must be save,
    the address seem like '.data zvm_hyp_context' */
    /* add zvm_hyp_context address to x2 */
    adrp    x2, zvm_hyp_context
    /* what the meannig of :lo12: ? */
    add     x1, x2, #:lo12:zvm_hyp_context
    /* tpidr_el2 provides a location where software executing at EL2 can store thread identifying information
    get the thread information , move tpdir_el2 value to x2*/
    mrs     x2, tpidr_el2
    add     x1, x1, x2

    /* store the hyp regs */
    str x18,         [x1, #REGS_OFFSET(18)]
    stp x19, x20,    [x1, #REGS_OFFSET(19)]
    stp x21, x22,    [x1, #REGS_OFFSET(21)]
    stp x23, x24,    [x1, #REGS_OFFSET(23)]
    stp x25, x26,    [x1, #REGS_OFFSET(25)]
    stp x27, x28,    [x1, #REGS_OFFSET(27)]
    stp x29, lr,     [x1, #REGS_OFFSET(29)]

    /* save hyp sp_el0 */
    mrs     x2, sp_el0
    str     x2, [x1, #SP_EL0_OFFSET]

    /* isr_el1 shows the pending status of the IRQ, FIQ, or SError interrupt */
    mrs     x1, isr_el1
    /* no interrupt? jump to 1f! */
    cbz     x1, 1f

    /* interrupt process, hold the irq exit code and ret it */
    mov     x0, #ARM64_EXCEPTION_IRQ
    ret 

1: 
    /* load the running vcpu */
    this_cpu_address x1, zvm_hyp_context, x2
    str     x0, [x1, #HOST_VCPU_CTXT]

    /* find the vcpu running context here, and store in x29*/
    add     x29, x0,    #CTXT_VCPU

    /* ** ignore mte here */
    /* ** ignore ptrauth  */

    /* restore guest sp_el0 */
    ldr     x0,     [x29, #SP_EL0_OFFSET]
    msr     sp_el0, x0

    /* Restore guest regs x0-x17 */
    ldp x0, x1,     [x29, #REGS_OFFSET(0)]
    ldp x2, x3,     [x29, #REGS_OFFSET(2)]
    ldp x4, x5,     [x29, #REGS_OFFSET(4)]
    ldp x6, x7,     [x29, #REGS_OFFSET(6)]
    ldp x8, x9,     [x29, #REGS_OFFSET(8)]
    ldp x10, x11,   [x29, #REGS_OFFSET(10)]
    ldp x12, x13,   [x29, #REGS_OFFSET(12)]
    ldp x14, x15,   [x29, #REGS_OFFSET(14)]
    ldp x16, x17,   [x29, #REGS_OFFSET(16)]

    /* Restore guest regs x18-x29 */
    ldr	x18,      [x29, #REGS_OFFSET(18)]
	ldp	x19, x20, [x29, #REGS_OFFSET(19)]
	ldp	x21, x22, [x29, #REGS_OFFSET(21)]
	ldp	x23, x24, [x29, #REGS_OFFSET(23)]
	ldp	x25, x26, [x29, #REGS_OFFSET(25)]
	ldp	x27, x28, [x29, #REGS_OFFSET(27)]
	ldp	x29, lr,  [x29, #REGS_OFFSET(29)]

    /* enter the elr_el1 entry */
    eret
    sb 

    


