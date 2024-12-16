/**
 * @file        mm.h
 * @brief       Memory management interface.
 * @description This header defines structures and functions for managing memory allocations 
 *              and paging on the Raspberry Pi.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#ifndef _MM_H_
#define _MM_H_

#define PAGE_SHIFT      12                          // 4KB pages
#define TABLE_SHIFT     10                          // Typically 10 for 64-bit ARMv8-A (could be 9 for 32-bit mode)
#define SECTION_SHIFT   (PAGE_SHIFT + TABLE_SHIFT)  // 12 + 10 = 22 for larger sections (or 21 for 2MB)

#define PAGE_SIZE       (1 << PAGE_SHIFT)           // 4KB
#define SECTION_SIZE    (1 << SECTION_SHIFT)        // 2MB or larger sections (may be 2MB or 16MB depending on configuration)

#define LOW_MEMORY      (2 * SECTION_SIZE)          // Typically 4MB for 2MB sections

#ifndef __ASSEMBLER__

#include <stdint.h>


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
extern void memzero(uint64_t src,  uint32_t n);

#endif

#endif /* _MM_H_ */