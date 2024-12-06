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

#endif /* _UTILS_H_ */