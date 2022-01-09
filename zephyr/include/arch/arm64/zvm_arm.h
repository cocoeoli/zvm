/*
 * Copyright (c) 2021 HNU 
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef __ZVM_ARM_H__
#define __ZVM_ARM_H__


#include <sys/util.h>           //BIT()

/* hrc_el2 register bits 
 * For hyp configure.
 */
#define HCR_TID5	BIT(58) 				
#define HCR_DCT		BIT(57)
#define HCR_ATA		BIT(56) 
#define HCR_AMVOFFEN	BIT(51)
#define HCR_FIEN	BIT(47)
#define HCR_FWB		BIT(46)
#define HCR_API		BIT(41)
#define HCR_APK		BIT(40)
#define HCR_TEA		BIT(37)
#define HCR_TERR	BIT(36)
#define HCR_TLOR	BIT(35)
#define HCR_E2H		BIT(34)
#define HCR_ID		BIT(33)
#define HCR_CD		BIT(32)
#define HCR_RW		BIT(31)
#define HCR_TRVM	BIT(30)
#define HCR_HCD		BIT(29)
#define HCR_TDZ		BIT(28)
#define HCR_TGE		BIT(27)
#define HCR_TVM		BIT(26)
#define HCR_TTLB	BIT(25)
#define HCR_TPU		BIT(24)
#define HCR_TPC		BIT(23)
#define HCR_TSW		BIT(22)
#define HCR_TACR	BIT(21)
#define HCR_TIDCP	BIT(20)
#define HCR_TSC		BIT(19)
#define HCR_TID3	BIT(18)
#define HCR_TID2	BIT(17)
#define HCR_TID1	BIT(16)
#define HCR_TID0	BIT(15)
#define HCR_TWE		BIT(14)
#define HCR_TWI		BIT(13)
#define HCR_DC		BIT(12)
#define HCR_BSU		(3 << 10)
#define HCR_BSU_IS	BIT(10)
#define HCR_FB		BIT(9)
#define HCR_VSE		BIT(8)
#define HCR_VI		BIT(7)
#define HCR_VF		BIT(6)
#define HCR_AMO		BIT(5)
#define HCR_IMO		BIT(4)
#define HCR_FMO		BIT(3)
#define HCR_PTW		BIT(2)
#define HCR_SWIO	BIT(1)
#define HCR_VM		BIT(0)
#define HCR_RES0	(BIT(48) | BIT(39))



#define HCR_HOST_NVHE_FLAGS (HCR_RW | HCR_API | HCR_APK | HCR_ATA)  /* Host os NVHE flag */


#endif /* ZEPHYR_INCLUDE_ARCH_ARM64_TPIDRRO_EL0_H_ */
