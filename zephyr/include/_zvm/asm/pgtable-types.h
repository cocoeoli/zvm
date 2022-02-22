/* 
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-03
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_ASM_PGTABLE_TYPES_H__
#define ZVM_ASM_PGTABLE_TYPES_H__

#include <stdint.h>
#include <_zvm/asm/zvm_host.h>

typedef uint64_t pgd_t;
typedef uint64_t pud_t;
typedef uint64_t pmd_t;
typedef uint64_t pte_t;


struct zvm_arm_pgtable{
    
    /* stage-2 translation struct */
    struct zvm_arch_stage2_mmu *mmu;


};

#endif /* ZVM_ASM_PGTABLE_TYPES_H__ */