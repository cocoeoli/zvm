/* 
 * This file is related to ZVM vcpu.
 *
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-30
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_ASM_VCPU_H__
#define ZVM_ASM_VCPU_H__

#include <stdint.h>

#define VM_NR_SPSR      5
#define NR_SYS_REGS     94
#define NR_COPRO_REGS   (NR_SYS_REGS * 2)

#ifndef _ASMLANGUAGE

/* User general purpose, floating point and debug registers. */
struct user_pt_regs{
    uint64_t regs[31];
    uint64_t sp;
    uint64_t pc;
    uint64_t pstate;
};

/* EL0&1 registers for vm. */
struct zvm_regs{
    /* El0 regs. SP = SP_EL0. */
    struct user_pt_regs regs;

    /* EL1 regs. */
    uint64_t sp_el1;
    uint64_t elr_el1;

    uint64_t spsr[VM_NR_SPSR];

    /**
     * @TODO Floating-point regs we add later. 
     */
};

#endif /* _ASMLANGUAGE */

struct vcpu_context {
    struct zvm_regs gp_regs;
    union{
        uint64_t sys_regs[NR_SYS_REGS];
        uint32_t copro[NR_COPRO_REGS];
    };    
};

typedef struct vcpu_context vcpu_context_t;

struct zvm_run{
    /* Out. */
    uint32_t exit_reason;
};


#endif /* ZVM_ASM_VCPU_H__ */