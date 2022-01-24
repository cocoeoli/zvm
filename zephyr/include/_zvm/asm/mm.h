/**
 * @file mm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ZVM_ASM_MM_H__
#define ZVM_ASM_MM_H__

#include <stdint.h>


#define default_mm_block_size   ((1UL)<<(12))

/* 64 bits virtual address */
typedef uint64_t vas_addr;

/* 64 bits physical address */
typedef uint64_t phys_addr;


/**
 * @brief Declare zvm_mem_slot structure to store the memory slot managed by hypervisor
 * 
 */
struct zvm_mem_slot {
    /*This slot id for slots in this VM*/
    uint32_t    this_slot_id;

    /* addr for hypervisor virtual address */
    vas_addr    hva_addr;

    /* addr for hypervisor physical address */ 
    phys_addr    hpa_addr;

    /* block list that used by guest os */
    uint64_t    *used_block;

    /* size of per block, default value 4k */
    uint64_t    mem_block_size;

    /* gpf_base vritual page frame base address  */
    uint64_t    gpf_vase;
};

/**
 * @brief Declare vm_task_area struct to handler one of VM task  
 * !!     ready to fill some code but not now.
 */
struct vm_task_mm_area {
    vas_addr    area_start;
    vas_addr    area_end;

    
};

#endif /* ZVM_ASM_MM_H__ */