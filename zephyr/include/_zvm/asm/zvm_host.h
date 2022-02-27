/* 
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-30
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_ASM_ZVM_HOST_H__
#define ZVM_ASM_ZVM_HOST_H__

#include <spinlock.h>

#include "pgtable-types.h"
#include "vcpu.h"
#include <_zvm/asm/pgtable-types.h>
#include <_zvm/asm/zvm_host.h>
#include <_zvm/vm/vm.h>

#define ZVM_MAX_VCPUS 32


struct zvm_arch {
    /* The VMID. */
    uint64_t vmid;

    /*  */
    // k_spinlock *pgd_lock;
    pgd_t *pgd;

	/* VTTBR value associated with above pgd and vmid */
	uint64_t vttbr;
    
	/* The maximum number of vCPUs depends on the used GIC model */
	int max_vcpus;

    /**
     * @TODO vGIC and vTimer add later.
     */
};

/* Record related info from 3 registers. */
struct vcpu_fault_info {
	uint32_t esr_el2;		/* Hyp Syndrom Register */
	uint64_t far_el2;		/* Hyp Fault Address Register */
	uint64_t hpfar_el2;		/* Hyp IPA Fault Address Register */
};


struct zvm_arch_stage2_mmu{
    /* vmid for page table entry*/
    uint64_t vmid_generation;
    uint32_t vmid;

    /* physical pgd address */
    phys_addr pgd_phys;

    /* pgt table entry */
    struct zvm_arm_pgtable *pgt;

    /* last ran vcpu id on each pcpu */
    int *last_vcpu_ran;
    
};


/* vcpu arch info */
struct zvm_vcpu_arch {
    /* vCPU context regs info. */
    vcpu_context_t ctxt;

    /* HYP configuration. */
    uint64_t hcr_el2;

    /* Exception information. */
    struct vcpu_fault_info fault;

    /* Pointer to host CPU context. */
    vcpu_context_t *host_cpu_context;

    /**
     * @TODO vGIC and vTimer add later. 
     */

    /* Don't run the guest. */
    bool pause;

    /* first run this vpcu flag */
    bool first_run_vcpu;

    /* stage-2 paging translation */
    struct zvm_arch_stage2_mmu *s2_mmu;

    /* register load flag */
    bool vcpu_sys_register_loaded;

    /*store the host's tarp register value before guest entry */
    uint64_t host_mdcr_el2; 

    /*store the guest's trap register value after guest entry */
    uint64_t guest_mdcr_el2;
};

struct u_point_regs{
    uint64_t    regs[31];

    uint64_t    sp;

    uint64_t    pc;

    uint64_t    pstate;
};



#endif /* ZVM_ASM_ZVM_HOST_H__ */