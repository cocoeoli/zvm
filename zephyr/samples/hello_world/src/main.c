/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

#define MEMORY_NODE_ID	memory_40000000

void main(void)
{
	char *node_id = DT_PATH(soc, MEMORY_NODE_ID);
    printk("%s\n", node_id);
	printk("Hello World! %s\n", CONFIG_BOARD);
}
