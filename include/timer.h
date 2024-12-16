/**
 * @file        timer.h
 * @brief       Timer driver interface for Raspberry Pi.
 * @description This file provides the interface definitions for configuring and 
 *              managing the system timers on a Raspberry Pi. It includes macros, 
 *              data structures, and function prototypes used by the timer driver.
 * 
 * @version     1.0
 * @date        2024-12-16
 */


#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include "base.h"

// Macro for setting a bit at position x
#define BIT_0(x)                    (0 << x)  // Set bit to 0 at position x
#define BIT_1(x)                    (1 << x)  // Set bit to 1 at position x

// Base address for the system timers
#define TIMER_BASE_ADDR     (PIBASE + 0x3000)

// 1.2 GHz for the ARM core clock
#define ARM_CLOCK_FREQUENCY_HZ 1200000

// System Timer Register Structure
struct TIMER_Registers {
    volatile uint32_t CS;       // Offset 0x00 - System Timer Control/Status
    volatile uint32_t LO;       // Offset 0x04 - System Timer Counter Lower 32 bits
    volatile uint32_t HI;       // Offset 0x08 - System Timer Counter Higher 32 bits
    volatile uint32_t CMPR[4];  // Offset 0x0C, 0x10, 0x14, 0x18 - System Timer Compare 0,1,2 and 3
};

// Access the system timer registers through the struct
#define TIMER ((struct TIMER_Registers *)(TIMER_BASE_ADDR))

// Timer Control/Status Register (TIMER_CS) bit fields
#define TIMER_CS_RUN          BIT_1(0)  // Timer is running
#define TIMER_CS_INT          BIT_1(1)  // Interrupt status
#define TIMER_CS_ENABLE       BIT_1(2)  // Timer enable
#define TIMER_CS_RESET        BIT_1(3)  // Timer reset

#define TIMER_0     0   // Timer 0 identifier
#define TIMER_1     1   // Timer 1 identifier
#define TIMER_2     2   // Timer 2 identifier
#define TIMER_3     3   // Timer 3 identifier

/**
 * @brief Initializes the specified system timer.
 * @description This function configures the specified system timer based on the timer index. It prepares the timer for use by setting up necessary control registers and interrupt settings.
 * 
 * @param timer_idx The index of the timer to initialize (e.g., TIMER_1, TIMER_3).
 */
extern void timer_init(uint8_t timer_idx);

/**
 * @brief       Get the current timer value (ticks).
 * @description This function reads the lower and higher 32 bits of the system timer 
 *              to return a 64-bit value representing the current timer ticks.
 * 
 * @return      A 64-bit value representing the current timer ticks.
 */
extern uint64_t timer_get_ticks(void) ;

/**
 * @brief Handles the specified timer interrupt.
 * @description This function processes the interrupt for the specified timer. It clears the interrupt flag and performs any necessary actions, such as resetting the timer or executing related tasks.
 * 
 * @param timer_idx The index of the timer whose interrupt is being handled (e.g., TIMER_1, TIMER_3).
 */
extern void handle_timer(uint8_t timer_idx);


#endif /* _TIMER_H_ */
