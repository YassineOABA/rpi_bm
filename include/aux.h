/**
 * @file        aux.h
 * @brief       Auxiliary register definitions for the Raspberry Pi.
 * @description This header contains definitions and macros for working with auxiliary peripherals 
 *              on the Raspberry Pi, such as the mini UART and SPI controllers.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#ifndef _AUX_H_
#define _AUX_H_

#include <stdint.h>
#include "base.h"

// Base address for auxiliary peripherals
#define AUX_BASE_ADDRESS    (PIBASE + 0x00215000)

// Defines the AUX (Auxiliary) peripheral register structure.
// This structure represents the memory-mapped registers used for auxiliary functions
// such as UART communication or SPI interfaces on the hardware.
struct AUX_Registers {
    volatile uint32_t IRQ;                // 0x7E21 5000 - Auxiliary Interrupt
    volatile uint32_t ENABLES;            // 0x7E21 5004 - Auxiliary enables
    volatile uint32_t reserved1[14];      // Reserved (0x7E21 5008 - 0x7E21 503C)

    // Mini UART Registers
    volatile uint32_t MU_IO_REG;          // 0x7E21 5040 - Mini UART I/O Data
    volatile uint32_t MU_IER_REG;         // 0x7E21 5044 - Mini UART Interrupt Enable
    volatile uint32_t MU_IIR_REG;         // 0x7E21 5048 - Mini UART Interrupt Identify
    volatile uint32_t MU_LCR_REG;         // 0x7E21 504C - Mini UART Line Control
    volatile uint32_t MU_MCR_REG;         // 0x7E21 5050 - Mini UART Modem Control
    volatile uint32_t MU_LSR_REG;         // 0x7E21 5054 - Mini UART Line Status
    volatile uint32_t MU_MSR_REG;         // 0x7E21 5058 - Mini UART Modem Status
    volatile uint32_t MU_SCRATCH;         // 0x7E21 505C - Mini UART Scratch
    volatile uint32_t MU_CNTL_REG;        // 0x7E21 5060 - Mini UART Extra Control
    volatile uint32_t MU_STAT_REG;        // 0x7E21 5064 - Mini UART Extra Status
    volatile uint32_t MU_BAUD_REG;        // 0x7E21 5068 - Mini UART Baudrate
    volatile uint32_t reserved2[5];       // Reserved (0x7E21 506C - 0x7E21 507C)

    // SPI 1 Registers
    volatile uint32_t SPI0_CNTL0_REG;     // 0x7E21 5080 - SPI 1 Control Register 0
    volatile uint32_t SPI0_CNTL1_REG;     // 0x7E21 5084 - SPI 1 Control Register 1
    volatile uint32_t SPI0_STAT_REG;      // 0x7E21 5088 - SPI 1 Status
    volatile uint32_t SPI0_IO_REG;        // 0x7E21 508C - SPI 1 Data
    volatile uint32_t SPI0_PEEK_REG;      // 0x7E21 5090 - SPI 1 Peek
    volatile uint32_t reserved3[11];      // Reserved (0x7E21 5094 - 0x7E21 50BC)

    // SPI 2 Registers
    volatile uint32_t SPI1_CNTL0_REG;     // 0x7E21 50C0 - SPI 2 Control Register 0
    volatile uint32_t SPI1_CNTL1_REG;     // 0x7E21 50C4 - SPI 2 Control Register 1
    volatile uint32_t SPI1_STAT_REG;      // 0x7E21 50C8 - SPI 2 Status
    volatile uint32_t reserved4[2];       // Reserved (0x7E21 50CC - 0x7E21 50D0)
    volatile uint32_t SPI1_IO_REG;        // 0x7E21 50D0 - SPI 2 Data
    volatile uint32_t SPI1_PEEK_REG;      // 0x7E21 50D4 - SPI 2 Peek
};

// Define AUX as a pointer to the AUX_Registers structure.
// This macro allows easy access to the auxiliary peripheral registers through a structured pointer.
// AUX_BASE_ADDRESS should be defined elsewhere as the base address of the AUX peripheral in memory.
#define AUX ((struct AUX_Registers *)(AUX_BASE_ADDRESS))

#endif // _AUX_H_
