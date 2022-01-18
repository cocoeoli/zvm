/*
 * Copyright (c) 2021 Huang Jiajia
 * E-mail: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-02 16:40
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>

#include <arch/cpu.h>
#include <arch/arm64/lib_helpers.h>
#include <sys/printk.h>
#include <asm/virt.h>
#include <zvm.h>

struct zvm_info *sys_info;
struct zvm_manage_info *zvm_overall_info; 

int __dt_get_cpu_info(struct zvm_info *sys_info){
    /* System's cpu number can get from CONFIG args. */
#ifdef CONFIG_SMP
    sys_info->phy_cpu_num = CONFIG_MP_NUM_CPUS;
#else
    sys_info->phy_cpu_num = SINGLE_CORE;
#endif
    /* node-id : DT_PATH(cpus, cpu_0) */
    sys_info->cpu_type = DT_PROP_BY_IDX(DT_PATH(cpus, cpu_0), compatible, 0);
    if(sys_info->cpu_type == NULL)
        return -EINVAL;

    return 0;
}

int __dt_get_mem_size(struct zvm_info *sys_info){
    /* node-id :  */
    sys_info->phy_mem = DT_REG_SIZE_BY_IDX(DT_PATH(soc, MEMORY_NODE_ID), 0);
    if(sys_info->phy_mem == 0)
        return -EINVAL;

    return 0;
}
 
int __zvm_info_init(struct zvm_info *sys_info){
    sys_info->vm_total_num = 0;
    sys_info->phy_mem_used = 0;
    sys_info->cpu_type = NULL;

    int cpu_ret = -1, mem_ret = -1;
    cpu_ret = __dt_get_cpu_info(sys_info);
    mem_ret = __dt_get_mem_size(sys_info);
    if(cpu_ret || mem_ret){
        pr_err("ZVM hardware info init fail.\n");
        return -EINVAL;
    }

    return 0;
}

void zvm_info_print(struct zvm_info *sys_info){
    printk(">---- System's information ----<\n");
    printk("  All phy-cpu: %d\n", sys_info->phy_cpu_num);
    printk("  CPU's type : %s\n", sys_info->cpu_type);
    printk("  All phy-mem: %.2fMB\n", (float)(sys_info->phy_mem)/DT_MB);
    printk("  Memory used: %.2fMB\n", (float)(sys_info->phy_mem_used)/DT_MB);
    printk("  VM's number: %d\n", sys_info->vm_total_num);
    printk(">------------------------------<\n");
}

/*
 * @brief Main work of this function is to initialize zvm.
 * 
 * All works include:
 *  -> Initialize struct variable "zvm_overall_info";
 *  -> 
 */
int zvm_init(void){
    int ret = 0;

    /* 
     * First initialize zvm_overall_info->hw_info. 
     * Remember to allocate memory before using pointers!
     */
    zvm_overall_info = (struct zvm_manage_info*)malloc  \
                            (sizeof(struct zvm_manage_info));
    zvm_overall_info->hw_info = (struct zvm_info*)malloc  \
                            (sizeof(struct zvm_info));
    if (!zvm_overall_info || !zvm_overall_info->hw_info){
        pr_err("Allocate memory for zvm_overall_info Error.\n");
        /* 
         * Too cumbersome resource release way. 
         * We can use resource stack way to manage these resouce. 
         */
        free(zvm_overall_info->hw_info);
        free(zvm_overall_info);
        return -EINVAL;
    }
    
    ret = __zvm_info_init(zvm_overall_info->hw_info);
    if(ret){
        pr_err("Get hardware info from dts failure.\n");
        free(zvm_overall_info->hw_info);
        free(zvm_overall_info);
        return -EINVAL;
    }

    /* Then initialize the last value in zvm_overall_info. */
    zvm_overall_info->next_alloc_vmid = 0;

    return ret;
}


