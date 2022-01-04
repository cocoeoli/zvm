/*
 * Copyright (c) 2021 Huang Jiajia
 * E-mail: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-02 16:40
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#include <_zvm/zvm.h>
#include <sys/printk.h>


int __dt_get_cpu_info(zvm_info_t *sys_info){
    /* System's cpu number can get from CONFIG args. */
#ifdef CONFIG_SMP
    sys_info->phy_cpu_num = CONFIG_MP_NUM_CPUS;
#else
    sys_info->phy_cpu_num = SINGLE_CORE;
    printk("There\n");
#endif
    /* node-id : DT_PATH(cpus, cpu_0) */
    sys_info->cpu_type = CPU_TYPENAME;
    if(sys_info->cpu_type == NULL)
        return -EINVAL;

    return 0;
}

int __dt_get_mem_size(zvm_info_t *sys_info){
    /* node-id :  */
    sys_info->phy_mem = MEMORY_SIZE;
    if(sys_info->phy_mem == 0)
        return -EINVAL;

    return 0;
}
 
int __zvm_info_init(zvm_info_t *sys_info){
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

void zvm_info_print(zvm_info_t *sys_info){
    printk(">---- System's information ----<\n");
    printk("  All phy-cpu: %d\n", sys_info->phy_cpu_num);
    printk("  CPU's type : %s\n", sys_info->cpu_type);
    printk("  All phy-mem: %.2fMB\n", (float)(sys_info->phy_mem)/DT_MB);
    printk("  Memory used: %.2fMB\n", (float)(sys_info->phy_mem_used)/DT_MB);
    printk("  VM's number: %d\n", sys_info->vm_total_num);
    printk(">------------------------------<\n");
}