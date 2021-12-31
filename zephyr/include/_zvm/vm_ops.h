/*
 * Copyright (c) 2021 Huang Jiajia
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-31
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_VM_OPS_H__
#define ZVM_VM_OPS_H__


/**
 * @file Realize APIs which realted to vm.
 *
 * All vm command include create, set, run, update, list, halt and delete vm.
 * These APIs will be called by subsys/zvm/shell.c.
 */

/* This struct includes the parameters that user input for defining a vm.
 * Such as vCPU cores, memory allocation, OS image location and so on.
 */
struct vm_input_params{
    size_t vcpu_num;
    size_t memory_alloc;
    char *os_img_path;
}

int _create_vm(size_t argc, char **argv);
int _set_vm(size_t argc, char **argv);
int _run_vm(size_t vm_num);
int _update_vm(size_t vm_num);
int _collect_vm_info(size_t vm_num);
int _halt_vm(size_t vm_num);
int _delete_vm(size_t vm_num);


#endif /* ZVM_VM_OPS_H__ */