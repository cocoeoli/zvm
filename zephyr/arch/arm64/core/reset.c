/*
 * Copyright (c) 2021 Carlo Caione <ccaione@baylibre.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel_internal.h>
#include <arch/cpu.h>
#include "boot.h"

void z_arm64_el2_init(void);

void __weak z_arm64_el_highest_plat_init(void)
{
	/* do nothing */
}

void __weak z_arm64_el3_plat_init(void)
{
	/* do nothing */
}

void __weak z_arm64_el2_plat_init(void)
{
	/* do nothing */
}

void __weak z_arm64_el1_plat_init(void)
{
	/* do nothing */
}

void z_arm64_el_highest_init(void)
{
	if (is_el_highest_implemented()) {
		write_cntfrq_el0(CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC);
	}

	z_arm64_el_highest_plat_init();

	isb();
}

enum el3_next_el {
	EL3_TO_EL2,
	EL3_TO_EL1_NO_EL2,
	EL3_TO_EL1_SKIP_EL2
};

static inline enum el3_next_el el3_get_next_el(void)
{
	if (!is_el_implemented(2)) {
		return EL3_TO_EL1_NO_EL2;
	} else if (is_in_secure_state() && !is_el2_sec_supported()) {
		/*
		 * Is considered an illegal return "[..] a return to EL2 when EL3 is
		 * implemented and the value of the SCR_EL3.NS bit is 0 if
		 * ARMv8.4-SecEL2 is not implemented" (D1.11.2 from ARM DDI 0487E.a)
		 */
		return EL3_TO_EL1_SKIP_EL2;
	} else {
		return EL3_TO_EL2;
	}
}

void z_arm64_el3_init(void)
{
	uint64_t reg;

	/* Setup vector table */
	write_vbar_el3((uint64_t)_vector_table);
	isb();

	reg = 0U;			/* Mostly RES0 */
	reg &= ~(CPTR_TTA_BIT |		/* Do not trap sysreg accesses */
		 CPTR_TFP_BIT |		/* Do not trap SVE, SIMD and FP */
		 CPTR_TCPAC_BIT);	/* Do not trap CPTR_EL2 / CPACR_EL1 accesses */
	write_cptr_el3(reg);

	reg = 0U;			/* Reset */
#ifdef CONFIG_ARMV8_A_NS
	reg |= SCR_NS_BIT;		/* EL2 / EL3 non-secure */
#endif
	reg |= (SCR_RES1 |		/* RES1 */
		SCR_RW_BIT |		/* EL2 execution state is AArch64 */
		SCR_ST_BIT |		/* Do not trap EL1 accesses to timer */
		SCR_HCE_BIT |		/* Do not trap HVC */
		SCR_SMD_BIT);		/* Do not trap SMC */
	write_scr_el3(reg);

#if defined(CONFIG_GIC_V3)
	reg = read_sysreg(ICC_SRE_EL3);
	reg = (ICC_SRE_ELx_SRE_BIT |	/* System register interface is used */
	       ICC_SRE_EL3_EN_BIT);	/* Enables lower Exception level access to ICC_SRE_EL1 */
	write_sysreg(reg, ICC_SRE_EL3);
#endif

	z_arm64_el3_plat_init();

	isb();

	if (el3_get_next_el() == EL3_TO_EL1_SKIP_EL2) {
		/*
		 * handle EL2 init in EL3, as it still needs to be done,
		 * but we are going to be skipping EL2.
		 */
		z_arm64_el2_init();
	}
}

void z_arm64_el2_init(void)
{
	bool this_reg_flag = false;			/* reg flag */
	uint64_t reg, reg1, m_reg;			/* 64bit register */

	/* hcr_el2 flag set, for trap to hyp */
	reg = HCR_HOST_NVHE_FLAGS;
	write_hcr_el2(reg);
	isb();

	/* Set EL2 mmu off */
	reg = read_sctlr_el2();			//above code had init sctlr_el2, 
	reg |= SCTLR_EL2_RES1; 
	write_sctlr_el2(reg);
	isb();

	/* Enable EL1 physical timer and clear vitrtual offset */
	reg = 3;
	write_cnthctl_el2(reg);
	reg = 0U;
	write_cntvoff_el2(reg);

	/* Debug related init */
	reg1 = read_id_aa64mmfr0_el1();
	__asm volatile(
		"	sbfx	%0, %1, #ID_AA64DFR0_PMUVER_SHIFT, #4 \n"
		:"=r" (reg) :"r" (reg1) : "memory" 
	);
	if(reg >= 1){
		reg = read_pmcr_el0();
		reg = (((1U << (16))-1) & reg)>>11;
		this_reg_flag = true;
	}
	if(this_reg_flag){
		m_reg = 0;
	}else
		m_reg = reg;
	reg = (((1U << (ID_AA64DFR0_PMSVER_SHIFT+4))-1) & reg1)>>ID_AA64DFR0_PMSVER_SHIFT;
	if(reg){
		__asm volatile(
			MRS_S("%0", SYS_PMBIDR_EL1)
			: :"r" (reg) : "memory"
		);
		reg = reg & (1U << SYS_PMBIDR_EL1_P_SHIFT);
		if(!reg){
			reg =  (1U << SYS_PMSCR_EL2_PA_SHIFT) | (1U << SYS_PMSCR_EL2_PCT_SHIFT);
			__asm volatile(
				MSR_S(SYS_PMSCR_EL2, reg)
				: : : 
			);
		}
		reg = MDCR_EL2_E2PB_MASK << MDCR_EL2_E2PB_SHIFT;
		m_reg = reg | m_reg;
	}
	reg = (((1U << (ID_AA64DFR0_TRBE_SHIFT+4))-1) & reg1)>>ID_AA64DFR0_TRBE_SHIFT;
	if(reg){
		__asm volatile(
			MRS_S("%0", SYS_TRBIDR_EL1)
			: :"r" (reg) : "memory"
		);
		reg = reg & TRBIDR_PROG;
		if(!reg){
			reg = MDCR_EL2_E2PB_MASK << MDCR_EL2_E2TB_SHIFT;
			m_reg = reg | m_reg;
		}
	}
	write_mdcr_el2(m_reg);



	/* Provides information about the implemented memory model and memory management support in AArch64 state.*/
	// reg1 = read_id_aa64mmfr1_el1();		read_id_aa64mmfr1_el1 is not supported by this asm
	__asm volatile(
		"	mrs	%0,	id_aa64mmfr1_el1  \n"
		: "=r" (reg1) : : "memory"
	);
	reg = (((1U << (ID_AA64MMFR1_LOR_SHIFT+4))-1) & reg1)>>ID_AA64MMFR1_LOR_SHIFT;
	if(!reg){					/* add some asm code */
		__asm volatile(
			MSR_S(LORC_EL1, "xzr")
			: : : 
		);
	}

	/* Stage-2 translation */
	reg = 0U;
	__asm volatile(
		"	msr	vttbr_el2,	xzr \n"
		: : : 
	);
	// write_vttbr_el2(reg); vttbr_el2 is not supported by this asm

	/* GICv3 init sys_register access */
	reg = read_id_aa64pfr0_el1();		
	reg = (((1U << (ID_AA64PFR0_GIC_SHIFT+4))-1) & reg)>>ID_AA64PFR0_GIC_SHIFT;
	if(reg){
		__asm volatile(
			MRS_S("%0", ICH_SRE_EL2)
			: :"r" (reg) : "memory"
		);
		reg = reg |  ICC_SRE_EL2_SRE | ICC_SRE_EL2_ENABLE;
		__asm volatile(
			MSR_S(ICH_SRE_EL2, "%0")
			: :"r" (reg) : "memory"
		);
		isb();
		__asm volatile(
			MRS_S("%0", ICH_SRE_EL2)
			: :"r" (reg) : "memory"
		);
		if(!(reg & 0x01))
			return;
		__asm volatile(
			MSR_S(ICH_HCR_EL2, "xzr")
			: : : "memory"
		);
	}

	/* Disable CP15 trapping to EL2 of EL1 accesses to the System register  */
	// wirte_hstr_el2(reg);		hstr_el2 not support
	__asm volatile(
		"	msr	hstr_el2,	xzr \n"
		: : : 
	);

	/* Init vCPU id register */
	// reg = read_midr_el1();	midr_el1 not support
	__asm volatile(
		"	mrs	%0,	midr_el1 \n"
		:"=r" (reg): : "memory"
	);
	reg1 = read_mpidr_el1();
	//write_vpidr_el2(reg);		vpidr_el2 not supported
	__asm volatile(
		"	msr	vpidr_el2,	%0 \n"
		: : "r" (reg) : 
	);
	write_vmpidr_el2(reg1);

	/* Controls trapping to EL2 of accesses to CPACR, CPACR_EL1, trace */
	reg = 0x33ff;
	write_cptr_el2(reg);

	/* SVE register access */
	/* This function is SVE related, which is not used in nvhe mode */
	/* wait a minute */

	/* Memory related traps */
	reg1 = read_id_aa64mmfr0_el1();
	m_reg = ID_AA64MMFR0_FGT_SHIFT;
	reg1 = (((1U << (m_reg+4))-1) & reg1)>>m_reg;
	if(reg1){
		reg = 0U;
		//write_id_aa64dfr0_el1(reg1);	id_aa64dfr0_el1  not support
		__asm volatile(
			"	mrs	%0,	id_aa64dfr0_el1 \n"
			:"=r" (reg1): : "memory"
		);
		m_reg = ID_AA64DFR0_PMSVER_SHIFT;
		reg1 = (((1U << (m_reg+4))-1) & reg1)>>m_reg;
		if(reg1 >= 0x03){
			m_reg = 1U;
			reg = (reg | (m_reg<<62));
		}
	}
	__asm volatile(
		MSR_S(HDFGRTR_EL2, "%0") "\n"
		MSR_S(HDFGWTR_EL2, "%0") "\n"
		MSR_S(HFGRTR_EL2, "xzr") "\n"
		MSR_S(HFGWTR_EL2, "xzr") "\n"
		MSR_S(HFGITR_EL2, "xzr") 
		: :"r" (reg) : "memory"
	);
	reg1 = read_id_aa64pfr0_el1();
	m_reg = ID_AA64PFR0_AMU_SHIFT;
	reg1 = (((1U << (m_reg+4))-1) & reg1)>>m_reg;
	if(reg1){
		__asm volatile(
			MSR_S(HAFGRTR_EL2, "xzr") 
			: : :
		);
	}

	/* Set Exception type to EL1h */
	reg = INIT_PSTATE_EL1;
	write_spsr_el2(reg);

	/* below with '//' is origin code */
	//reg = read_sctlr_el2();
	//reg |= (SCTLR_EL2_RES1 |	/* RES1 */
	//	SCTLR_I_BIT |		/* Enable i-cache */
	//	SCTLR_SA_BIT);		/* Enable SP alignment check */
	//write_sctlr_el2(reg);

	//reg = read_hcr_el2();
	//reg |= HCR_RW_BIT;		/* EL1 Execution state is AArch64 */
	//write_hcr_el2(reg);

	//reg = 0U;			/* RES0 */
	//reg |= CPTR_EL2_RES1;		/* RES1 */
	//reg &= ~(CPTR_TFP_BIT |		/* Do not trap SVE, SIMD and FP */
	//	 CPTR_TCPAC_BIT);	/* Do not trap CPACR_EL1 accesses */
	//write_cptr_el2(reg);

 	//zero_cntvoff_el2();		/* Set 64-bit virtual timer offset to 0 */
	//zero_cnthctl_el2();
	//zero_cnthp_ctl_el2(); 
	/*
	 * Enable this if/when we use the hypervisor timer.
	 * write_cnthp_cval_el2(~(uint64_t)0);
	 */

	z_arm64_el2_plat_init();

	isb();
}

void z_arm64_el1_init(void)
{
	uint64_t reg;

	/* Setup vector table */
	write_vbar_el1((uint64_t)_vector_table);
	isb();

	/* when el2 is implemnted, cpacr_el1 is not work */
	reg = 0U;			/* RES0 */
	reg |= CPACR_EL1_FPEN_NOTRAP;	/* Do not trap NEON/SIMD/FP initially */
					/* TODO: CONFIG_FLOAT_*_FORBIDDEN */
	write_cpacr_el1(reg);

	reg = read_sctlr_el1();
	reg |= (SCTLR_EL1_RES1 |	/* RES1 */
		SCTLR_I_BIT |		/* Enable i-cache */
		SCTLR_SA_BIT);		/* Enable SP alignment check */
	write_sctlr_el1(reg);

	write_cntv_cval_el0(~(uint64_t)0);
	/*
	 * Enable these if/when we use the corresponding timers.
	 * write_cntp_cval_el0(~(uint64_t)0);
	 * write_cntps_cval_el1(~(uint64_t)0);
	 */

	z_arm64_el1_plat_init();

	isb();
}

void z_arm64_el3_get_next_el(uint64_t switch_addr)
{
	uint64_t spsr;

	write_elr_el3(switch_addr);

	/* Mask the DAIF */
	spsr = SPSR_DAIF_MASK;

	if (el3_get_next_el() == EL3_TO_EL2) {
		/* Dropping into EL2 */
		spsr |= SPSR_MODE_EL2T;
	} else {
		/* Dropping into EL1 */
		spsr |= SPSR_MODE_EL1T;
	}

	write_spsr_el3(spsr);
}
