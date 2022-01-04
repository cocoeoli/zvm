/*
 * Copyright (c) 2021 Huang Jiajia 
 * Email: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-31
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <_zvm/vm_ops.h>

/**
 * @file
 * 
 * Most of the vm commands receive args, so the first thing we need to do is
 * parsing args. We can realize it under the help of zpehyr/lib/util/getopt.
 */

/* Structure for parsing args. */
struct getopt_state *state;

/* Structure for stroing input args. */
struct vm_input_params *vm_params;

int _create_vm(size_t argc, char **argv){
	int ret = _set_vm(argc, argv);
	if(ret){
		/* Parsing input error. */
		pr_err("Parsing number Error!\n");
		return -ENOMEM;
	}

    return 0;
}

int _set_vm(size_t argc, char **argv){
	free(state);
	free(vm_params);

	/* Initial structure pointer. */
	state = (struct getopt_state*)malloc(sizeof(struct getopt_state));
	if(!state){
		pr_err("Allocation memory Error!\n");
		return -ENOMEM;
	}
	getopt_init(state);

	vm_params = (struct vm_input_params*)malloc(sizeof(struct vm_input_params));
	if(!vm_params){
		pr_err("Allocation memory Error!\n");
		free(state);
		return -ENOMEM;
	}

    /* Parse input args. */
	int opt;
	char *optstring = "n:c:m:i:";
	while ((opt = getopt(state, argc, argv, optstring)) != -1) {
		switch (opt) {
		case 'n':
			vm_params->vm_num = atoi(state->optarg);
			break;
		case 'c':
			vm_params->vcpu_num = atoi(state->optarg);
			break;
		case 'm':
			vm_params->vm_memory = atoi(state->optarg);
			break;
		case 'i':
			vm_params->os_img_path = state->optarg;
			break;
		default:
			return -EINVAL;
		}
	}

    return 0;
}

int _run_vm(size_t vm_num){

    return 0;
}

int _update_vm(size_t vm_num){

    return 0;
}

int _collect_vm_info(size_t vm_num){

    return 0;
}

int _halt_vm(size_t vm_num){

    return 0;
}

int _delete_vm(size_t vm_num){

    return 0;
}