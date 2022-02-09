/*
 * Copyright (c) 2021 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include<_zvm/asm/zvm_host.h>
#include<_zvm/asm/mm.h>
#include<arch/arm64/arm_mmu.h>



static int __map_vtma_to_block(struct arm_mmu_ptable *ptable, const char *name,
        uintptr_t phys, uintptr_t virt, size_t size, uint32_t attrs)
{
    int ret;

    if(size) {
        
    }


}