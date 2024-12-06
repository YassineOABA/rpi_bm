/**
 * @file        utils.S
 * @brief       Low-level utility functions.
 * @description This assembly file contains low-level utility routines such as delay loops and 
 *              processor-specific instructions.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





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
.globl delay
delay:
    subs x0, x0, #1     // 1. Subtract 1 from x0, setting flags
    bne delay           // 2. If x0 is not zero (result of subtraction), branch to 'delay'
    ret                 // 3. Return when x0 reaches zero

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
.globl put32
put32:
    str w1, [x0]        // 1. Store the value of w1 into the address pointed by x0
    ret                 // 2. Return from function

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
.globl get32
get32:
    ldr w0, [x0]        // 1. Load a 32-bit value from the address pointed to by x0 into w0
    ret                 // 2. Return from function

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
.globl get_el    
get_el:
    mrs x0, CurrentEL        // Move the value of the CurrentEL system register into x0
                             // CurrentEL is a 4-bit register where the top 2 bits represent the EL
    lsr x0, x0, #2           // Logical Shift Right by 2 bits to isolate the EL value
                             // After shifting:
                             // - EL3: 0b11 (3)
                             // - EL2: 0b10 (2)
                             // - EL1: 0b01 (1)
                             // - EL0: 0b00 (0)
    ret                      // Return to the caller, with the EL value in x0