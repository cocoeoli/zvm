/*
 * Copyright (c) 2021 Huang Jiajia
 * E-mail: Huangjj2020@hnu.edu.cn
 * Date: 2021-12-05 15:34
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <shell/shell.h>
#include <_zvm/debug/debug.h>
#include <_zvm/vm/vm_ops.h>

#define SHELL_HELP_ZVM "ZVM manager command. " \
    "Some subcommand you can choice as below:"  \
    "new set run update list delete"
#define SHELL_HELP_CREATE_NEW_VM "Create a new vm.\n"
#define SHELL_HELP_SET_VM "Set vm.\n"
#define SHELL_HELP_RUN_VM "Run vm x.\n"
#define SHELL_HELP_UPDATE_VM "Update vm x.\n"
#define SHELL_HELP_LIST_VM "List all vm info.\n"
#define SHELL_HELP_HALT_VM "Halt vm x.\n"
#define SHELL_HELP_DELETE_VM "Delete vm x.\n"

static int cmd_zvm_new(const struct shell *shell, size_t argc, char **argv){
    shell_fprintf(shell, SHELL_NORMAL, "Creating new vm...\n");

    int ret = _create_vm(argc, argv);

    if(ret){
        /* Initial vm failure. */ 
        pr_err("The return value from _create_vm(): %d\n", ret);
        return -EAGAIN;
    }else{
        shell_fprintf(shell, SHELL_NORMAL, "Create vm success.\n");
        return 0;
    }
}

static int cmd_zvm_set(const struct shell *shell, size_t argc, char **argv){
    shell_fprintf(shell, SHELL_NORMAL, "Set vm's configuration...\n");
    int ret = 0;
    if(ret){
        /* Set vm failure. */ 
        pr_err("The return value: %d\n", ret);
        return -EAGAIN;
    }else{
        shell_fprintf(shell, SHELL_NORMAL, "Set vm's configuration success.\n");
        return 0;
    }
}

static int cmd_zvm_run(const struct shell *shell, size_t argc, char **argv){
    /* Run vm code. */
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_fprintf(shell, SHELL_NORMAL, "Run a new vm success.\n");
    return 0;
}

static int cmd_zvm_update(const struct shell *shell, size_t argc, char **argv){
    /* Update vm code. */
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_fprintf(shell, SHELL_NORMAL, "Update a new vm success.\n");
    return 0;
}

static int cmd_zvm_list(const struct shell *shell, size_t argc, char **argv){
    /* List vm code. */
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_fprintf(shell, SHELL_NORMAL, "List a new vm success.\n");
    return 0;
}

static int cmd_zvm_halt(const struct shell *shell, size_t argc, char **argv){
    /* Halt vm code. */
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_fprintf(shell, SHELL_NORMAL, "Halt a new vm success.\n");
    return 0;
}

static int cmd_zvm_delete(const struct shell *shell, size_t argc, char **argv){
    /* Delete vm code. */
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_fprintf(shell, SHELL_NORMAL, "Delete a new vm success.\n");
    return 0;
}

/* Add subcommand for Root0 command zvm. */
SHELL_STATIC_SUBCMD_SET_CREATE(m_sub_zvm,
    SHELL_CMD(new, NULL, SHELL_HELP_CREATE_NEW_VM, cmd_zvm_new),
    SHELL_CMD(set, NULL, SHELL_HELP_SET_VM, cmd_zvm_set),
    SHELL_CMD(run, NULL, SHELL_HELP_RUN_VM, cmd_zvm_run),
    SHELL_CMD(update, NULL, SHELL_HELP_UPDATE_VM, cmd_zvm_update),
    SHELL_CMD(list, NULL, SHELL_HELP_LIST_VM, cmd_zvm_list) ,
    SHELL_CMD(delete, NULL, SHELL_HELP_DELETE_VM, cmd_zvm_delete),
    SHELL_CMD(halt, NULL, SHELL_HELP_HALT_VM, cmd_zvm_halt),
    SHELL_SUBCMD_SET_END
);

/* Add command for hypervisor. */
SHELL_CMD_REGISTER(zvm, &m_sub_zvm, SHELL_HELP_ZVM, NULL);
