/**
 * @file        act_led.c
 * @brief       ACT LED control implementation for the Raspberry Pi.
 * @description This source file contains the implementation of functions for controlling
 *              the ACT LED GPIO pin on the Raspberry Pi, including initialization and toggling.
 * 
 * @version     1.0
 * @date        2024-12-16
 */

#include "act_led.h"
#include "gpio.h"

/**
 * @brief Initializes the ACT LED GPIO pin.
 * 
 * This function sets up the ACT LED GPIO pin for output mode. It also configures
 * the pull-down resistor to ensure the pin starts in a known state.
 */
void act_led_init(void)
{
    // Configure the pin as an output.
    gpio_set_pin_function(ACT_LED_GPIO, GPIO_OUTPUT);
    // Set the pin to pull-down mode.
    gpio_pull_up_down(ACT_LED_GPIO, GPIO_PUD_DOWN);
}

/**
 * @brief Toggles the ACT LED state.
 * 
 * This function reads the current state of the ACT LED GPIO pin. If the pin
 * is high (logic level 1), it clears the pin to turn off the LED. If the pin
 * is low (logic level 0), it sets the pin to turn on the LED.
 */
void act_led_toggle(void)
{
    uint8_t act_pin_val;

    // Read the current state of the pin.
    act_pin_val = gpio_read_pin(ACT_LED_GPIO);
    
    if (act_pin_val == 1)
    {
        // Turn off the LED if it is currently on.
        gpio_clear_pin(ACT_LED_GPIO);
    }
    else
    {
        // Turn on the LED if it is currently off.
        gpio_set_pin(ACT_LED_GPIO);
    }
}
