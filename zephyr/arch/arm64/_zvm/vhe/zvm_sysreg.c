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
#include <_zvm/vm/vm.h>





/**
 * zvm_vcpu_load_sysregs_vhe - Load guest system registers to the physical CPU
 *
 * @vcpu: The VCPU pointer
 *
 * Load system registers that do not affect the host's execution, for
 * example EL1 system registers on a VHE system where the host kernel
 * runs at EL2.  This function is called from KVM's vcpu_load() function
 * and loading system register state early avoids having to load them on
 * every entry to the VM.
 */

void zvm_vcpu_load_sysreg(struct vcpu *vcpu)
{
    struct zvm_arm_cpu_context *g_context = &vcpu->arch.ctxt;
    struct zvm_arm_cpu_context *h_context;

    /* **get and save the current cpu state */
    /////* ** ready to load guest on el1

}