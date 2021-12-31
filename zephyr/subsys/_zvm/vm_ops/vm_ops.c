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


}

int _set_vm(size_t argc, char **argv){


}

int _run_vm(size_t vm_num){


}

int _update_vm(size_t vm_num){


}

int _collect_vm_info(size_t vm_num){


}

int _halt_vm(size_t vm_num){


}

int _delete_vm(size_t vm_num){


}
