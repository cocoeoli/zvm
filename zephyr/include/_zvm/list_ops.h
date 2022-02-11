/*
 * Copyright (c) xiongcl@hnu.edu.cn
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIST_OPS_H__
#define LIST_OPS_H__

#include <zephyr.h>
#include <stdint.h>
#include <_zvm/vm/vm.h>

/* below code may have copyright risk */

/**
 * @brief list_addr_t struct for the list of heap or page
 * 
 */
struct list_addr_t{
    struct list_addr_t *prev, *next;
};

/**
 * @brief init_list for init the vma list
 * 
 */
static void inline init_list(struct list_addr_t *list)
{
    list->next = list;
    list->prev = list;
}

/**
 * @brief add vtma after head
 * 
 * @param head 
 * @param new_node 
 */
static void inline list_add_after(struct list_addr_t *head,
		struct list_addr_t *new_node)
{
	head->prev->next = new_node;
	new_node->next = head;
	new_node->prev = head->prev;
	head->prev = new_node;
}

/**
 * @brief add vtma before head
 * 
 * @param head 
 * @param new 
 */
static void inline list_insert_before(struct list_addr_t *head,
		struct list_addr_t *new_node)
{
	new_node->prev = head->prev;
	new_node->next = head;
	head->prev->next = new_node;
	head->prev = new_node;
}

/**
 * @brief del list node in vtma
 * 
 * @param list 
 */
static void inline list_del(struct list_addr_t *list)
{
	list->next->prev = list->prev;
	list->prev->next = list->next;
	list->next = (void *)0x10;
	list->prev = (void *)0x20;
}

#define container_of(ptr, name, member)	(name *)((unsigned char *)ptr - ((unsigned char *)&(((name *)0)->member)))

#define list_entry(ptr, type, member)	container_of(ptr, type, member)

#define list_for_each_entry(pos, head, member)	\
	for (pos = list_entry((head)->next, __typeof__(*pos), member); \
	&pos->member != (head); \
	pos = list_entry(pos->member.next, __typeof__(*pos), member))

/* above code may have copyright risk */

#endif  /*LIST_OPS_H__*/