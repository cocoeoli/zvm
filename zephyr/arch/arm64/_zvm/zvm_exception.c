/**
 * @file exception.c
 * @author xiongcl (xiongcl@hnu.edu.cn)
 * @brief This file is for exception processs.
 * @version 0.1
 * @date 2022-03-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <kernel.h>
#include <kernel_internal.h>
#include <arch/arm64/lib_helpers.h>
#include <arch/cpu.h>
#include <arch/arm64/_zvm/zvm.h>
#include <_zvm/vm/vm.h>


/* **We chose to add below later for two reason:
 1. Too completed to simple copy from linux
 2. We don't know the reason why we need it, may be it could simplyfied later
 */
/**
 * @brief exception64_entry
 * 
 * @param vcpu 
 * @param target_mode 
 * @param type 
 */
void exception64_entry(struct vcpu *vcpu, uint64_t target_mode, uint32_t type)
{
    unsigned long sctlr, vbar, old, new, mode;
	uint64_t exc_offset;

	mode = *((uint32_t *)&vcpu->arch.ctxt.regs.pstate) & (SPSR_MODE_MASK | 0x00000010);

	if      (mode == target_mode)
		exc_offset = 0x200;
	else if ((mode | 0x01) == target_mode)
		exc_offset = 0x00;
	else if (!(mode & 0x10))
		exc_offset = 0x400;
	else
		exc_offset = 0x600;

	switch (target_mode) {
	case SPSR_MODE_EL1H:
		vbar = __vcpu_read_sys_reg(vcpu, VBAR_EL1);
		sctlr = __vcpu_read_sys_reg(vcpu, SCTLR_EL1);
		__vcpu_write_sys_reg(vcpu, *vcpu_pc(vcpu), ELR_EL1);
		break;
	default:
		/* Don't do that */
		BUG();
	}

	*vcpu_pc(vcpu) = vbar + exc_offset + type;

	old = *vcpu_cpsr(vcpu);
	new = 0;

	new |= (old & PSR_N_BIT);
	new |= (old & PSR_Z_BIT);
	new |= (old & PSR_C_BIT);
	new |= (old & PSR_V_BIT);

	if (kvm_has_mte(vcpu->kvm))
		new |= PSR_TCO_BIT;

	new |= (old & PSR_DIT_BIT);

	// PSTATE.UAO is set to zero upon any exception to AArch64
	// See ARM DDI 0487E.a, page D5-2579.

	// PSTATE.PAN is unchanged unless SCTLR_ELx.SPAN == 0b0
	// SCTLR_ELx.SPAN is RES1 when ARMv8.1-PAN is not implemented
	// See ARM DDI 0487E.a, page D5-2578.
	new |= (old & PSR_PAN_BIT);
	if (!(sctlr & SCTLR_EL1_SPAN))
		new |= PSR_PAN_BIT;

	// PSTATE.SS is set to zero upon any exception to AArch64
	// See ARM DDI 0487E.a, page D2-2452.

	// PSTATE.IL is set to zero upon any exception to AArch64
	// See ARM DDI 0487E.a, page D1-2306.

	// PSTATE.SSBS is set to SCTLR_ELx.DSSBS upon any exception to AArch64
	// See ARM DDI 0487E.a, page D13-3258
	if (sctlr & SCTLR_ELx_DSSBS)
		new |= PSR_SSBS_BIT;

	// PSTATE.BTYPE is set to zero upon any exception to AArch64
	// See ARM DDI 0487E.a, pages D1-2293 to D1-2294.

	new |= PSR_D_BIT;
	new |= PSR_A_BIT;
	new |= PSR_I_BIT;
	new |= PSR_F_BIT;

	new |= target_mode;

	*vcpu_cpsr(vcpu) = new;
	__vcpu_write_spsr(vcpu, old);
}

