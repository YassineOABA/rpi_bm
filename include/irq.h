/**
 * @file        irq.h
 * @brief       IRQ management and interrupt controller interface.
 * @description This header file defines structures and functions for handling
 *              interrupts in an ARMv8-A system. It includes register mappings
 *              for the interrupt controller, as well as declarations for 
 *              initialization and control routines.
 * 
 * @version     1.0
 * @date        2024-12-15
 */

#ifndef _IRQ_H_
#define _IRQ_H_

#include <stdint.h>
#include "base.h"

// Base address for the ARM interrupt registers.
#define IRQ_BASE_ADDR   (PIBASE + 0xB200)

#define BIT_0(x)                    (0 << x)  // Set bit to 0 at position x
#define BIT_1(x)                    (1 << x)  // Set bit to 1 at position x

/**
 * @brief Structure representing the ARM interrupt registers.
 */
struct IRQ_Registers{
    volatile uint32_t IRQBasicPending;      // 0x200: IRQ Basic Pending Register
    volatile uint32_t IRQPending1;          // 0x204: IRQ Pending 1 Register
    volatile uint32_t IRQPending2;          // 0x208: IRQ Pending 2 Register
    volatile uint32_t FIQControl;           // 0x20C: FIQ Control Register
    volatile uint32_t EnableIRQs1;          // 0x210: Enable IRQs 1 Register
    volatile uint32_t EnableIRQs2;          // 0x214: Enable IRQs 2 Register
    volatile uint32_t EnableBasicIRQs;      // 0x218: Enable Basic IRQs Register
    volatile uint32_t DisableIRQs1;         // 0x21C: Disable IRQs 1 Register
    volatile uint32_t DisableIRQs2;         // 0x220: Disable IRQs 2 Register
    volatile uint32_t DisableBasicIRQs;     // 0x224: Disable Basic IRQs Register
};

// Pointer to the IRQ registers
#define IRQ_REG         ((struct IRQ_Registers *)(IRQ_BASE_ADDR))

// Bit 0 correponds to System Timer 0
#define TIMER_0_IRQ     BIT_1(0)

// Bit 1 correponds to System Timer 1
#define TIMER_1_IRQ     BIT_1(1)

// Bit 2 correponds to System Timer 2
#define TIMER_2_IRQ     BIT_1(2)

// Bit 3 correponds to System Timer 3
#define TIMER_3_IRQ     BIT_1(3)

// Bit 29 corresponds to AUX IRQ
#define AUX_IRQ         BIT_1(29)

/**
 * @brief       Initialize the IRQ vector table.
 * @description Sets the Vector Base Address Register (VBAR_EL1) to point to 
 *              the exception vector table.
 * 
 * @note        Ensure the vector_table symbol points to the correct memory location.
 */
extern void irq_init(void);

/**
 * @brief       Enable IRQs at EL1.
 * @description Clears the IRQ disable bit in the DAIF (Interrupt Mask Bits) register,
 *              allowing interrupts to be serviced.
 */
extern void irq_enable(void);

/**
 * @brief       Disable IRQs at EL1.
 * @description Sets the IRQ disable bit in the DAIF (Interrupt Mask Bits) register,
 *              preventing interrupts from being serviced.
 */
extern void irq_disable(void);

/**
 * @brief       Show an invalid entry message.
 * @description Prints a detailed error message when an invalid exception vector
 *              entry is accessed.
 * 
 * @param type      The type of invalid exception (index in entry_error_message array).
 * @param esr       The Exception Syndrome Register (ESR) value.
 * @param address   The address at which the exception occurred.
 */
extern void show_invalid_entry_message(uint32_t type, uint64_t esr, uint64_t address);

/**
 * @brief       Enable the interrupt controller for auxiliary devices.
 * @description This function configures the interrupt controller to enable
 *              interrupts for auxiliary devices, such as Mini UART.
 */
extern void enable_interrupt_controller(void);

/**
 * @brief       Handle pending IRQs.
 * @description This function processes pending interrupts and handles auxiliary
 *              device IRQs, such as UART data reception.
 */
extern void handle_irq(void);

#endif /* _IRQ_H_ */
