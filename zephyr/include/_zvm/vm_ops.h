/*
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-31
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_VM_OPS_H__
#define ZVM_VM_OPS_H__

#include <stddef.h>
#include <stdlib.h>

#include <getopt.h>
#include <_zvm/debug/debug.h>
#include <shell/shell.h>
#include <sys/printk.h>
#include <errno.h>

/**
 * @file Realize APIs which realted to vm.
 *
 * All vm command include create, set, run, update, list, halt and delete vm.
 * These APIs will be called by subsys/zvm/shell.c.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This struct includes the parameters that user input for defining a vm.
 * Such as vm serial number, vCPU cores, memory allocation, OS image location 
 * and so on.
 */
struct vm_input_params{
    int vm_num;         /* Which vm we set. */
    int vcpu_num;       /* 0 ~ 8. */
    int vm_memory;      /* 0 ~ 50M, default unit is MB. */
    char *os_img_path;  /* OS image file path. */
};

typedef struct vm_input_params vm_info_t;

int _create_vm(size_t argc, char **argv);
int _set_vm(size_t argc, char **argv);
int _run_vm(size_t vm_num);
int _update_vm(size_t vm_num);
int _collect_vm_info(size_t vm_num);
int _halt_vm(size_t vm_num);
int _delete_vm(size_t vm_num);

#ifdef __cplusplus
}
#endif

#endif /* ZVM_VM_OPS_H__ */