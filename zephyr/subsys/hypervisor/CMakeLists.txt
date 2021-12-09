# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Huang Jiajia 
# Email: Huangjj2020@hnu.edu.cn
# Date: 2021-12-07

add_subdirectory(virt)

zephyr_sources_ifdef(
    CONFIG_HYPERVISOR
    shell.c
)

