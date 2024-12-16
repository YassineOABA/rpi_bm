/**
 * @file        irq.c
 * @brief       Exception handling and interrupt management for ARMv8-A at EL1.
 * @description This file implements exception handling and interrupt management for the 
 *              ARMv8-A architecture. It includes invalid entry message handling, interrupt 
 *              controller configuration, and auxiliary IRQ processing.
 * 
 * @version     1.0
 * @date        2024-12-15
 */

#include "common.h"
#include "gpio.h"
#include "mini_uart.h"
#include "uart_printf.h"
#include "entry.h"
#include "irq.h"
#include "aux.h"
#include "timer.h"

/**
 * @brief       Array of error messages for invalid exception entries.
 * @description This array maps exception types to corresponding error messages
 *              to help debug invalid vector entries at EL1 or EL0.
 */
const char entry_error_message[16][32] = 
{
    "VECTOR_INVALID_SYN_EL1_SP_EL0",    // Invalid synchronous exception from EL1, SP_EL0
    "VECTOR_INVALID_IRQ_EL1_SP_EL0",    // Invalid IRQ from EL1, SP_EL0
    "VECTOR_INVALID_FIQ_EL1_SP_EL0",    // Invalid FIQ from EL1, SP_EL0
    "VECTOR_INVALID_SER_EL1_SP_EL0",    // Invalid SError from EL1, SP_EL0
    "VECTOR_INVALID_SYN_EL1_SP_EL1",    // Invalid synchronous exception from EL1, SP_EL1
    "VECTOR_INVALID_IRQ_EL1_SP_EL1",    // Invalid IRQ from EL1, SP_EL1
    "VECTOR_INVALID_FIQ_EL1_SP_EL1",    // Invalid FIQ from EL1, SP_EL1
    "VECTOR_INVALID_SER_EL1_SP_EL1",    // Invalid SError from EL1, SP_EL1
    "VECTOR_INVALID_SYN_EL0_AARCH64",   // Invalid synchronous exception from EL0, AArch64
    "VECTOR_INVALID_IRQ_EL0_AARCH64",   // Invalid IRQ from EL0, AArch64
    "VECTOR_INVALID_FIQ_EL0_AARCH64",   // Invalid FIQ from EL0, AArch64
    "VECTOR_INVALID_SER_EL0_AARCH64",   // Invalid SError from EL0, AArch64
    "VECTOR_INVALID_SYN_EL0_AARCH32",   // Invalid synchronous exception from EL0, AArch32
    "VECTOR_INVALID_IRQ_EL0_AARCH32",   // Invalid IRQ from EL0, AArch32
    "VECTOR_INVALID_FIQ_EL0_AARCH32",   // Invalid FIQ from EL0, AArch32
    "VECTOR_INVALID_SER_EL0_AARCH32"    // Invalid SError from EL0, AArch32
};

/**
 * @brief       Show an invalid entry message.
 * @description Prints a detailed error message when an invalid exception vector
 *              entry is accessed.
 * 
 * @param type      The type of invalid exception (index in entry_error_message array).
 * @param esr       The Exception Syndrome Register (ESR) value.
 * @param address   The address at which the exception occurred.
 */
void show_invalid_entry_message(uint32_t type, uint64_t esr, uint64_t address) 
{
    uart_printf(
        "ERROR CAUGHT: %s - %d, ESR: %X, Address: %X\n", 
        entry_error_message[type],   // Corresponding error message
        type,                        // Error type (index)
        esr,                         // Exception Syndrome Register value
        address                      // Address where the exception occurred
    );
}

/**
 * @brief       Enable the interrupt controller for auxiliary devices.
 * @description This function configures the interrupt controller to enable
 *              interrupts for auxiliary devices, such as Mini UART.
 */
void enable_interrupt_controller(void) 
{
    // Enable IRQs
    IRQ_REG->EnableIRQs1 = AUX_IRQ | TIMER_1_IRQ | TIMER_3_IRQ;
}

/**
 * @brief       Handle pending IRQs.
 * @description This function processes pending interrupts and handles auxiliary
 *              device IRQs, such as UART data reception, as well as timer interrupts.
 */
void handle_irq(void) 
{
    uint32_t irq;

    // Read pending IRQs from the interrupt register
    irq = IRQ_REG->IRQPending1;

    // Process all pending IRQs
    while (irq)
    {
        // Check if the IRQ is from the auxiliary device (e.g., UART)
        if (irq & AUX_IRQ)
        {
            // Clear the AUX_IRQ flag to acknowledge the interrupt
            irq &= ~AUX_IRQ;

            // Handle UART data while it is available
            while ((AUX->MU_IIR_REG & 4) == 4) 
            {
                // Log received UART data
                uart_printf("UART Recv: ");   
                // Echo the received data back
                uart_send(uart_recv());       
                // Send a newline for clarity
                uart_printf("\t\n");          
            }
        }

        // Check if the interrupt is from Timer 1
        if (irq & TIMER_1_IRQ)
        {
            // Clear the TIMER_1_IRQ flag to acknowledge the interrupt
            irq &= ~TIMER_1_IRQ;

            // Call the timer handler for Timer 1
            handle_timer(TIMER_1);
        }

        // Check if the interrupt is from Timer 3
        if (irq & TIMER_3_IRQ)
        {
            // Clear the TIMER_3_IRQ flag to acknowledge the interrupt
            irq &= ~TIMER_3_IRQ;

            // Call the timer handler for Timer 3
            handle_timer(TIMER_3);
        }
    }
}

