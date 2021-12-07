
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_KERNEL_H
#define Z_INCLUDE_SYSCALLS_KERNEL_H




#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall.h>

#include <linker/sections.h>


#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic push
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#if !defined(__XCC__)
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern k_tid_t z_impl_k_thread_create(struct k_thread * new_thread, k_thread_stack_t * stack, size_t stack_size, k_thread_entry_t entry, void * p1, void * p2, void * p3, int prio, uint32_t options, k_timeout_t delay);

__pinned_func
static inline k_tid_t k_thread_create(struct k_thread * new_thread, k_thread_stack_t * stack, size_t stack_size, k_thread_entry_t entry, void * p1, void * p2, void * p3, int prio, uint32_t options, k_timeout_t delay)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		uintptr_t more[] = {
			*(uintptr_t *)&p2,
			*(uintptr_t *)&p3,
			*(uintptr_t *)&prio,
			*(uintptr_t *)&options,
			*(uintptr_t *)&delay
		};
		/* coverity[OVERRUN] */
		return (k_tid_t) arch_syscall_invoke6(*(uintptr_t *)&new_thread, *(uintptr_t *)&stack, *(uintptr_t *)&stack_size, *(uintptr_t *)&entry, *(uintptr_t *)&p1, (uintptr_t) &more, K_SYSCALL_K_THREAD_CREATE);
	}
#endif
	compiler_barrier();
	return z_impl_k_thread_create(new_thread, stack, stack_size, entry, p1, p2, p3, prio, options, delay);
}


extern int z_impl_k_thread_stack_space_get(const struct k_thread * thread, size_t * unused_ptr);

__pinned_func
static inline int k_thread_stack_space_get(const struct k_thread * thread, size_t * unused_ptr)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&thread, *(uintptr_t *)&unused_ptr, K_SYSCALL_K_THREAD_STACK_SPACE_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_thread_stack_space_get(thread, unused_ptr);
}


extern int z_impl_k_thread_join(struct k_thread * thread, k_timeout_t timeout);

__pinned_func
static inline int k_thread_join(struct k_thread * thread, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&thread, *(uintptr_t *)&timeout, K_SYSCALL_K_THREAD_JOIN);
	}
#endif
	compiler_barrier();
	return z_impl_k_thread_join(thread, timeout);
}


extern int32_t z_impl_k_sleep(k_timeout_t timeout);

__pinned_func
static inline int32_t k_sleep(k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int32_t) arch_syscall_invoke1(*(uintptr_t *)&timeout, K_SYSCALL_K_SLEEP);
	}
#endif
	compiler_barrier();
	return z_impl_k_sleep(timeout);
}


extern int32_t z_impl_k_usleep(int32_t us);

__pinned_func
static inline int32_t k_usleep(int32_t us)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int32_t) arch_syscall_invoke1(*(uintptr_t *)&us, K_SYSCALL_K_USLEEP);
	}
#endif
	compiler_barrier();
	return z_impl_k_usleep(us);
}


extern void z_impl_k_busy_wait(uint32_t usec_to_wait);

__pinned_func
static inline void k_busy_wait(uint32_t usec_to_wait)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&usec_to_wait, K_SYSCALL_K_BUSY_WAIT);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_busy_wait(usec_to_wait);
}


extern void z_impl_k_yield(void);

__pinned_func
static inline void k_yield(void)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke0(K_SYSCALL_K_YIELD);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_yield();
}


extern void z_impl_k_wakeup(k_tid_t thread);

__pinned_func
static inline void k_wakeup(k_tid_t thread)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&thread, K_SYSCALL_K_WAKEUP);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_wakeup(thread);
}


extern k_tid_t z_impl_z_current_get(void);

__pinned_func
static inline k_tid_t z_current_get(void)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (k_tid_t) arch_syscall_invoke0(K_SYSCALL_Z_CURRENT_GET);
	}
#endif
	compiler_barrier();
	return z_impl_z_current_get();
}


extern void z_impl_k_thread_abort(k_tid_t thread);

__pinned_func
static inline void k_thread_abort(k_tid_t thread)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&thread, K_SYSCALL_K_THREAD_ABORT);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_thread_abort(thread);
}


extern void z_impl_k_thread_start(k_tid_t thread);

__pinned_func
static inline void k_thread_start(k_tid_t thread)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&thread, K_SYSCALL_K_THREAD_START);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_thread_start(thread);
}


extern k_ticks_t z_impl_k_thread_timeout_expires_ticks(const struct k_thread * t);

__pinned_func
static inline k_ticks_t k_thread_timeout_expires_ticks(const struct k_thread * t)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (k_ticks_t) arch_syscall_invoke1(*(uintptr_t *)&t, K_SYSCALL_K_THREAD_TIMEOUT_EXPIRES_TICKS);
	}
#endif
	compiler_barrier();
	return z_impl_k_thread_timeout_expires_ticks(t);
}


extern k_ticks_t z_impl_k_thread_timeout_remaining_ticks(const struct k_thread * t);

__pinned_func
static inline k_ticks_t k_thread_timeout_remaining_ticks(const struct k_thread * t)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (k_ticks_t) arch_syscall_invoke1(*(uintptr_t *)&t, K_SYSCALL_K_THREAD_TIMEOUT_REMAINING_TICKS);
	}
#endif
	compiler_barrier();
	return z_impl_k_thread_timeout_remaining_ticks(t);
}


extern int z_impl_k_thread_priority_get(k_tid_t thread);

__pinned_func
static inline int k_thread_priority_get(k_tid_t thread)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&thread, K_SYSCALL_K_THREAD_PRIORITY_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_thread_priority_get(thread);
}


extern void z_impl_k_thread_priority_set(k_tid_t thread, int prio);

__pinned_func
static inline void k_thread_priority_set(k_tid_t thread, int prio)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke2(*(uintptr_t *)&thread, *(uintptr_t *)&prio, K_SYSCALL_K_THREAD_PRIORITY_SET);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_thread_priority_set(thread, prio);
}


extern void z_impl_k_thread_deadline_set(k_tid_t thread, int deadline);

__pinned_func
static inline void k_thread_deadline_set(k_tid_t thread, int deadline)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke2(*(uintptr_t *)&thread, *(uintptr_t *)&deadline, K_SYSCALL_K_THREAD_DEADLINE_SET);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_thread_deadline_set(thread, deadline);
}


extern void z_impl_k_thread_suspend(k_tid_t thread);

__pinned_func
static inline void k_thread_suspend(k_tid_t thread)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&thread, K_SYSCALL_K_THREAD_SUSPEND);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_thread_suspend(thread);
}


extern void z_impl_k_thread_resume(k_tid_t thread);

__pinned_func
static inline void k_thread_resume(k_tid_t thread)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&thread, K_SYSCALL_K_THREAD_RESUME);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_thread_resume(thread);
}


extern int z_impl_k_is_preempt_thread(void);

__pinned_func
static inline int k_is_preempt_thread(void)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke0(K_SYSCALL_K_IS_PREEMPT_THREAD);
	}
#endif
	compiler_barrier();
	return z_impl_k_is_preempt_thread();
}


extern void z_impl_k_thread_custom_data_set(void * value);

__pinned_func
static inline void k_thread_custom_data_set(void * value)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&value, K_SYSCALL_K_THREAD_CUSTOM_DATA_SET);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_thread_custom_data_set(value);
}


extern void * z_impl_k_thread_custom_data_get(void);

__pinned_func
static inline void * k_thread_custom_data_get(void)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (void *) arch_syscall_invoke0(K_SYSCALL_K_THREAD_CUSTOM_DATA_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_thread_custom_data_get();
}


extern int z_impl_k_thread_name_set(k_tid_t thread, const char * str);

__pinned_func
static inline int k_thread_name_set(k_tid_t thread, const char * str)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&thread, *(uintptr_t *)&str, K_SYSCALL_K_THREAD_NAME_SET);
	}
#endif
	compiler_barrier();
	return z_impl_k_thread_name_set(thread, str);
}


extern int z_impl_k_thread_name_copy(k_tid_t thread, char * buf, size_t size);

__pinned_func
static inline int k_thread_name_copy(k_tid_t thread, char * buf, size_t size)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke3(*(uintptr_t *)&thread, *(uintptr_t *)&buf, *(uintptr_t *)&size, K_SYSCALL_K_THREAD_NAME_COPY);
	}
#endif
	compiler_barrier();
	return z_impl_k_thread_name_copy(thread, buf, size);
}


extern void z_impl_k_timer_start(struct k_timer * timer, k_timeout_t duration, k_timeout_t period);

__pinned_func
static inline void k_timer_start(struct k_timer * timer, k_timeout_t duration, k_timeout_t period)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke3(*(uintptr_t *)&timer, *(uintptr_t *)&duration, *(uintptr_t *)&period, K_SYSCALL_K_TIMER_START);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_timer_start(timer, duration, period);
}


extern void z_impl_k_timer_stop(struct k_timer * timer);

__pinned_func
static inline void k_timer_stop(struct k_timer * timer)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&timer, K_SYSCALL_K_TIMER_STOP);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_timer_stop(timer);
}


extern uint32_t z_impl_k_timer_status_get(struct k_timer * timer);

__pinned_func
static inline uint32_t k_timer_status_get(struct k_timer * timer)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (uint32_t) arch_syscall_invoke1(*(uintptr_t *)&timer, K_SYSCALL_K_TIMER_STATUS_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_timer_status_get(timer);
}


extern uint32_t z_impl_k_timer_status_sync(struct k_timer * timer);

__pinned_func
static inline uint32_t k_timer_status_sync(struct k_timer * timer)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (uint32_t) arch_syscall_invoke1(*(uintptr_t *)&timer, K_SYSCALL_K_TIMER_STATUS_SYNC);
	}
#endif
	compiler_barrier();
	return z_impl_k_timer_status_sync(timer);
}


extern k_ticks_t z_impl_k_timer_expires_ticks(const struct k_timer * timer);

__pinned_func
static inline k_ticks_t k_timer_expires_ticks(const struct k_timer * timer)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (k_ticks_t) arch_syscall_invoke1(*(uintptr_t *)&timer, K_SYSCALL_K_TIMER_EXPIRES_TICKS);
	}
#endif
	compiler_barrier();
	return z_impl_k_timer_expires_ticks(timer);
}


extern k_ticks_t z_impl_k_timer_remaining_ticks(const struct k_timer * timer);

__pinned_func
static inline k_ticks_t k_timer_remaining_ticks(const struct k_timer * timer)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (k_ticks_t) arch_syscall_invoke1(*(uintptr_t *)&timer, K_SYSCALL_K_TIMER_REMAINING_TICKS);
	}
#endif
	compiler_barrier();
	return z_impl_k_timer_remaining_ticks(timer);
}


extern void z_impl_k_timer_user_data_set(struct k_timer * timer, void * user_data);

__pinned_func
static inline void k_timer_user_data_set(struct k_timer * timer, void * user_data)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke2(*(uintptr_t *)&timer, *(uintptr_t *)&user_data, K_SYSCALL_K_TIMER_USER_DATA_SET);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_timer_user_data_set(timer, user_data);
}


extern void * z_impl_k_timer_user_data_get(const struct k_timer * timer);

__pinned_func
static inline void * k_timer_user_data_get(const struct k_timer * timer)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (void *) arch_syscall_invoke1(*(uintptr_t *)&timer, K_SYSCALL_K_TIMER_USER_DATA_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_timer_user_data_get(timer);
}


extern int64_t z_impl_k_uptime_ticks(void);

__pinned_func
static inline int64_t k_uptime_ticks(void)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int64_t) arch_syscall_invoke0(K_SYSCALL_K_UPTIME_TICKS);
	}
#endif
	compiler_barrier();
	return z_impl_k_uptime_ticks();
}


extern void z_impl_k_queue_init(struct k_queue * queue);

__pinned_func
static inline void k_queue_init(struct k_queue * queue)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&queue, K_SYSCALL_K_QUEUE_INIT);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_queue_init(queue);
}


extern void z_impl_k_queue_cancel_wait(struct k_queue * queue);

__pinned_func
static inline void k_queue_cancel_wait(struct k_queue * queue)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&queue, K_SYSCALL_K_QUEUE_CANCEL_WAIT);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_queue_cancel_wait(queue);
}


extern int32_t z_impl_k_queue_alloc_append(struct k_queue * queue, void * data);

__pinned_func
static inline int32_t k_queue_alloc_append(struct k_queue * queue, void * data)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int32_t) arch_syscall_invoke2(*(uintptr_t *)&queue, *(uintptr_t *)&data, K_SYSCALL_K_QUEUE_ALLOC_APPEND);
	}
#endif
	compiler_barrier();
	return z_impl_k_queue_alloc_append(queue, data);
}


extern int32_t z_impl_k_queue_alloc_prepend(struct k_queue * queue, void * data);

__pinned_func
static inline int32_t k_queue_alloc_prepend(struct k_queue * queue, void * data)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int32_t) arch_syscall_invoke2(*(uintptr_t *)&queue, *(uintptr_t *)&data, K_SYSCALL_K_QUEUE_ALLOC_PREPEND);
	}
#endif
	compiler_barrier();
	return z_impl_k_queue_alloc_prepend(queue, data);
}


extern void * z_impl_k_queue_get(struct k_queue * queue, k_timeout_t timeout);

__pinned_func
static inline void * k_queue_get(struct k_queue * queue, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (void *) arch_syscall_invoke2(*(uintptr_t *)&queue, *(uintptr_t *)&timeout, K_SYSCALL_K_QUEUE_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_queue_get(queue, timeout);
}


extern int z_impl_k_queue_is_empty(struct k_queue * queue);

__pinned_func
static inline int k_queue_is_empty(struct k_queue * queue)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&queue, K_SYSCALL_K_QUEUE_IS_EMPTY);
	}
#endif
	compiler_barrier();
	return z_impl_k_queue_is_empty(queue);
}


extern void * z_impl_k_queue_peek_head(struct k_queue * queue);

__pinned_func
static inline void * k_queue_peek_head(struct k_queue * queue)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (void *) arch_syscall_invoke1(*(uintptr_t *)&queue, K_SYSCALL_K_QUEUE_PEEK_HEAD);
	}
#endif
	compiler_barrier();
	return z_impl_k_queue_peek_head(queue);
}


extern void * z_impl_k_queue_peek_tail(struct k_queue * queue);

__pinned_func
static inline void * k_queue_peek_tail(struct k_queue * queue)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (void *) arch_syscall_invoke1(*(uintptr_t *)&queue, K_SYSCALL_K_QUEUE_PEEK_TAIL);
	}
#endif
	compiler_barrier();
	return z_impl_k_queue_peek_tail(queue);
}


extern int z_impl_k_futex_wait(struct k_futex * futex, int expected, k_timeout_t timeout);

__pinned_func
static inline int k_futex_wait(struct k_futex * futex, int expected, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke3(*(uintptr_t *)&futex, *(uintptr_t *)&expected, *(uintptr_t *)&timeout, K_SYSCALL_K_FUTEX_WAIT);
	}
#endif
	compiler_barrier();
	return z_impl_k_futex_wait(futex, expected, timeout);
}


extern int z_impl_k_futex_wake(struct k_futex * futex, bool wake_all);

__pinned_func
static inline int k_futex_wake(struct k_futex * futex, bool wake_all)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&futex, *(uintptr_t *)&wake_all, K_SYSCALL_K_FUTEX_WAKE);
	}
#endif
	compiler_barrier();
	return z_impl_k_futex_wake(futex, wake_all);
}


extern void z_impl_k_event_init(struct k_event * event);

__pinned_func
static inline void k_event_init(struct k_event * event)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&event, K_SYSCALL_K_EVENT_INIT);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_event_init(event);
}


extern void z_impl_k_event_post(struct k_event * event, uint32_t events);

__pinned_func
static inline void k_event_post(struct k_event * event, uint32_t events)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke2(*(uintptr_t *)&event, *(uintptr_t *)&events, K_SYSCALL_K_EVENT_POST);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_event_post(event, events);
}


extern void z_impl_k_event_set(struct k_event * event, uint32_t events);

__pinned_func
static inline void k_event_set(struct k_event * event, uint32_t events)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke2(*(uintptr_t *)&event, *(uintptr_t *)&events, K_SYSCALL_K_EVENT_SET);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_event_set(event, events);
}


extern uint32_t z_impl_k_event_wait(struct k_event * event, uint32_t events, bool reset, k_timeout_t timeout);

__pinned_func
static inline uint32_t k_event_wait(struct k_event * event, uint32_t events, bool reset, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (uint32_t) arch_syscall_invoke4(*(uintptr_t *)&event, *(uintptr_t *)&events, *(uintptr_t *)&reset, *(uintptr_t *)&timeout, K_SYSCALL_K_EVENT_WAIT);
	}
#endif
	compiler_barrier();
	return z_impl_k_event_wait(event, events, reset, timeout);
}


extern uint32_t z_impl_k_event_wait_all(struct k_event * event, uint32_t events, bool reset, k_timeout_t timeout);

__pinned_func
static inline uint32_t k_event_wait_all(struct k_event * event, uint32_t events, bool reset, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (uint32_t) arch_syscall_invoke4(*(uintptr_t *)&event, *(uintptr_t *)&events, *(uintptr_t *)&reset, *(uintptr_t *)&timeout, K_SYSCALL_K_EVENT_WAIT_ALL);
	}
#endif
	compiler_barrier();
	return z_impl_k_event_wait_all(event, events, reset, timeout);
}


extern int32_t z_impl_k_stack_alloc_init(struct k_stack * stack, uint32_t num_entries);

__pinned_func
static inline int32_t k_stack_alloc_init(struct k_stack * stack, uint32_t num_entries)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int32_t) arch_syscall_invoke2(*(uintptr_t *)&stack, *(uintptr_t *)&num_entries, K_SYSCALL_K_STACK_ALLOC_INIT);
	}
#endif
	compiler_barrier();
	return z_impl_k_stack_alloc_init(stack, num_entries);
}


extern int z_impl_k_stack_push(struct k_stack * stack, stack_data_t data);

__pinned_func
static inline int k_stack_push(struct k_stack * stack, stack_data_t data)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&stack, *(uintptr_t *)&data, K_SYSCALL_K_STACK_PUSH);
	}
#endif
	compiler_barrier();
	return z_impl_k_stack_push(stack, data);
}


extern int z_impl_k_stack_pop(struct k_stack * stack, stack_data_t * data, k_timeout_t timeout);

__pinned_func
static inline int k_stack_pop(struct k_stack * stack, stack_data_t * data, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke3(*(uintptr_t *)&stack, *(uintptr_t *)&data, *(uintptr_t *)&timeout, K_SYSCALL_K_STACK_POP);
	}
#endif
	compiler_barrier();
	return z_impl_k_stack_pop(stack, data, timeout);
}


extern int z_impl_k_mutex_init(struct k_mutex * mutex);

__pinned_func
static inline int k_mutex_init(struct k_mutex * mutex)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&mutex, K_SYSCALL_K_MUTEX_INIT);
	}
#endif
	compiler_barrier();
	return z_impl_k_mutex_init(mutex);
}


extern int z_impl_k_mutex_lock(struct k_mutex * mutex, k_timeout_t timeout);

__pinned_func
static inline int k_mutex_lock(struct k_mutex * mutex, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&mutex, *(uintptr_t *)&timeout, K_SYSCALL_K_MUTEX_LOCK);
	}
#endif
	compiler_barrier();
	return z_impl_k_mutex_lock(mutex, timeout);
}


extern int z_impl_k_mutex_unlock(struct k_mutex * mutex);

__pinned_func
static inline int k_mutex_unlock(struct k_mutex * mutex)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&mutex, K_SYSCALL_K_MUTEX_UNLOCK);
	}
#endif
	compiler_barrier();
	return z_impl_k_mutex_unlock(mutex);
}


extern int z_impl_k_condvar_init(struct k_condvar * condvar);

__pinned_func
static inline int k_condvar_init(struct k_condvar * condvar)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&condvar, K_SYSCALL_K_CONDVAR_INIT);
	}
#endif
	compiler_barrier();
	return z_impl_k_condvar_init(condvar);
}


extern int z_impl_k_condvar_signal(struct k_condvar * condvar);

__pinned_func
static inline int k_condvar_signal(struct k_condvar * condvar)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&condvar, K_SYSCALL_K_CONDVAR_SIGNAL);
	}
#endif
	compiler_barrier();
	return z_impl_k_condvar_signal(condvar);
}


extern int z_impl_k_condvar_broadcast(struct k_condvar * condvar);

__pinned_func
static inline int k_condvar_broadcast(struct k_condvar * condvar)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&condvar, K_SYSCALL_K_CONDVAR_BROADCAST);
	}
#endif
	compiler_barrier();
	return z_impl_k_condvar_broadcast(condvar);
}


extern int z_impl_k_condvar_wait(struct k_condvar * condvar, struct k_mutex * mutex, k_timeout_t timeout);

__pinned_func
static inline int k_condvar_wait(struct k_condvar * condvar, struct k_mutex * mutex, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke3(*(uintptr_t *)&condvar, *(uintptr_t *)&mutex, *(uintptr_t *)&timeout, K_SYSCALL_K_CONDVAR_WAIT);
	}
#endif
	compiler_barrier();
	return z_impl_k_condvar_wait(condvar, mutex, timeout);
}


extern int z_impl_k_sem_init(struct k_sem * sem, unsigned int initial_count, unsigned int limit);

__pinned_func
static inline int k_sem_init(struct k_sem * sem, unsigned int initial_count, unsigned int limit)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke3(*(uintptr_t *)&sem, *(uintptr_t *)&initial_count, *(uintptr_t *)&limit, K_SYSCALL_K_SEM_INIT);
	}
#endif
	compiler_barrier();
	return z_impl_k_sem_init(sem, initial_count, limit);
}


extern int z_impl_k_sem_take(struct k_sem * sem, k_timeout_t timeout);

__pinned_func
static inline int k_sem_take(struct k_sem * sem, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&sem, *(uintptr_t *)&timeout, K_SYSCALL_K_SEM_TAKE);
	}
#endif
	compiler_barrier();
	return z_impl_k_sem_take(sem, timeout);
}


extern void z_impl_k_sem_give(struct k_sem * sem);

__pinned_func
static inline void k_sem_give(struct k_sem * sem)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&sem, K_SYSCALL_K_SEM_GIVE);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_sem_give(sem);
}


extern void z_impl_k_sem_reset(struct k_sem * sem);

__pinned_func
static inline void k_sem_reset(struct k_sem * sem)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&sem, K_SYSCALL_K_SEM_RESET);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_sem_reset(sem);
}


extern unsigned int z_impl_k_sem_count_get(struct k_sem * sem);

__pinned_func
static inline unsigned int k_sem_count_get(struct k_sem * sem)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (unsigned int) arch_syscall_invoke1(*(uintptr_t *)&sem, K_SYSCALL_K_SEM_COUNT_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_sem_count_get(sem);
}


extern int z_impl_k_msgq_alloc_init(struct k_msgq * msgq, size_t msg_size, uint32_t max_msgs);

__pinned_func
static inline int k_msgq_alloc_init(struct k_msgq * msgq, size_t msg_size, uint32_t max_msgs)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke3(*(uintptr_t *)&msgq, *(uintptr_t *)&msg_size, *(uintptr_t *)&max_msgs, K_SYSCALL_K_MSGQ_ALLOC_INIT);
	}
#endif
	compiler_barrier();
	return z_impl_k_msgq_alloc_init(msgq, msg_size, max_msgs);
}


extern int z_impl_k_msgq_put(struct k_msgq * msgq, const void * data, k_timeout_t timeout);

__pinned_func
static inline int k_msgq_put(struct k_msgq * msgq, const void * data, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke3(*(uintptr_t *)&msgq, *(uintptr_t *)&data, *(uintptr_t *)&timeout, K_SYSCALL_K_MSGQ_PUT);
	}
#endif
	compiler_barrier();
	return z_impl_k_msgq_put(msgq, data, timeout);
}


extern int z_impl_k_msgq_get(struct k_msgq * msgq, void * data, k_timeout_t timeout);

__pinned_func
static inline int k_msgq_get(struct k_msgq * msgq, void * data, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke3(*(uintptr_t *)&msgq, *(uintptr_t *)&data, *(uintptr_t *)&timeout, K_SYSCALL_K_MSGQ_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_msgq_get(msgq, data, timeout);
}


extern int z_impl_k_msgq_peek(struct k_msgq * msgq, void * data);

__pinned_func
static inline int k_msgq_peek(struct k_msgq * msgq, void * data)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&msgq, *(uintptr_t *)&data, K_SYSCALL_K_MSGQ_PEEK);
	}
#endif
	compiler_barrier();
	return z_impl_k_msgq_peek(msgq, data);
}


extern void z_impl_k_msgq_purge(struct k_msgq * msgq);

__pinned_func
static inline void k_msgq_purge(struct k_msgq * msgq)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&msgq, K_SYSCALL_K_MSGQ_PURGE);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_msgq_purge(msgq);
}


extern uint32_t z_impl_k_msgq_num_free_get(struct k_msgq * msgq);

__pinned_func
static inline uint32_t k_msgq_num_free_get(struct k_msgq * msgq)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (uint32_t) arch_syscall_invoke1(*(uintptr_t *)&msgq, K_SYSCALL_K_MSGQ_NUM_FREE_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_msgq_num_free_get(msgq);
}


extern void z_impl_k_msgq_get_attrs(struct k_msgq * msgq, struct k_msgq_attrs * attrs);

__pinned_func
static inline void k_msgq_get_attrs(struct k_msgq * msgq, struct k_msgq_attrs * attrs)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke2(*(uintptr_t *)&msgq, *(uintptr_t *)&attrs, K_SYSCALL_K_MSGQ_GET_ATTRS);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_msgq_get_attrs(msgq, attrs);
}


extern uint32_t z_impl_k_msgq_num_used_get(struct k_msgq * msgq);

__pinned_func
static inline uint32_t k_msgq_num_used_get(struct k_msgq * msgq)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (uint32_t) arch_syscall_invoke1(*(uintptr_t *)&msgq, K_SYSCALL_K_MSGQ_NUM_USED_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_msgq_num_used_get(msgq);
}


extern int z_impl_k_pipe_alloc_init(struct k_pipe * pipe, size_t size);

__pinned_func
static inline int k_pipe_alloc_init(struct k_pipe * pipe, size_t size)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&pipe, *(uintptr_t *)&size, K_SYSCALL_K_PIPE_ALLOC_INIT);
	}
#endif
	compiler_barrier();
	return z_impl_k_pipe_alloc_init(pipe, size);
}


extern int z_impl_k_pipe_put(struct k_pipe * pipe, void * data, size_t bytes_to_write, size_t * bytes_written, size_t min_xfer, k_timeout_t timeout);

__pinned_func
static inline int k_pipe_put(struct k_pipe * pipe, void * data, size_t bytes_to_write, size_t * bytes_written, size_t min_xfer, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke6(*(uintptr_t *)&pipe, *(uintptr_t *)&data, *(uintptr_t *)&bytes_to_write, *(uintptr_t *)&bytes_written, *(uintptr_t *)&min_xfer, *(uintptr_t *)&timeout, K_SYSCALL_K_PIPE_PUT);
	}
#endif
	compiler_barrier();
	return z_impl_k_pipe_put(pipe, data, bytes_to_write, bytes_written, min_xfer, timeout);
}


extern int z_impl_k_pipe_get(struct k_pipe * pipe, void * data, size_t bytes_to_read, size_t * bytes_read, size_t min_xfer, k_timeout_t timeout);

__pinned_func
static inline int k_pipe_get(struct k_pipe * pipe, void * data, size_t bytes_to_read, size_t * bytes_read, size_t min_xfer, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke6(*(uintptr_t *)&pipe, *(uintptr_t *)&data, *(uintptr_t *)&bytes_to_read, *(uintptr_t *)&bytes_read, *(uintptr_t *)&min_xfer, *(uintptr_t *)&timeout, K_SYSCALL_K_PIPE_GET);
	}
#endif
	compiler_barrier();
	return z_impl_k_pipe_get(pipe, data, bytes_to_read, bytes_read, min_xfer, timeout);
}


extern size_t z_impl_k_pipe_read_avail(struct k_pipe * pipe);

__pinned_func
static inline size_t k_pipe_read_avail(struct k_pipe * pipe)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (size_t) arch_syscall_invoke1(*(uintptr_t *)&pipe, K_SYSCALL_K_PIPE_READ_AVAIL);
	}
#endif
	compiler_barrier();
	return z_impl_k_pipe_read_avail(pipe);
}


extern size_t z_impl_k_pipe_write_avail(struct k_pipe * pipe);

__pinned_func
static inline size_t k_pipe_write_avail(struct k_pipe * pipe)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (size_t) arch_syscall_invoke1(*(uintptr_t *)&pipe, K_SYSCALL_K_PIPE_WRITE_AVAIL);
	}
#endif
	compiler_barrier();
	return z_impl_k_pipe_write_avail(pipe);
}


extern int z_impl_k_poll(struct k_poll_event * events, int num_events, k_timeout_t timeout);

__pinned_func
static inline int k_poll(struct k_poll_event * events, int num_events, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke3(*(uintptr_t *)&events, *(uintptr_t *)&num_events, *(uintptr_t *)&timeout, K_SYSCALL_K_POLL);
	}
#endif
	compiler_barrier();
	return z_impl_k_poll(events, num_events, timeout);
}


extern void z_impl_k_poll_signal_init(struct k_poll_signal * sig);

__pinned_func
static inline void k_poll_signal_init(struct k_poll_signal * sig)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&sig, K_SYSCALL_K_POLL_SIGNAL_INIT);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_poll_signal_init(sig);
}


extern void z_impl_k_poll_signal_reset(struct k_poll_signal * sig);

__pinned_func
static inline void k_poll_signal_reset(struct k_poll_signal * sig)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&sig, K_SYSCALL_K_POLL_SIGNAL_RESET);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_poll_signal_reset(sig);
}


extern void z_impl_k_poll_signal_check(struct k_poll_signal * sig, unsigned int * signaled, int * result);

__pinned_func
static inline void k_poll_signal_check(struct k_poll_signal * sig, unsigned int * signaled, int * result)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke3(*(uintptr_t *)&sig, *(uintptr_t *)&signaled, *(uintptr_t *)&result, K_SYSCALL_K_POLL_SIGNAL_CHECK);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_poll_signal_check(sig, signaled, result);
}


extern int z_impl_k_poll_signal_raise(struct k_poll_signal * sig, int result);

__pinned_func
static inline int k_poll_signal_raise(struct k_poll_signal * sig, int result)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&sig, *(uintptr_t *)&result, K_SYSCALL_K_POLL_SIGNAL_RAISE);
	}
#endif
	compiler_barrier();
	return z_impl_k_poll_signal_raise(sig, result);
}


extern void z_impl_k_str_out(char * c, size_t n);

__pinned_func
static inline void k_str_out(char * c, size_t n)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke2(*(uintptr_t *)&c, *(uintptr_t *)&n, K_SYSCALL_K_STR_OUT);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_str_out(c, n);
}


extern int z_impl_k_float_disable(struct k_thread * thread);

__pinned_func
static inline int k_float_disable(struct k_thread * thread)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&thread, K_SYSCALL_K_FLOAT_DISABLE);
	}
#endif
	compiler_barrier();
	return z_impl_k_float_disable(thread);
}


extern int z_impl_k_float_enable(struct k_thread * thread, unsigned int options);

__pinned_func
static inline int k_float_enable(struct k_thread * thread, unsigned int options)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&thread, *(uintptr_t *)&options, K_SYSCALL_K_FLOAT_ENABLE);
	}
#endif
	compiler_barrier();
	return z_impl_k_float_enable(thread, options);
}


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */
