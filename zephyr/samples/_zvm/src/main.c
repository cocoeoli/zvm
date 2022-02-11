/*
 * THIS FILE IS PART OF ZVM PROJECT - main.c
 *
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-07
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <shell/shell.h>
#include <zvm.h>
#include <_zvm/vm/vm.h>
#include <_zvm/vm/vm_mm.h>
#include <_zvm/asm/mm.h>


void vm_mm_test()
{
   struct vm *vm;
   uint64_t base_addr = 0x0;
   uint64_t size = 4096;
   int ret = 0;

   vm = k_malloc(sizeof(struct vm));
   printk("prepare alloc memory!");

   zvm_mm_struct_init(vm);
   printk("mm_struct init successful!");

   ret = vm_mm_init(vm, base_addr, size, 0);
   if(!ret)
      printk("mm test error!");
   else
      printk("mm init successful!");

}

int main(int argc, char **argv){
   int ret = zvm_init();
   printk("ZVM test. ret = %d.\n", ret);
   zvm_info_print(zvm_overall_info->hw_info);
   vm_mm_test();

   return 0;
}