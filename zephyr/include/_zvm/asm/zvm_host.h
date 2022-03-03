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
#include <arch/arm64/_zvm/zvm.h>
#include <_zvm/asm/pgtable-types.h>
#include <_zvm/asm/zvm_host.h>
#include <_zvm/vm/vm.h>

#define ZVM_MAX_VCPUS 32

/* below are vcpu_arch flags */
#define ZVM_ARM64_EXCEPT_ES         (0)
#define ZVM_ARM64_FP_ENABLED        BIT(1)

#define ZVM_ARM64_PENDING_EXCEPTION BIT(8)
#define ZVM_ARM64_INCREMENT_PC      BIT(9)


#define ZVM_ARM64_EXCEPT_MASK       (7 << 9)


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

    /* VTCR_EL2 for this VM */
    uint64_t    vtcr_el2;

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

    /* stage-2 related vcpu_arch */
    struct zvm_arch *arch_zvm;
    
};


/* vcpu arch info */
struct zvm_vcpu_arch {
    /* vCPU context regs info. */
    struct zvm_arm_cpu_context ctxt;

    /* HYP configuration. */
    uint64_t hcr_el2;

    /* Exception information. */
    struct vcpu_fault_info fault;

    /* Pointer to host CPU context. */
    struct zvm_arm_cpu_context *host_cpu_context;

    /**
     * @TODO vGIC and vTimer add later. 
     */

    /* Don't run the guest on this vcpu */
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

    /* interrupt related field, get from 3.16 */
    uint64_t irq_line;

    /* vcpu features state flag*/
    uint64_t vcpu_flags;
};



/* below function is defined in hyp.S */
extern void _zvm_flush_vm_context(void);

/* hyp_vector function */
extern void _hyp_vector_table(void);

/* -------------end------------------ */

/* call hyp function entry */
uint64_t _zvm_sys_call_hyp(void *hyp_func, ...);



#endif /* ZVM_ASM_ZVM_HOST_H__ */