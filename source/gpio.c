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
    // Set all GPIO pins to input by setting the Function Select registers to 0 (input mode)
    *GPIO_FSEL0 = 0x00000000;
    *GPIO_FSEL1 = 0x00000000;
    *GPIO_FSEL2 = 0x00000000;
    *GPIO_FSEL3 = 0x00000000;
    *GPIO_FSEL4 = 0x00000000;
    *GPIO_FSEL5 = 0x00000000;
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
void gpio_set_pin_function(uint32_t pin, uint32_t function)
{
    uint32_t reg_index = pin / 10;        // Each register controls 10 GPIO pins
    uint32_t shift = (pin % 10) * 3;      // Each pin is 3 bits in the register
    volatile uint32_t *fsel_reg = (volatile uint32_t *)(uintptr_t)(GPIO_BASE + (reg_index * 4));

    // Clear the bits for the specified pin and set the new function
    *fsel_reg &= ~(0x7 << shift);         // Clear the 3 bits for this pin
    *fsel_reg |= (function << shift);     // Set the new function
}

/**
 * @brief Sets a GPIO pin to a high state (logic level 1).
 * 
 * This function sets a specific GPIO pin to a high state, driving the
 * pin to a logic level of 1 (3.3V on the Raspberry Pi).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 */
void gpio_set_pin(uint32_t pin)
{
    // Set the corresponding bit in the GPIO_SET0 register to set the pin high
    if (pin < 32)
    {
        *GPIO_SET0 = (1 << pin);
    }
    else
    {
        *GPIO_SET1 = (1 << (pin - 32));
    }
}

/**
 * @brief Clears a GPIO pin to a low state (logic level 0).
 * 
 * This function sets a specific GPIO pin to a low state, driving the
 * pin to a logic level of 0 (0V).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 */
void gpio_clear_pin(uint32_t pin) {
    // Set the corresponding bit in the GPIO_CLR0 register to clear the pin
    if (pin < 32)
    {
        *GPIO_CLR0 = (1 << pin);
    }
    else
    {
        *GPIO_CLR1 = (1 << (pin - 32));
    }
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
uint32_t gpio_read_pin(uint32_t pin) 
{
    // Read the state from the GPIO_LEV0 or GPIO_LEV1 register based on the pin number
    if (pin < 32) 
    {
        return (*GPIO_LEV0 & (1 << pin)) ? 1 : 0;
    } 
    else
    {
        return (*GPIO_LEV1 & (1 << (pin - 32))) ? 1 : 0;
    }
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
void gpio_pull_up_down(uint32_t pin, uint32_t pud)
{
    // Step 1: Write to GPPUD to set the required control signal
    // pud: 0 = none (disable pull-up/down), 1 = pull-down, 2 = pull-up
    *GPIO_PUD = pud;

    // Step 2: Wait for 150 cycles (set-up time)
    delay(150);

    // Step 3: Write to GPPUDCLK0/1 to clock the control signal into the GPIO pad(s)
    // The clock is only applied to the specified pin
    if (pin < 32)
    {
        *GPIO_PUDCLK0 = (1 << pin); // Apply to GPIO0-GPIO31
    } else
    {
        *GPIO_PUDCLK1 = (1 << (pin - 32)); // Apply to GPIO32-GPIO53
    }

    // Step 4: Wait for 150 cycles (hold time)
    delay(150);

    // Step 5: Write to GPPUD to remove the control signal
    *(volatile uint32_t *)GPIO_PUD = 0;

    // Step 6: Write to GPPUDCLK0/1 to remove the clock
    if (pin < 32)
    {
        *GPIO_PUDCLK0 = 0;
    }
    else
    {
        *GPIO_PUDCLK1 = 0;
    }
}

