/*
 * Copyright (c) 2022 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <toolchain.h>
#include <linker/sections.h>
#include <offsets.h>
#include <arch/cpu.h>

_ASM_FILE_PROLOGUE


/*
 * @ _zvm_sys_call_hyp()
 * Call this function will trap to the hyp mode, and the first argument
 * containing a pointer to the function you wish to run at hyp mode.
 */
GTEXT(_zvm_sys_call_hyp)
SECTION_SUBSEC_FUNC(TEXT, __hyp_section, _zvm_sys_call_hyp)
	hvc #0
	ret



/*
 * _zvm_flush_vm_context: aim to flush cache and other hardware before enter guest code. 
 */
GTEXT(_zvm_flush_vm_context)
SECTION_SUBSEC_FUNC(TEXT, __hyp_section, _zvm_flush_vm_context)
	dsb 	ishst
	tlbi	alle1is
	ic 		ialluis
	dsb 	ish 
	ret


	









