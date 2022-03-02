/**
 * @file zvm.h
 * @author xiongcl (xiongcl@hnu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-02-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ARM64_ZVM_H_
#define __ARM64_ZVM_H_

#include <kernel.h>
#include <kernel_internal.h>
#include <arch/cpu.h>
#include <arch/arm64/lib_helpers.h>
#include <_zvm/asm/vcpu.h>

/*below value is caculated from vcpu_sysreg on '../arm64/kvm_host.h' 
for the base value with 149 */
#define VCPU_SYS_REG_NUM    (125)

#define VCPU_MPIDR_EL1      (1)
#define VCPU_CSSELR_EL1     (2)
#define VCPU_SCTLR_EL1      (3)

#define VCPU_CPACR_EL1      (5)

#define VCPU_TTBR0_EL1      (7)
#define VCPU_TTBR1_EL1      (8)
#define VCPU_TCR_EL1        (9)
#define VCPU_ESR_EL1        (10)
#define VCPU_AFSR0_EL1      (11)
#define VCPU_AFSR1_EL1      (12)
#define VCPU_FAR_EL1        (13)
#define VCPU_MAIR_EL1       (14)
#define VCPU_VBAR_EL1       (15)
#define VCPU_CONTEXTIDR_EL1 (16)
#define VCPU_TPIDR_EL0      (17)
#define VCPU_TPIDRRO_EL0    (18)
#define VCPU_TPIDR_EL1      (19)
#define VCPU_AMAIR_EL1      (20)
#define VCPU_CNTKCTL_EL1    (21)
#define VCPU_PAR_EL1        (22)
#define VCPU_MDSCR_EL1      (23)

#define VCPU_ELR_EL1        (106)
#define VCPU_SP_EL1         (107)
#define VCPU_SPSR_EL1       (108)


/* User general purpose, floating point and debug registers. */
struct user_pt_regs{
    uint64_t regs[31];
    uint64_t sp;
    uint64_t pc;
    uint64_t pstate;
};


/* arm aarch64 cpu context struct */
struct zvm_arm_cpu_context{
    /* some common regs in this context */
    struct user_pt_regs regs;
    
    /* ** spsr register struct */

    struct vcpu *running_vcpu;

    /* vcpu_sys_regs */
    uint64_t sys_regs[VCPU_SYS_REG_NUM];

};

/* zvm_host_data for storing the zephyr context */
struct zvm_host_data{
    /* related context */
    struct zvm_arm_cpu_context host_ctext;
};

#endif  /* ARM64_ZVM_H */
