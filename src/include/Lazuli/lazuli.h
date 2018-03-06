/**
 * @file src/include/Lazuli/lazuli.h
 * @brief The public API of the Lazuli kernel.
 * @date Feb 2017
 * @author Remi Andruccioli
 *
 * This file describes the public API of the Lazuli kernel.
 * It defines public types and functions that can by used by user tasks.
 */

#ifndef LZ_LAZULI_H
#define LZ_LAZULI_H

#include <Lazuli/common.h>

_EXTERN_C_DECL_BEGIN

/**
 * Represents the configuration of a task being registered in the scheduler.
 */
typedef struct {
  /**
   * A pointer to an allocated  const string containing the name to give to the
   * task.
   * That string must not be deallocated after registering the task.
   */
  char const *name;

  /**
   * The size of the stack needed by the task
   */
  size_t stackSize;
}Lz_TaskConfiguration;

/**
 * Register a new task.
 *
 * @param taskEntryPoint The entry point of the task to register.
 *                       i.e. A pointer to the function representing the task.
 * @param taskConfiguration A pointer to a TaskConfiguration containing the
 *                          configuration of the task being registered.
 *                          If NULL is passed, then default values are applied
 *                          for all parameters.
 */
void
Lz_RegisterTask(void (*taskEntryPoint)(),
                Lz_TaskConfiguration * const taskConfiguration);

/**
 * @brief Initialize an Lz_TaskConfiguration with default values for all
 *        parameters.
 *
 * No function is provided for allocating a new TaskConfiguration. The user is
 * responsible of the creation of a new TaskConfiguration.
 *
 * @param taskConfiguration A pointer to the TaskConfiguration to initialize.
 */
void
Lz_InitTaskConfiguration(Lz_TaskConfiguration * const taskConfiguration);

/**
 * Run the scheduler.
 *
 * Start scheduling tasks.
 */
void
Lz_Run();

/**
 * Wait for the interrupt "External Interrupt Request 0".
 * Blocks the calling task until "External Interrupt Request 0" occurs.
 */
void
Lz_WaitInt0();

/**
 * Get the name of the calling task.
 *
 * @return A pointer to a string containing the name of the current running
 *         task, or NULL if the task has no name.
 */
char const*
Lz_GetTaskName();

_EXTERN_C_DECL_END

#endif /* LZ_LAZULI_H */