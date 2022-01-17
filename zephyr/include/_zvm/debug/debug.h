/*
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-01-04
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_BEBUG_DEBUG_H__
#define ZVM_BEBUG_DEBUG_H__

#include <sys/printk.h>

/* Log module switch. Turn off output nothing. */
#define __DEBUG
#define __NO_ARCH

#ifdef  __DEBUG
    #define DEBUG(format, ...)  printk(format, ##__VA_ARGS__)
#else
    #define DEBUG(format, ...)
#endif

/* The most we use log function is pr_err. */
#define pr_err(format, ...) \
    do{\
        DEBUG("\033[36m[ERROR]File:%s Line:%d. " format "\n\033[0m", __FILE__, \
                __LINE__, ##__VA_ARGS__);\
    }while(0); 

#define TEST_POINT(i)   printk("Test Point %d.\n", i);

#endif  /* ZVM_BEBUG_DEBUG_H__ */