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


#define default_mm_block_size   ((1UL)<<(12))

/* 64 bits virtual address */
typedef uint64_t vas_addr;

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
 * The VM area of virtual space, below flag record the area of space
 * for user to operate 
 * ------------------------*
 * | no permission area |
 * | -------------------|
 * |  env varible area  |
 * | -------------------|
 * | command line area  |
 * | -------------------|
 * |    stack area      |
 * | -------------------|
 * |    share area      |
 * | -------------------|
 * |     heap area      |
 * | -------------------|
 * |     bss area       |
 * | -------------------|
 * |     data area      |
 * | -------------------|
 * |     code area      |
 * | -------------------|
 * ------------------------*
 */
#define VM_MM_NO_ACCESS	    (0UL)
#define VM_MM_ENV_INFO		BIT(0)
#define VM_MM_CML 		    BIT(1)
#define VM_MM_STACK		    BIT(2)
#define VM_MM_EMPTY		    BIT(3)
#define VM_MM_HEAP 		    BIT(4)
#define VM_MM_BSS		    BIT(5)
#define VM_MM_DATA		    BIT(6)
#define VM_MM_CODE		    BIT(7)

#define VM_MM_RO            BIT(13)
#define VM_MM_RW            BIT(14)
#define VM_MM_EXE           BIT(15)



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
    vas_addr    vm_addr;
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
    vas_addr    area_start;
    vas_addr    area_end;

    /* the vm_task_mm_area list link lots of area in one kind */ 
    struct  vm_task_mm_area *vm_tma_next, *vm_tma_prev; 

    /* vm_task_mm_area belong to one zvm_mm */
    struct  zvm_mm_struct   *zvm_mm;

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

    /* num of vm'task list */
    uint32_t    vm_task_num;

    /* base addr of this zvm_mm area */
    uint64_t    zvm_mm_base_addr;
    /* size of this zvm_mm area */
    uint64_t    zvm_mm_vsize;

    /* code start and end address of virtual mm_struct */
    uint64_t    start_code, end_code;
    /* data */
    uint64_t    start_data, end_date;
    /* head */
    uint64_t    start_heap, end_heap;
    /* stack */
    uint64_t    start_stack;
    /* command arg */
    uint64_t    start_args, end_args;
    /* env addr */
    uint64_t    start_env, end_env;

};

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

#endif /* ZVM_ASM_MM_H__ */