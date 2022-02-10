/*
 * Copyright (c) 2021 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include<_zvm/asm/zvm_host.h>
#include<_zvm/asm/mm.h>
#include<arch/arm64/arm_mmu.h>
#include<logging/log.h>
#include<sys/mem_manage.h>

#include"../core/mmu.h"

#define CONFIG_MAX_HYP_XLAT_TABLES  8



/**
 * @brief map vtma to physical block address:
 * this function aim to translate virt address to phys address by setting the 
 * hyp page table.
 * @param ptable : level1 page table base address
 * @param name : region's name 
 * @param phys : phys address
 * @param virt : virt address
 * @param size : virt space size
 * @param attrs : attrs of this space 
 * @return int :
 * 0    --  success
 * !0   --  error
 */
static int __map_vtma_to_block(uintptr_t phys, uint8_t *virt, size_t size, uint32_t attrs)
{
    int ret;
    uint8_t *buf = phys + HYP_VIRT_BASE_ADDR;

    z_phys_map(&virt, z_mem_phys_addr(buf), size, attrs|K_MEM_CACHE_WB|K_MEM_PERM_RW);
      
    return 0;
}