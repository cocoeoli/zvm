/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-06
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_ASM_VIRT_H__
#define ZVM_ASM_VIRT_H__

/*
 * @file arch, armv8, virtualization, initialization
 */

#define SCTLR_EL2_VALUE	0x30c51878

/*
 * @brief Initial EL2 registers.
 * 
 * All virtualzation-related registers include:
 *  -> sctlr_el2    (System control register)
 *  -> hcr_el2      (Hypervisor configuration register)
 *  -> 
 */
int init_hyp_mode(void);



#endif  /* ZVM_ASM_VIRT_H__ */