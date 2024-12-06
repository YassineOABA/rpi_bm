/**
 * @file        gpio.c
 * @brief       Implementation of GPIO control functions.
 * @description This file provides the logic for initializing, configuring, and controlling 
 *              GPIO pins on the Raspberry Pi.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#include "gpio.h"
#include "utils.h"

/**
 * @brief Initializes the GPIO peripheral.
 * 
 * This function initializes the General Purpose Input/Output (GPIO) system
 * on the platform, setting up any necessary configurations for GPIO control.
 * It should be called before any other GPIO functions to ensure proper 
 * initialization.
 */
void gpio_init(void)
{
    uint8_t i;

    // Loop through all GPFSEL registers (6 registers in total).
    // Each GPFSEL register controls 10 GPIO pins (30 bits per register).
    for (i = 0; i < 6; i++)
    {
        // Set all bits in the GPFSEL register to 0.
        // This configures all pins controlled by the register as inputs (default state).
        GPIO->GPFSEL[i] = 0;
    }
}


/**
 * @brief Sets the function of a specific GPIO pin.
 * 
 * This function allows you to configure a specific GPIO pin to one of its
 * available functions (e.g., input, output, alternate functions).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 * @param function The function to set the pin to (e.g., input, output, etc.).
 */
void gpio_set_pin_function(uint8_t pin, uint8_t function)
{
    // Calculate the bit position within the GPFSEL register for the specified pin.
    // Each pin requires 3 bits to specify its function.
    uint8_t bitStart = (pin * 3) % 30;

    // Determine which GPFSEL register controls the specified pin.
    // Each GPFSEL register controls 10 pins (30 bits per register).
    uint8_t reg = pin / 10;

    // Read the current value of the selected GPFSEL register.
    uint32_t selector = GPIO->GPFSEL[reg];

    // Clear the 3 bits corresponding to the specified pin.
    // Use a mask to set the 3 bits to 0 while preserving other bits.
    selector &= ~(7 << bitStart);

    // Set the desired function for the pin by writing the new value to the cleared bits.
    // The `function` parameter specifies the desired mode (e.g., input, output, alternate function).
    selector |= (function << bitStart);

    // Write the updated value back to the GPFSEL register to apply the configuration.
    GPIO->GPFSEL[reg] = selector;
}


/**
 * @brief Sets a GPIO pin to a high state (logic level 1).
 * 
 * This function sets a specific GPIO pin to a high state, driving the
 * pin to a logic level of 1 (3.3V on the Raspberry Pi).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 */
void gpio_set_pin(uint8_t pin)
{
    // Determine which GPSET register to use.
    // Each GPSET register controls up to 32 pins, so the register index is pin / 32.
    // For example:
    // - Pins 0-31 are controlled by GPSET[0].
    // - Pins 32-63 are controlled by GPSET[1], and so on.
    GPIO->GPSET[pin / 32] = (1 << (pin % 32));
}


/**
 * @brief Clears a GPIO pin to a low state (logic level 0).
 * 
 * This function sets a specific GPIO pin to a low state, driving the
 * pin to a logic level of 0 (0V).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 */
void gpio_clear_pin(uint8_t pin)
{
    // Determine which GPCLR register to use.
    // Each GPCLR register controls up to 32 pins, so the register index is pin / 32.
    // For example:
    // - Pins 0-31 are controlled by GPCLR[0].
    // - Pins 32-63 are controlled by GPCLR[1], and so on.
    GPIO->GPCLR[pin / 32] = (1 << (pin % 32));
}


/**
 * @brief Reads the state of a GPIO pin.
 * 
 * This function reads the current state (high or low) of a specified GPIO pin.
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 * 
 * @return        The current state of the pin (1 for high, 0 for low).
 */
uint8_t gpio_read_pin(uint8_t pin) 
{
    // Read the state from the GPIO_LEV0 or GPIO_LEV1 register based on the pin number
    return (GPIO->GPLEV[pin / 32] & (1 << (pin % 32))) ? 1 : 0;
}

/**
 * @brief Configures the pull-up or pull-down resistor for a GPIO pin.
 * 
 * This function configures the internal pull-up or pull-down resistors for
 * a GPIO pin, which can help ensure a stable logic level on the pin when
 * it is set as an input.
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 * @param pud     The pull-up/down mode (e.g., 0 = none, 1 = pull-up, 2 = pull-down).
 */
void gpio_pull_up_down(uint8_t pin, uint8_t pud)
{
    // Set the desired pull-up/down value in the GPPUD register.
    // `pud` should specify the type: 0 (disable), 1 (pull-down), or 2 (pull-up).
    GPIO->GPPUD = pud;

    // Wait 150 cycles for the value to take effect (hardware requirement).
    delay(150);

    // Enable the clock for the pin's pull-up/down configuration.
    // This is done by writing a 1 to the bit corresponding to the pin in the GPPUDCLK register.
    // The pin number is divided by 32 to determine the appropriate clock register (if multiple exist).
    GPIO->GPPUDCLK[pin / 32] = 1 << (pin % 32);

    // Wait another 150 cycles for the configuration to take effect.
    delay(150);

    // Clear the GPPUD register to remove the pull-up/down control signal.
    // This step is necessary to avoid unintended behavior.
    GPIO->GPPUD = 0;

    // Clear the clock register to finish the setup for the pin.
    // This step prevents further changes to the pull-up/down state until explicitly reconfigured.
    GPIO->GPPUDCLK[pin / 32] = 0;
}


