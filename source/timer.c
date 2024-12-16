/**
 * @file        timer.c
 * @brief       Timer driver implementation for Raspberry Pi.
 * @description This file provides the implementation for configuring and managing 
 *              the system timers on a Raspberry Pi. It includes functions for 
 *              initializing timers, handling timer interrupts, and configuring 
 *              timer-specific behavior.
 * 
 * @version     1.0
 * @date        2024-12-16
 */


#include "timer.h"
#include "mini_uart.h"
#include "uart_printf.h"
#include "irq.h"
#include "act_led.h"

static uint32_t timer_get_lower(void);
static uint32_t timer_get_higher(void);
static void timer_set_compare(uint8_t compare_idx, uint32_t value);
static void timer_clear_interrupt(uint8_t timer_idx);

/**
 * @brief Retrieves the lower 32 bits of the system timer counter.
 * @description This function reads and returns the lower 32 bits of the system timer's 64-bit counter value. It is used to track the current time or elapsed time.
 * 
 * @return The lower 32 bits of the system timer's counter.
 */
static uint32_t timer_get_lower(void)
{
    return TIMER->LO;
}


/**
 * @brief Retrieves the higher 32 bits of the system timer counter.
 * @description This function reads and returns the higher 32 bits of the system timer's 64-bit counter value. It is used in conjunction with the lower 32 bits to get the full 64-bit timer value.
 * 
 * @return The higher 32 bits of the system timer's counter.
 */
static uint32_t timer_get_higher(void)
{
    return TIMER->HI;
}

/**
 * @brief Sets the specified system timer compare value.
 * @description This function sets a comparison value for the specified timer compare register. The timer will trigger an interrupt or perform other actions when the counter matches this value.
 * 
 * @param compare_idx The index of the compare register to modify (e.g., TIMER_COMPARE_0, TIMER_COMPARE_1).
 * @param value The value to set in the compare register.
 */
static void timer_set_compare(uint8_t compare_idx, uint32_t value)
{
    TIMER->CMPR[compare_idx] = value;
}

/**
 * @brief Clears the interrupt flag for the specified timer.
 * @description This function clears the interrupt flag for the specified timer. It is typically called after handling the timer interrupt to reset the interrupt condition.
 * 
 * @param timer_idx The index of the timer whose interrupt flag is being cleared (e.g., TIMER_1, TIMER_3).
 */
static void timer_clear_interrupt(uint8_t timer_idx)
{
    TIMER->CS |= 1 << timer_idx;
}

/**
 * @brief       Get the current timer value (ticks).
 * @description This function reads the lower and higher 32 bits of the system timer 
 *              to return a 64-bit value representing the current timer ticks.
 * 
 * @return      A 64-bit value representing the current timer ticks.
 */
uint64_t timer_get_ticks(void) 
{
    uint32_t hi = timer_get_higher();  // Get the higher 32 bits of the timer
    uint32_t lo = timer_get_lower();   // Get the lower 32 bits of the timer

    // Double check if the high value has changed after reading it
    if (hi != timer_get_higher())      // If the high part has changed since it was first read
    {
        hi = timer_get_higher();       // Re-read the higher 32 bits
        lo = timer_get_lower();        // Re-read the lower 32 bits as well
    }

    return ((uint64_t) (hi) << 32) | lo ;  // Combine high and low parts into a 64-bit value and return
}

/**
 * @brief Initializes the specified system timer.
 * @description This function configures the specified system timer based on the timer index. It prepares the timer for use by setting up necessary control registers and interrupt settings.
 * 
 * @param timer_idx The index of the timer to initialize (e.g., TIMER_1, TIMER_3).
 */
void timer_init(uint8_t timer_idx)
{
    uint32_t current_val;

    if(TIMER_1 == timer_idx)
    {
        current_val = timer_get_lower() + ARM_CLOCK_FREQUENCY_HZ;
        timer_set_compare(timer_idx,current_val);
        act_led_toggle();
    }

    if(TIMER_3 == timer_idx)
    {
        // not used now
    }
}

/**
 * @brief Handles the specified timer interrupt.
 * @description This function processes the interrupt for the specified timer. It clears the interrupt flag and performs any necessary actions, such as resetting the timer or executing related tasks.
 * 
 * @param timer_idx The index of the timer whose interrupt is being handled (e.g., TIMER_1, TIMER_3).
 */
void handle_timer(uint8_t timer_idx)
{
    timer_init(timer_idx);
    timer_clear_interrupt(timer_idx);
}