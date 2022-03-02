/**
 * @file zvm_sysreg.c
 * @author xiongchenglai (xiongcl@hnu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <kernel.h>
#include <kernel_internal.h>
#include <arch/cpu.h>
#include <arch/arm64/lib_helpers.h>
#include <arch/arm64/_zvm/zvm.h>
#include <_zvm/vm/vm.h>
#include <_zvm/asm/virt.h>


struct zvm_host_data zhost_date;


/**
 * zvm_vcpu_load_sysregs_vhe - Load guest system registers to the physical CPU
 * This function first save the host register information and then load the guest vcpu 
 * register information.
 * warning: must consider the redirection situation of register when OS on el2. 
 * @vcpu: The VCPU pointer
 */
void zvm_vcpu_load_sysreg(struct vcpu *vcpu)
{
    struct zvm_arm_cpu_context *g_context = &vcpu->arch.ctxt;
    struct zvm_arm_cpu_context *h_context;

    /* ** smp related, find current cpu */

    h_context = &zhost_date.host_ctext;

    /* Store the host information in some register:
     Thread identifying information stored by software running at this Exception level */ 
    h_context->sys_regs[VCPU_TPIDR_EL0] = read_tpidr_el0();
    h_context->sys_regs[VCPU_TPIDRRO_EL0] = read_tpidrro_el0();

    /* ** ignore the situation of guest(aarch32) on el1 */

    /* load the guest register: thread information */
    write_tpidr_el0(g_context->sys_regs[VCPU_TPIDR_EL0]);
    write_tpidrro_el0(g_context->sys_regs[VCPU_TPIDRRO_EL0]);
    

    /* load other guest registers */
    /* vmpidr_el2 holds the value of the Virtualization Multiprocessor ID. 
    This is the value returned by EL1 reads of MPIDR_EL1 */
    write_vmpidr_el2(g_context->sys_regs[VCPU_MPIDR_EL1]);

    /* Selects the current Cache Size ID Register, CCSIDR_EL1, 
    by specifying the required cache level and the cache type*/ 
    write_csselr_el1(g_context->sys_regs[VCPU_CSSELR_EL1]);
    /* detect vhe mode */
    if(is_el2_now()){
        /* Provides top level control of the system, including its memory system, at EL1 and EL0. */
        write_sctlr_el12(g_context->sys_regs[VCPU_SCTLR_EL1]);
        /* The control register for stage 1 of the EL1&0 translation regime. */
        write_tcr_el12(g_context->sys_regs[VCPU_TCR_EL1]);
    }else{
        pr_err("OS not run vhe mode");
        return -1;
    }
    /* Controls access to trace, SVE, and Advanced SIMD and floating-point functionality. */
    write_cpacr_el12(g_context->sys_regs[VCPU_CPACR_EL1]);
    /* Holds the base address of the translation table for the initial lookup for stage 1 of the translation 
    of an address from the lower VA range in the EL1&0 translation regime, */
    write_ttbr0_el12(g_context->sys_regs[VCPU_TTBR0_EL1]);
    /* Holds the base address of the translation table for the initial lookup for stage 1 of the translation 
    of an address from the higher VA range in the EL1&0 stage 1 translation regime  */
    write_ttbr1_el12(g_context->sys_regs[VCPU_TTBR1_EL1]);
    /* Holds syndrome information for an exception taken to EL1. */
    write_esr_el12(g_context->sys_regs[VCPU_ESR_EL1]);
    /* Provides additional IMPLEMENTATION DEFINED fault status information for exceptions taken to EL1. */
    write_afsr0_el12(g_context->sys_regs[VCPU_AFSR0_EL1]);
    /* Provides additional IMPLEMENTATION DEFINED fault status information for exceptions taken to EL1. */
    write_afsr1_el12(g_context->sys_regs[VCPU_AFSR1_EL1]);
    /* Holds the faulting Virtual Address for all synchronous Instruction or Data Abort, PC alignment fault 
    and Watchpoint exceptions that are taken to EL1 */
    write_far_el12(g_context->sys_regs[VCPU_FAR_EL1]);
    /* Provides the memory attribute encodings corresponding to the possible AttrIndx values 
    in a Long-descriptor format translation table entry for stage 1 translations at EL1. */
    write_mair_el12(g_context->sys_regs[VCPU_MAIR_EL1]);
    /* Holds the vector base address for any exception that is taken to EL1. */
    write_vbar_el12(g_context->sys_regs[VCPU_VBAR_EL1]);
    /* Holds Context ID */
    write_contextidr_el12(g_context->sys_regs[VCPU_CONTEXTIDR_EL1]);
    /* Provides IMPLEMENTATION DEFINED memory attributes for the memory regions specified by MAIR_EL1. */
    write_amair_el12(g_context->sys_regs[VCPU_AMAIR_EL1]);
    /* When FEAT_VHE is not implemented, or when HCR_EL2.{E2H, TGE} is not {1, 1}, this register 
    controls the generation of an event stream from the virtual counter, and access from EL0 to the 
    physical counter, virtual counter, EL1 physical timers, and the virtual timer.
    When FEAT_VHE is implemented and HCR_EL2.{E2H, TGE} is {1, 1}, this register does not 
    cause any event stream from the virtual counter to be generated, and does not control access to the 
    counters and timers. The access to counters and timers at EL0 is controlled by CNTHCTL_EL2. */
    write_cntkctl_el12(g_context->sys_regs[VCPU_CNTKCTL_EL1]);

    /* Returns the output address (OA) from an Address translation instruction that executed successfully, 
    or fault information if the instruction did not execute successfully. */
    write_par_el1(g_context->sys_regs[VCPU_PAR_EL1]);
    /* Provides a location where software executing at EL1 can store thread identifying information, 
    for OS management purposes. */
    write_tpidr_el1(g_context->sys_regs[VCPU_TPIDR_EL1]);

    /* ** ignore mte on this stage */

    /* Holds the stack pointer associated with EL1. */
    write_sp_el1(g_context->sys_regs[VCPU_SP_EL1]);
    /* When taking an exception to EL1, holds the address to return to */
    write_elr_el12(g_context->sys_regs[VCPU_ELR_EL1]);
    /* Holds the saved process state when an exception is taken to EL1. */
    write_spsr_el12(g_context->sys_regs[VCPU_SPSR_EL1]);

    /* Set the vcpu_loaded falg */
    vcpu->arch.vcpu_sys_register_loaded = true;

    active_hyp_trap(vcpu);
}