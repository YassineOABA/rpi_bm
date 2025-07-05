/**
 * @file        i2c.c
 * @brief       I2C driver implementation for the BCM2835 BSC controller.
 * @description This source file contains the implementation of functions for
 *              interacting with the I2C interface of the Broadcom BCM2835 BSC
 *              controller.
 *
 * @version     1.0
 * @date        2024-12-16
 */

#include "i2c.h"
#include <stdint.h>


/**
 * @brief Initializes the specified I2C controller.
 * 
 * Configures the I2C peripheral with a clock divider to set the communication speed.
 * 
 * @param index      The I2C controller index (I2C_CONTROLLER_0, I2C_CONTROLLER_1, I2C_CONTROLLER_2).
 * @param clock_div  The clock divider value to configure the I2C speed.
 */
void i2c_init(I2C_Controller_Index index, uint16_t clock_div)
{
    struct I2C_Registers *i2c;

    switch (index) {
        case I2C_CONTROLLER_0:
            i2c = BSC0_I2C;
            break;
        case I2C_CONTROLLER_1:
            i2c = BSC1_I2C;
            break;
        case I2C_CONTROLLER_2:
            i2c = BSC2_I2C;
            break;
        default:
            return;  // Invalid index
    }

    i2c->CONTROL = I2C_CTL_I2CEN_Disable;  // Disable I2C during configuration
    i2c->DIV = clock_div;  // Set clock divider for I2C speed
    //i2c->CLKT = 0x40;   // Set clock stretch timeout
    i2c->CONTROL = I2C_CTL_I2CEN_Enable;  // Enable I2C
}

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
int i2c_write(I2C_Controller_Index index, uint8_t slave_addr, uint8_t *data, uint32_t length)
{
    struct I2C_Registers *i2c;

    switch (index) {
        case I2C_CONTROLLER_0:
            i2c = BSC0_I2C;
            break;
        case I2C_CONTROLLER_1:
            i2c = BSC1_I2C;
            break;
        case I2C_CONTROLLER_2:
            i2c = BSC2_I2C;
            break;
        default:
            return -1;  // Invalid index
    }

    if (length == 0) return -1;  // Invalid data length

    i2c->CONTROL = I2C_CTL_CLEAR_ClearFifo;  // Clear FIFO
    i2c->STATUS = 0xFFFFFFFF;  // Clear status flags

    i2c->A = slave_addr;  // Set the slave address
    i2c->DLEN = length;   // Set data length

    for (uint32_t i = 0; i < length; i++) {
        i2c->FIFO = data[i];  // Write data to FIFO
    }

    i2c->CONTROL = I2C_CTL_I2CEN_Enable | I2C_CTL_ST_Start;  // Start transfer

    // Wait for transfer to complete
    while (!(i2c->STATUS & I2C_STAT_DONE_Done)) {
        if (i2c->STATUS & I2C_STAT_ERR_Error) return -2;  // ACK Error
        if (i2c->STATUS & I2C_STAT_CLKT_Error) return -3; // Clock stretch timeout
    }

    i2c->STATUS = I2C_STAT_DONE_Done;  // Clear DONE flag
    return 0;  // Success
}

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
int i2c_read(I2C_Controller_Index index, uint8_t slave_addr, uint8_t *buffer, uint32_t length)
{
    struct I2C_Registers *i2c;

    switch (index) {
        case I2C_CONTROLLER_0:
            i2c = BSC0_I2C;
            break;
        case I2C_CONTROLLER_1:
            i2c = BSC1_I2C;
            break;
        case I2C_CONTROLLER_2:
            i2c = BSC2_I2C;
            break;
        default:
            return -1;  // Invalid index
    }

    if (length == 0) return -1;  // Invalid data length

    i2c->CONTROL = I2C_CTL_CLEAR_ClearFifo;  // Clear FIFO
    i2c->STATUS = 0xFFFFFFFF;  // Clear status flags

    i2c->A = slave_addr;  // Set the slave address
    i2c->DLEN = length;   // Set data length

    i2c->CONTROL = I2C_CTL_I2CEN_Enable | I2C_CTL_ST_Start | I2C_CTL_READ_Read;  // Start transfer (Read)

    for (uint32_t i = 0; i < length; i++) {
        while (!(i2c->STATUS & I2C_STAT_RXD_Contains)) {
            if (i2c->STATUS & I2C_STAT_ERR_Error) return -2;  // ACK Error
            if (i2c->STATUS & I2C_STAT_CLKT_Error) return -3; // Clock stretch timeout
        }
        buffer[i] = i2c->FIFO;  // Read data from FIFO
    }

    while (!(i2c->STATUS & I2C_STAT_DONE_Done)) {
        if (i2c->STATUS & I2C_STAT_ERR_Error) return -2;
        if (i2c->STATUS & I2C_STAT_CLKT_Error) return -3;
    }

    i2c->STATUS = I2C_STAT_DONE_Done;  // Clear DONE flag
    return 0;  // Success
}
