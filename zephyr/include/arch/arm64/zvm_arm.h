/*
 * Copyright (c) 2021 HNU 
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef __ZVM_ARM_H__
#define __ZVM_ARM_H__


#include <sys/util.h>           //BIT()

#define HCR_API		    BIT(41)
#define HCR_RW		(1 << 31)


/*
 * The bits we set in HCR:
 * TLOR:	Trap LORegion register accesses
 * RW:		64bit by default, can be overridden for 32bit VMs
 * TACR:	Trap ACTLR
 * TSC:		Trap SMC
 * TSW:		Trap cache operations by set/way
 * TWE:		Trap WFE
 * TWI:		Trap WFI
 * TIDCP:	Trap L2CTLR/L2ECTLR
 * BSU_IS:	Upgrade barriers to the inner shareable domain
 * FB:		Force broadcast of all maintenance operations
 * AMO:		Override CPSR.A and enable signaling with VA
 * IMO:		Override CPSR.I and enable signaling with VI
 * FMO:		Override CPSR.F and enable signaling with VF
 * SWIO:	Turn set/way invalidates into set/way clean+invalidate
 * PTW:		Take a stage2 fault if a stage1 walk steps in device memory
 */

#define HCR_HOST_NVHE_FLAGS (HCR_RW | HCR_API | HCR_APK | HCR_ATA)


#endif /* ZEPHYR_INCLUDE_ARCH_ARM64_TPIDRRO_EL0_H_ */
