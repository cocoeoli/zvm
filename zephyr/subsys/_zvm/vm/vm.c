/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-13
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <toolchain/gcc.h>

#include <kernel.h>
#include <kernel/thread.h>
#include <kernel/thread_stack.h>

#include <_zvm/zvm.h>
#include <_zvm/asm/mm.h>
#include <_zvm/vm/vm.h>
#include <_zvm/vm/vm_mm.h>
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
 * @brief init guest vm memory manager:
 * this function aim to init vm's memory manger,for below step:
 * 1. allocate virt space to vm(base/size), and distribute vtma_list to it.
 * 2. add this vtma to used_vtma_list.
 * 3. divide vtma area to block and init block list, 
 * then allocate physical space to these block.
 * 4. build page table from vtma virt address to block physical address. 
 * 
 * @param vm 
 * @param base 
 * @param size 
 * @param flag
 * @return int 
 */
int vm_mm_init(struct vm *vm, uint64_t base, uint64_t size, uint64_t flag)
{
    uint64_t start_addr, end_addr, this_vma_end;
    struct zvm_mm_struct *z_mm = vm->z_mm;
    struct vm_task_mm_area *vtma, *new_vtma, *old_vtma;

    new_vtma = NULL;
    old_vtma = NULL;
    this_vma_end = base + size;

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
		}else if(base == start_addr && this_vma_end < end_addr){
            old_vtma = vtma;
            old_vtma->area_start = this_vma_end;
            old_vtma->area_size -= size;
        }
        else{  /* first try,  other situation is regard as error ! */
            pr_err("there are some old vmm_area!");
        }
        new_vtma = k_malloc(sizeof(struct vm_task_mm_area));
        if(!new_vtma){
            pr_err("allocate memory error!");
            return -1;
        }
        new_vtma->area_start = base;
        new_vtma->area_end = base + size -1;
        new_vtma->area_size = size;
        new_vtma->vm_tma_flag = 0;
        break;
    }

    /* init vtma failed */
    if((old_vtma == NULL) && (new_vtma==NULL)){
        pr_err("useless vtma config!");
        /* ** release the vtma */
        return -1;
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
            pr_err("alloc vm physical memory failed!");
            return -1;
        }

        if(map_vtma_to_block(z_mm, vtma)){
            pr_err("mapping block error!");
            return -1;
        }
    }

    return 0;

}

/**
 * @brief Create a vcpu task object and create a thread bind to this vcpu
 * This function aim to create a task for an vcpu, we treat the vcpu as a 
 * thread, then create and initial a thread for it.
 * *****************---******************
 * warning: there is some unfinished error in thread's stack init, we must 
 * spend some time to make it dynamicly allocate stack space.
 * **************************************
 * @param name : vcpu task's name 
 * @param func : the thread exec function
 * @param arg : arguments for func
 * @param prio : priority of this thread
 * @param stack_size : thread's stack size
 * @param flag : task's option flag
 * @return struct vcpu_task* 
 */
struct vcpu_task *create_vcpu_task(char *name, k_thread_entry_t func, void *arg,
                    uint8_t prio, uint32_t flag)
{
    struct vcpu_task *task;

    /* **check priority of thread */

    /* **jude weather it is a realtime thread */

    task = k_malloc(sizeof(struct vcpu_task));
    if(!task){
        pr_err("Create task error!");
        return NULL;
    }
    memset(task, 0, sizeof(struct vcpu_task));
    
    k_thread_create(task->vcpu_thread, task->vt_stack, VCPU_THREAD_STACKSIZE,
                func, NULL, NULL, NULL, prio, 0, K_NO_WAIT);
    
    return task;
}

/**
 * @brief allocate a vcpu struct and alloca memory
 * 
 * @return struct vcpu* 
 */
static struct vcpu *allocate_vcpu(void)
{
    struct vcpu *vcpu;

    vcpu = k_malloc(sizeof(vcpu));
    memset(vcpu, 0, sizeof(struct vcpu));
    if(!vcpu){
        return NULL;
    }

    vcpu->virq_struct = k_malloc(sizeof(struct virq_struct));
    if(vcpu->virq_struct){
        k_free(vcpu);
        return  NULL;
    }

    /* ** what is vmcs? io block, wait a minut */

    return vcpu;
}


/**
 * @brief Create a vcpus object for zvm run task
 * 
 * @param vm 
 * @return int 
 */

int create_vcpus(struct vm *vm)
{
    char vm_name[VM_NAME_LEN];
    int i;
    struct vcpu *vcpu;
    struct vcpu_task *task;

    /* ** lock the vm struct for operation */

    /* check vcpu args */
    if(vm->vcpu_num > ZVM_MAX_VCPUS){
        pr_err("Vcpu counts is too big!");
        return -1;
    }

    for(i=0; i<vm->vcpu_num; i++){
        memset(vm_name, 0, VM_NAME_LEN);
        snprintk(vm_name, VM_NAME_LEN-1, "%s's vcpu--id-%d", vm->vm_name, i);
        
        /* ** create a thread and bind to this vcpu */
        task = create_vcpu_task(vm_name, vm->code_entry_point, NULL, VCPU_THREAD_PRIO, 0);

        /* alloc_vcpu struct */
        vcpu = allocate_vcpu();

        /* allocate vcpu context */
        vcpu->run = k_malloc(sizeof(struct zvm_run)); 


        if(!vcpu){
            /* **free task */
            k_free(task);
            pr_err("create vcpu failed!");
            return -1;
        }

        /* init vcpu struct */
        task->v_date = vcpu;
        vcpu->task = task;
        vcpu->vcpu_id = i;
        vcpu->vm = vm;
        /* init vcpu list */
        init_list(&vcpu->vcpu_lists);
        
        /* ** init vcpu virt_irq struct: prepare to add */
        
        /* init vm vpcu list */
        vm->vcpu[i] = vcpu;
        vcpu->next_vcpu = NULL;
        if(i)
            vm->vcpu[i-1]->next_vcpu = vcpu;
    }
    return 0;
}