/**
 * @file zvm_exception.h
 * @author xiongcl (xiongcl@hnu.edu.cn)
 * @brief 
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

#ifndef __ZVM_EXCEPTION_H_
#define __ZVM_EXCEPTION_H_

void exception64_entry(struct vcpu *vcpu, uint64_t target_mode, uint32_t type);

#endif // !__ZVM_EXCEPTION_H_
