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
#include <arch/cpu.h>
#include <arch/arm64/lib_helpers.h>
#include <_zvm/debug/debug.h>
#include <_zvm/vm/vm.h>
#include <_zvm/vhe/zvm_sysreg.h>

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
        pr_err("hyp mode not available.\n");
        return -ENODEV;
    }

    /* Detect whether OS is running on EL2? is vhe available? */
    is_kernel_run_el2 = is_el2_now();
    
    return is_kernel_run_el2;
}

/* unable init_hyp_mode  
int init_hyp_mode()
{

    zvm_hypstart_code_init();

    zvm_hyp_memstruct_alloc();

    creat_hyp_mapping();
}
*/

/**
 * @brief check arm64 arch support for zvm
 * 
 * @return int 
 */
int zvm_arch_init(void){
    bool in_vhe_mode;
    int ret = 0, err;

    /* Is hyp、vhe available? */
    in_vhe_mode = is_basic_hardware_support();

    
    
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

/**
 * @brief init work for first run this vcpu
 * this function is for init some hardware feature for first build this 
 * vcpu on this vm.
 * @param vcpu : vcpu struct wait for test
 * @return int 
 */
static int zvm_vcpu_first_init_run(struct vcpu *vcpu){
    struct vm *vm = vcpu->vm;

    /* whether is first run vcpu */
    if(!vcpu->arch.first_run_vcpu)
        return 0;
    
    vcpu->arch.first_run_vcpu = false;

    /* ** enable vgic */

    /* ** enable vtimer */


}

/**
 * @brief zvm_arch_vcpu_load is for hardware init 
 * This function aim to load hardware feature for vcpu,
 * for vgic, vtimer and ex.
 * @param vcpu 
 * @param cpu 
 */
static void zvm_arch_vcpu_load(struct vcpu *vcpu, int cpu)
{
    struct zvm_arch_stage2_mmu *mmu;

    mmu = vcpu->arch.s2_mmu;

    /* ** record the last run cpu to speed up with tlb and cache */

    vcpu->cpu = cpu;

    /* **load vgic for this vcpu */

    /* **load vtimer for this vcpu */

    /* VHE mode register load */
    if(2)
       zvm_vcpu_load_sysreg(vcpu); 
    


}


int zvm_arch_vcpu_run(struct vcpu *vcpu)
{
    struct zvm_run *run = vcpu->run;
    int ret; 

    /* ** judge whether it is first run vcpu */

    /* first init cpu run */
    ret = zvm_vcpu_first_init_run(vcpu);
    if(ret)
        return ret;
    
    /* ** process mmio access for this vcpu */

    /* no premption for this vcpu */
    /* no smp for this vcpu now */
    zvm_arch_vcpu_load(vcpu, 0);

}




