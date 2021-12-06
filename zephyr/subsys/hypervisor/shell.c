/*
 * Copyright (c) 2021 Huang Jiajia
 * 
 * E-mail: Huangjj2020@hnu.edu.cn
 * 
 * Date: 2021-12-05 15:34
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#include <shell/shell.h>
#include <hypervisor/shell.h>
#include <unistd.h>


static int cmd_zvisor(const struct shell *shell, size_t argc, char **argv)
{
    int ch;
    opterr = 0; /* not print error msg */
    while ((ch = getopt(argc, argv, "nsruad")) != -1)
    {
        switch (ch)
        {
            case 'n':
                /* create a new vm */
                shell_print(shell, "create a new vm success!\n");
                break;

            case 's':
                /* set vm */
                shell_print(shell, "set vm!\n");
                break;

            case 'r':
                /* start/run vm */
                shell_print(shell, "start/run vm!\n");
                break;

            case 'u':
                /* update vm */
                shell_print(shell, "update vm!\n");
                break;

            case 'a':
                /* check vm status */
                shell_print(shell, "check vm status!\n");
                break;
                      
            case 'd':
                /* destroy vm */
                shell_print(shell, "destroy vm!\n");
                break;
            
            default:
                shell_print(shell, "Input Error!\n");
                break;
        }
    }
    return 0;    
}


