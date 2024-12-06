/**
 * @file        gpio.h
 * @brief       GPIO control interface for the Raspberry Pi.
 * @description This header contains declarations and macros for configuring and controlling 
 *              the GPIO pins on the Raspberry Pi.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>
#include "base.h"

// GPIO Base address (BCM2835)
#define GPIO_BASE    (PIBASE + 0x00200000)

// GPIO Register Structure for BCM2835
// This structure defines the memory-mapped GPIO registers for the BCM2835 SoC.
// Each field in this structure corresponds to a specific register used to control and configure the GPIO pins.
// The fields in the structure represent different functionalities, including pin function select,
// pin output set/clear, and pull-up/pull-down configuration for the GPIO pins.
struct GPIO_Registers {
    volatile uint32_t GPFSEL[6];    // 0x20200000 - 0x20200014: GPIO Function Select (GPFSEL0 to GPFSEL5)
    volatile uint32_t reserved1;    // Reserved (0x20200018 - 0x2020001C)

    volatile uint32_t GPSET[2];     // 0x2020001C - 0x20200020: GPIO Pin Output Set (GPSET0, GPSET1)
    volatile uint32_t reserved2;    // Reserved (0x20200024 - 0x20200028)

    volatile uint32_t GPCLR[2];     // 0x20200028 - 0x2020002C: GPIO Pin Output Clear (GPCLR0, GPCLR1)
    volatile uint32_t reserved3;    // Reserved (0x20200030 - 0x20200034)

    volatile uint32_t GPLEV[2];     // 0x20200034 - 0x20200038: GPIO Pin Level (GPLEV0, GPLEV1)
    volatile uint32_t reserved4;    // Reserved (0x2020003C - 0x20200040)

    volatile uint32_t GPEDS[2];     // 0x20200040 - 0x20200044: GPIO Pin Event Detect Status (GPEDS0, GPEDS1)
    volatile uint32_t reserved5;    // Reserved (0x20200048 - 0x2020004C)

    volatile uint32_t GPREN[2];     // 0x2020004C - 0x20200050: GPIO Pin Rising Edge Detect Enable (GPREN0, GPREN1)
    volatile uint32_t reserved6;    // Reserved (0x20200054 - 0x20200058)

    volatile uint32_t GPFEN[2];     // 0x20200058 - 0x2020005C: GPIO Pin Falling Edge Detect Enable (GPFEN0, GPFEN1)
    volatile uint32_t reserved7;    // Reserved (0x20200060 - 0x20200064)

    volatile uint32_t GPHEN[2];     // 0x20200064 - 0x20200068: GPIO Pin High Detect Enable (GPHEN0, GPHEN1)
    volatile uint32_t reserved8;    // Reserved (0x2020006C - 0x20200070)

    volatile uint32_t GPLEN[2];     // 0x2020006C - 0x20200070: GPIO Pin Low Detect Enable (GPLEN0, GPLEN1)
    volatile uint32_t reserved9;    // Reserved (0x20200074 - 0x20200078)

    volatile uint32_t GPAREN[2];    // 0x20200074 - 0x20200078: GPIO Pin Async Rising Edge Detect Enable (GPAREN0, GPAREN1)
    volatile uint32_t reserved10;   // Reserved (0x2020007C - 0x20200080)

    volatile uint32_t GPAFEN[2];    // 0x2020007C - 0x20200080: GPIO Pin Async Falling Edge Detect Enable (GPAFEN0, GPAFEN1)
    volatile uint32_t reserved11;   // Reserved (0x20200084 - 0x20200088)

    volatile uint32_t GPPUD;        // 0x20200094: GPIO Pin Pull-up/down Enable

    volatile uint32_t GPPUDCLK[2];  // 0x20200098 - 0x2020009C: GPIO Pull-up/down Enable Clock (GPPUDCLK0, GPPUDCLK1)
    volatile uint32_t reserved12;   // Reserved (0x202000A0 - 0x202000B4)

    volatile uint32_t TEST;         // 0x202000B0: GPIO Test Register (TEST)
};

// Define GPIO as a pointer to a structure representing the GPIO hardware registers.
// This macro allows easy access to the GPIO registers by dereferencing the pointer.
// GPIO_BASE should be defined elsewhere as the base address of the GPIO peripheral.
#define GPIO ((struct GPIO_Registers *)(GPIO_BASE))

// GPIO Pin Modes in Binary Representation
#define GPIO_INPUT   0b000  // Input: 000 (3-bit binary)
#define GPIO_OUTPUT  0b001  // Output: 001 (3-bit binary)
#define GPIO_ALT0    0b100  // Alternate Function 0: 100 (3-bit binary)
#define GPIO_ALT1    0b101  // Alternate Function 1: 101 (3-bit binary)
#define GPIO_ALT2    0b110  // Alternate Function 2: 110 (3-bit binary)
#define GPIO_ALT3    0b111  // Alternate Function 3: 111 (3-bit binary)
#define GPIO_ALT4    0b011  // Alternate Function 4: 011 (3-bit binary)
#define GPIO_ALT5    0b010  // Alternate Function 5: 010 (3-bit binary)

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

// GPIO Pull-up/Pull-down Modes in Binary Representation
#define GPIO_PUD_OFF   0b00  // No pull-up/down: 00 (2-bit binary) - The pin is not connected to a pull-up or pull-down resistor.
#define GPIO_PUD_DOWN  0b01  // Pull-down: 01 (2-bit binary) - The pin is connected to a pull-down resistor, keeping it low when not driven.
#define GPIO_PUD_UP    0b10  // Pull-up: 10 (2-bit binary) - The pin is connected to a pull-up resistor, keeping it high when not driven.

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
extern void gpio_set_pin_function(uint8_t pin, uint8_t function); 

/**
 * @brief Sets a GPIO pin to a high state (logic level 1).
 * 
 * This function sets a specific GPIO pin to a high state, driving the
 * pin to a logic level of 1 (3.3V on the Raspberry Pi).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 */
extern void gpio_set_pin(uint8_t pin); 

/**
 * @brief Clears a GPIO pin to a low state (logic level 0).
 * 
 * This function sets a specific GPIO pin to a low state, driving the
 * pin to a logic level of 0 (0V).
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 */
extern void gpio_clear_pin(uint8_t pin); 

/**
 * @brief Reads the state of a GPIO pin.
 * 
 * This function reads the current state (high or low) of a specified GPIO pin.
 * 
 * @param pin     The GPIO pin number (e.g., 0 to 53 on Raspberry Pi).
 * 
 * @return        The current state of the pin (1 for high, 0 for low).
 */
extern uint8_t gpio_read_pin(uint8_t pin); 

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
extern void gpio_pull_up_down(uint8_t pin, uint8_t pud); 

#endif /* _GPIO_H_ */
