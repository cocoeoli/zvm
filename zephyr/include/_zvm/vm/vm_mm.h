/*
 * Copyright (c) xiongcl@hnu.edu.cn
 * Date: 2022-02
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZVM_VM_MM_H__
#define ZVM_VM_MM_H__

#include <zephyr.h>
#include <stdint.h>

/**
 * @brief initial vm_mm struct for guest vm
 */
void zvm_mm_struct_init(struct vm *this_vm);

/**
 * @brief alloc physical memory for vtma
 */
int alloc_vm_memory(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area);

/**
 * @brief map virtual addr 'v_area' to physical addr 'phy'
 */
int map_vtma_to_block(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area);

/**
 * @brief map vtma to physical block address:
 */
int __map_vtma_to_block(uintptr_t phys, uintptr_t virt, size_t size, uint32_t attrs);

/**
 * @brief add vtma_space to vm's used list area:
 */
int add_used_vtma_space(struct zvm_mm_struct *z_mm, struct vm_task_mm_area *v_area);


#endif /* VM_MM_H__ */