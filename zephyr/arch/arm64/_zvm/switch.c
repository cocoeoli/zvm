/**
 * @file switch.c
 * @author xiongcl (xiongcl@hnu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-02-27
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
 * @brief active trap register before entry guest
 * 
 * @param vcpu 
 */
void active_hyp_trap(struct vcpu *vcpu)
{
    /* Trap on AArch32 cp15 c15 (impdef sysregs) accesses (EL1 or EL0) */
    write_hstr_el2(BIT(15));

    /* **ignore pmu on this stage */

    /* store the mdcr_el2 register information to struct*/
    vcpu->arch.host_mdcr_el2 = read_mdcr_el2();
    write_mdcr_el2(vcpu->arch.guest_mdcr_el2);

}