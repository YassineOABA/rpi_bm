/**
 * @file        mm.S
 * @brief       Implementation of memory management functions.
 * @description This file provides the logic for managing memory allocations, handling paging, 
 *              and setting up memory regions on the Raspberry Pi.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





/**
 * @brief Zero Memory Function (memzero)
 * @description
 *   This function sets a block of memory to zero. It repeatedly stores zero 
 *   into the memory addresses starting from the one pointed to by `x0`, 
 *   decrementing the size (`x1`) by 8 bytes each time until `x1` becomes zero.
 *   The function uses `x1` to track the remaining number of bytes to clear.
 * @notes
 *   - The function operates in a loop, clearing 8 bytes at a time (using 64-bit zeroing).
 *   - `x0` must hold the address of the memory to be zeroed.
 *   - `x1` must hold the total number of bytes to clear (multiple of 8 for efficiency).
 * @param x0 (address)
 *   The address of the memory region to be zeroed.
 * @param x1 (size)
 *   The number of bytes to zero, must be a multiple of 8.
 * @return 
 *   This function does not return a value. It clears memory and then returns control to the caller.
 */
.globl memzero          // Make the memzero label globally accessible (visible to the linker).
memzero:                // Define the memzero function label.
    str xzr, [x0], #8   // 1. Store zero (xzr) into memory at the address in x0, then increment x0 by 8 bytes.
    subs x1, x1, #8     // 2. Subtract 8 from x1 (the remaining size to zero), and update flags based on the result.
    b.gt memzero        // 3. If x1 > 0 (still bytes left to clear), branch back to memzero to continue zeroing.
    ret                 // 4. Return from function once all memory has been zeroed.