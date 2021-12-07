/*
 * THIS FILE IS PART OF ZephyrVisor PROJECT
 * main.c - 
 *
 * Copyright (c) 2012-2014 Wind River Systems, Inc. 
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-07
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <shell/shell.h>


int main(int argc, char **argv)
{
   printk("Hypervisor test.../n");
   return 0;
}
