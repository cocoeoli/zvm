/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-07
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file 
 * @brief This file mainly declare all of struct in the hypervisor.
 *
 * As a hypervisor, zvm also needs lots of data structs to manage all the VMs.
 * The simplest case is that when creating a new vm, we should number it. Then 
 * this number will be recorded into a struct which is declared in this file.
 */

#ifndef ZVM_H__
#define ZVM_H__

#ifndef CONFIG_ZVM
#define CONFIG_ZVM
#endif 

/**
 * @brief We need devicetree.h file.
 *  
 * Before managing VMs, we need to make clear that how many resource available 
 * in current system. This information can be get from system device tree file.
 */

#include <stdint.h>

#include <devicetree.h>
#include <errno.h>
#include <_zvm/debug/debug.h>

#define SINGLE_CORE     1U
#define MEMORY_NODE_ID  memory_40000000
#define DT_MB           (1024 * 1024)

/**
 * @brief Declare zvm_info structure to store basic information of zvm.
 * 
 * What hardware resource we concern about now includes CPU and memory(named 
 * sram in dts file), such as CPU's compatible property and memory size. Other 
 * devices we do not care currently. Then we need a structure to store basic 
 * information of hardware.
 */
struct zvm_info {
    /* Number of vm in system, vm's number starts from 1. */
    uint16_t vm_total_num;

    /* Physical CPU core number. */
    uint16_t phy_cpu_num;

    /* Physical memory. */
    uint64_t phy_mem;

    /* Physical memory used. */
    uint64_t phy_mem_used;

    /* Physical cpu type. */
    char *cpu_type;
};

/**
 * @brief Get number of physical cpu and its typename.
 * 
 * Through devicetree macro and pass value into system information structure.
 * @return If get number of physical cpu and typename success, then return 0; 
 * else return error code.
 */
int __dt_get_cpu_info(struct zvm_info *sys_info);

/**
 * @brief Get physical memory size.
 * 
 * Through devicetree macro and pass value into system information structure.
 * @return If get memory size success, then return 0; else return error code.
 */
int __dt_get_mem_size(struct zvm_info *sys_info);

/**
 * @brief Structure zvm_info initial.
 * 
 * Call last two functions to initialize zvm_info.
 * @return If initialize zvm_info success return 0, else return error code.
 */
int __zvm_info_init(struct zvm_info *sys_info);

/**
 * @brief Print zvm_info structure.
 */
void zvm_info_print(struct zvm_info *sys_info);

/*
 * @brief ZVM manage structure.   
 * 
 * As a hypervisor, zvm should know how much resouce it can use and how many vm 
 * it carries. 
 * At first aspect, File subsys/_zvm_zvm_host/zvm_host.c can get hardware info
 * from devicetree file. We construct corresponding data structure type 
 * "struct zvm_info" to store it. "struct zvm_info" includes: 
 *  -> the number of total vm
 *  -> the number of physical CPU
 *  -> system's CPU typename
 *  -> the number of physical memory
 *  -> how much physical memory has been used
 * and so on.
 * At second aspect, we should konw what kind of resource vm possess is proper. 
 * Then we construct a proper data structure, just like "vm_info_t", to describe 
 * it. It includes information as below:
 *  -> ...
 */
struct zvm_manage_info {
    struct zvm_info *hw_info;

    struct vm *vms[CONFIG_MAX_VM_NUM];

    /* Record every vm's vcpu number. */
    uint8_t vcpus_num[CONFIG_MAX_VM_NUM];

    /* 
     * This value is current smallest vmid which can be allocated. It's default 
     * value is 0. Everytime create a new vm, we will allocate a vmid for it.
     * The allocation value is this. Conversely, everytime delete/destroy a vm,
     * we will recycle vmid and compare with this value.  
     */
    uint32_t next_alloc_vmid;
};

/* This struct variable should be init in function zvm_init(). */
extern struct zvm_manage_info *zvm_overall_info;   

static inline bool vm_num_full(){
    return (zvm_overall_info->next_alloc_vmid == CONFIG_MAX_VM_NUM);
}

/* 
 * Before we use zvm, we should initialize operation environment. The main works
 * include:
 *  -> Arch realted initialization works
 *  -> Arch non-related initialzation works
 *  -> Initialize struct variable "zvm_overall_info"
 *  -> ...
 */
int zvm_init(void);

/*
 * In this function, we should complete some tasks as below:
 *  -> detect Hyp-mode(for ARMv8) is available
 *  -> initialize vm related struct variables
 *  -> Initialize memory mappings on all CPUs.
 *  -> ...
 */
int zvm_arch_init(void);

#endif /* ZVM_H__ */