/**
 * @file        irq_asm.S
 * @brief       Assembly routines for IRQ initialization and control.
 * @description This file contains low-level assembly routines to initialize
 *              the vector table, and enable or disable interrupts for ARMv8-A
 *              in EL1.
 * 
 * @version     1.0
 * @date        2024-12-15
 */


/**
 * @brief       Initialize the IRQ vector table.
 * @description Sets the Vector Base Address Register (VBAR_EL1) to point to 
 *              the exception vector table.
 * 
 * @note        Ensure the vector_table symbol points to the correct memory location.
 */
.globl irq_init
irq_init:
    adr x0, vector_table         // Load the address of the vector table into x0
    msr vbar_el1, x0             // Set the Vector Base Address Register
    ret                          // Return to the caller

/**
 * @brief       Enable IRQs at EL1.
 * @description Clears the IRQ disable bit in the DAIF (Interrupt Mask Bits) register,
 *              allowing interrupts to be serviced.
 */
.globl irq_enable
irq_enable:
    msr daifclr, #2              // Clear the IRQ disable bit in DAIF
    ret                          // Return to the caller

/**
 * @brief       Disable IRQs at EL1.
 * @description Sets the IRQ disable bit in the DAIF (Interrupt Mask Bits) register,
 *              preventing interrupts from being serviced.
 */
.globl irq_disable
irq_disable:
    msr daifset, #2              // Set the IRQ disable bit in DAIF
    ret                          // Return to the caller
