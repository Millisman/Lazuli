/**
 * @file arch.h
 *
 * Defines architecture specific functions for AVR.
 */

#ifndef LZ_ARCH_H
#define LZ_ARCH_H

#include <sys/types.h>

_EXTERN_C_DECL_BEGIN

/**
 * Get the current stack pointer.
 *
 * @return The address pointed by the machine stack pointer.
 */
void *
GetStackPointer();

/**
 * Enable global interrupts.
 */
extern void
GlobalInterruptsEnable();

/**
 * Disable global interrupts.
 */
extern void
GlobalInterruptsDisable();

/**
 * Function that loops forever, never returns.
 */
extern void
InfiniteLoop();

_EXTERN_C_DECL_END

#endif /* LZ_ARCH_H */