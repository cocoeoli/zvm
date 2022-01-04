/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// #include <stdlib.h>
#include <zephyr.h>
#include <sys/printk.h>

void main(void){
	printk("Hello World! %s\n", CONFIG_BOARD);
	char *s = "99";
	printk("s = %s\n", s);
	int c = atoi(s);
	printk("i = %d\n", c);
	return 0;
}
