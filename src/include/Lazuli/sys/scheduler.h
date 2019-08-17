/**
 * @file src/include/Lazuli/sys/scheduler_base.h
 * @brief Base scheduler interface. The kernel API of the base scheduler.
 * @date Feb 2017
 * @author Remi Andruccioli
 *
 * This file describes the common interface of every scheduler classes in
 * Lazuli.
 * It defines the interface to which each scheduler class must conform.
 * It also defines symbols that are accessible to any scheduler class.
 */

#ifndef LAZULI_SYS_SCHEDULER_BASE_H
#define LAZULI_SYS_SCHEDULER_BASE_H

#include <stdint.h>

#include <Lazuli/common.h>
#include <Lazuli/lazuli.h>

#include <Lazuli/sys/task.h>

_EXTERN_C_DECL_BEGIN

/**
 * Represents all possible operations common to all scheduler classes.
 */
typedef struct {
  /**
   * Initialize the scheduler.
   */
  void (*init)(void);

  /**
   * Register a new task.
   *
   * This function must basically allocate the space to store the specific Task
   * structure in memory and initialize its specific fields.
   *
   * @param taskConfiguration A pointer to an Lz_TaskConfiguration containing
   *                          the configuration of the task being registered.
   *                          This parameter can never be _NULL_, but some of
   *                          its fields can contain default configuration
   *                          values.
   * @param idleTask A boolean value indicating that the call is made to
   *                 register the idle task of the scheduler.
   *
   * @return A pointer to the newly allocated and initialized Task.
   */
  Task * (*registerTask)(const Lz_TaskConfiguration * const taskConfiguration,
                         const bool idleTask);

  /**
   * Run the scheduler.
   *
   * Start scheduling tasks.
   */
  void (*run)(void);

  /**
   * Entry point of the interrupt handler for this scheduler.
   *
   * @param sp The stack pointer of the task being executed before the
   *           interrupt.
   *           This is used to save the task's context address.
   * @param interruptCode The code of the interrupt that occured.
   */
  void (*handleInterrupt)(void * const sp, const uint8_t interruptCode);

  /**
   * Entry point of the wait handler for this scheduler.
   *
   * @param sp The stack pointer of the task calling the wait routine.
   * @param eventCode The code of the wait event.
   */
  void (*waitEvent)(void * const sp, const uint8_t eventCode);

  /**
   * Wake up all tasks waiting for a mutex.
   *
   * @param waitingTasks A pointer to the Lz_LinkedList containing all the tasks
   * waiting for the mutex.
   */
  void (*wakeupTasksWaitingMutex)(Lz_LinkedList * const waitingTasks);

  /**
   * Place the current running task in the queue of tasks waiting for a mutex.
   *
   * @param sp The stack pointer of the current running task after saving its
   *           context.
   * @param waitingTasks A pointer to the Lz_LinkedList containing all the tasks
   * waiting for the mutex.
   */
  void (*waitMutex)(void * const sp, Lz_LinkedList * const waitingTasks);

  /**
   * Manage the termination of a task.
   *
   * Will be called when a task returns from its main function or calls
   * Lz_Task_Terminate().
   *
   * @param sp The stack pointer of the terminating task.
   */
  void (*manageTaskTermination)(void * const sp);

  /**
   * Abort the curent running task.
   *
   * @param sp The stack pointer of the running task after saving its context.
   */
  void (*abortTask)(void * const sp);
}SchedulerOperations;

/**
 * A pointer to the current running task.
 */
extern Task *currentTask;

/**
 * Reverse the bytes of a function pointer.
 *
 * @param pointer A function pointer.
 *
 * @return A new function pointer from reversed bytes of parameter "pointer".
 */
void
(*ReverseBytesOfFunctionPointer(void (* const pointer)(void)))(void);

/**
 * Initialize the scheduler prior to running it.
 * This function is called by kernel initialization.
 */
void
BaseScheduler_Init(void);

/**
 * Call the appropriate scheduler to manage task termination.
 *
 * This function is called when a task terminates its execution.
 * i.e. when the task returns from its main function of when it calls
 * Lz_Task_Terminate().
 *
 * @param sp The stack pointer of the terminating task.
 *           This parameter will be used only if configuration option
 *           LZ_CONFIG_SAVE_TASK_CONTEXT_ON_TERMINATION is set to 1.
 */
void
BaseScheduler_ManageTaskTermination(void * const sp);

/**
 * Call the appropriate scheduler to abort the curent running task.
 *
 * @param sp The stack pointer of the running task after saving its context.
 */
void
BaseScheduler_AbortTask(void * const sp);

/*
 * TODO: Maybe rename interruptCode and eventCode to xxxxxId or something like
 * that...
 */
/**
 * This function is called by arch-specific interrupt handling routine, after
 * saving the context of the current running task.
 *
 * @param sp The stack pointer of the current running task after saving its
 *           context.
 * @param interruptCode The code of the interrupt being handled.
 */
void
BaseScheduler_HandleInterrupt(void * const sp, const uint8_t interruptCode);

/**
 * This function is called from arch-specific Wait routine in order to get the
 * current running task wait for a particular event, after saving its context.
 *
 * @param sp The stack pointer of the current running task after saving its
 *           context.
 * @param eventCode The code of the event the task is waiting for.
 */
void
BaseScheduler_WaitEvent(void * const sp, const uint8_t eventCode);

/**
 * Wake up all tasks waiting for a mutex.
 *
 * @param waitingTasks A pointer to the Lz_LinkedList containing all the tasks
 * waiting for the mutex.
 */
void
BaseScheduler_WakeupTasksWaitingMutex(Lz_LinkedList * const waitingTasks);

/**
 * Place the current running task in the queue of tasks waiting for a mutex.
 * This function is called from arch-specific WaitMutex routine in order to get
 * the current running task wait for a mutex, after saving its context.
 *
 * @param sp The stack pointer of the current running task after saving its
 *           context.
 * @param waitingTasks A pointer to the Lz_LinkedList containing all the tasks
 * waiting for the mutex.
 */
void
BaseScheduler_WaitMutex(void * const sp, Lz_LinkedList * const waitingTasks);

/**
 * Register a new task.
 *
 * @param taskEntryPoint The entry point of the task to register.
 *                       i.e. A pointer to the function representing the task.
 * @param taskConfiguration A pointer to an Lz_TaskConfiguration containing the
 *                          configuration of the task being registered.
 *                          If NULL is passed, then default values are applied
 *                          for all parameters.
 * @param idleTask A boolean value indicating that the task to register is the
 *                 scheduler idle task.
 *
 * @return
 *         - _true_ if the task has been registered without error.
 *         - _false_ if an error occured during registration.
 */
bool
BaseScheduler_RegisterTask(void (* const taskEntryPoint)(void),
                           const Lz_TaskConfiguration * taskConfiguration,
                           bool idleTask);

_EXTERN_C_DECL_END

#endif /* LAZULI_SYS_SCHEDULER_BASE_H */