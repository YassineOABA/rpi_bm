#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>
#include "base.h"

// GPIO Base address (BCM2835)
#define GPIO_BASE    (PIBASE + 0x200000)

// GPIO Registers with volatile pointers
#define GPIO_FSEL0   ((volatile uint32_t *) (GPIO_BASE + 0x00))  // Function Select 0
#define GPIO_FSEL1   ((volatile uint32_t *) (GPIO_BASE + 0x04))  // Function Select 1
#define GPIO_FSEL2   ((volatile uint32_t *) (GPIO_BASE + 0x08))  // Function Select 2
#define GPIO_FSEL3   ((volatile uint32_t *) (GPIO_BASE + 0x0C))  // Function Select 3
#define GPIO_FSEL4   ((volatile uint32_t *) (GPIO_BASE + 0x10))  // Function Select 4
#define GPIO_FSEL5   ((volatile uint32_t *) (GPIO_BASE + 0x14))  // Function Select 5

#define GPIO_SET0    ((volatile uint32_t *) (GPIO_BASE + 0x1C))  // GPIO Pin Output Set 0
#define GPIO_SET1    ((volatile uint32_t *) (GPIO_BASE + 0x20))  // GPIO Pin Output Set 1

#define GPIO_CLR0    ((volatile uint32_t *) (GPIO_BASE + 0x28))  // GPIO Pin Output Clear 0
#define GPIO_CLR1    ((volatile uint32_t *) (GPIO_BASE + 0x2C))  // GPIO Pin Output Clear 1

#define GPIO_LEV0    ((volatile uint32_t *) (GPIO_BASE + 0x34))  // GPIO Pin Level 0 (Read state of GPIO pins)
#define GPIO_LEV1    ((volatile uint32_t *) (GPIO_BASE + 0x38))  // GPIO Pin Level 1

#define GPIO_PUD     ((volatile uint32_t *) (GPIO_BASE + 0x94))  // GPIO Pull-up/down control
#define GPIO_PUDCLK0 ((volatile uint32_t *) (GPIO_BASE + 0x98))  // GPIO Pull-up/down Clock 0
#define GPIO_PUDCLK1 ((volatile uint32_t *) (GPIO_BASE + 0x9C))  // GPIO Pull-up/down Clock 1

// GPIO Pin Modes
#define GPIO_INPUT   0b000  // Input
#define GPIO_OUTPUT  0b001  // Output
#define GPIO_ALT0    0b100  // Alternate Function 0
#define GPIO_ALT1    0b101  // Alternate Function 1
#define GPIO_ALT2    0b110  // Alternate Function 2
#define GPIO_ALT3    0b111  // Alternate Function 3
#define GPIO_ALT4    0b011  // Alternate Function 4
#define GPIO_ALT5    0b010  // Alternate Function 5

// GPIO Pin numbers (BCM pin numbers)
#define GPIO_PIN_0   (1 << 0)
#define GPIO_PIN_1   (1 << 1)
#define GPIO_PIN_2   (1 << 2)
#define GPIO_PIN_3   (1 << 3)
#define GPIO_PIN_4   (1 << 4)
#define GPIO_PIN_5   (1 << 5)
#define GPIO_PIN_6   (1 << 6)
#define GPIO_PIN_7   (1 << 7)
#define GPIO_PIN_8   (1 << 8)
#define GPIO_PIN_9   (1 << 9)
#define GPIO_PIN_10  (1 << 10)
#define GPIO_PIN_11  (1 << 11)
#define GPIO_PIN_12  (1 << 12)
#define GPIO_PIN_13  (1 << 13)
#define GPIO_PIN_14  (1 << 14)
#define GPIO_PIN_15  (1 << 15)
#define GPIO_PIN_16  (1 << 16)
#define GPIO_PIN_17  (1 << 17)
#define GPIO_PIN_18  (1 << 18)
#define GPIO_PIN_19  (1 << 19)
#define GPIO_PIN_20  (1 << 20)
#define GPIO_PIN_21  (1 << 21)
#define GPIO_PIN_22  (1 << 22)
#define GPIO_PIN_23  (1 << 23)
#define GPIO_PIN_24  (1 << 24)
#define GPIO_PIN_25  (1 << 25)
#define GPIO_PIN_26  (1 << 26)
#define GPIO_PIN_27  (1 << 27)

// GPIO Pull-up/down values
#define GPIO_PUD_OFF   0b00  // No pull-up/down
#define GPIO_PUD_DOWN  0b01  // Pull-down
#define GPIO_PUD_UP    0b10  // Pull-up

// GPIO Functions
/**
 * @brief Initializes the GPIO peripheral.
 * 
 * This function initializes the General Purpose Input/Output (GPIO) system
 * on the platform, setting up any necessary configurations for GPIO control.
 * It should be called before any other GPIO functions to ensure proper 
 * initialization.
 */
extern void gpio_init(void); 

/**
 * @brief Sets the function of a specific GPIO pin.
 * 
 * This function allows you to configure a specific GPIO pin to one of its
 * available functions (e.g., input, output, alternate functions).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 * @param function The function to set the pin to (e.g., input, output, etc.).
 */
extern void gpio_set_pin_function(uint32_t pin, uint32_t function); 

/**
 * @brief Sets a GPIO pin to a high state (logic level 1).
 * 
 * This function sets a specific GPIO pin to a high state, driving the
 * pin to a logic level of 1 (3.3V on the Raspberry Pi).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 */
extern void gpio_set_pin(uint32_t pin); 

/**
 * @brief Clears a GPIO pin to a low state (logic level 0).
 * 
 * This function sets a specific GPIO pin to a low state, driving the
 * pin to a logic level of 0 (0V).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 */
extern void gpio_clear_pin(uint32_t pin); 

/**
 * @brief Reads the state of a GPIO pin.
 * 
 * This function reads the current state (high or low) of a specified GPIO pin.
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 * 
 * @return        The current state of the pin (1 for high, 0 for low).
 */
extern uint32_t gpio_read_pin(uint32_t pin); 

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
extern void gpio_pull_up_down(uint32_t pin, uint32_t pud); 

#endif /* _GPIO_H_ */
