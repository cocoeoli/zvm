/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// #include <stdlib.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <arch/cpu.h>
#include <arch/arm64/lib_helpers.h>

void main(void){
    printk("Hello world, %s.\n", CONFIG_BOARD);
	uint32_t curr_el = GET_EL(read_currentel());
    printk("Current EL = %d.\n", curr_el);
}
