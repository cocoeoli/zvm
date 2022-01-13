# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Huang Jiajia 
# Email: Huangjj2020@hnu.edu.cn
# Date: 2022-01-13

zephyr_sources_ifdef(
    CONFIG_ZVM
    os_linux.c
)
