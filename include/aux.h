#ifndef _AUX_H_
#define _AUX_H_

#include <stdint.h>
#include "base.h"

// Base address for auxiliary peripherals
#define AUX_BASE       (uint32_t)(PIBASE + 0x00215000)

// Auxiliary Interrupt Register
#define AUX_IRQ        ((volatile uint32_t *)(AUX_BASE + 0x0000)) // 3 bytes
#define AUX_IRQ_MASK   0x00000007 // Mask for interrupt status (3 bits)

// Auxiliary Enables Register
#define AUX_ENABLES     ((volatile uint32_t *)(AUX_BASE + 0x0004)) // 3 bytes
#define AUX_ENABLES_MASK 0x00000007 // Mask for auxiliary enables (3 bits)

// Mini UART Registers
#define AUX_MU_IO_REG        ((volatile uint32_t *)(AUX_BASE + 0x0040)) // I/O data register
#define AUX_MU_IER_REG       ((volatile uint32_t *)(AUX_BASE + 0x0044)) // Interrupt Enable register
#define AUX_MU_IIR_REG       ((volatile uint32_t *)(AUX_BASE + 0x0048)) // Interrupt Identification register
#define AUX_MU_LCR_REG       ((volatile uint32_t *)(AUX_BASE + 0x004C)) // Line Control register
#define AUX_MU_MCR_REG       ((volatile uint32_t *)(AUX_BASE + 0x0050)) // Modem Control register
#define AUX_MU_LSR_REG       ((volatile uint32_t *)(AUX_BASE + 0x0054)) // Line Status register
#define AUX_MU_MSR_REG       ((volatile uint32_t *)(AUX_BASE + 0x0058)) // Modem Status register
#define AUX_MU_SCRATCH_REG   ((volatile uint32_t *)(AUX_BASE + 0x005C)) // Scratch register
#define AUX_MU_CNTL_REG      ((volatile uint32_t *)(AUX_BASE + 0x0060)) // Extra Control register
#define AUX_MU_STAT_REG      ((volatile uint32_t *)(AUX_BASE + 0x0064)) // Extra Status register
#define AUX_MU_BAUD_REG      ((volatile uint32_t *)(AUX_BASE + 0x0068)) // Baudrate register

// SPI 1 Registers
#define AUX_SPI0_CNTL0_REG   ((volatile uint32_t *)(AUX_BASE + 0x0080)) // SPI 1 Control register 0
#define AUX_SPI0_CNTL1_REG   ((volatile uint32_t *)(AUX_BASE + 0x0084)) // SPI 1 Control register 1
#define AUX_SPI0_STAT_REG    ((volatile uint32_t *)(AUX_BASE + 0x0088)) // SPI 1 Status register
#define AUX_SPI0_IO_REG      ((volatile uint32_t *)(AUX_BASE + 0x0090)) // SPI 1 Data register
#define AUX_SPI0_PEEK_REG    ((volatile uint32_t *)(AUX_BASE + 0x0094)) // SPI 1 Peek register

// SPI 2 Registers
#define AUX_SPI1_CNTL0_REG   ((volatile uint32_t *)(AUX_BASE + 0x00C0)) // SPI 2 Control register 0
#define AUX_SPI1_CNTL1_REG   ((volatile uint32_t *)(AUX_BASE + 0x00C4)) // SPI 2 Control register 1
#define AUX_SPI1_STAT_REG    ((volatile uint32_t *)(AUX_BASE + 0x00C8)) // SPI 2 Status register
#define AUX_SPI1_IO_REG      ((volatile uint32_t *)(AUX_BASE + 0x00D0)) // SPI 2 Data register
#define AUX_SPI1_PEEK_REG    ((volatile uint32_t *)(AUX_BASE + 0x00D4)) // SPI 2 Peek register

#endif // _AUX_H_
