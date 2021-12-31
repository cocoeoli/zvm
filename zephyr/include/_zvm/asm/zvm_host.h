/* 
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-30
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_ASM_ZVM_HOST_H__
#define ZVM_ASM_ZVM_HOST_H__

#include "vcpu.h"

struct zvm_arch{
    /* The VMID. */
    uint64_t vmid;

    
}




struct zvm_vcpu_fault_info {
	uint32_t esr_el2;		/* Hyp Syndrom Register */
	uint64_t far_el2;		/* Hyp Fault Address Register */
	uint64_t hpfar_el2;		/* Hyp IPA Fault Address Register */
};

struct zvm_vcpu_arch{
    /* vCPU context regs info. */
    struct zvm_vcpu_context ctxt;

    /* HYP configuration. */
    uint64_t hcr_el2;

    /* Exception information. */
    struct zvm_vcpu_fault_info fault;

    /* Pointer to host CPU context. */
    zvm_vcpu_context_t *host_cpu_context;

    /* Don't run the guest. */
    bool pause;
}





#endif /* ZVM_ASM_ZVM_HOST_H__ */