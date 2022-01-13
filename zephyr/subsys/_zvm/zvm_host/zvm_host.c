/*
 * Copyright (c) 2021 Huang Jiajia
 * E-mail: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-02 16:40
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#include <arch/cpu.h>
#include <arch/arm64/lib_helpers.h>
#include <sys/printk.h>
#include <_zvm/asm/virt.h>
#include <_zvm/zvm.h>


struct zvm_info sys_info;
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
    if(cpu_ret || mem_ret)
        return -EINVAL;

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

int zvm_init(void){
    /*  */
    return 0;
}

int zvm_arch_init(void){
    int ret = 0, err;

    /* Detect hyp mode available. */
    if(!is_el_implemented(2)){
        pr_err("Hyp mode not available.\n");
        return -ENODEV;
    }

    /* Detect current EL is EL2. */
   	int curr_el = GET_EL(read_currentel());
    if(curr_el != 2){
        pr_err("Current EL is not EL2.\n");
        return -ENODEV;
    }
    
    /* Init hyp mode. */
    err = init_hyp_mode();
    if(err){
        pr_err("Init hyp mode Error.\n");
        return err;
    }
    
    return ret;
}
