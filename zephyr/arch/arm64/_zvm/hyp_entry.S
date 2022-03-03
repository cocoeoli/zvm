/*
 * Copyright (c) 2022 hnu <xiongcl@hnu.edu.cn>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

_ASM_FILE_PROLOGUE


#include <toolchain.h>
#include <linker/sections.h>
#include <_zvm/zvm.h>



GTEXT(_guest_vm_entry)
SECTION_SUBSEC_FUNC(TEXT, __hyp_section, _guest_vm_entry)
    /* add zvm_hyp_ctxt address to x2 */
    adrp    x2, zvm_hyp_ctxt
    /* what the meannig of :lo12: ? */
    add     x1, x2, #:lo12:zvm_hyp_ctxt
    /* tpidr_el2 provides a location where software executing at EL2 can store thread identifying information
    get the thread information */
    mrs     x1, tpidr_el2
    add     x1, x1, x2

    


