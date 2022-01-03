/*
 * THIS FILE IS PART OF ZVM PROJECT
 * main.c - 
 *
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-07
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <shell/shell.h>
#include <_zvm/zvm.h>

int main(int argc, char **argv){
   int ret = __zvm_info_init(&sys_info);
   
   printk("ZVM test, %d\n", ret);
   zvm_info_print(&sys_info);
   return 0;
}