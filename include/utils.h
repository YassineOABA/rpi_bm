/**
 * @file        utils.h
 * @brief       Utility functions and macros.
 * @description This header contains generic utility functions and inline assembly snippets 
 *              for performing low-level operations.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>



/**
 * @brief Delays the execution for a specified number of ticks.
 * 
 * This function causes the program to wait for a certain amount of time, determined by the
 * `tick` parameter. The function is typically used for generating delays in bare-metal systems
 * where no OS timer or scheduler is available. The delay is not accurate in terms of time units,
 * but is based on the number of "ticks" (which could be any arbitrary unit of time).
 * 
 * @param tick The number of ticks to wait before returning. Higher values result in longer delays.
 */
extern void delay(uint64_t tick);


/**
 * @brief Writes a 32-bit value to a specified memory address.
 * 
 * This function writes a 32-bit value (`val`) to a memory address (`addr`). It is commonly
 * used for interacting with hardware peripherals by writing to specific registers at defined
 * memory addresses. It can also be used for general memory manipulation in bare-metal systems.
 * 
 * @param addr The memory address where the value will be written.
 * @param val The 32-bit value to write to the specified address.
 */
extern void put32(uint64_t addr, uint32_t val);


/**
 * @brief Reads a 32-bit value from a specified memory address.
 * 
 * This function reads a 32-bit value from the specified memory address (`addr`). It is commonly
 * used for reading the state of hardware registers in bare-metal systems. The function returns
 * the value stored at the given address.
 * 
 * @param addr The memory address from which to read the 32-bit value.
 * 
 * @return The 32-bit value stored at the specified memory address.
 */
extern uint32_t get32(uint64_t addr);

/**
 * @brief Retrieves the current Exception Level (EL) of the processor.
 * 
 * This function reads the `CurrentEL` system register, which contains the 
 * processor's current Exception Level. It isolates the Exception Level by 
 * shifting the register value 2 bits to the right.
 * 
 * ## Register Format:
 * The `CurrentEL` system register is a 32-bit register where:
 * - Bits [31:4]: Reserved (0)
 * - Bits [3:2]: Current Exception Level (EL) (e.g., 0b00 = EL0, 0b01 = EL1)
 * - Bits [1:0]: Reserved (0)
 * 
 * Example Values:
 * - `0b00000000_00000000_00000000_00000000_00000000_00000000_00001100` (EL3)
 * - `0b00000000_00000000_00000000_00000000_00000000_00000000_00001000` (EL2)
 * - `0b00000000_00000000_00000000_00000000_00000000_00000000_00000100` (EL1)
 * - `0b00000000_00000000_00000000_00000000_00000000_00000000_00000000` (EL0)
 * 
 * ## Operation:
 * 1. Read the `CurrentEL` register.
 * 2. Shift the 4-bit value right by 2 bits to isolate the EL field.
 * 3. Return the isolated value (0, 1, 2, or 3).
 * 
 * ## Return Value:
 * - x0: The current Exception Level (0 = EL0, 1 = EL1, 2 = EL2, 3 = EL3).
 */
extern uint8_t get_el(void);

/**
 * @brief Retrieves the current Stack Pointer (SP) value.
 * 
 * This function reads the `SPSel` system register, which indicates the current
 * stack pointer selection, and returns the value of the stack pointer (SP).
 * 
 * ## Operation:
 * 1. Read the `SPSel` register into the x0 register.
 * 2. Return the value in the x0 register, which holds the current stack pointer.
 * 
 * ## Return Value:
 * - x0: The current Stack Pointer (SP) value.
 */
extern uint8_t get_sp(void);

#endif /* _UTILS_H_ */