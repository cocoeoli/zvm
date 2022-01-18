/*
 * Copyright (c) 2021 Carlo Caione <ccaione@baylibre.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel_internal.h>
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

/* Configure EL2/virtualization related registers. */
void z_arm64_el2_init(void)
{
	uint64_t reg, reg1;			/* 64bit register */

	/* Set EL2 mmu off */
	reg = read_sctlr_el2();			//above code had inited sctlr_el2, 
	reg |= SCTLR_EL2_RES1; 
	write_sctlr_el2(reg);
	isb();

	/* hcr_el2 flag set, for trap to hyp(aarch64 Synchronous) */
	reg = 1UL << 31;
	write_hcr_el2(reg);
	isb();

	/* Enable EL1 physical timer and clear vitrtual offset */
	reg = 3;
	write_cnthctl_el2(reg);
	zero_sysreg(cntvoff_el2);


	/* Init vCPU id register */
	reg = read_midr_el1();	
	reg1 = read_mpidr_el1();
	write_vpidr_el2(reg);	
	write_vmpidr_el2(reg1);

	/* Controls trapping to EL2 of accesses to CPACR, CPACR_EL1, trace */
	reg = 0x33ff;
	write_cptr_el2(reg);

	/* Disable CP15 trapping to EL2 of EL1 accesses to the System register  */
	zero_sysreg(hstr_el2);

	/* Debug related init */
	reg1 = read_id_aa64mmfr0_el1();
	if(reg1 >= 0)
		reg = (((1ULL << (ID_AA64DFR0_PMUVER_SHIFT+4))-1) & reg1)>>ID_AA64DFR0_PMUVER_SHIFT;						/* filled with 0 */
	else
		reg = ((((1ULL << (ID_AA64DFR0_PMUVER_SHIFT+4))-1) & reg1)>>ID_AA64DFR0_PMUVER_SHIFT) | (~((1ULL << 4)-1));	/* filled with 1 */
	if(reg >= 1){
		reg = read_pmcr_el0(); 
		reg = (((1ULL << (16))-1) & reg)>>11;
		write_mdcr_el2(reg);
	}

	/* Stage-2 translation  init*/
	zero_sysreg(vttbr_el2);


	/* Set Exception type to EL1h */
	reg = INIT_PSTATE_EL1;
	write_spsr_el2(reg);


	z_arm64_el2_plat_init();
	isb();
}

void z_arm64_el1_init(void)
{
	uint64_t reg;

	/* Setup vector table */
	write_vbar_el1((uint64_t)_vector_table);
	isb();

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

void z_arm64_el3_get_next_el(uint64_t switch_addr){
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
