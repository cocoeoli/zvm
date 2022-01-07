/*
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-01-04
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_BEBUG_DEBUG_H__
#define ZVM_BEBUG_DEBUG_H__

#include <stdio.h>

/* Log module switch. Turn off output nothing. */
#define __DEBUG

#ifdef  __DEBUG
    #define DEBUG(format, ...)  printf(format, ##__VA_ARGS__)
#else
    #define DEBUG(format, ...)
#endif

/* Define log level */
enum PRINT_LEVEL {    
    PRINT_LEVEL_OFF = 0,
    PRINT_LEVEL_FATAL,
    PRINT_LEVEL_ERR,
    PRINT_LEVEL_WARN,
    PRINT_LEVEL_INFO,
    PRINT_LEVEL_ALL,
};

#define pr_fatal(level, format, ...) \
    do { \
        if(level>=PRINT_LEVEL_FATAL)\
            DEBUG("->FATAL @ FUNC:%s FILE:%s LINE:%d \n" format "\n",\
                    __func__, __FILE__, __LINE__, ##__VA_ARGS__);\
    } while (0)


/* The most we use log function is pr_err. */
#define pr_err(format, ...) \
    do {\
        DEBUG("\033[36m[ERROR]File:%s Line:%d. " format "\n\033[0m",\
                __FILE__, __LINE__, ##__VA_ARGS__);\
    } while (0)

#define pr_warn(level, format, ...) \
    do { \
        if(level>=PRINT_LEVEL_WARN)\
            DEBUG("\n->WARN  @ FUNC:%s \n" format "\n",\
                    __func__, ##__VA_ARGS__ );\
    } while (0)

#define pr_info(level, format, ...) \
    do { \
        if(level>=PRINT_LEVEL_INFO)\
            DEBUG("\n->INFO  \n"format"\n",##__VA_ARGS__ );\
    } while (0)

#define pr_debug(level, format, ...) \
    do { \
        if(level>=PRINT_LEVEL_ALL)\
            DEBUG("\n->DEBUG \n"format"\n",##__VA_ARGS__ );\
    } while (0)

#endif  /* ZVM_BEBUG_DEBUG_H__ */