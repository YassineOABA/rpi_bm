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
 * @brief Initializes the UART interface for serial communication.
 * 
 * This function configures the UART hardware (baud rate, data bits, stop bits, etc.)
 * and prepares it for communication. It should be called before using any UART 
 * communication functions.
 */
void uart_init(void)
{
    gpio_set_pin_function(MINI_UART_TXD, GPIO_ALT5);
    gpio_set_pin_function(MINI_UART_RXD, GPIO_ALT5);

    gpio_pull_up_down(MINI_UART_TXD, 0);
    gpio_pull_up_down(MINI_UART_RXD, 0);

    *AUX_ENABLES        = 1;
    *AUX_MU_CNTL_REG    = 0;
    *AUX_MU_IER_REG     = 0;
    *AUX_MU_LCR_REG     = 3;
    *AUX_MU_MCR_REG     = 0;
    *AUX_MU_BAUD_REG    = 271;
    *AUX_MU_CNTL_REG    = 3;

    uart_send('\n');
    uart_send('M');
    uart_send('I');
    uart_send('N');
    uart_send('I');
    uart_send('U');
    uart_send('A');
    uart_send('R');
    uart_send('T');
    uart_send('\n');
    uart_send('\n');
    uart_send('\n');
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
    while(!(*AUX_MU_LCR_REG & 0x00000001)) 
    {
        // Busy-wait loop: does nothing while waiting for the Data Ready Flag to be set.
        // This ensures that the function doesn't read from the UART until new data is available.
        ;
    }

    // Retrieve the received character from the UART data register.
    // The character is stored in the lower 8 bits of the AUX_MU_LCR_REG register.
    // The `& 0xFF` operation ensures that only the 8 least significant bits (the character) are returned.
    return (*AUX_MU_LCR_REG & 0xFF);
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
    while(!((*AUX_MU_LCR_REG) & 0x00000020)) 
    {
        // Busy-wait loop: does nothing while waiting for the flag to be set.
        // This ensures that we don't attempt to send data until the UART is ready.
        ;
    }

    // Transmit the character `c` by writing it to the UART's data register.
    // The character will be sent out through the Mini UART hardware.
    *AUX_MU_IO_REG = c;
}


/**
 * @brief Sends a string of characters over the UART.
 * 
 * This function sends a null-terminated string over the UART interface.
 * Each character of the string is transmitted sequentially until the null 
 * terminator is reached. The function blocks until all characters have been sent.
 * 
 * @param str Pointer to the null-terminated string to be sent via UART.
 */
void uart_send_string(char *str)
{
    // Loop through each character of the string
    // Continue looping until we reach the null terminator ('\0')
    while (*str != '\0')  // The string is terminated by the null character '\0'
    {
        uart_send(*str);  // Send the current character via UART
        str++;  // Move the pointer to the next character in the string
    }
}


