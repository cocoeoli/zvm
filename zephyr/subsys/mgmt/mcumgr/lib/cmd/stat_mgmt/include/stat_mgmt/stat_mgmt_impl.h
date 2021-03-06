/*
 * Copyright (c) 2018-2021 mcumgr authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Declares implementation-specific functions required by statistics
 *	  management.  The default stubs can be overridden with functions that
 *	  are compatible with the host OS.
 */

#ifndef H_STAT_MGMT_IMPL_
#define H_STAT_MGMT_IMPL_

#ifdef __cplusplus
extern "C" {
#endif

struct stat_mgmt_entry;

typedef int stat_mgmt_foreach_entry_fn(struct stat_mgmt_entry *entry, void *arg);

/**
 * @brief Retrieves the name of the stat group at the specified index.
 *
 * @param idx		The index of the stat group to retrieve.
 * @param out_name	On success, the name of the requested stat group gets written here.
 *
 * @return	0 on success;
 *		MGMT_ERR_ENOENT if no group with the specified index exists;
 *		Other MGMT_ERR_[...] code on failure.
 */
int stat_mgmt_impl_get_group(int idx, const char **out_name);

/**
 * @brief Applies a function to every entry in the specified stat group.
 *
 * @param group_name	The name of the stat group to operate on.
 * @param cb		The callback to apply to each stat entry.
 * @param arg		An optional argument to pass to the callback.
 *
 * @return 0 on success; MGMT_ERR_[...] code on failure.
 */
int stat_mgmt_impl_foreach_entry(const char *group_name, stat_mgmt_foreach_entry_fn *cb, void *arg);

#ifdef __cplusplus
}
#endif

#endif
