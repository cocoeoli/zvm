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
#include <kernel_structs.h>
#include <sys/atomic.h>
#include <syscall_handler.h>
#include <spinlock.h>
#include <toolchain.h>
#include <arch/cpu.h>
#include <arch/arm64/lib_helpers.h>
#include <arch/arm64/_zvm/zvm_arm.h>
#include <_zvm/zvm.h>
#include <_zvm/asm/zvm_host.h>
#include <_zvm/debug/debug.h>
#include <_zvm/vm/vm.h>
#include <_zvm/vhe/zvm_sysreg.h>

/* vmid atomic variable */
static atomic_t global_zvm_vmid = ATOMIC_INIT(1);
/* next vmid ready to allocate to guest vm*/
static uint16_t global_zvm_next_vmid;
/* spin lock of vmid */
static struct k_spinlock global_zv_lock;



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

/**
 * @brief update_vm_vmid aim to allocate a special vmid for each vm
 * 
 * @param vmid 
 * @param vmid_gen 
 */
static void update_vm_vmid(uint32_t *vmid, uint64_t *vmid_gen)
{
    k_spinlock_key_t key;

    /* this vmid is in used */
    if(unlikely(*vmid_gen == ATOMIC_READ(global_zvm_vmid)))
        return;
    
    /* add lock */
    k_spin_lock(&global_zv_lock);

    /* this vmid is in used */
    if(unlikely(*vmid_gen == ATOMIC_READ(global_zvm_vmid))){
        k_spin_unlock(&global_zv_lock, key);
        return;
    }

    /* First use of vmid value  */
    if(unlikely(global_zvm_next_vmid == 0)){
        /* zvm_vmid inc 1 */
        atomic_inc(&global_zvm_vmid);

        /* First init vmid */
        global_zvm_next_vmid = 1;

        /* ** add smp support later, we must consider the situation
        that other cpu entry this guest */

        /* flush the tlb and cache cleaned */
        _zvm_sys_call_hyp(_zvm_flush_vm_context);
        
    }
    /* read current vmid generation*/
    *vmid_gen = ATOMIC_READ(global_zvm_vmid);

    /* get the new vmid */
    *vmid = global_zvm_next_vmid;
    global_zvm_next_vmid++;

    /* unlock vmid */
    k_spin_unlock(&global_zv_lock, key);
}

/**
 * @brief zvm_guest_vm_enter only set a VCPU flag to this thread;
 * 
 */
static void zvm_guest_vm_enter(void)
{
    uint32_t flag;

    /* **save local irq later */

    _current->base.user_options |= K_VCPU;

    /* **restore local irq later */

    /* ** no smp process stage , just do it later */
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

    /* **update vm's vmid on this vcpu, below function need to perfecting later,
    there is still something to do, 
    for example: where to allocate arch.pgd table? */
    update_vm_vmid(&vcpu->arch.s2_mmu->vmid, &vcpu->arch.s2_mmu->vmid_generation);

    /* judge wheather this guest run on this vcpu */
    if(vcpu->arch.pause){
        _wait_q_t *this_vcpu_wq = vcpu->t_wq;
        /* ** if we set pause flag, we must wait for a signal that active this thread, 
        it will be done later */
    }

    /* disable preempt on this context, as likely memory barrier */
    compiler_barrier();

    /* ** disable irq before running guest context, it will do later after learn it */

    /* ** flush vgic hareware state, no need to do on this stage */

    /* ** set vcpu->mode to IN_GUEST_NODE */

    /* ** re-check the exit_request(atomic condition) , 
    if exit , we should re_sync vgic and timer hardware state, remenber do it later*/

    if(ret <=0 || unlikely(vcpu->arch.s2_mmu->vmid == ATOMIC_READ(global_zvm_vmid))){
        /* ** enable irq before exit guest */
        
        return ret;
    }

    /* ** we will add debug function on next stage */
    

    /*********************** enter guest ******************************/
    /* ** maybe do trace point here later */

    zvm_guest_vm_enter();
    vcpu->r_mode = ZVM_IN_GUEST_MODE;

    /* run the vcpu */
    _zvm_sys_call_hyp(_zvm_vcpu_run, vcpu);

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




