/**
 * @file switch.c
 * @author xiongcl (xiongcl@hnu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <kernel.h>
#include <kernel_internal.h>
#include <arch/arm64/lib_helpers.h>
#include <arch/cpu.h>
#include <arch/arm64/_zvm/zvm.h>
#include <arch/arm64/_zvm/zvm_arm.h>
#include <_zvm/vm/vm.h>


/* Now, we just consider the situation with one cpu */
struct zvm_host_date zhost_data;



static void active_hyp_trap(struct vcpu *vcpu)
{
    uint64_t val;
    uint64_t hcr_elx;

    hcr_elx = vcpu->arch.hcr_el2;
    /* ** Don't set HCR_TVM bit here, after learn cpus_have_final_cap() function,
    we can start edit it */

    /* write trap control register here */
    write_hcr_el2(hcr_elx);

    /* **ignore serror virt interupt on this stage, after we know the function of 
     cpus_have_final_cap(), we will add it */
    
    val = read_cpacr_el1();
    /* Traps EL0 and EL1 System register accesses to all implemented trace registers from 
    both Execution states to EL1, or to EL2 when it is implemented  */
    val |= CPACR_EL1_TTA;
    val &=  ~CPACR_EL1_ZEN;
    val |= CPTR_EL2_TAM;
    val &= ~CPACR_EL1_FPEN_NOTRAP;
    /******** --- Do it later ----*********/
    //fpsimd
}


int _zvm_vcpu_run(struct vcpu *vcpu)
{
    int ret;
    uint32_t  this_vmid;
    uint64_t  exit_code;
    uint64_t  vm_pgd_addr, final_vmid;
    struct zvm_arm_cpu_context *h_ctxt, *g_ctxt;
    
    /* mask daif flag*/
    __asm__ volatile ("msr  daifset, #0xf \n" : : :"memory" );

    /* ** enable irq routing to EL2 later */

    h_ctxt = &zhost_data->host_ctext;
    h_ctxt->running_vcpu = vcpu;
    
    /* Get the vcpu context */
    g_ctxt = &vcpu->arch.ctxt;

    /* save host state here, this code aim to: Main control register for the debug implementation.  */
    h_ctxt->sys_regs[VCPU_MDSCR_EL1] = read_mdscr_el1();

    /** Configure stage-2 translation here **/
    /* Set control register for stage 2 of the EL1&0 translation regime. */
    write_vtcr_el2(vcpu->arch.s2_mmu->arch_zvm->vtcr_el2);
    
    /* set the register that holds the base address of the translation table for 
     * the initial lookup for stage 2 of an address translation in the EL1&0 translation regime, */
    this_vmid = vcpu->arch.s2_mmu->vmid;
    vm_pgd_addr = vcpu->arch.s2_mmu->pgd_phys;
    final_vmid = (this_vmid << VTTBR_VMID_SHIFT) | vm_pgd_addr;
    write_vttbr_el2(final_vmid);
    isb();
    /** end load stage-2 **/

    /* active trap to el2*/
    active_hyp_trap(vcpu);
}
