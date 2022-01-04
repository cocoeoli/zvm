/*
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-08
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_HOST_H__
#define ZVM_HOST_H__

#include <spinlock.h>

/**
 * @TODO We support SMP later. 
 */
#define VM_MAX_VCPUS 1

struct vcpu{
    /* Which vm this vCPU belongs to. */
    struct vm *vm;

    int vcpu_id;


    /* VM run info record. */
    struct zvm_run *run;

};

/**
 * @TODO  
 */
struct vm {
    /* Need a spinlock for protecting mmu. */
    struct k_spinlock spinlock;

    /* Block memory allocated for this vm. */

    
    struct zvm_arch arch;

    /* A array for collect vcpu. */
    struct vm_vcpu *vcpus[VM_MAX_VCPUS];
};

#endif /* ZVM_HOST_H__ */