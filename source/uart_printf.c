/**
 * @file        uart_printf.c
 * @brief       Implementation of formatted output functions using UART.
 * @description This file provides functions for printing formatted strings via the UART interface, 
 *              useful for debugging and logging.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#include "uart_printf.h"
#include <stdarg.h>
#include "mini_uart.h"

// Helper static functions for printing integers in different formats
// These are static functions so they are not exposed outside this file.
static void uart_print_int(int num);
static void uart_print_unsigned_int(unsigned int num);
static void uart_print_hex(int num, int uppercase);
static void uart_print_long_long_int(long long int num);
static void uart_print_unsigned_long_long_int(unsigned long long int num);
static void uart_print_long_long_hex(long long int num, int uppercase);

/**
 * @brief Helper function to print a signed integer over UART.
 * 
 * This function prints a signed integer (int) over UART.
 * 
 * @param num The signed integer to be printed over UART.
 * 
 * @return void
 */
static void uart_print_int(int num) {
    char buffer[20];  // Buffer to hold the integer as a string
    int i = 0;

    // Special case for zero
    if (num == 0) {
        uart_send('0');
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        uart_send('-');
        num = -num;
    }

    // Convert the number to a string (in reverse order)
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Send the digits in the correct order
    while (i-- > 0) {
        uart_send(buffer[i]);
    }
}

/**
 * @brief Helper function to print an unsigned integer over UART.
 * 
 * This function prints an unsigned integer (unsigned int) over UART.
 * 
 * @param num The unsigned integer to be printed over UART.
 * 
 * @return void
 */
static void uart_print_unsigned_int(unsigned int num) {
    char buffer[20];  // Buffer to hold the unsigned integer as a string
    int i = 0;

    // Special case for zero
    if (num == 0) {
        uart_send('0');
        return;
    }

    // Convert the number to a string (in reverse order)
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Send the digits in the correct order
    while (i-- > 0) {
        uart_send(buffer[i]);
    }
}

/**
 * @brief Helper function to print an integer in hexadecimal format.
 * 
 * This function prints an integer (int) in hexadecimal format over UART.
 * 
 * @param num The integer to be printed in hexadecimal format.
 * @param uppercase If true, prints in uppercase hexadecimal (A-F), otherwise lowercase (a-f).
 * 
 * @return void
 */
static void uart_print_hex(int num, int uppercase) {
    char buffer[16];  // Buffer to hold the hexadecimal representation
    int i = 0;
    const char hex_digits_lower[] = "0123456789abcdef";
    const char hex_digits_upper[] = "0123456789ABCDEF";

    // Special case for zero
    if (num == 0) {
        uart_send('0');
        return;
    }

    // Convert the number to a hexadecimal string (in reverse order)
    while (num > 0) {
        int digit = num % 16;
        buffer[i++] = (uppercase ? hex_digits_upper : hex_digits_lower)[digit];
        num /= 16;
    }

    // Send the digits in the correct order
    while (i-- > 0) {
        uart_send(buffer[i]);
    }
}

/**
 * @brief Helper function to print a signed 64-bit integer over UART.
 * 
 * This function handles negative numbers and prints a 64-bit integer 
 * (long long int) over UART.
 * 
 * @param num The signed 64-bit integer to be printed over UART.
 * 
 * @return void
 */
static void uart_print_long_long_int(long long int num) {
    char buffer[20];  // Buffer to hold the 64-bit integer as a string
    int i = 0;

    // Special case for zero
    if (num == 0) {
        uart_send('0');
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        uart_send('-');
        num = -num;
    }

    // Convert the number to a string (in reverse order)
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Send the digits in the correct order
    while (i-- > 0) {
        uart_send(buffer[i]);
    }
}

/**
 * @brief Helper function to print an unsigned 64-bit integer over UART.
 * 
 * This function prints an unsigned 64-bit integer (unsigned long long int)
 * over UART.
 * 
 * @param num The unsigned 64-bit integer to be printed over UART.
 * 
 * @return void
 */
static void uart_print_unsigned_long_long_int(unsigned long long int num) {
    char buffer[20];  // Buffer to hold the unsigned 64-bit integer as a string
    int i = 0;

    // Special case for zero
    if (num == 0) {
        uart_send('0');
        return;
    }

    // Convert the number to a string (in reverse order)
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Send the digits in the correct order
    while (i-- > 0) {
        uart_send(buffer[i]);
    }
}

/**
 * @brief Helper function to print a signed 64-bit integer in hexadecimal format.
 * 
 * This function prints a signed 64-bit integer in hexadecimal format 
 * (either lowercase or uppercase) over UART.
 * 
 * @param num The signed 64-bit integer to be printed in hexadecimal format.
 * @param uppercase If true, print uppercase letters; if false, print lowercase letters.
 * 
 * @return void
 */
static void uart_print_long_long_hex(long long int num, int uppercase) {
    char buffer[16];  // Buffer to hold the hexadecimal representation
    int i = 0;
    const char hex_digits_lower[] = "0123456789abcdef";
    const char hex_digits_upper[] = "0123456789ABCDEF";

    // Special case for zero
    if (num == 0) {
        uart_send('0');
        return;
    }

    while (num > 0) {
        int digit = num % 16;
        buffer[i++] = (uppercase ? hex_digits_upper : hex_digits_lower)[digit];
        num /= 16;
    }

    // Send the digits in the correct order
    while (i-- > 0) {
        uart_send(buffer[i]);
    }
}

/**
 * @brief A formatted uart_printf-like function to send data over UART.
 * 
 * This function mimics the behavior of the standard `printf` function, enabling 
 * formatted output via UART. It processes the format string, handles variable 
 * arguments using `va_list`, and calls the appropriate functions (like `uart_send`, 
 * `uart_print_int`, or `uart_print_hex`) for each format specifier.
 * 
 * Supported format specifiers:
 * - `%c` for characters
 * - `%d` for signed integers
 * - `%i` for signed integers (same as `%d`)
 * - `%u` for unsigned integers
 * - `%s` for strings
 * - `%x` for hexadecimal (lowercase)
 * - `%X` for hexadecimal (uppercase)
 * - `%lld` for signed 64-bit integers
 * - `%llu` for unsigned 64-bit integers
 * 
 * @param format The format string containing text and format specifiers.
 * @param ... The variables to be formatted and printed.
 * 
 * @return void
 */
void uart_printf(const char *format, ...) {
    va_list args;  // Declare a variable argument list
    va_start(args, format);  // Initialize the argument list

    char c;
    int i;
    unsigned int u;
    long long int ll;
    unsigned long long int ull;
    char *s;

    // Iterate through the format string
    while (*format) {
        if (*format == '%') {  // Check if the current character is a format specifier
            format++;  // Skip the '%' character

            switch (*format) {
                case 'c':  // Character format specifier
                    c = (char) va_arg(args, int);  // Fetch the character argument
                    uart_send(c);  // Send the character via UART
                    break;

                case 'd':  // Integer format specifier (signed)
                case 'i':  // Integer format specifier (signed)
                    i = va_arg(args, int);  // Fetch the signed integer argument
                    uart_print_int(i);  // Print the signed integer via UART
                    break;

                case 'u':  // Unsigned integer format specifier
                    u = va_arg(args, unsigned int);  // Fetch the unsigned integer argument
                    uart_print_unsigned_int(u);  // Print the unsigned integer via UART
                    break;

                case 's':  // String format specifier
                    s = va_arg(args, char*);  // Fetch the string argument
                    uart_send_string(s);  // Send the string via UART
                    break;

                case 'x':  // Hexadecimal format specifier (lowercase)
                    i = va_arg(args, int);  // Fetch the integer argument
                    uart_print_hex(i, 0);  // Print the integer in lowercase hexadecimal
                    break;

                case 'X':  // Hexadecimal format specifier (uppercase)
                    i = va_arg(args, int);  // Fetch the integer argument
                    uart_print_hex(i, 1);  // Print the integer in uppercase hexadecimal
                    break;

                case 'l':  // Check for long and long long types
                    format++;  // Skip the 'l' character
                    if (*format == 'd' || *format == 'i') {  // %lld (signed 64-bit)
                        ll = va_arg(args, long long int);
                        uart_print_long_long_int(ll);
                    } else if (*format == 'u') {  // %llu (unsigned 64-bit)
                        ull = va_arg(args, unsigned long long int);
                        uart_print_unsigned_long_long_int(ull);
                    } else if (*format == 'x') {  // %llx (hexadecimal)
                        ll = va_arg(args, long long int);
                        uart_print_long_long_hex(ll, 0);
                    } else if (*format == 'X') {  // %llX (hexadecimal uppercase)
                        ll = va_arg(args, long long int);
                        uart_print_long_long_hex(ll, 1);
                    }
                    break;

                default:  // For unsupported format specifiers
                    uart_send('%');  // Send the '%' character
                    uart_send(*format);  // Send the format specifier itself
                    break;
            }
        } else {
            uart_send(*format);  // If not a format specifier, send the character as is
        }

        // If a newline is encountered, send a carriage return as well
        if (*format == '\n') {
            uart_send('\r');  // Move cursor to the beginning of the line
        }

        format++;  // Move to the next character in the format string
    }

    va_end(args);  // Clean up the argument list
}