/* auto-generated by gen_syscalls.py, don't edit */
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic push
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif
#include <syscalls/kernel.h>

extern int z_vrfy_k_pipe_put(struct k_pipe * pipe, void * data, size_t bytes_to_write, size_t * bytes_written, size_t min_xfer, k_timeout_t timeout);
uintptr_t z_mrsh_k_pipe_put(uintptr_t arg0, uintptr_t arg1, uintptr_t arg2,
		uintptr_t arg3, uintptr_t arg4, uintptr_t arg5, void *ssf)
{
	_current->syscall_frame = ssf;
	int ret = z_vrfy_k_pipe_put(*(struct k_pipe **)&arg0, *(void **)&arg1, *(size_t*)&arg2, *(size_t **)&arg3, *(size_t*)&arg4, *(k_timeout_t*)&arg5)
;
	_current->syscall_frame = NULL;
	return (uintptr_t) ret;
}

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif
