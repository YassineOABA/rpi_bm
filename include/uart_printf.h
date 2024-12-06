/**
 * @file        uart_printf.h
 * @brief       UART-based formatted output.
 * @description This header provides declarations for functions that enable formatted output 
 *              over the UART interface, similar to printf.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#ifndef UART_PRINTF_H
#define UART_PRINTF_H

#include <stdarg.h>  // For va_list and related functions

// Function declarations for the UART printing system

/**
 * @brief Prints formatted data over UART.
 * 
 * This function mimics the behavior of the standard `printf` function, enabling 
 * formatted output via UART. It supports different format specifiers like `%d`, `%i`, 
 * `%u`, `%x`, `%X`, `%s`, and 64-bit integer formats like `%lld`, `%llu`, `%llx`, and `%llX`.
 * 
 * @param format The format string containing text and format specifiers.
 * @param ... The variables to be formatted and printed.
 */
void uart_printf(const char *format, ...);

#endif // UART_PRINTF_H

