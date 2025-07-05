/**
 * @file        lcd_2004.h
 * @brief       Header file for the 20x4 LCD module driver using I2C.
 * @description This header file defines the interface for the 20x4 character LCD module
 *              driver, including macros, data structures, and function prototypes for
 *              initializing and controlling the LCD module.
 *
 * @version     1.0
 * @date        2024-12-19
 */


#ifndef _LCD_2004_H_
#define _LCD_2004_H_

#include <stdint.h>

#define SDA_PIN                     2 ///< Define the pin used for SDA (data line) in I2C communication, typically pin 2
#define SCL_PIN                     3 ///< Define the pin used for SCL (clock line) in I2C communication, typically pin 3
#define LCD_I2C_ADDRESS             0x27 ///< Define the default I2C address for the LCD module, commonly 0x27 for many LCD I2C modules
#define LCD_I2C_DIVIDER             1500

// LCD Commands
#define LCD_CMD_CLEAR_DISPLAY       0x01 ///< Clear display command
#define LCD_CMD_RETURN_HOME         0x02 ///< Return cursor to home position
#define LCD_CMD_ENTRY_MODE_SET      0x04 ///< Set entry mode
#define LCD_CMD_DISPLAY_CONTROL     0x08 ///< Control display, cursor, and blinking
#define LCD_CMD_CURSOR_SHIFT        0x10 ///< Move cursor or shift display
#define LCD_CMD_FUNCTION_SET        0x20 ///< Set function (e.g., 4-bit/8-bit mode)
#define LCD_CMD_SET_CGRAM_ADDR      0x40 ///< Set CGRAM address
#define LCD_CMD_SET_DDRAM_ADDR      0x80 ///< Set DDRAM address

// Flags for display entry mode
#define LCD_ENTRY_RIGHT             0x00 ///< Move cursor to the right
#define LCD_ENTRY_LEFT              0x02 ///< Move cursor to the left
#define LCD_ENTRY_SHIFT_INCREMENT   0x01 ///< Shift display to the right
#define LCD_ENTRY_SHIFT_DECREMENT   0x00 ///< Shift display to the left

// Flags for display on/off control
#define LCD_DISPLAY_ON              0x04 ///< Turn display on
#define LCD_DISPLAY_OFF             0x00 ///< Turn display off
#define LCD_CURSOR_ON               0x02 ///< Turn cursor on
#define LCD_CURSOR_OFF              0x00 ///< Turn cursor off
#define LCD_BLINK_ON                0x01 ///< Turn blinking on
#define LCD_BLINK_OFF               0x00 ///< Turn blinking off

// Flags for function set
#define LCD_8BIT_MODE               0x10 ///< Set 8-bit mode
#define LCD_4BIT_MODE               0x00 ///< Set 4-bit mode
#define LCD_2LINE                   0x08 ///< Enable 2-line display
#define LCD_1LINE                   0x00 ///< Enable 1-line display
#define LCD_5x10DOTS                0x04 ///< Use 5x10 dot character font
#define LCD_5x8DOTS                 0x00 ///< Use 5x8 dot character font

// Backlight control
#define LCD_BACKLIGHT               0x08 ///< Backlight on
#define LCD_NOBACKLIGHT             0x00 ///< Backlight off

// Control bits
#define LCD_CMD_MODE                0x00 ///< Command mode
#define REGISTER_SELECT             0x01 ///< Register select signal
#define READ_WRITE                  0x02 ///< Read/Write signal
#define ENABLE                      0x04 ///< Enable signal

// LCD Initialization constants
#define LCD_WAKE_UP                 0x03 ///< Wake up command for initialization

// Function prototypes

/**
 * @brief Initializes the 20x4 LCD module.
 * 
 * This function initializes the GPIO pins, configures the I2C interface,
 * and sets up the LCD module in 4-bit mode with the desired display settings.
 */
extern void lcd_init(void);

/**
 * @brief Controls the LCD backlight.
 * 
 * This function turns the backlight on or off.
 * 
 * @param on Set to 1 to turn on the backlight, or 0 to turn it off.
 */
extern void lcd_backlight(uint8_t on);

/**
 * @brief Clears the LCD display.
 * 
 * This function clears the display and resets the cursor to the home position.
 */
extern void lcd_clear(void);

/**
 * @brief Moves the cursor to the home position on the LCD.
 * 
 * This function sends the "Return Home" command to the LCD, which resets the
 * cursor to the top-left corner (position 0,0) of the display. It also resets 
 * any shifted display settings to their default state.
 */
extern void lcd_home(void);

/**
 * @brief Sets the cursor position on the LCD.
 * 
 * This function moves the cursor to the specified column and row.
 * 
 * @param col The column position (0-19).
 * @param row The row position (0-3).
 */
extern void lcd_set_cursor(uint8_t col, uint8_t row);

/**
 * @brief Prints a string to the LCD.
 * 
 * This function writes a null-terminated string to the LCD starting
 * from the current cursor position.
 * 
 * @param str Pointer to the string to print.
 */
extern void lcd_print(const char *str);

#endif /* _LCD_2004_H_ */
