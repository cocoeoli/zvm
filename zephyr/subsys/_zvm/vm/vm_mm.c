/*
 * Copyright (c) 2021 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <_zvm/zvm.h>
#include <_zvm/asm/mm.h>
#include <_zvm/vm/vm.h>
#include <_zvm/list_ops.h>

/**
 * @brief add vtma_space to vm's unused list area
 * 
 * @param z_mm 
 * @param v_area 
 * @return int 
 */
static int add_unused_vtma_space(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area)
{
    uint64_t size;
    struct vm_task_mm_area *vtma = v_area;

    if(vtma == NULL)
        return -1;
    
    vtma->vma_list.next = NULL;
    size = vtma->area_size;
    
    vtma->vm_tma_flag = 0;
    vtma->vm_id = 0;
    
    /*** try to reduce memory comsumer */


    /* add vtma free list to mm_struct unused list */
    if(vtma->vma_list.next == NULL){
        list_add_after(&z_mm->unused_mma_list, &vtma->vma_list);
    }

    return 0;
}

/**
 * @brief add vtma_space to vm's used list area
 * 
 * @param z_mm 
 * @param v_area 
 * @return int 
 */
static int add_used_vtma_space(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area)
{
    if(!v_area)
        return -1;
    
    list_add_after(&z_mm->used_mma_list, &v_area->vma_list);
    return 0;
}



/**
 * @brief this function for init the vma struct for vm's virtual address space
 * 
 * @param base 
 * @param size 
 * @return struct vm_task_mm_area* 
 */
static struct vm_task_mm_area *alloc_vm_task_mm_area(uint64_t base, uint64_t size)
{
    struct vm_task_mm_area *vtma;

    /* allocate memory for vtma */
    vtma = k_malloc(sizeof(struct vm_task_mm_area));
    if(vtma == NULL)
        return NULL;
    
    vtma->area_start = base;
    vtma->area_end = base + size - 1;
    vtma->vm_tma_flag = 0;
    vtma->area_size = size;

    return vtma;
}

/**
 * @brief initial vm_mm struct for guest vm
 * 
 * @param this_vm 
 */
static void zvm_mm_struct_init(struct vm *this_vm)
{
    int ret;
    uint64_t base_addr, size;

    struct vm_task_mm_area *vtma;

    /* get mm struct */
    struct zvm_mm_struct *z_mm = &this_vm->z_mm;

    z_mm->this_vm = this_vm;

    /* init the list of used and unused vma */
    init_list(&z_mm->unused_mma_list);
    init_list(&z_mm->used_mma_list);

    /* default as 64bits address */
    base_addr = BITS_64_BASE;
    size = BITS_64_SIZE;

    /* ** check address align for mem block */

    /* init vtma struct */
    vtma = alloc_vm_task_mm_area(base_addr, size);
    if(vtma == NULL){
        pr_err("Fail to allocate memory!");
        /* throw the error !*/
    }

    /* ** add spin_lock for vmm_area list */

    /* In initial stage, add free_vtma to mm_struct */
    ret = add_unused_vtma_space(z_mm, vtma);
    if(ret)
        pr_err("Fail to add free vtma to list!");

    /* ** relase spin_lock for vmm_area list */
}


/**
 * @brief alloc physical memory for vtma
 * 
 * @param z_mm 
 * @param v_area 
 * @return int 
 */
static int alloc_vm_memory(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area)
{
    
}

