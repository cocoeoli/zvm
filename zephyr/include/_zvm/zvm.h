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

#ifdef __cplusplus
extern "C" {
#endif 

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

#include <arch/arm64/lib_helpers.h>
#include <devicetree.h>
#include <errno.h>
#include <_zvm/debug/debug.h>


#define SINGLE_CORE     1U
#define MEMORY_NODE_ID  memory_40000000
#define CPU_TYPENAME    DT_PROP_BY_IDX(DT_PATH(cpus, cpu_0), compatible, 0)
#define MEMORY_SIZE     DT_REG_SIZE_BY_IDX(DT_PATH(soc, MEMORY_NODE_ID), 0)
#define DT_MB           (1024 * 1024)
#define HYP_MODE_LEVEL  2

/**
 * @brief Declare zvm_info structure to store basic information of zvm.
 * 
 * What hardware resource we concern about now includes CPU and memory(named 
 * sram in dts file), such as CPU's compatible property and memory size. Other 
 * devices we do not care currently. Then we need a structure to store basic 
 * information of hardware.
 */
struct zvm_info{
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

typedef struct zvm_info zvm_info_t;
static zvm_info_t sys_info;

/**
 * @brief Get number of physical cpu and its typename.
 * 
 * Through devicetree macro and pass value into system information structure.
 * @return If get number of physical cpu and typename success, then return 0; 
 * else return error code.
 */
int __dt_get_cpu_info(zvm_info_t *sys_info);

/**
 * @brief Get physical memory size.
 * 
 * Through devicetree macro and pass value into system information structure.
 * @return If get memory size success, then return 0; else return error code.
 */
int __dt_get_mem_size(zvm_info_t *sys_info);


/**
 * @brief Structure zvm_info initial.
 * 
 * Call last two functions to initialize zvm_info.
 * @return If initialize zvm_info success return 0, else return error code.
 */
int __zvm_info_init(zvm_info_t *sys_info);

/**
 * @brief Print zvm_info structure.
 */
void zvm_info_print(zvm_info_t *sys_info);

#ifdef __cplusplus
}
#endif

#endif /* ZVM_H__ */