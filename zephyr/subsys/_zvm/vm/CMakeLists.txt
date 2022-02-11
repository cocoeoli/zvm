# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Huang Jiajia 
# Email: Huangjj2020@hnu.edu.cn
# Date: 2021-12-31

zephyr_sources_ifdef(
    CONFIG_ZVM
    vm_mm.c
    vm_ops.c
    vm.c
)
