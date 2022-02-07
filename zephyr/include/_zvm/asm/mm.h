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

#include <zephyr.h>
#include <stdint.h>
#include <_zvm/vm/vm.h>


#define default_mm_block_size   ((1UL)<<(12))

/* 64 bits virtual address */
typedef uint64_t virt_addr;

/* 64 bits physical address */
typedef uint64_t phys_addr;

/*
 * Address types:
 *  _gva_t - guest virtual address
 *  _gpa_t - guest physical address
 *  _gpa_pf - guest page frame number
 *  _hva_t - host virtual address
 *  _hpa_t - host physical address
 *  _hpa_pf - host page frame number
 */
typedef uint64_t    _gva_t;
typedef uint64_t    _gpa_t;
typedef uint64_t    _gpa_pf;

typedef uint64_t    _hva_t;
typedef uint64_t    _hpa_t;
typedef uint64_t    _hpa_pf;


/**
 * @brief list_addr_t struct for the list of heap or page
 * 
 */
struct list_addr_t{
    struct list_addr_t *prev, *next;
};

/**
 * @brief vm_ramblock struct for build the relationship of gpa to hva
 * 
 */
struct vm_ramblock{
    /* ramblock's related region */ 
    struct vm_gpa_memory_region *mr;    
    
};


/**
 * @brief vm_gpa_memory_region struct for recording one kind of memory in guest os 
 * 
 */
struct vm_gpa_memory_region{
    /* the base addr of this region (gpa)*/
    phys_addr   vm_ram_addr;

    /* related hva addr of this region */
    virt_addr    vm_addr;
};

/**
 * @brief vm_gpa_address_space struct for recording the total gpa info for a guest os
 * 
 */
struct vm_gpa_address_space{
    
};


/**
 * @brief Declare vm_task_area struct to store one of VM task area  
 * 
 */
struct vm_task_mm_area {
    /* vm_task_mm_area's start and end address on zvm_mm_struct */
    virt_addr    area_start;
    virt_addr    area_end;

    /* the vm_task_mm_area list link lots of area in one kind */ 
    struct  list_addr_t vma_list; 

    /* vm_task_mm_area belong to one zvm_mm */
    struct  zvm_mm_struct   *zvm_mm;

    /* record the vm's id */
    VM_ID    vm_id;

    /* mm flag for user, see VM_MM_*  flag */
    uint16_t    vm_tma_flag;
};

/**
 * @brief zvm_mm_struct describe the full virtual address space of zvm. 
 * 
 */
struct zvm_mm_struct{
    /* vm_task_mm_area list for vm's task list*/
    struct  vm_task_mm_area *mma_list;

    /* vm_task_mm_area list for used or unuse list */
    struct list_addr_t unused_mma_list;
    struct list_addr_t used_mma_list;

    /* Need a spin_mmlock for protecting mm. */
    struct k_spinlock spin_mmlock;

    /* num of vm'task list */
    uint32_t    vm_task_num;

    /* base addr of this zvm_mm area */
    uint64_t    zvm_mm_base_addr;
    /* size of this zvm_mm area */
    uint64_t    zvm_mm_vsize;

};

/**
 * @brief Declare zvm_mem_slot structure to store the memory slot managed by hypervisor
 * 
 */
struct zvm_mem_slot {
    /*This slot id for slots in this VM*/
    uint32_t    this_slot_id;

    /* addr for hypervisor virtual address */
    virt_addr    hva_addr;

    /* addr for hypervisor physical address */ 
    phys_addr    hpa_addr;

    /* block list that used by guest os */
    uint64_t    *used_block;

    /* size of per block, default value 4k */
    uint64_t    mem_block_size;

    /* gpf_base vritual page frame base address  */
    uint64_t    gpf_vase;
};

#endif /* ZVM_ASM_MM_H__ */