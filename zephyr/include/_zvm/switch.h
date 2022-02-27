/**
 * @file switch.h
 * @author xiongcl (xiongcl@hnu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-02-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ARM64_SWITCH_H_
#define __ARM64_SWITCH_H_

#include <kernel.h>
#include <kernel_internal.h>
#include <_zvm/vm/vm.h>

/* @brief active trap register before entry guest */
void active_hyp_trap(struct vcpu *vcpu);

#endif