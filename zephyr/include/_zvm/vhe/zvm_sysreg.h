/**
 * @file zvm_sysreg.h
 * @author xiongcl (xiongcl@hnu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ZVM_SYSREG_H__
#define __ZVM_SYSREG_H__

#include <zephyr.h>
#include <stdint.h>

/**
 * zvm_vcpu_load_sysregs_vhe - Load guest system registers to the physical CPU
 */

void zvm_vcpu_load_sysreg(struct vcpu *vcpu);


#endif //__ZVM_SYSREG_H__