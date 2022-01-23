/*
 * Copyright 2021-2022 HNU
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 *
 * This module contains zvm init code for arm64 
 */
#include <kernel.h>
#include <kernel_internal.h>
#include <cpu.h>
#include <_zvm/debug/debug.h>

/**
 * @brief whether hyp and vhe is supported.
 * 
 * @return true : vhe available
 * @return false : vhe not available
 * @error : hyp not available
 */
static inline bool is_basic_hardware_support()
{
    bool is_kernel_run_el2;
    /* Detect hyp mode available. */
    if(!is_el_implemented(MODE_EL2)){
        pr_err("Hyp mode not available.\n");
        return -ENODEV;
    }

    /* Detect whether OS is running on EL2? 
       is vhe available?
    */
    is_kernel_run_el2 = is_el2_now();
    
    return is_kernel_run_el2;
}

int init_hyp_mode()
{
    /* Allocate mem and enable */
    zvm_hypstart_code_init();

    zvm_hyp_memstruct_alloc();

    creat_hyp_mapping();
}


int zvm_arch_init(void){
    bool in_vhe_mode;
    int ret = 0, err;

    /* Is hyp、vhe available? */
    in_vhe_mode = is_basic_hardware_support();

    ipa_limit_check();

    
    /* Init hyp mode. */
    err = init_hyp_mode();
    if(err){
        pr_err("Init hyp mode Error.\n");
        return err;
    }
    
    return ret;
}




/**
 * @brief the function that called by device init
 * Name: zvm_arm_init (no idea on finally function name )
 * The main function of this code is to call zvm_init, 
 * int *name()
 * { 
 *  call zvm_init()
 * }
 * pass two para:
 * @ zvm_vcpu struct
 * @ device module
 */


