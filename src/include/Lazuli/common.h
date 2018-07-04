/**
 * @file src/include/Lazuli/common.h
 * @brief Basic type definitions and useful macros.
 * @date Feb 2017
 * @author Remi Andruccioli
 *
 * This file describes basic type definitions and useful macros used in the
 * Lazuli project.
 * This file can be used within kernel code or within user code without any
 * dependency.
 */

#ifndef LAZULI_COMMON_H
#define LAZULI_COMMON_H

#ifdef __cplusplus

/**
 * Open C++ header file declarations.
 */
#define _EXTERN_C_DECL_BEGIN extern "C" {

/**
 * Close C++ header file declarations.
 */
#define _EXTERN_C_DECL_END }

#else /* __cplusplus */

#define _EXTERN_C_DECL_BEGIN
#define _EXTERN_C_DECL_END

#endif /* __cplusplus */

/**
 * Tell the compiler that the variable X is left unsed.
 *
 * @param X The unused variable.
 */
#define UNUSED(X) ((void)(X))

/**
 * Perform an assertion at compile time.
 * Won't compile if the assertion is false.
 *
 * @param C The condition to check.
 * @param M A string explaining why the assertion is performed. This parameter
 *          is not actualy used, it's only here to display an informative
 *          message directly in the source code in case of a failure.
 */
#define STATIC_ASSERT(C, M) extern char _static_assertion_##M[(C) ? 1 : -1]

/**
 * NULL pointer.
 */
#define NULL ((void *)0)

/**
 * Represents the difference between two pointers.
 */
typedef int ptrdiff_t;

/**
 * Unsigned integer of 1 byte long.
 */
typedef unsigned char u8;
STATIC_ASSERT(sizeof(u8) == 1, u8_MUST_be_1_byte_long);

/**
 * Signed integer of 1 byte long.
 */
typedef signed char s8;
STATIC_ASSERT(sizeof(s8) == 1, s8_MUST_be_1_byte_long);

/**
 * Unsigned integer of 2 bytes long.
 */
typedef unsigned int u16;
STATIC_ASSERT(sizeof(u16) == 2, u16_MUST_be_2_bytes_long);

/**
 * Signed integer of 2 bytes long.
 */
typedef signed int s16;
STATIC_ASSERT(sizeof(s16) == 2, s16_MUST_be_2_bytes_long);

/**
 * Unsigned integer of 4 bytes long.
 */
typedef unsigned long int u32;
STATIC_ASSERT(sizeof(u32) == 4, u32_MUST_be_4_bytes_long);

/**
 * Signed integer of 4 bytes long.
 */
typedef signed long int s32;
STATIC_ASSERT(sizeof(s32) == 4, s32_MUST_be_4_bytes_long);

/**
 * Boolean type.
 */
typedef u8 bool;
STATIC_ASSERT(sizeof(bool) == 1, bool_MUST_be_1_byte_long);

/**
 * Machine word (unsigned).
 *
 * Represents an unsigned integer that has the length of the data word
 * manipulated by the processor.
 * i.e. 8 bits on an 8-bit machine, 16 bits on a 16-bit machine, and so on.
 *
 * The equivalent for an address word is the type void*.
 */
typedef u8 mword;
STATIC_ASSERT(sizeof(mword) == 1, mword_MUST_be_1_byte_long);

/**
 * Represents the size of an object.
 */
typedef u16 size_t;

/**
 * Maximum value of u8.
 */
#define u8_MAX ((u8)0xff)

/**
 * Minimum value of u8.
 */
#define u8_MIN ((u8)0x00)

/**
 * Maximum value of s8.
 */
#define s8_MAX ((s8)0x7f)

/**
 * Minimum value of s8.
 */
#define s8_MIN ((s8)0x80)

/**
 * Maximum value of u16.
 */
#define u16_MAX ((u16)0xffff)

/**
 * Minimum value of u16.
 */
#define u16_MIN ((u16)0x0000)

/**
 * Maximum value of s16.
 */
#define s16_MAX ((s16)0x7fff)

/**
 * Minimum value of s16.
 */
#define s16_MIN ((s16)0x8000)

/**
 * Maximum value of u32.
 */
#define u32_MAX ((u32)0xffffffff)

/**
 * Minimum value of u32.
 */
#define u32_MIN ((u32)0x00000000)

/**
 * Maximum value of s32.
 */
#define s32_MAX ((s32)0x7fffffff)

/**
 * Minimum value of s32.
 */
#define s32_MIN ((s32)0x80000000)

/**
 * Boolean TRUE constant value.
 */
#define true ((bool)1)

/**
 * Boolean FALSE constant value.
 */
#define false ((bool)0)

/**
 * @brief Allow arithmetic on a void pointer.
 *
 * Arithmetic on void pointers isn't allowed in standard C.
 *
 * @param X The void pointer on which to perform arithmetic.
 */
#define ALLOW_ARITHM(X) ((u8 *)(X))

/*
 * This assertion is mandatory for ALLOW_ARITHM macro.
 * ALLOW_ARITHM can work with any type whose size is 1 byte.
 */
STATIC_ASSERT(sizeof(u8) == 1,
              u8_MUST_be_1_byte_long_to_allow_arithmetic_on_void_pointers);

/**
 * Check that the lvalue V is of type T at compile time.
 *
 * @param V The lvalue to check.
 * @param T The supposed type of the lvalue.
 */
#define STATIC_CHECK_TYPE(V, T) UNUSED(1 ? &V : (T*)0)

/**
 * Set the corresponding bits of X in the value V of type T.
 *
 * @param V The value to set bits.
 * @param T The type of the value V.
 * @param X A value containing the bits (at logical 1) to set.
 */
#define SET_BITS(V, T, X)                           \
  do {                                              \
    STATIC_CHECK_TYPE(V, T);                        \
    V |= (T)(X);                                    \
  } while (0)

/**
 * Clear the corresponding bits of X in the value V of type T.
 *
 * @param V The value to set bits.
 * @param T The type of the value V.
 * @param X A value containing the bits (at logical 1) to clear.
 */
#define CLEAR_BITS(V, T, X)                     \
  do {                                          \
    STATIC_CHECK_TYPE(V, T);                    \
    V &= (T)(~(X));                             \
  } while (0)

/**
 * Define a constant bit at position X, starting from index 0.
 *
 * @param X An integer representing the position of the bit, starting from index
 *          0.
 */
#define POSITION(X) (1 << (X))

/**
 * Define an indirect read/write variable at an absolute address.
 * i.e. A variable that is accessed through a pointer.
 *
 * @param X The address of the variable.
 * @param T The type of the variable.
 */
#define INDIRECT_T(X, T) ((volatile T *)(X))

/**
 * Define an indirect read/write register at an absolute address.
 * i.e. A register that is accessed through a pointer.
 *
 * @param X The address of the register.
 */
#define INDIRECT(X) INDIRECT_T(X, u8)

/**
 * Define a direct read/write variable at an absolute address.
 *
 * @param X The address of the variable.
 * @param T The type of the variable.
 */
#define DIRECT_T(X, T) (*INDIRECT_T(X, T))

/**
 * Define a direct read/write register at an absolute address.
 *
 * @param X The address of the register.
 */
#define DIRECT(X) DIRECT_T(X, u8)

/**
 * Take the low byte of a 16-bit value.
 *
 * @param X The 16-bit value.
 */
#define LO8(X) ((u8)X)

/**
 * Take the high byte of a 16-bit value.
 *
 * @param X The 16-bit value.
 */
#define HI8(X) LO8(X >> 8)

/**
 * Get the offset of a member in a structure.
 *
 * @param M The name of the member.
 * @param T The type of the structure.
 */
#define OFFSET_OF(M, T)                         \
  ((size_t)(&(((T*)0)->M)))

/**
 * Get a pointer to the structure T containing the member M pointed by P.
 *
 * May not compile if P doesn't point to the type defined by M.
 *
 * @param P The pointer to the member.
 * @param M The name of the member.
 * @param T The type of the structure.
 */
#define CONTAINER_OF(P, M, T)                                   \
  ((T*) ((u8*) (1 ? (P) : &(((T*)0)->M)) - OFFSET_OF(M, T)))

/**
 * Convert the name of a symbol to a string.
 *
 * @param X The symbol name to convert.
 */
#define NAME_OF(X) #X

/**
 * Get the number of elements in a statically initialized array.
 *
 * @param The array variable.
 */
#define ELEMENTS_COUNT(X) (sizeof(X) / sizeof(X[0]))

#endif /* LAZULI_COMMON_H */
