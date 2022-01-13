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

#include <getopt.h>
#include <errno.h>

#include <arch/arm64/cpu.h>
#include <shell/shell.h>
#include <sys/printk.h>

/**
 * @file Realize APIs which realted to vm.
 *
 * All vm command include create, set, run, update, list, halt and delete vm.
 * These APIs will be called by subsys/zvm/shell.c.
 */

/* Structure for parsing args. */
extern struct getopt_state *state;

/* 
 * Apart Create VM, other instructions will compose a function pointer struct 
 * for operating vm. 
 */
int _create_vm(size_t argc, char **argv);

struct vm_ops {
    void (*set_vm)(size_t argc, char **argv);
    void (*run_vm)(uint32_t vmid);
    void (*update_vm)(size_t argc, char **argv);
    void (*collect_vm_info)(size_t argc, char **argv);
    void (*pause_vm)(uint32_t vmid);
    void (*halt_vm)(size_t argc, char **argv);
    void (*delete_vm)(uint32_t vmid);
};

#endif /* ZVM_VM_OPS_H__ */