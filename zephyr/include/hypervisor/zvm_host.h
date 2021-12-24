/*
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-08
 * 
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef ZEPHYR_VM_H__
#define ZEPHYR_VM_H__

#include <spinlock.h>


#define VM_MAX_VCPUS 2



struct vcpu{
    struct vm *vm;
};


struct vm {
    /* Need a spinlock for protecting mmu. */
    struct spinlock ;

    /* Block memory allocated for this vm. */

    
    /* A array for collect vcpu. */
    struct vm_vcpu *vcpus[VM_MAX_VCPUS];




};





#endif /* ZEPHYR_VM_H__ */
