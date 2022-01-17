/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-13
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include <os/os.h>

void os_init(struct os* os){
    os->type = OS_TYPE_MAX;
    memset(os->name, '\0', OS_NAME_LENGTH);
}

char *strlwr(char *s){
    char *str;
    str = s;
    
    while(*str != '\0'){
        if(*str >= 'A' && *str <= 'Z') {
            *str += 'a'-'A';
        }
        str++;
    }

    return s;
}

uint32_t get_os_id_by_type(char *s){
    uint32_t os_type;
    char *lower = strlwr(s);

    if (strcmp(lower, "linux") == 0){
        os_type = OS_TYPE_LINUX;
    }else if(strcmp(lower, "zephyr") == 0){
        os_type = OS_TYPE_ZEPHYR;
    }else{
        os_type = OS_TYPE_OTHERS;
    }

    return os_type;
}

char *get_os_type_by_id(uint32_t osid){
    switch (osid){
    case OS_TYPE_LINUX:
        return "linux";
        break;
    case OS_TYPE_ZEPHYR:
        return "zephyr";
        break;
    default:
        return "others";
        break;
    }
}
