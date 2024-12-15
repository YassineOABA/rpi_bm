/**
 * @file        entry.S
 * @brief       ARMv8-A Exception Vector Table and Exception Handlers.
 * @description This assembly file defines the exception vector table for EL1 
 *              and associated handlers. It provides macros for context saving 
 *              and restoring, and a mechanism for managing invalid entries 
 *              and interrupt handling.
 * 
 * @version     1.0
 * @date        2024-12-15
 */

#include "entry.h"

/**
 * @brief Macro to save the CPU context during an exception.
 * @description This macro saves the general-purpose registers (x0-x30) and adjusts 
 *              the stack pointer to reserve space for the saved state.
 */
.macro kernel_exception_enter
    sub sp, sp, #S_FRAME_SIZE        // Adjust the stack pointer to reserve space for the saved registers
    stp x0, x1, [sp, #16 * 0]        // Save registers x0 and x1 to the stack
    stp x2, x3, [sp, #16 * 1]        // Save registers x2 and x3 to the stack
    stp x4, x5, [sp, #16 * 2]        // Save registers x4 and x5 to the stack
    stp x6, x7, [sp, #16 * 3]        // Save registers x6 and x7 to the stack
    stp x8, x9, [sp, #16 * 4]        // Save registers x8 and x9 to the stack
    stp x10, x11, [sp, #16 * 5]      // Save registers x10 and x11 to the stack
    stp x12, x13, [sp, #16 * 6]      // Save registers x12 and x13 to the stack
    stp x14, x15, [sp, #16 * 7]      // Save registers x14 and x15 to the stack
    stp x16, x17, [sp, #16 * 8]      // Save registers x16 and x17 to the stack
    stp x18, x19, [sp, #16 * 9]      // Save registers x18 and x19 to the stack
    stp x20, x21, [sp, #16 * 10]     // Save registers x20 and x21 to the stack
    stp x22, x23, [sp, #16 * 11]     // Save registers x22 and x23 to the stack
    stp x24, x25, [sp, #16 * 12]     // Save registers x24 and x25 to the stack
    stp x26, x27, [sp, #16 * 13]     // Save registers x26 and x27 to the stack
    stp x28, x29, [sp, #16 * 14]     // Save registers x28 and x29 to the stack
    str x30, [sp, #16 * 15]          // Save register x30 (link register) to the stack
.endm

/**
 * @brief Macro to restore the CPU context after an exception.
 * @description This macro restores the general-purpose registers (x0-x30) 
 *              from the saved state and adjusts the stack pointer accordingly.
 */
.macro kernel_exception_exit
    ldp x0, x1, [sp, #16 * 0]        // Restore registers x0 and x1 from the stack
    ldp x2, x3, [sp, #16 * 1]        // Restore registers x2 and x3 from the stack
    ldp x4, x5, [sp, #16 * 2]        // Restore registers x4 and x5 from the stack
    ldp x6, x7, [sp, #16 * 3]        // Restore registers x6 and x7 from the stack
    ldp x8, x9, [sp, #16 * 4]        // Restore registers x8 and x9 from the stack
    ldp x10, x11, [sp, #16 * 5]      // Restore registers x10 and x11 from the stack
    ldp x12, x13, [sp, #16 * 6]      // Restore registers x12 and x13 from the stack
    ldp x14, x15, [sp, #16 * 7]      // Restore registers x14 and x15 from the stack
    ldp x16, x17, [sp, #16 * 8]      // Restore registers x16 and x17 from the stack
    ldp x18, x19, [sp, #16 * 9]      // Restore registers x18 and x19 from the stack
    ldp x20, x21, [sp, #16 * 10]     // Restore registers x20 and x21 from the stack
    ldp x22, x23, [sp, #16 * 11]     // Restore registers x22 and x23 from the stack
    ldp x24, x25, [sp, #16 * 12]     // Restore registers x24 and x25 from the stack
    ldp x26, x27, [sp, #16 * 13]     // Restore registers x26 and x27 from the stack
    ldp x28, x29, [sp, #16 * 14]     // Restore registers x28 and x29 from the stack
    ldr x30, [sp, #16 * 15]          // Restore register x30 (link register) from the stack
    add sp, sp, #S_FRAME_SIZE        // Adjust the stack pointer back after restoring the registers
    eret                             // Return from exception (exception return)
.endm

/**
 * @brief Macro to handle invalid exception entries.
 * @description This macro logs an error message for invalid entries 
 *              and enters an infinite loop for debugging.
 * 
 * @param type Exception type identifier.
 */
.macro handle_invalid_entry type
    kernel_exception_enter          // Call the kernel_exception_enter macro to save the context
    mov x0, #\type                  // Set x0 to the exception type (passed as an argument)
    mrs x1, esr_el1                 // Read the ESR_EL1 register value into x1
    mrs x2, elr_el1                 // Read the ELR_EL1 register value (exception link register) into x2
    bl show_invalid_entry_message   // Branch to the show_invalid_entry_message function to display the error
    b err_hang                      // Branch to err_hang for an infinite loop (to halt the system)
.endm

/**
 * @brief Macro to define an exception vector entry.
 * @description Aligns the vector table entries and branches to the appropriate handler.
 * 
 * @param label Label of the handler to branch to.
 */
.macro ventry label
    .align 7                          // Align the vector entry to 128-byte boundary
    b \label                          // Branch to the specified label (handler)
.endm

/**
 * @brief Infinite loop to halt the system on error.
 */
.globl err_hang
err_hang:
    b err_hang                        // Infinite loop to prevent further execution (for debugging purposes)

/**
 * @brief ARMv8-A Exception Vector Table.
 * @description This table defines the entry points for exceptions at various
 *              exception levels and states (e.g., EL1, EL0, AArch64, AArch32).
 *              Each entry branches to the appropriate handler function.
 */
.align 11
.globl vector_table
vector_table:
    ventry handler_vector_0  // VECTOR_SYNC_EL1_SP_EL0
    ventry handler_vector_1  // VECTOR_IRQ_EL1_SP_EL0
    ventry handler_vector_2  // VECTOR_FIQ_EL1_SP_EL0
    ventry handler_vector_3  // VECTOR_SERR_EL1_SP_EL0

    ventry handler_vector_4  // VECTOR_SYNC_EL1_SP_EL1
    ventry handler_vector_5  // VECTOR_IRQ_EL1_SP_EL1
    ventry handler_vector_6  // VECTOR_FIQ_EL1_SP_EL1
    ventry handler_vector_7  // VECTOR_SERR_EL1_SP_EL1

    ventry handler_vector_8  // VECTOR_SYNC_EL0_AARCH64
    ventry handler_vector_9  // VECTOR_IRQ_EL0_AARCH64
    ventry handler_vector_10 // VECTOR_FIQ_EL0_AARCH64
    ventry handler_vector_11 // VECTOR_SERR_EL0_AARCH64

    ventry handler_vector_12 // VECTOR_SYNC_EL0_AARCH32
    ventry handler_vector_13 // VECTOR_IRQ_EL0_AARCH32
    ventry handler_vector_14 // VECTOR_FIQ_EL0_AARCH32
    ventry handler_vector_15 // VECTOR_SERR_EL0_AARCH32

// Handlers for exception vectors
handler_vector_0:
    handle_invalid_entry VECTOR_INVALID_SYN_EL1_SP_EL0

handler_vector_1:
    handle_invalid_entry VECTOR_INVALID_IRQ_EL1_SP_EL0

handler_vector_2:
    handle_invalid_entry VECTOR_INVALID_FIQ_EL1_SP_EL0

handler_vector_3:
    handle_invalid_entry VECTOR_INVALID_SER_EL1_SP_EL0

handler_vector_4:
    handle_invalid_entry VECTOR_INVALID_SYN_EL1_SP_EL1

handler_vector_5:
    kernel_exception_enter
    bl handle_irq
    kernel_exception_exit

handler_vector_6:
    handle_invalid_entry VECTOR_INVALID_FIQ_EL1_SP_EL1

handler_vector_7:
    handle_invalid_entry VECTOR_INVALID_SER_EL1_SP_EL1

handler_vector_8:
    handle_invalid_entry VECTOR_INVALID_SYN_EL0_AARCH64

handler_vector_9:
    handle_invalid_entry VECTOR_INVALID_IRQ_EL0_AARCH64

handler_vector_10:
    handle_invalid_entry VECTOR_INVALID_FIQ_EL0_AARCH64

handler_vector_11:
    handle_invalid_entry VECTOR_INVALID_SER_EL0_AARCH64

handler_vector_12:
    handle_invalid_entry VECTOR_INVALID_SYN_EL0_AARCH32

handler_vector_13:
    handle_invalid_entry VECTOR_INVALID_IRQ_EL0_AARCH32

handler_vector_14:
    handle_invalid_entry VECTOR_INVALID_FIQ_EL0_AARCH32

handler_vector_15:
    handle_invalid_entry VECTOR_INVALID_SER_EL0_AARCH32