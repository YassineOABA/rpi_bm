/**
 * @file        act_led.h
 * @brief       ACT LED control interface for the Raspberry Pi.
 * @description This header contains declarations and macros for configuring and controlling 
 *              the ACT LED GPIO pin on the Raspberry Pi.
 * 
 * @version     1.0
 * @date        2024-12-16
 */

#ifndef ACT_LED_H
#define ACT_LED_H

#include <stdint.h>

#define ACT_LED_GPIO  29

/**
 * @brief Initializes the ACT LED GPIO pin.
 * 
 * This function sets up the ACT LED GPIO pin for output mode. It also configures
 * the pull-down resistor to ensure the pin starts in a known state.
 */
extern void act_led_init(void);

/**
 * @brief Toggles the ACT LED state.
 * 
 * This function reads the current state of the ACT LED GPIO pin. If the pin
 * is high (logic level 1), it clears the pin to turn off the LED. If the pin
 * is low (logic level 0), it sets the pin to turn on the LED.
 */
extern void act_led_toggle(void);

#endif // ACT_LED_H
