/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-31
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>

#include <_zvm/debug/debug.h>
#include <_zvm/vm/vm_ops.h>
#include <_zvm/vm/vm.h>

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
	// if(!is_el2_now()){
	// 	pr_err("Current exception level is not EL2.\n");
	// 	return -EACCES;		/* Permission denied. */
	// }

	if(vm_num_full()){
		pr_err("System vm's num has reached the limit.\n");
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
			pr_err("Allocation memory for getopt_state Error!\n");
			return -ENOSR;		/* Insufficient memory. */
		}
		getopt_init(state);
	}

	struct vm *new_vm = (struct vm*)malloc(sizeof(struct vm));
	if(!new_vm){
		pr_err("Allocation memory for new_vm Error!\n");
		free(state);
		return -ENOSR;		/* Insufficient memory. */
	}

	int opt;
	char *optstring = "t:n:";
	while ((opt = getopt(state, argc, argv, optstring)) != -1) {
		switch (opt) {
		case 't':
			new_vm->os->type = atoi(state->optarg);
			break;
		case 'n':
			new_vm->os->name = state->optarg;
			break;
		default:
			pr_err("Input args invalid.\n");
			return -EINVAL;		/* Invalid argument. */
		}
	}

	new_vm->vmid = _allocate_vmid();
	new_vm->vm_status = VM_STATUS_NEVER_RUN;

	return 0;
}
