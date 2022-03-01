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
#include <_zvm/zvm.h>
#include <_zvm/debug/debug.h>
#include <_zvm/vm/vm.h>
#include <_zvm/vhe/zvm_sysreg.h>
#include <arch/arm64/_zvm/zvm_arm.h>

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

    /* **load vgic for this vcpu later */

    /* **load vtimer for this vcpu later */

    /* VHE mode register load */
    if(2)
       zvm_vcpu_load_sysreg(vcpu); 
    
    /* ** avoid set any FPSMID flag on this stage */

    /* ** support pmu_v3 latter */

    /* ** enable vcpu preempted function later: kvm_arm_is_pvtime_enabled()*/ 

/* judge if this cpu run mutiple threads */  
#ifdef CONFIG_SCHED_CPU_MASK_PIN_ONLY
    /*TWE: Traps EL0 and EL1 execution of WFE instructions to EL2, when EL2 is enabled in the current 
    Security state, from both Execution states, reported using EC syndrome value 0x01 */
	vcpu->arch.hcr_el2 &= ~HCR_TWE;

    /* ** vgic TWI bit flag, init later */
#else
    /* first line is TWE instruction, and second line is TWI instruction, detail see above log. */
    vcpu->arch.hcr_el2 |= HCR_TWE;
    vcpu->arch.hcr_el2 |= HCR_TWI;
#endif

    /*For vhe mode, DEBUG related code do nothing */

}


static void update_vm_vmid(uint32_t vmid, uint64_t vmid_gen)
{

}

/**
 * @brief zvm_guest_loop for prepare running guest code. 
 * This function aim to make preparetion before running guest os and restore
 * the origin hardware state after guest exit.
 * @param vcpu 
 * @return int 
 */
static int zvm_guest_loop(struct vcpu *vcpu)
{
    int ret;

    /* check conditions for reschdule before guest, check wheather there is more importent 
    thread need to run */
    /* ** Do it later for call cond_resched()*/

    /* ** update vm's vmid on this vcpu, below function need to perfecting later */
    update_vm_vmid(vcpu->arch.s2_mmu->vmid, vcpu->arch.s2_mmu->vmid_generation);

    /* ** request wheather this guest run on this vcpu */

    /* ** disable preempt on this context, likely memory barrier */

    /* ** disable irq before running guest context */

    /* ** flush vgic hareware state */

    /* ** set vcpu->mode to IN_GUEST_NODE */

    /* ** re-check the exit_request , if exit , we should re_sync vgic and timer hardware state*/

    /* ** we will add debug function on next stage */

    /*********************** enter guest ******************************/



    /*********************** exit  guest ******************************/

    /* ** if we set debug before, we must clear it here */

    /* ** sync hardware vgic state here */

    /* ** sync hardware vtimer state here */

    /* ** if set FPSIMD before, we must clear it here */

    /* ** enable irq after running guest */

    /* ** running guest_exit here */

    /* ** call trace_kvm_exit(ret, kvm_vcpu_trap_get_class(vcpu), *vcpu_pc(vcpu)); */

    /* ** we should handle exit here between we re-enable preepted */

    /* ** enable preempt here to restart preempt */

    /* ** finally get the ret code before start the next loop */

    return ret;
}



/**
 * @brief zvm_arch_vcpu_run is aim to run guest code.
 * This function aim to make full prepartion for running guest code, 
 * and then execute VM code in a loop.
 * 
 * @param vcpu 
 * @return int 
 */
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

    /* load vcpu register and init context for this vcpu */
    zvm_arch_vcpu_load(vcpu, 0);

    /* judge if exit now */
    if(run->exit_now){
        ret = -1;
        /* ** We can't understand the function of out: clearly, let add it later */ 
    }

    /* ** add signal later for thread synchronize */
    if(vcpu->set_sig_on){
        //set signal here
    }
    
    run->exit_reason = ZVM_EXIT_UNKNOWN;

    ret = 1;

    /* prepare to enter guest on below loop */
    while(ret > 0){
        ret = zvm_guest_loop(vcpu);
    }

}




