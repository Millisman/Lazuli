/**
 * @file swap.h
 *
 * This file defines the interface for byte swap routines.
 */

#ifndef LZ_SYS_SWAP_H
#define LZ_SYS_SWAP_H

#include <Lazuli/common.h>

#include <Lazuli/sys/swap.h>

_EXTERN_C_DECL_BEGIN

/**
 * Get an u16 byte-swapped from an u16.
 *
 * @param u16 The u16 to swap.
 *
 * @return A new byte-swapped u16 from the value u.
 */
u16
Swap16(u16 u);

_EXTERN_C_DECL_END

#endif /* LZ_SYS_SWAP_H */
