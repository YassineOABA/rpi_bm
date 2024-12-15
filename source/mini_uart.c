/**
 * @file        mini_uart.c
 * @brief       Implementation of mini UART functions.
 * @description This file provides the logic for initializing and interacting with the mini UART 
 *              peripheral on the Raspberry Pi.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#include "gpio.h"
#include "aux.h"
#include "mini_uart.h"


/*
  +-------------------------+   
  |  GPIO 14 (TXD)   Pin 8  |
  |  GPIO 15 (RXD)   Pin 10 |
  +-------------------------+
*/


/**
 * @brief Initializes the Mini UART on the Raspberry Pi for serial communication.
 * 
 * This function configures the necessary GPIO pins for UART (TX and RX), sets the
 * appropriate alternate function, configures the UART parameters (such as baud rate),
 * and enables the Mini UART for communication. It also ensures that the UART pins have
 * no pull-up or pull-down resistors enabled. After initialization, the function sends
 * an initial message to the UART terminal to indicate that the kernel initialization has started.
 * 
 * GPIO pins are configured to alternate function 5 (Mini UART) and the UART is set to 8 data bits,
 * no parity, and 1 stop bit, with a baud rate of 115200 (433 for 3.6864 MHz clock).
 * 
 * This function is intended to be called during the early stages of the Raspberry Pi bare metal
 * kernel initialization process.
 * 
 * @note Assumes that the GPIO pin numbers for Mini UART TXD and RXD are already defined
 *       (e.g., MINI_UART_TXD and MINI_UART_RXD).
 * 
 * @return void
 */
void uart_init(void)
{
    // Set the GPIO pins for Mini UART TX (Transmit) and RX (Receive) to alternate function 5.
    // This configuration enables the UART signals on the GPIO pins for communication.
    gpio_set_pin_function(MINI_UART_TXD, GPIO_ALT5);  // Set the TXD pin to use alternate function 5
    gpio_set_pin_function(MINI_UART_RXD, GPIO_ALT5);  // Set the RXD pin to use alternate function 5

    // Configure pull-up/down resistors for the TX and RX pins.
    // Setting both pins to '0' disables any pull-up or pull-down resistors.
    gpio_pull_up_down(MINI_UART_TXD, 0);  // No pull-up or pull-down for TXD
    gpio_pull_up_down(MINI_UART_RXD, 0);  // No pull-up or pull-down for RXD

    // Enable the Mini UART (AUX) by setting the relevant bit in the ENABLES register.
    AUX->ENABLES = 1;  // Enable the AUX (Mini UART) peripheral

    // Configure Mini UART control registers.
    AUX->MU_CNTL_REG = 0;     // Disable Mini UART to configure it safely
    AUX->MU_IER_REG = 1;      // Disable interrupts for the Mini UART
    AUX->MU_LCR_REG = 3;      // Set Line Control Register to 3 (8 data bits, no parity, 1 stop bit)
    AUX->MU_MCR_REG = 0;      // Set Modem Control Register to 0 (no control)
    
    // Set the baud rate for the Mini UART.
    // The baud rate is set to 433 (typically used for 115200 baud with a 3.6864 MHz clock).
    AUX->MU_BAUD_REG = 433;   // Set the baud rate to 115200 (433 for 3.6864 MHz clock)

    // Enable the Mini UART for use.
    AUX->MU_CNTL_REG = 3;     // Re-enable the Mini UART with TX and RX enabled

    // Send a carriage return and newline characters to the UART terminal to indicate initialization is complete.
    uart_send('\r');  // Send a carriage return
    uart_send('\n');  // Send a newline
    uart_send('\n');  // Send another newline for separation
}

/**
 * @brief Receives a character from the Mini UART.
 *
 * This function waits until data is available to read from the UART, 
 * and then retrieves the received character from the UART data register.
 *
 * @return The character received from the Mini UART.
 */
char uart_recv(void)
{
    // Wait until the UART has received data.
    // The Data Ready Flag (bit 0) in the AUX_MU_LCR_REG register is checked 
    // to see if new data has been received and is ready to be read.
    while(!(AUX->MU_LSR_REG & 0x01)) 
    {
        // Busy-wait loop: does nothing while waiting for the Data Ready Flag to be set.
        // This ensures that the function doesn't read from the UART until new data is available.
        ;
    }

    // Retrieve the received character from the UART data register.
    // The character is stored in the lower 8 bits of the AUX_MU_LCR_REG register.
    // The `& 0xFF` operation ensures that only the 8 least significant bits (the character) are returned.
    return (AUX->MU_IO_REG & 0xFF);
}

/**
 * @brief Sends a character over the Mini UART.
 *
 * This function waits for the UART transmitter to be ready by checking the 
 * appropriate control register bit, and then sends the character `c` 
 * through the UART data register.
 *
 * @param c The character to send via the Mini UART.
 */
void uart_send(char c)
{
    // Wait until the UART transmitter is ready to send data.
    // The Transmitter Empty Flag (bit 5) in the AUX_MU_LCR_REG register 
    // is checked to determine if the UART can accept new data.
    while(!(AUX->MU_LSR_REG & 0x20)) 
    {
        // Busy-wait loop: does nothing while waiting for the flag to be set.
        // This ensures that we don't attempt to send data until the UART is ready.
        ;
    }

    // Transmit the character `c` by writing it to the UART's data register.
    // The character will be sent out through the Mini UART hardware.
    AUX->MU_IO_REG = c;
}

/**
 * @brief Sends a null-terminated string over the UART.
 * 
 * This function sends a string of characters to the UART one by one. If a newline 
 * character ('\n') is encountered, a carriage return ('\r') is first sent, as required
 * by many terminal emulators to properly handle newlines in serial communication.
 * The function continues sending characters until the null terminator ('\0') is reached, 
 * which marks the end of the string.
 * 
 * @param str A pointer to the null-terminated string to be sent over UART.
 * 
 * @return void
 */
void uart_send_string(char *str)
{
    // Loop through each character of the string
    // Continue looping until we reach the null terminator ('\0')
    while(*str) {
        // If the character is a newline, send a carriage return first for proper formatting
        if (*str == '\n') 
        {
            uart_send('\r');  // Send carriage return before newline for proper display on UART terminal
        }

        // Send the current character
        uart_send(*str);
        
        // Move to the next character in the string
        str++;
    }
}


