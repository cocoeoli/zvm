/*
 * Copyright (c) 2021 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <toolchain.h>
#include <linker/sections.h>
#include <offsets.h>
#include <arch/cpu.h>

_ASM_FILE_PROLOGUE


GDATA(_hyp_vector_table)
SECTION_SUBSEC_FUNC(hyp_vector_table,_vector_table_section,_hyp_vector_table)

	/* The whole table must be 2K aligned */
	.align 11

	/*EL2  Synchronous with sp0*/ 
	.align 7
	b	.                       /* invalid */
	/*EL2  IRQ with sp0 */
	.align 7
	b	.                       /* invalid */
	/*EL2 FIQ with sp0 */
	.align 7
	b 	.                       /* invalid */
	/*EL2 SError with sp0 */
	.align 7
	b	.                       /* invalid */

    /*EL2  Synchronous with spx*/ 
	.align 7
	b	z_hyp_sync_exc          /* valid */
	/*EL2  IRQ with spx */
	.align 7
	b	.                       /* invalid */
	/*EL2 FIQ with spx */
	.align 7
	b 	.                       /* invalid */
	/*EL2 SError with spx */
	.align 7
	b	.                       /* invalid */

	/*EL2 using AArch64 / Synchronous */
	.align 7                    /* valid */
	b	z_hyp_sync_exc
	/*EL2 using AArch64 / IRQ */
	.align 7
	b 	.                       /* invalid */
	/*EL2 using AArch64 / FIQ */
	.align 7
	b	.                       /* invalid */
	/*EL2 using AArch64 / SError */
	.align 7
	b	.                       /* invalid */

	/*EL2 using AArch32 / Synchronous */
	.align 7
	b	.                       /* invalid */
	/*EL2 using AArch32 / IRQ */
	.align 7
	b	.                       /* invalid */
	/*EL2 using AArch32 / FIQ */
	.align 7
	b	.                       /* invalid */
	/*EL2 using AArch32 / SError */
	.align 7
	b	.                       /* invalid */


GTEXT(z_hyp_sync_exc)
SECTION_FUNC(TEXT, z_hyp_sync_exc)
	/* no function, just a test */
    mov x9, #0x08
	eret

	


