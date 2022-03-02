/*
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-08
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_HOST_H__
#define ZVM_HOST_H__

#include <toolchain/gcc.h>
#include <stddef.h>

#include <kernel/thread.h>
#include <kernel_structs.h>
#include <_zvm/asm/zvm_host.h>
#include <_zvm/asm/mm.h>
#include <_zvm/os/os.h>
#include <_zvm/zvm.h>
#include <_zvm/virt_irq.h>

#include "vm_ops.h"
#include <stdint.h>

/* VM's id */
typedef uint16_t VM_ID;

/* vm's name length */
#define VM_NAME_LEN    32
/* vm image's name length */ 
#define RAMDISK_NAME_LEN    32

/* cpu_per_vm */
#define CONFIG_VCPU_PER_VM  1

/* vcpu stack thread's size used by each vcpu*/
#define VCPU_THREAD_STACKSIZE 1024

/* priority of thread */
#define VCPU_THREAD_PRIO 0x4

struct vcpu_task;

/**
 * @TODO We support SMP later. 
 */
struct vcpu {
    /* Which vm this vCPU belongs to. */
    struct vm *vm;

    /* bind to physical cpu */
    int cpu;

    /* vcpu's id */
    uint32_t vcpu_id;

    /* VM run info record. context of this vm*/
    struct zvm_run *run;

    /* virq struct for this vcpu */
    struct virq_struct *virq_struct;

    /* vcpu's related task */
    struct vcpu_task *task;

    /* vcpu's list for vm */
    struct list_addr_t vcpu_lists;

    /* vcpu list's next vcpu */
    struct vcpu *next_vcpu;

    /* arch related vcpu info */
    struct zvm_vcpu_arch arch;

    /* set signal info between threads */
    int set_sig_on;

    /* vcpu's thread wait queue */
    _wait_q_t *t_wq; 

    /* vcpu's running mode */
    int32_t r_mode;


};

/* vcpu task struct */
struct vcpu_task{
    /* point to vcpu struct */
    void *v_date;   

    /* vcpu's thread struct */
    struct k_thread *vcpu_thread;

    /* thread's stack */
    K_KERNEL_STACK_MEMBER(vt_stack, VCPU_THREAD_STACKSIZE);

};

enum {
    VM_STATUS_NEVER_RUN = 0,
    VM_STATUS_RUNNING = 1,
    VM_STATUS_PAUSE = 2,    /* Stop running but still power-up. */
    VM_STATUS_HALT = 3      /* Stop running and power-down. */
};

/**
 * @brief vm description for guest vm
 * 
 */
struct vm_desc {
	VM_ID vmid;
	char name[VM_NAME_LEN];

    /* vcpu's number */
	int32_t vcpu_num;

    /* mem_base address */
	uint64_t mem_base;
	uint64_t mem_size;

    /* vm's code entry */
	uint64_t entry;
	
    /* vm's flag */
	uint64_t flags;

    /* vm's image load address */
	uint64_t image_load_address;

    /* image's name */
	char vm_kernel_image_name[RAMDISK_NAME_LEN];
	char vm_dtb_image_name[RAMDISK_NAME_LEN];
};

/**
 * @brief vm struct for getting the  guest vm 
 */
struct vm {
    VM_ID vmid;
    uint32_t vm_status;

    /* vcpu's number */
	int32_t vcpu_num;

    /* Need a spinlock for protecting mmu. */
    struct k_spinlock spinlock;

    /* Block memory allocated for this vm. */
    struct zvm_mm_struct *z_mm;

    /* OS the vm loading. */
    struct os *os;

    /* vcpu struct lidt*/
    struct vcpu **vcpu;

    /* Bind the vm and the os type ops. */
    struct vm_ops *ops;

    struct zvm_arch *arch;

    /* A array for collect vcpu. */
    struct vm_vcpu *vcpus[CONFIG_VCPU_PER_VM];

    /* vm's name */
    char vm_name[VM_NAME_LEN];

    /* vm image's code entry */
    void *code_entry_point;
};

/* Allocate vmid. */
uint32_t _allocate_vmid(void);

/* @brief init guest vm memory manager */
int vm_mm_init(struct vm *vm, uint64_t base, uint64_t size, uint64_t flag);

/**
 * @brief Create a vcpus object for zvm run task. 
 */
int create_vcpus(struct vm *vm);

static inline void _find_next_vmid(void){
    do{
        zvm_overall_info->next_alloc_vmid++;
        if(zvm_overall_info->next_alloc_vmid == CONFIG_MAX_VM_NUM)
            return;
    }while(zvm_overall_info->vms[zvm_overall_info->next_alloc_vmid] != NULL);
}

static inline struct vm *get_vm_by_id(uint32_t vmid){
    if(unlikely(vmid >= CONFIG_MAX_VM_NUM))
        return NULL;

    return zvm_overall_info->vms[vmid];
}

static inline uint32_t get_vmid(struct vm *vm){
    return vm->vmid;
}

static inline uint32_t get_vm_status(struct vm *vm){
    return vm->vm_status;
}

#endif /* ZVM_HOST_H__ */