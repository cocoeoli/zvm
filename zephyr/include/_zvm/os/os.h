/*
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-12
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_VIRT_OS_H__
#define ZVM_VIRT_OS_H__

#define OS_NAME_LENGTH 32

#include <stdint.h>

enum {
    OS_TYPE_OTHERS = 0,
    OS_TYPE_LINUX  = 1,
    OS_TYPE_ZEPHYR = 2,
    OS_TYPE_MAX = 3,
};

/* Abstract of OS. */
struct os {
    uint32_t type;                  /* os type. */
    char name[OS_NAME_LENGTH];      /* os name. */
};

void os_init(struct os* os);

/* Return lower string. */
char *strlwr(char *s);

uint32_t get_os_id_by_type(char *s);

char *get_os_type_by_id(uint32_t osid);

#endif  /* ZVM_VIRT_OS_H__ */