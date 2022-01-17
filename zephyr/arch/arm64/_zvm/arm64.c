/*
 * Copyright 2021-2022 HNU
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 *
 * This module contains zvm init code for arm64 
 */


int zvm_arch_init(){
    bool kernel_mode;

    /* Is cpus boot in el2 and 'CONFIG_KVM' enable */
    is_cpus_boot_in_hyp();

    /* Is kernel run in EL2 */
    
    kernel_mode
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


