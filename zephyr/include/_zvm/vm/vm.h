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

#include <_zvm/asm/zvm_host.h>
#include <_zvm/os/os.h>
#include <_zvm/zvm.h>

#include "vm_ops.h"

/**
 * @TODO We support SMP later. 
 */

struct vcpu {
    /* Which vm this vCPU belongs to. */
    struct vm *vm;

    uint32_t vcpu_id;

    /* VM run info record. */
    struct zvm_run *run;
};

enum {
    VM_STATUS_NEVER_RUN = 0,
    VM_STATUS_RUNNING = 1,
    VM_STATUS_PAUSE = 2,    /* Stop running but still power-up. */
    VM_STATUS_HALT = 3      /* Stop running and power-down. */
};

/**
 * @TODO  
 */
struct vm {
    uint32_t vmid;
    uint32_t vm_status;

    /* Need a spinlock for protecting mmu. */
    struct k_spinlock spinlock;

    /* Block memory allocated for this vm. */

    /* OS the vm loading. */
    struct os *os;

    struct zvm_arch *arch;

    /* A array for collect vcpu. */
    struct vm_vcpu *vcpus[CONFIG_MAX_VCPU_PER_VM];
};

/* Allocate vmid. */
uint32_t _allocate_vmid(void);

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