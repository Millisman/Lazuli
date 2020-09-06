/*
 * SPDX-License-Identifier: GPL-3.0-only
 * This file is part of Lazuli.
 */

/**
 * @file
 * @brief Lazuli scheduler interface. The kernel API of the scheduler.
 * @copyright 2017-2020, Remi Andruccioli <remi.andruccioli@gmail.com>
 *
 * This file describes the kernel interface of the Lazuli scheduler.
 */

#ifndef LAZULI_SYS_SCHEDULER_H
#define LAZULI_SYS_SCHEDULER_H

#include <stdint.h>

#include <Lazuli/common.h>
#include <Lazuli/lazuli.h>
#include <Lazuli/mutex.h>

#include <Lazuli/sys/task.h>

_EXTERN_C_DECL_BEGIN

/**
 * Reverse the bytes of a function pointer.
 *
 * @param pointer A function pointer.
 *
 * @return A new function pointer from reversed bytes of parameter @p pointer.
 */
void
(*ReverseBytesOfFunctionPointer(void (* const pointer)(void)))(void);

/**
 * Initialize the scheduler prior to running it.
 * This function is called by kernel initialization.
 */
void
Scheduler_Init(void);

/**
 * Call the appropriate scheduler to abort the curent running task.
 *
 * @param sp The stack pointer of the running task after saving its context.
 */
void
Scheduler_AbortTask(void * const sp);

/*
 * TODO: Maybe rename interruptCode and eventCode to xxxxxId or something like
 * that...
 */
/**
 * This function is called by arch-specific interrupt handling routine. This
 * function is executed in the context of the current running task, i.e. on its
 * stack.
 *
 * @param interruptCode The code of the interrupt being handled.
 */
void
Scheduler_HandleInterrupt(const uint8_t interruptCode);

/**
 * This function is called when a clock tick occured, catch by the interrupt
 * handler.
 *
 * @param sp The stack pointer of the current running task after saving its
 *           context.
 */
void
Scheduler_HandleClockTick(void * const sp);

/**
 * This function is called from arch-specific Wait routine in order to get the
 * current running task wait for a particular event, after saving its context.
 *
 * @param sp The stack pointer of the current running task after saving its
 *           context.
 * @param eventCode The code of the event the task is waiting for.
 */
void
Scheduler_WaitEvent(void * const sp, const uint8_t eventCode);

/**
 * Wake up all tasks waiting for a mutex.
 *
 * @param mutex A pointer to the mutex the tasks are waiting for.
 */
void
Scheduler_WakeupTasksWaitingMutex(Lz_Mutex * const mutex);

/**
 * Get a pointer to the current running task.
 *
 * @return A valid pointer to the current running task.
 */
Task*
Scheduler_GetCurrentTask(void);

/**
 * Put the current task to sleep until the end of its time slice.
 */
void
Scheduler_SleepUntilEndOfTimeSlice(void);

_EXTERN_C_DECL_END

#endif /* LAZULI_SYS_SCHEDULER_H */
