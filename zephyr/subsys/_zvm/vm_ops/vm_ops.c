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

int _create_vm(size_t argc, char **argv){
    /* Parse input args. */
	struct getopt_state state = {1, 1, 0, 0, NULL, ""};
	struct vm_input_params vm_params = {0, 0, ""};
	int opt;

	while ((opt = getopt(&state, argc, argv, "c:m:i:")) != -1) {
		switch (opt) {
		case 'c':
			vm_params.vcpu_num = atoi(state.optarg);
			break;
		case 'm':
			vm_params.vm_memory = atoi(state.optarg);
			break;
		case 'i':
			vm_params.os_img_path = state.optarg;
			break;
		default:
			return -EINVAL;
		}
	}

    return 0;
}

int _set_vm(size_t argc, char **argv){

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