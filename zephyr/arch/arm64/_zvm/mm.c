/*
 * Copyright (c) 2021 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include<_zvm/asm/zvm_host.h>
#include<_zvm/asm/mm.h>

static int ipa_mem_abort(struct zvm_vcpu *vcpu, phys_addr ipa_addr, struct zvm_mem_slot *memslots)
{
    /* give a lock for this mem lock for this thread */


    /* vma is necessary? try it later */
    

    /* allocate a memory region for ipa */


    /* unlock the mem lock for this thread */
}