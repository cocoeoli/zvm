/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-13
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <toolchain/gcc.h>

#include <_zvm/zvm.h>
#include <_zvm/vm/vm.h>

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

