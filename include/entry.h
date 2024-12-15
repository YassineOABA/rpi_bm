/**
 * @file entry.h
 * @brief Exception Vector Table Definitions and Frame Size.
 * 
 * This header file contains macros defining the vector table entries for various 
 * types of exceptions in ARM architecture. The vector entries correspond to different 
 * exception types such as invalid exceptions and faults in various exception levels 
 * (EL0, EL1) and architectures (AArch32, AArch64).
 * 
 * Additionally, it defines the size of the exception frame, which is used to store 
 * the context during exception handling.
 * 
 * ## Vector Entry Descriptions:
 * - Each vector corresponds to a specific type of exception, such as synchronous exceptions, 
 *   IRQ (interrupt requests), FIQ (fast interrupt requests), and SError (system errors) 
 *   across different Exception Levels (EL0, EL1) and architectures (AArch32, AArch64).
 * 
 * ## S_FRAME_SIZE:
 * - The macro `S_FRAME_SIZE` defines the size of the exception frame, which is used 
 *   during the context saving/restoring process when an exception occurs.
 */

#ifndef _ENTRY_H_
#define _ENTRY_H_


// Exception vector definitions for invalid exceptions
#define VECTOR_INVALID_SYN_EL1_SP_EL0       0    // Synchronous exception at EL1, SP at EL0
#define VECTOR_INVALID_IRQ_EL1_SP_EL0       1    // IRQ exception at EL1, SP at EL0
#define VECTOR_INVALID_FIQ_EL1_SP_EL0       2    // FIQ exception at EL1, SP at EL0
#define VECTOR_INVALID_SER_EL1_SP_EL0       3    // SError exception at EL1, SP at EL0
#define VECTOR_INVALID_SYN_EL1_SP_EL1       4    // Synchronous exception at EL1, SP at EL1
#define VECTOR_INVALID_IRQ_EL1_SP_EL1       5    // IRQ exception at EL1, SP at EL1
#define VECTOR_INVALID_FIQ_EL1_SP_EL1       6    // FIQ exception at EL1, SP at EL1
#define VECTOR_INVALID_SER_EL1_SP_EL1       7    // SError exception at EL1, SP at EL1
#define VECTOR_INVALID_SYN_EL0_AARCH64      8    // Synchronous exception at EL0, AArch64 mode
#define VECTOR_INVALID_IRQ_EL0_AARCH64      9    // IRQ exception at EL0, AArch64 mode
#define VECTOR_INVALID_FIQ_EL0_AARCH64      10   // FIQ exception at EL0, AArch64 mode
#define VECTOR_INVALID_SER_EL0_AARCH64      11   // SError exception at EL0, AArch64 mode
#define VECTOR_INVALID_SYN_EL0_AARCH32      12   // Synchronous exception at EL0, AArch32 mode
#define VECTOR_INVALID_IRQ_EL0_AARCH32      13   // IRQ exception at EL0, AArch32 mode
#define VECTOR_INVALID_FIQ_EL0_AARCH32      14   // FIQ exception at EL0, AArch32 mode
#define VECTOR_INVALID_SER_EL0_AARCH32      15   // SError exception at EL0, AArch32 mode

// Size of the exception frame used for context saving/restoring
#define S_FRAME_SIZE			256    // Size of exception frame in bytes

#endif  /* _ENTRY_H_ */
