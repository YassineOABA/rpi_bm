/**
 * @file        lcd_2004.c
 * @brief       Source file for the 20x4 LCD module driver using I2C.
 * @description This source file implements the functions to interface with and 
 *              control the 20x4 character LCD module over I2C. It includes the 
 *              initialization process, sending commands, displaying characters, 
 *              and handling I2C communication for the LCD.
 *
 * @version     1.0
 * @date        2024-12-19
 */

#include <stdint.h>
#include "gpio.h"
#include "lcd_2004.h"
#include "i2c.h"
#include "timer.h"

// Static variables
static const uint8_t row_offsets[4] = {0x00, 0x40, 0x14, 0x54}; ///< Row offsets for the 20x4 LCD (addresses of the rows)
static uint8_t backlight = LCD_BACKLIGHT; ///< Current backlight state (on or off)

// Function prototypes
static void lcd_write(uint8_t data); ///< Function to write a byte to the LCD
static void lcd_pulse(uint8_t data); ///< Function to set the ENABLE pin high and then low to latch the data
static void lcd_send(uint8_t data, uint8_t mode); ///< Function to send a byte (command/data) to the LCD
static void lcd_write_command(uint8_t cmd); ///< Function to send a command to the LCD
static void lcd_write_data(uint8_t data); ///< Function to send data (character) to the LCD

/**
 * @brief Writes a byte to the LCD over I2C.
 * 
 * This function sends a single byte to the LCD module through the I2C interface.
 * 
 * @param data Byte to send to the LCD.
 */
static void lcd_write(uint8_t data)
{
    uint8_t status = 0;

    data = data | backlight; ///< Add the backlight state to the data byte
    status = i2c_write(I2C_CONTROLLER_1, LCD_I2C_ADDRESS, &data, 1); ///< Send the data over I2C
    if (status != 0)
    {
        // Handle errors (optional)
    }
}

/**
 * @brief Generates an enable pulse for the LCD.
 * 
 * This function sets the ENABLE pin high and then low to latch the data
 * sent to the LCD. It includes the necessary delays for the pulse width.
 * 
 * @param data The data to send to the LCD with the ENABLE bit toggled.
 */
static void lcd_pulse(uint8_t data)
{
    lcd_write(data | ENABLE);  ///< Set ENABLE bit high
    delay_micro_s(1);          ///< Wait for the enable pulse width
    lcd_write(data & ~ENABLE); ///< Set ENABLE bit low
    delay_micro_s(1);          ///< Wait for command to latch
}

/**
 * @brief Sends a command or data to the LCD.
 * 
 * This function sends high and low nibbles of the given byte to the LCD,
 * controlling the RS pin and the backlight state.
 * 
 * @param data The byte to send (command or data).
 * @param mode Mode for the data: 0 for command, REGISTER_SELECT for data.
 */
static void lcd_send(uint8_t data, uint8_t mode)
{
    uint8_t high_nibble = data & 0xF0; ///< Extract the high nibble (upper 4 bits)
    uint8_t low_nibble = (data << 4) & 0xF0; ///< Extract the low nibble (lower 4 bits)

    // Send high nibble
    lcd_write(high_nibble | mode); ///< Prepare high nibble with the appropriate mode
    lcd_pulse(high_nibble | mode); ///< Pulse to latch the high nibble

    // Send low nibble
    lcd_write(low_nibble | mode); ///< Prepare low nibble with the appropriate mode
    lcd_pulse(low_nibble | mode); ///< Pulse to latch the low nibble
}

/**
 * @brief Sends a command to the LCD.
 * 
 * Commands configure the LCD module (e.g., clear display, set cursor).
 * This function automatically handles longer delays for commands such as
 * Clear Display and Return Home.
 * 
 * @param cmd Command to send to the LCD.
 */
static void lcd_write_command(uint8_t cmd)
{
    lcd_send(cmd, 0); ///< Send the command (mode 0 indicates command)
}

/**
 * @brief Sends data to the LCD.
 * 
 * Data is displayed as characters on the LCD. The RS pin is set to indicate data mode.
 * 
 * @param data Byte to send as data.
 */
static void lcd_write_data(uint8_t data)
{
    lcd_send(data, REGISTER_SELECT); ///< Send the data (mode REGISTER_SELECT indicates data mode)
}

/**
 * @brief Initializes the 20x4 LCD module.
 * 
 * This function initializes the GPIO pins, configures the I2C interface,
 * and sets up the LCD module in 4-bit mode with the desired display settings.
 */
void lcd_init(void)
{
    // Configure GPIO pins for I2C communication
    gpio_set_pin_function(SDA_PIN, GPIO_ALT0); ///< Set SDA to I2C function
    gpio_set_pin_function(SCL_PIN, GPIO_ALT0); ///< Set SCL to I2C function
    gpio_pull_up_down(SDA_PIN, GPIO_PUD_UP); ///< Disable pull-up/down on SDA pin
    gpio_pull_up_down(SCL_PIN, GPIO_PUD_UP); ///< Disable pull-up/down on SCL pin

    // Initialize I2C controller for communication
    i2c_init(I2C_CONTROLLER_1, LCD_I2C_DIVIDER); ///< Set I2C clock speed to 100 kHz

    // Wait for LCD to power on and stabilize
    delay_micro_s(50000); ///< Wait 50ms for power stabilization

    // Initialize LCD in 4-bit mode using wake-up sequence
    lcd_write_command(0x03); ///< Wake up sequence (HD44780-specific)
    delay_micro_s(5000);  ///< Wait 5ms
    lcd_write_command(0x03); ///< Repeat wake up sequence
    delay_micro_s(160);   ///< Wait 160µs
    lcd_write_command(0x03); ///< Final wake up sequence
    delay_micro_s(160);   ///< Wait 160µs
    lcd_write_command(LCD_CMD_FUNCTION_SET | LCD_4BIT_MODE); ///< Switch to 4-bit mode
    delay_micro_s(160);   ///< Wait 160µs

    // Configure LCD display settings
    lcd_write_command(LCD_CMD_FUNCTION_SET | LCD_4BIT_MODE | LCD_2LINE | LCD_5x8DOTS); ///< 2-line, 5x8 font mode
    delay_micro_s(160);   ///< Wait 160µs
    lcd_write_command(LCD_CMD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF); ///< Display on, cursor off, blink off
    delay_micro_s(160);   ///< Wait 160µs
    lcd_write_command(LCD_CMD_CLEAR_DISPLAY); ///< Clear the display
    delay_micro_s(2000);  ///< Wait 2ms for clear display
    lcd_write_command(LCD_CMD_ENTRY_MODE_SET | LCD_ENTRY_LEFT | LCD_ENTRY_SHIFT_DECREMENT); ///< Set entry mode
    delay_micro_s(160);   ///< Wait 160µs
    lcd_write_command(LCD_CMD_RETURN_HOME); ///< Send the clear display command
    delay_micro_s(2000);
}

/**
 * @brief Controls the LCD backlight.
 * 
 * This function turns the backlight on or off.
 * 
 * @param on Set to 1 to turn on the backlight, or 0 to turn it off.
 */
void lcd_backlight(uint8_t on)
{
    if (on)
    {
        backlight = LCD_BACKLIGHT; ///< Turn on the backlight
    } else
    {
        backlight = LCD_NOBACKLIGHT; ///< Turn off the backlight
    }

    lcd_write_command(0); ///< Update the backlight state
    delay_micro_s(37); ///< Wait for the LCD to process the command
}

/**
 * @brief Clears the LCD display.
 * 
 * This function clears the display and resets the cursor to the home position.
 */
void lcd_clear(void)
{
    lcd_write_command(LCD_CMD_CLEAR_DISPLAY); ///< Send the clear display command
    delay_micro_s(2000); ///< Wait for the LCD to process the command
}

/**
 * @brief Moves the cursor to the home position on the LCD.
 * 
 * This function sends the "Return Home" command to the LCD, which resets the
 * cursor to the top-left corner (position 0,0) of the display. It also resets 
 * any shifted display settings to their default state.
 */
void lcd_home(void)
{
    lcd_write_command(LCD_CMD_RETURN_HOME); ///< Send the Return Home command
    delay_micro_s(2000); ///< Wait for the LCD to process the command
}


/**
 * @brief Sets the cursor position on the LCD.
 * 
 * This function moves the cursor to the specified column and row.
 * 
 * @param col The column position (0-19).
 * @param row The row position (0-3).
 */
void lcd_set_cursor(uint8_t col, uint8_t row)
{
    if (row > 3) row = 3; // Cap to max row index
    lcd_write_command(LCD_CMD_SET_DDRAM_ADDR | (col + row_offsets[row])); ///< Set DDRAM address based on column and row
    delay_micro_s(50); ///< Wait for the LCD to process the command
}

/**
 * @brief Prints a string to the LCD.
 * 
 * This function writes a null-terminated string to the LCD starting
 * from the current cursor position.
 * 
 * @param str Pointer to the string to print.
 */
void lcd_print(const char *str)
{
    while (*str)
    {
        lcd_write_data(*str++); ///< Write each character to the LCD
    }
}