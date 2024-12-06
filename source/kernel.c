/**
 * @file        kernel.c
 * @brief       Kernel entry point and system initialization.
 * @description This file contains the entry point for the Raspberry Pi kernel, along with 
 *              initialization code for subsystems like UART, GPIO, and memory.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#include "common.h"
#include "gpio.h"
#include "mini_uart.h"
#include "uart_printf.h"


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
    uart_printf("Raspberry PI bare metal kernel initialization... \n");

    // Send platform information to the UART terminal
    uart_printf("Platform : Raspberry PI %d B + \n",3);

    // Send current exception level EL
    uart_printf("Current EL : %i\n",get_el());

    // Infinite loop to continuously read from UART and echo received characters
    while(1)
    {
        // Receive a character via UART and send it back (echo)
        uart_send(uart_recv());
    }

    // Return 0 (this return is never actually reached)
    return 0;
}