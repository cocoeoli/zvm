/**
 * @author xcl (xiongcl@hnu.edu.cn)
 * @brief 
 * @date 2022-02-15
 * 
 * @copyright Copyright (c) 2022
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _VIRT_IRQ_H_
#define _VIRT_IRQ_H_

#include <stdint.h>
#include <_zvm/list_ops.h>

#define VM_VIRQ_NUM 16

struct virq_desc{
    /* virq id */
    uint8_t id;

    /* vcpu id */
    uint8_t vcpu_id;
};

struct virq_struct{
    /* active irq */
    uint32_t act_num_virq;

    /* pending virt irq */
    uint32_t pen_virq;

    /* pending phys irq */
    uint32_t pen_pirq;

    /* Need a spinlock for protecting mmu. */
    struct k_spinlock spinlock;

    /* list of irq */
    struct list_addr_t pen_list;
    struct list_addr_t act_list;

    /* virq desctription list */
    struct virq_desc this_vcpu_desc[VM_VIRQ_NUM];

};


#endif // !_VIRT_IRQ_H_
