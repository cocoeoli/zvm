/*
 * Copyright (c) 2021 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include<_zvm/asm/zvm_host.h>
#include<_zvm/asm/mm.h>

#define test_heap_size  4096

K_HEAP_DEFINE(vm_test_heap, test_heap_size);



static int ipa_mem_abort(struct zvm_vcpu *vcpu, virt_addr hva_addr, struct zvm_mem_slot *memslots)
{

    /* give a lock for this mem lock for this thread */


    /* vm_struct for record the page list */
    

    /* allocate a memory region for hva */
    
    

    /* unlock the mem lock for this thread */
}