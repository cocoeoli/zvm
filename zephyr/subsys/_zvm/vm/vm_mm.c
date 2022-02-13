/*
 * Copyright (c) 2021 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <_zvm/zvm.h>
#include <_zvm/asm/mm.h>
#include <_zvm/vm/vm.h>
#include <_zvm/vm/vm_mm.h>
#include <_zvm/list_ops.h>

/**
 * @brief add vtma_space in vm's virtual space
 */
static int add_unused_vtma_space(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area);

/**
 * @brief this function for init the vma struct for vm's virtual address space
 */
static struct vm_task_mm_area *alloc_vm_task_mm_area(uint64_t base, uint64_t size);

/**
 * @brief add vtma_space to vm's unused list area:
 * this function init the vm_task_mm_area for vm_mm struct and 
 * add it to vm_mm unused vtma list.
 * 
 * @param z_mm : the vm_mm struct
 * @param v_area : the virtual space of vm_mm
 * @return int  
 * 0    -- success
 * !0   -- failed
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
    
    /*** try to reduce memory comsumption */


    /* add vtma free list to mm_struct unused list */
    if(vtma->vma_list.next == NULL){
        list_add_after(&z_mm->unused_mma_list, &vtma->vma_list);
    }

    return 0;
}

/**
 * @brief add vtma_space to vm's used list area:
 * this function add the v_area space to vm_mm struct list
 * 
 * @param z_mm :  the vm_mm struct
 * @param v_area : the virtual space of vm_mm
 * @return int 
 * 0    --  success
 * !0   --  error
 */
int add_used_vtma_space(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area)
{
    if(!v_area)
        return -1;
    
    list_add_after(&z_mm->used_mma_list, &v_area->vma_list);
    return 0;
}


/**
 * @brief Init a vtma struct for vm's virtual address space:
 * this function init a vtma struct using given para('base' , 'size'),
 * and allocate a physical memory for this struce.
 * 
 * @param base : vtma virtual space's bass address 
 * @param size : vtma virtual space's size(bytes)
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
 * @brief init vm_mm struct for guest vm:
 * this function init the vm_mm struct for vm, including init vtma list and 
 * set the origin virtual space for vm, call  alloc_vm_task_mm_area func to init 
 * specific vtma struct and add it to unused vtma list.
 * 
 * @param this_vm : vm struct for store vm_mm struct
 */
void zvm_mm_struct_init(struct vm *this_vm)
{
    int ret;
    uint64_t base_addr, size;

    struct vm_task_mm_area *vtma;

    /* get mm struct */
    struct zvm_mm_struct *z_mm = this_vm->z_mm;

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
 * @brief alloc memory block for vtma:
 * this function divide the vtma to some blocks, and allocate 
 * physical memory to these blocks.
 * 
 * @param z_mm : vm's mm struct
 * @param v_area : vtma struct
 * @return int :
 * 0    --  success
 * !0   --  error code
 */
int alloc_vm_memory(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area)
{
    uint64_t blk_count, i;
    struct mem_block *block;
    block = k_malloc(sizeof(struct mem_block));

    init_list(&v_area->blk_list);

    v_area->vm_tma_flag |= BLK_MAP;

    /* virtual size / 4k block size */
    blk_count = v_area->area_size >> BLK_MEM_SHIFT;

    /* allocate physical memory for block */
    for(i=0; i<blk_count; i++){
        memset(block, 0, sizeof(struct mem_block));
        block->phy_pointer = k_malloc(BLK_MEM_SIZE);
        if(block->phy_pointer == NULL){
            pr_err("allocate memory error!");
            return -1;
        }
        /* get the block number */
        block->cur_bn_offset = i;
        /* set the block flag */
        block->blk_flag = 0x1000 & 0xffff;
        /* get the physical address */
        block->phy_base = (uint64_t)block->phy_pointer;
        
        list_add_after(&v_area->blk_list, &block->blk_list);
    }
    return 0;
}

/**
 * @brief map virtual addr 'v_area' to physical addr 'phy'
 * this function aim to build the map from virt to phys,
 * when we want to read/write/exec the code in memory, we should find the 
 * physical memory address, but how system auto find the physical address
 * through the virtual address? 
 * @answer: the answer is made mmu enable, and build the mapping relationship
 * between virt and phys, but there is a question exist that we should build a 
 * 
 * @param z_mm : vm's mm struct
 * @param v_area : vtma for each task
 * @return int :
 * 0    --  success
 * !0   --  error code
 */
int map_vtma_to_block(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area)
{
    int ret;
    struct mem_block *blk;
    uint64_t base_addr = v_area->area_start;
    uint64_t size = v_area->area_size;
    uint64_t base;

    list_for_each_entry(blk, &v_area->blk_list, blk_list){
        /* find the virt address for this block */
        base = base_addr + (blk->cur_bn_offset * BLK_MEM_SIZE);

        /* add mapping from virt to block physcal address */
        ret = __map_vtma_to_block(blk->phy_base, base, size, 0);
    }
    return ret;
}

