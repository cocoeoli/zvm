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

#include "vm_ops.h"

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


/*
 * ZVM manage structure. It equals to zvm_info_t and vm_info_t.  
 * 
 * As a hypervisor, zvm should know how much resouce it can use and how many vm 
 * it carries. 
 * At first aspect, File subsys/_zvm_zvm_host/zvm_host.c can get hardware info
 * from devicetree file. We construct corresponding data structure type 
 * "zvm_info_t" to store it. "zvm_info_t" includes: 
 *  -> the number of total vm
 *  -> the number of physical CPU
 *  -> system's CPU typename
 *  -> the number of physical memory
 *  -> how much physical memory has been used
 * and so on.
 * At second aspect, we should konw what kind of resource vm possess is proper. 
 * Then we construct a proper data structure, just like "vm_info_t", to describe 
 * it. We can construct type "vm_info_t" based on type "vm_input_params", which 
 * has:
 *  -> vm serial number
 *  -> vCPU cores
 *  -> memory allocation
 *  -> OS image location.
 * And it also includes information as below:
 *  -> ...
 */
struct zvm_manage_info{
    zvm_info_t _zvm_info;
    vm_info_t _vm_info; /* [] */
};




#endif /* ZVM_HOST_H__ */