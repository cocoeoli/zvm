
/**
 * @brief this file define the struct offset used by hyp_entry.s
 * 
 */

#ifndef __STRUCT_OFFSET_H_
#define __STRUCT_OFFSET_H_

#include <_zvm/zvm.h>
#include <sys/util.h>

/**
 * Define the offset of vcpu's element value.
 */
#define CTXT_VCPU			offsetof(struct vcpu, arch.ctxt)

/**
 * Define the offset of zvm_arm_cpu_context's element value.
 */
#define	CTXT_CPU_USER_PTR	offsetof(struct zvm_arm_cpu_context, regs)
#define HOST_VCPU_CTXT		offsetof(struct zvm_arm_cpu_context, running_vcpu)

#endif
