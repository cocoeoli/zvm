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
#include <_zvm/list_ops.h>


/* virtual base address, aim to avoid conflict with exist virt address  */
#define HYP_VIRT_BASE_ADDR  ((1UL)<<32)

/* block size in virt space */
#define default_mm_block_size   ((1UL)<<(12))

/* 64bits machine virtual address space */
#define BITS_64_BASE    0X00
#define BITS_64_SIZE    0X0001000000000000


/* VM memory type */
#define IO_MEM          0x00000001
#define NORMAL_MEM      0X00000002
#define MEM_TYPE_MASK   0X000000ff

#define BLK_MAP         0x01000000
#define PGE_MAP         0x02000000

/* memory type size */
#define BLK_MEM_SIZE    0x1000
#define BLK_MEM_SHIFT   (12)

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

    /* vm_task_mm_area's size */
    uint64_t    area_size;

    /* the vm_task_mm_area list link lots of area in one kind */ 
    struct  list_addr_t vma_list; 

    /* vm_task_mm_area belong to one zvm_mm */
    struct  zvm_mm_struct   *zvm_mm;

    /* record the vm's id */
    VM_ID    vm_id;

    /* mm flag for user, see VM_MM_*  flag */
    uint16_t    vm_tma_flag;

    /* mem_block lists for physical memmory management */
    struct  list_addr_t blk_list;
};

/**
 * @brief zvm_mm_struct describe the full virtual address space of zvm. 
 * 
 */
struct zvm_mm_struct{
    /* num of vm'task list */
    uint32_t    vm_task_num;

    /* vm_task_mm_area list for vm's task list*/
    struct  vm_task_mm_area *mma_list;

    /* vm_task_mm_area list for used or unuse list */
    struct list_addr_t unused_mma_list;
    struct list_addr_t used_mma_list;

    /* Need a spin_mmlock for protecting mm. */
    struct k_spinlock spin_mmlock;


    /* base addr of this zvm_mm area */
    uint64_t    zvm_mm_base_addr;
    /* size of this zvm_mm area */
    uint64_t    zvm_mm_vsize;

    /* for store vm struct */
    void *this_vm;

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

/**
 * @brief mem_block record the translation relation of virt addr to phy addr
 * 
 */
struct mem_block{
    /* block num of this vtma */
    uint64_t    cur_bn_offset;

    /* physical base address of this mem_block */
    uint64_t    phy_base;

    /* physical address pointer*/
    uint8_t     phy_pointer;

    /* flag of this block */
    uint16_t    blk_flag;

    /* block list of this vtma */
    struct  list_addr_t blk_list;
};


/**
 * @brief add vtma_space in vm's virtual space
 */
static int add_unused_vtma_space(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area);

/**
 * @brief this function for init the vma struct for vm's virtual address space
 */
static struct vm_task_mm_area *alloc_vm_task_mm_area(uint64_t base, uint64_t size);

/**
 * @brief initial vm_mm struct for guest vm
 */
static void zvm_mm_struct_init(struct vm *this_vm);

/**
 * @brief alloc physical memory for vtma
 */
static int alloc_vm_memory(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area);

/**
 * @brief map virtual addr 'v_area' to physical addr 'phy'
 */
static int map_vtma_to_block(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area);

/**
 * @brief map vtma to physical block address:
 */
static int __map_vtma_to_block(uintptr_t phys, uintptr_t virt, size_t size, uint32_t attrs);

#endif /* ZVM_ASM_MM_H__ */