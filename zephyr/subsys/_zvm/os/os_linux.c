/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2022-01-13
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <_zvm/vm/vm_ops.h>

/*
 * @brief Setup for linux vm.
 *
 * When we new a vm, we only know:
 *  -> os type
 *  -> vm name
 * There is still lots of args should be set for linux vm run. As follows:
 *  -> -i  specific vmid
 *  -> -c  vcpu number
 *  -> -m  allocation memory number
 *  -> -o  os image path (need zephyr file system support)
 *  -> -r  ramdisk path
 *  -> -d  dtb path (should parse dtb file before running)
 *  -> ... ...
 */
static void linux_vm_setup(size_t argc, char **argv){
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    return;
}

static void linux_vm_run(uint32_t vmid){
    ARG_UNUSED(vmid);
    return;
}

static void linux_vm_update(size_t argc, char **argv){
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    return;
}

static void linux_vm_info(size_t argc, char **argv){
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    return;
}

static void linux_vm_pause(uint32_t vmid){
    ARG_UNUSED(vmid);
    return;
}

static void linux_vm_halt(size_t argc, char **argv){
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    return;
}

static void linux_vm_destroy(uint32_t vmid){
    ARG_UNUSED(vmid);
    return;
}

struct vm_ops linux_vm_ops = {
    .set_vm = linux_vm_setup,
    .run_vm = linux_vm_run,
    .update_vm = linux_vm_update,
    .collect_vm_info = linux_vm_info,
    .pause_vm = linux_vm_pause,
    .halt_vm = linux_vm_halt,
    .delete_vm = linux_vm_destroy,
};
