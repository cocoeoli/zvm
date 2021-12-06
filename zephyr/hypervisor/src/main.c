/*
 * THIS FILE IS PART OF ZephyrVisor PROJECT
 * main.c - 
 *
 * Copyright (c) 2012-2014 Wind River Systems, Inc. 
 * Copyright (c) 2021 Huang Jiajia - Huangjj2020@hnu.edu.cn
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
/*
 * #include <lib/util/getopt/getopt.h>
 */
#include <unistd.h>

int main(int argc, char **argv){
   printk("Hello world!\n");
   return 0;
}
