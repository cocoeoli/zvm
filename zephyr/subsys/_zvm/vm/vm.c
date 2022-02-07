/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-13
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <toolchain/gcc.h>

#include <_zvm/zvm.h>
#include <_zvm/asm/mm.h>
#include <_zvm/vm/vm.h>
#include <_zvm/list_ops.h>

uint32_t _allocate_vmid(){   
    if(unlikely(zvm_overall_info->next_alloc_vmid == CONFIG_MAX_VM_NUM))
        return -EOVERFLOW;      /* Value overflow. */
    
    /* Store return value. */
    int res = zvm_overall_info->next_alloc_vmid;

    /* Update next allocate vmid and overall system total vm number. */
    _find_next_vmid();
	zvm_overall_info->hw_info->vm_total_num++;

    return res;
}


/**
 * @brief init guest vm memory manager
 * 
 * @param vm 
 * @param base 
 * @param size 
 * @param flag
 * @return int 
 */
static int vm_mm_init(struct vm *vm, uint64_t base, uint64_t size, uint64_t flag)
{
    uint64_t start_addr, end_addr, this_vma_end;
    this_vma_end = base + size;

    struct zvm_mm_struct *z_mm;

    struct vm_task_mm_area *vtma, *new_vtma, *old_vtma;
    new_vtma = NULL;
    old_vtma = NULL;

    /* ** check vm_mm's flag */

    /* ** add spin_lock for vmta*/

    list_for_each_entry(vtma, &z_mm->unused_mma_list, vma_list){
        start_addr = vtma->area_start;
        end_addr = vtma->area_end + 1;

        if ((base > end_addr) || (base < start_addr) || (this_vma_end > end_addr))
			continue;

		if ((base == start_addr) && (this_vma_end == end_addr)) {
			new_vtma = vtma;
			break;
		}else{  /* first try,  other situation is regard as error ! */
            pr_err("there are some old vmm_area!");
        }
    }

    /* init vtma failed */
    if((old_vtma == NULL) && (new_vtma==NULL)){
        pr_err("useless vtma config!");
        /* ** release the vtma */
        return NULL;
    }

    list_del(&vtma->vma_list);

    /* ** change the old free area list */

    if(new_vtma){
        new_vtma->vm_tma_flag = flag;
        add_used_vtma_space(z_mm, new_vtma);
    }else{
        pr_err("Invalid memory config for vm!");
        return -1;
    }

    /* ** release the vtma's spin_lock */

    list_for_each_entry(vtma, &z_mm->used_mma_list, vma_list){
        if(!(vtma->vm_tma_flag & NORMAL_MEM))
            continue;

        if(alloc_vm_memory(z_mm, vtma)){
            
        }
    }

}
