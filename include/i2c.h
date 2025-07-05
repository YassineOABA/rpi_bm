/**
 * @file        i2c.h
 * @brief       I2C driver interface for the BCM2835 BSC controller.
 * @description This header file provides function declarations and macros for interacting
 *              with the I2C interface of the Broadcom BCM2835 BSC controller.
 *
 * @version     1.0
 * @date        2024-12-16
 */

#ifndef I2C_H
#define I2C_H

#include "base.h"
#include <stdint.h>


#define BSC0_I2C_BASE_ADDR   (PIBASE + 0x205000)
#define BSC1_I2C_BASE_ADDR   (PIBASE + 0x804000)
#define BSC2_I2C_BASE_ADDR   (PIBASE + 0x805000)

#define I2C_SPEED 100000

// I2C register structure definition
struct I2C_Registers
{
    volatile uint32_t CONTROL;  // Control register (offset 0x00)
    volatile uint32_t STATUS;   // Status register (offset 0x04)
    volatile uint32_t DLEN;     // Data Length register (offset 0x08)
    volatile uint32_t A;        // Slave Address register (offset 0x0C)
    volatile uint32_t FIFO;     // Data FIFO register (offset 0x10)
    volatile uint32_t DIV;      // Clock Divider register (offset 0x14)
    volatile uint32_t DEL;      // Data Delay register (offset 0x18)
    volatile uint32_t CLKT;     // Clock Stretch Timeout register (offset 0x1C)
};

#define BSC0_I2C        ((struct I2C_Registers *)(BSC0_I2C_BASE_ADDR))
#define BSC1_I2C        ((struct I2C_Registers *)(BSC1_I2C_BASE_ADDR))
// Reserved for HDMI, should not be used
#define BSC2_I2C        ((struct I2C_Registers *)(BSC2_I2C_BASE_ADDR))

// Enum for I2C controller indices.
typedef enum {
    I2C_CONTROLLER_0 = 0,  ///< Index for BSC0 I2C controller
    I2C_CONTROLLER_1 = 1,  ///< Index for BSC1 I2C controller
    I2C_CONTROLLER_2 = 2   ///< Index for BSC2 I2C controller
} I2C_Controller_Index;

// Bit definitions for the I2C Control Register
#define I2C_CTL_I2CEN_Pos       15           // I2C Enable bit position
#define I2C_CTL_I2CEN_Disable   (0 << I2C_CTL_I2CEN_Pos) // Disable I2C
#define I2C_CTL_I2CEN_Enable    (1 << I2C_CTL_I2CEN_Pos) // Enable I2C

#define I2C_CTL_INTR_Pos        10           // Interrupt on RX bit position
#define I2C_CTL_INTR_Disable    (0 << I2C_CTL_INTR_Pos)  // Disable RX interrupt
#define I2C_CTL_INTR_Enable     (1 << I2C_CTL_INTR_Pos)  // Enable RX interrupt

#define I2C_CTL_INTT_Pos        9            // Interrupt on TX bit position
#define I2C_CTL_INTT_Disable    (0 << I2C_CTL_INTT_Pos)  // Disable TX interrupt
#define I2C_CTL_INTT_Enable     (1 << I2C_CTL_INTT_Pos)  // Enable TX interrupt

#define I2C_CTL_INTD_Pos        8            // Interrupt on DONE bit position
#define I2C_CTL_INTD_Disable    (0 << I2C_CTL_INTD_Pos)  // Disable DONE interrupt
#define I2C_CTL_INTD_Enable     (1 << I2C_CTL_INTD_Pos)  // Enable DONE interrupt

#define I2C_CTL_ST_Pos          7            // Start Transfer bit position
#define I2C_CTL_ST_NoAction     (0 << I2C_CTL_ST_Pos)    // No action
#define I2C_CTL_ST_Start        (1 << I2C_CTL_ST_Pos)    // Start transfer

#define I2C_CTL_CLEAR_Pos       4            // CLEAR FIFO bit position
#define I2C_CTL_CLEAR_NoAction  (0 << I2C_CTL_CLEAR_Pos) // No action
#define I2C_CTL_CLEAR_ClearFifo (1 << I2C_CTL_CLEAR_Pos) // Clear FIFO

#define I2C_CTL_READ_Pos        0            // Read Transfer bit position
#define I2C_CTL_READ_Write      (0 << I2C_CTL_READ_Pos)  // Write packet transfer
#define I2C_CTL_READ_Read       (1 << I2C_CTL_READ_Pos)  // Read packet transfer

// Bit definitions for the I2C Status Register

// Reserved (31:10) - Write as 0, read as don't care

#define I2C_STAT_CLKT_Pos       9              // Clock Stretch Timeout bit position
#define I2C_STAT_CLKT_NoError   (0 << I2C_STAT_CLKT_Pos) // No errors detected
#define I2C_STAT_CLKT_Error     (1 << I2C_STAT_CLKT_Pos) // Clock stretch timeout occurred

#define I2C_STAT_ERR_Pos        8              // ACK Error bit position
#define I2C_STAT_ERR_NoError    (0 << I2C_STAT_ERR_Pos)  // No errors detected
#define I2C_STAT_ERR_Error      (1 << I2C_STAT_ERR_Pos)  // ACK error occurred

#define I2C_STAT_RXF_Pos        7              // FIFO Full bit position
#define I2C_STAT_RXF_NotFull    (0 << I2C_STAT_RXF_Pos)  // FIFO not full
#define I2C_STAT_RXF_Full       (1 << I2C_STAT_RXF_Pos)  // FIFO full

#define I2C_STAT_TXE_Pos        6              // FIFO Empty bit position
#define I2C_STAT_TXE_NotEmpty   (0 << I2C_STAT_TXE_Pos)  // FIFO not empty
#define I2C_STAT_TXE_Empty      (1 << I2C_STAT_TXE_Pos)  // FIFO empty

#define I2C_STAT_RXD_Pos        5              // FIFO Contains Data bit position
#define I2C_STAT_RXD_Empty      (0 << I2C_STAT_RXD_Pos)  // FIFO empty
#define I2C_STAT_RXD_Contains   (1 << I2C_STAT_RXD_Pos)  // FIFO contains at least 1 byte

#define I2C_STAT_TXD_Pos        4              // FIFO Can Accept Data bit position
#define I2C_STAT_TXD_Full       (0 << I2C_STAT_TXD_Pos)  // FIFO is full
#define I2C_STAT_TXD_Accept     (1 << I2C_STAT_TXD_Pos)  // FIFO can accept at least 1 byte

#define I2C_STAT_RXR_Pos        3              // FIFO Needs Reading (full) bit position
#define I2C_STAT_RXR_NotFull    (0 << I2C_STAT_RXR_Pos)  // FIFO less than full
#define I2C_STAT_RXR_Full       (1 << I2C_STAT_RXR_Pos)  // FIFO full

#define I2C_STAT_TXW_Pos        2              // FIFO Needs Writing (not full) bit position
#define I2C_STAT_TXW_Full       (0 << I2C_STAT_TXW_Pos)  // FIFO is at least full
#define I2C_STAT_TXW_NotFull    (1 << I2C_STAT_TXW_Pos)  // FIFO is less than full

#define I2C_STAT_DONE_Pos       1              // Transfer Done bit position
#define I2C_STAT_DONE_NotDone   (0 << I2C_STAT_DONE_Pos) // Transfer not completed
#define I2C_STAT_DONE_Done      (1 << I2C_STAT_DONE_Pos) // Transfer completed

#define I2C_STAT_TA_Pos         0              // Transfer Active bit position
#define I2C_STAT_TA_NotActive   (0 << I2C_STAT_TA_Pos)   // Transfer not active
#define I2C_STAT_TA_Active      (1 << I2C_STAT_TA_Pos)   // Transfer active


/**
 * @brief Initializes the specified I2C controller.
 * 
 * Configures the I2C peripheral with a clock divider to set the communication speed.
 * 
 * @param index      The I2C controller index (I2C_CONTROLLER_0, I2C_CONTROLLER_1, I2C_CONTROLLER_2).
 * @param clock_div  The clock divider value to configure the I2C speed.
 */
extern void i2c_init(I2C_Controller_Index index, uint16_t clock_div);

/**
 * @brief Writes data to an I2C slave device.
 * 
 * Sends a buffer of data to the specified I2C slave device using the I2C controller.
 * 
 * @param index       The I2C controller index (I2C_CONTROLLER_0, I2C_CONTROLLER_1, I2C_CONTROLLER_2).
 * @param slave_addr  The address of the I2C slave device.
 * @param data        Pointer to the buffer containing data to send.
 * @param length      Number of bytes to send.
 * @return int        Returns 0 on success, -1 for invalid input, -2 for ACK errors,
 *                    and -3 for clock stretch timeouts.
 */
extern int i2c_write(I2C_Controller_Index index, uint8_t slave_addr, uint8_t *data, uint32_t length);

/**
 * @brief Reads data from an I2C slave device.
 * 
 * Reads a buffer of data from the specified I2C slave device using the I2C controller.
 * 
 * @param index       The I2C controller index (I2C_CONTROLLER_0, I2C_CONTROLLER_1, I2C_CONTROLLER_2).
 * @param slave_addr  The address of the I2C slave device.
 * @param buffer      Pointer to the buffer where the received data will be stored.
 * @param length      Number of bytes to read.
 * @return int        Returns 0 on success, -1 for invalid input, -2 for ACK errors,
 *                    and -3 for clock stretch timeouts.
 */
extern int i2c_read(I2C_Controller_Index index, uint8_t slave_addr, uint8_t *buffer, uint32_t length);

#endif // I2C_H
