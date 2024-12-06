/**
 * @file        mini_uart.h
 * @brief       Mini UART interface for the Raspberry Pi.
 * @description This header provides function declarations and macros for configuring and 
 *              interacting with the mini UART peripheral.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#ifndef _MINI_UART_H_
#define _MINI_UART_H_

#define MINI_UART_TXD   14
#define MINI_UART_RXD   15

/**
 * @brief Initializes the UART interface for serial communication.
 * 
 * This function configures the UART hardware (baud rate, data bits, stop bits, etc.)
 * and prepares it for communication. It should be called before using any UART 
 * communication functions.
 */
extern void uart_init(void);

/**
 * @brief Receives a single character from the UART.
 * 
 * This function waits until a character is received over the UART interface
 * and returns the received character. The function will block until a character 
 * is available to be read.
 * 
 * @return The character received from the UART.
 */
extern char uart_recv(void);

/**
 * @brief Sends a single character over the UART.
 * 
 * This function sends a single character over the UART interface. The function
 * blocks until the character has been successfully transmitted.
 * 
 * @param c The character to be sent via UART.
 */
extern void uart_send(char c);

/**
 * @brief Sends a string of characters over the UART.
 * 
 * This function sends a null-terminated string over the UART interface.
 * Each character of the string is transmitted sequentially until the null 
 * terminator is reached. The function blocks until all characters have been sent.
 * 
 * @param str Pointer to the null-terminated string to be sent via UART.
 */
extern void uart_send_string(char *str);


#endif /* _MINI_UART_H_ */