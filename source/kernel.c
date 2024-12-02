#include "common.h"
#include "gpio.h"
#include "mini_uart.h"


/**
 * @brief The main entry point for the kernel.
 * 
 * This function is executed when the kernel starts. It performs the following actions:
 * 1. Initializes the GPIO system by calling gpio_init().
 * 2. Initializes the UART system for serial communication by calling uart_init().
 * 3. Sends an initial message via UART to notify that the kernel is initializing.
 * 4. Enters an infinite loop, where it continuously receives characters over UART
 *    and sends them back (echoing).
 * 
 * This function represents the main kernel execution flow, handling basic I/O
 * and communication over UART.
 * 
 * @return Always returns 0 (this is not used as the system does not exit).
 */
int kernel_main(void)
{
    // Initialize the GPIO system
    gpio_init();

    // Initialize the UART system for serial communication
    uart_init();

    // Send an initialization message to the UART terminal
    uart_send_string("Raspberry PI bare metal kernel initialization... \n");

    // Infinite loop to continuously read from UART and echo received characters
    while(1)
    {
        // Receive a character via UART and send it back (echo)
        uart_send(uart_recv());
    }

    // Return 0 (this return is never actually reached)
    return 0;
}