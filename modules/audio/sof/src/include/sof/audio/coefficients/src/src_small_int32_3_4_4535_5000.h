/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright(c) 2020 Intel Corporation. All rights reserved.
 *
 */

#include <sof/audio/src/src.h>
#include <stdint.h>

const int32_t src_int32_3_4_4535_5000_fir[348] = {
	-44332,
	116220,
	-109098,
	-33627,
	240794,
	-321403,
	115423,
	314448,
	-641593,
	494186,
	186994,
	-962890,
	1134308,
	-321345,
	-1062931,
	1936076,
	-1340584,
	-632851,
	2616649,
	-2843421,
	631013,
	2714105,
	-4544561,
	2881667,
	1674072,
	-5853890,
	5957644,
	-978228,
	-5926194,
	9256227,
	-5409919,
	-3827011,
	11701916,
	-11254604,
	1202783,
	11847580,
	-17457904,
	9439780,
	8102312,
	-22244662,
	20407986,
	-979447,
	-23198384,
	32716389,
	-16485998,
	-17318105,
	44008192,
	-39279944,
	-595684,
	50819147,
	-71212136,
	34705264,
	47219229,
	-121324396,
	117558963,
	12007300,
	-271449759,
	699289475,
	1331682741,
	264196935,
	-277391437,
	137011038,
	14653148,
	-97174200,
	89922210,
	-26044986,
	-38244880,
	61211232,
	-37344719,
	-7151448,
	37860721,
	-36448675,
	9888950,
	18871978,
	-29424490,
	17517576,
	4722472,
	-19958970,
	18625052,
	-4372503,
	-10638077,
	15687969,
	-8840413,
	-3112105,
	10881122,
	-9677242,
	1864049,
	5915120,
	-8178093,
	4298066,
	1895591,
	-5623779,
	4721216,
	-695006,
	-3029403,
	3902352,
	-1886988,
	-1013767,
	2589898,
	-2031207,
	201489,
	1338673,
	-1591125,
	694772,
	443429,
	-977201,
	702816,
	-34518,
	-455787,
	487427,
	-184804,
	-134209,
	246601,
	-153072,
	-83,
	81507,
	14525,
	88419,
	-176706,
	129137,
	93113,
	-352599,
	394250,
	-62740,
	-486395,
	808288,
	-495364,
	-404446,
	1262020,
	-1261867,
	111838,
	1509828,
	-2277344,
	1241357,
	1192856,
	-3248717,
	3002871,
	-68364,
	-3665015,
	5134469,
	-2517444,
	-2875968,
	7023220,
	-6075974,
	-266908,
	7733102,
	-10184738,
	4495975,
	6156960,
	-13734821,
	11207733,
	1279548,
	-15131077,
	18926056,
	-7504671,
	-12483154,
	25885754,
	-20107684,
	-3845504,
	29512631,
	-35593886,
	12690366,
	26358450,
	-52226792,
	39548761,
	11261209,
	-67734857,
	82782282,
	-27722745,
	-79749407,
	172051496,
	-154131608,
	-86310851,
	1095777154,
	1095777154,
	-86310851,
	-154131608,
	172051496,
	-79749407,
	-27722745,
	82782282,
	-67734857,
	11261209,
	39548761,
	-52226792,
	26358450,
	12690366,
	-35593886,
	29512631,
	-3845504,
	-20107684,
	25885754,
	-12483154,
	-7504671,
	18926056,
	-15131077,
	1279548,
	11207733,
	-13734821,
	6156960,
	4495975,
	-10184738,
	7733102,
	-266908,
	-6075974,
	7023220,
	-2875968,
	-2517444,
	5134469,
	-3665015,
	-68364,
	3002871,
	-3248717,
	1192856,
	1241357,
	-2277344,
	1509828,
	111838,
	-1261867,
	1262020,
	-404446,
	-495364,
	808288,
	-486395,
	-62740,
	394250,
	-352599,
	93113,
	129137,
	-176706,
	88419,
	14525,
	81507,
	-83,
	-153072,
	246601,
	-134209,
	-184804,
	487427,
	-455787,
	-34518,
	702816,
	-977201,
	443429,
	694772,
	-1591125,
	1338673,
	201489,
	-2031207,
	2589898,
	-1013767,
	-1886988,
	3902352,
	-3029403,
	-695006,
	4721216,
	-5623779,
	1895591,
	4298066,
	-8178093,
	5915120,
	1864049,
	-9677242,
	10881122,
	-3112105,
	-8840413,
	15687969,
	-10638077,
	-4372503,
	18625052,
	-19958970,
	4722472,
	17517576,
	-29424490,
	18871978,
	9888950,
	-36448675,
	37860721,
	-7151448,
	-37344719,
	61211232,
	-38244880,
	-26044986,
	89922210,
	-97174200,
	14653148,
	137011038,
	-277391437,
	264196935,
	1331682741,
	699289475,
	-271449759,
	12007300,
	117558963,
	-121324396,
	47219229,
	34705264,
	-71212136,
	50819147,
	-595684,
	-39279944,
	44008192,
	-17318105,
	-16485998,
	32716389,
	-23198384,
	-979447,
	20407986,
	-22244662,
	8102312,
	9439780,
	-17457904,
	11847580,
	1202783,
	-11254604,
	11701916,
	-3827011,
	-5409919,
	9256227,
	-5926194,
	-978228,
	5957644,
	-5853890,
	1674072,
	2881667,
	-4544561,
	2714105,
	631013,
	-2843421,
	2616649,
	-632851,
	-1340584,
	1936076,
	-1062931,
	-321345,
	1134308,
	-962890,
	186994,
	494186,
	-641593,
	314448,
	115423,
	-321403,
	240794,
	-33627,
	-109098,
	116220,
	-44332

};

struct src_stage src_int32_3_4_4535_5000 = {
	1, 1, 3, 116, 348, 4, 3, 0, 0,
	src_int32_3_4_4535_5000_fir};
