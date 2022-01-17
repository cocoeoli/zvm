/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-31
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <string.h>

#include <asm/virt.h>
#include <debug/debug.h>
#include <os/os.h>
#include <vm/vm_ops.h>
#include <vm/vm.h>

/**
 * @file
 * 
 * Most of the vm commands receive args, so the first thing we need to do is
 * parsing args. We can realize it under the help of zpehyr/lib/util/getopt.
 */

/* Structure for parsing args. */
struct getopt_state *state;

/*
 * @brief Create a blank vm struct for subsequent operations. 
 * 
 * In vm_shell.c file, we add some shell commands for zvm. First command should 
 * implement is this one. And this one will seperate from others. Other command 
 * will compose a struct which include several function pointer. 
 * The main work function _create_vm do is:
 * 	-> 1. Judge whether current exception level is EL2;
 * 	-> 2. Instantiate struct vm and allocate memory for new vm;
 * 	-> 3. Parsing input args and make sure new vm's OS type;
 *  -> 4. Allocate a vmid to the new vm;
 *  -> ......
 */
int _create_vm(size_t argc, char **argv){
	if(!is_el2_now()){
		pr_err("Current exception level is not EL2.");
		return -EACCES;
	}

	if(vm_num_full()){
		pr_err("System vm's num has reached the limit.");
		return -ENXIO;
	}

	/* Current exception level is EL2, parse input args.*/
	if(state == NULL){
		/*
		 * If state is NULL, which means this is first time to use this struct.
		 * Then we should to initialize it by allocate memory for it. Otherwise, 
		 * it means state has been used before and there is some specific value 
		 * in it.   
		 */
		state = (struct getopt_state*)malloc(sizeof(struct getopt_state));
		if(!state){
			pr_err("Allocation memory for getopt_state Error!");
			return -ENOMEM;		
		}
	}
	getopt_init(state);

	struct vm *new_vm = (struct vm*)malloc(sizeof(struct vm));
	if(!new_vm){
		pr_err("Allocation memory for new_vm Error!");
		return -ENOMEM;		
	}

	int opt;
	char *optstring = "t:n:";
	new_vm->os = (struct os*)malloc(sizeof(struct os));
	if(!new_vm->os){
		pr_err("Allocation memory for new_vm->os Error!");
		free(new_vm);
		return -ENOMEM;		
	}
	os_init(new_vm->os);
	
	while ((opt = getopt(state, argc, argv, optstring)) != -1) {
		switch (opt) {
		case 't':
			new_vm->os->type = get_os_id_by_type(state->optarg);
			break;
		case 'n':
			strcpy(new_vm->os->name, state->optarg);
			break;
		default:
			pr_err("Input args invalid.");
			free(new_vm->os);
			free(new_vm);
			return -EINVAL;
		}
	}
	
	if (new_vm->os->type == OS_TYPE_MAX || strlen(new_vm->os->name) == 0) {
		pr_err("Input args Error.");
		free(new_vm->os);
		free(new_vm);
		return -EINVAL;
	}

	new_vm->vmid = _allocate_vmid();
	new_vm->vm_status = VM_STATUS_NEVER_RUN;
	/* According to OS type to bind vm_ops. */
	switch (new_vm->os->type){
		case OS_TYPE_LINUX:
			new_vm->ops = &linux_vm_ops;
			break;
		case OS_TYPE_ZEPHYR:
			new_vm->ops = NULL;	/* Add correspoding ops later. */
			break;
		default:
			new_vm->ops = NULL;	/* Add correspoding ops later. */
			break;
	}

	printk("--INIT VM--\nOS-type: %s\nVM-name: %s\nNew-vmid: %d\n", \
		get_os_type_by_id(new_vm->os->type), new_vm->os->name, new_vm->vmid);
	return 0;
}
