/*
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-12
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_VIRT_OS_H__
#define ZVM_VIRT_OS_H__

enum {
    OS_TYPE_OTHERS = 0,
    OS_TYPE_LINUX = 1,
    OS_TYPE_ZEPHYR = 2,
    OS_TYPE_NUM = 3,
};


/* Abstract of OS. */
struct os {
    char *name;     /* os name. */
    int type;       /* os type. */
};




#endif  /* ZVM_VIRT_OS_H__ */