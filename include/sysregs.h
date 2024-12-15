/**
 * @file sysregs.h
 * @brief System Register Definitions and Macros for ARM Architecture.
 * 
 * This file contains macros for configuring and manipulating various 
 * system control registers (SCTLR, CPACR, HCR, SCR, SPSR, etc.) in the ARM 
 * architecture. These registers control features like the Memory Management Unit 
 * (MMU), data and instruction caches, exception levels, and security configuration.
 * 
 * These macros are designed to enable or disable various hardware features, 
 * set system control register values, and perform necessary shifts and bitwise 
 * operations to configure the system.
 */

#ifndef _SYSREG_H_
#define _SYSREG_H_

// Macro for setting a bit at position x
#define BIT_0(x)                    (0 << x)  // Set bit to 0 at position x
#define BIT_1(x)                    (1 << x)  // Set bit to 1 at position x

// Macro for shifting a value v by p positions
#define SHIFT(v, p)                 ((v) << (p)) // Shift value v by p positions

// Enable, Disable FPEN (Floating Point Exception)
#define CPACR_FPEN_DISABLE          SHIFT(3,20)  // Disable Floating Point Exception
#define CPACR_FPEN_ENABLE           SHIFT(0,20)  // Enable Floating Point Exception

// cpacr_el1 register configuration
#define CPACR_EL1_VAL               (CPACR_FPEN_DISABLE)  // Set the CPACR register value to disable FPEN

// MMU Enable, Disable (bit 0)
#define SCTLR_MMU_DISABLE           BIT_0(0)    // Disable MMU (Memory Management Unit)
#define SCTLR_MMU_ENABLE            BIT_1(0)    // Enable MMU

// Data cache Enable, Disable (bit 2)
#define SCTLR_DATA_C_DISABLE        BIT_0(2)    // Disable data cache
#define SCTLR_DATA_C_ENABLE         BIT_1(2)    // Enable data cache

// Instruction cache Enable, Disable (bit 12)
#define SCTLR_INSTR_I_DISABLE       BIT_0(12)   // Disable instruction cache
#define SCTLR_INSTR_I_ENABLE        BIT_1(12)   // Enable instruction cache

// Endianness configuration for EL0 (Exception Level 0)
#define SCTLR_E0E_LITTLE            BIT_0(24)   // Set Little-endian mode for EL0
#define SCTLR_E0E_BIG               BIT_1(24)   // Set Big-endian mode for EL0

// Endianness configuration for EL1 (Exception Level 1)
#define SCTLR_E1E_LITTLE            BIT_0(25)   // Set Little-endian mode for EL1
#define SCTLR_E1E_BIG               BIT_1(25)   // Set Big-endian mode for EL1

// sctlr_el1 register configuration
#define SCTLR_EL1_VAL               (SCTLR_MMU_DISABLE | SCTLR_DATA_C_DISABLE | SCTLR_INSTR_I_DISABLE | SCTLR_E1E_LITTLE)

// Enable Arch64 (Architecture 64-bit support)
#define HCR_EL1_ARCH_32             BIT_0(31)   // Set HCR to 32-bit architecture mode
#define HCR_EL1_ARCH_64             BIT_1(31)   // Set HCR to 64-bit architecture mode

// hcr_el2 register configuration
#define HCR_EL2_VAL                 (HCR_EL1_ARCH_64)  // Configure HCR for 64-bit architecture mode

// Enable, Disable non-secure bit in SCR (Secure Configuration Register)
#define SCR_NS_DISABLE              BIT_0(0)    // Disable non-secure state
#define SCR_NS_ENABLE               BIT_1(0)    // Enable non-secure state

// Configure RW (Read/Write mode) in SCR
#define SCR_RW_ARCH32               BIT_0(10)   // Configure SCR for 32-bit mode
#define SCR_RW_ARCH64               BIT_1(10)   // Configure SCR for 64-bit mode

// scr_el3 register configuration
#define SCR_EL3_VAL                 (SCR_NS_ENABLE | SCR_RW_ARCH64) // Enable non-secure mode and 64-bit mode

// Select Stack Pointer (SP) for exception handling
#define SPSR_M_EL1h                 SHIFT(5,0)  // Set SPSR mode to EL1h (hyp mode)

// FIQ interrupt mask configuration
#define SPSR_FIQ_F_MASK_ENABLE      BIT_0(6)    // Enable FIQ interrupt mask
#define SPSR_FIQ_F_MASK_DISABLE     BIT_1(6)    // Disable FIQ interrupt mask

// IRQ interrupt mask configuration
#define SPSR_IRQ_I_MASK_ENABLE      BIT_0(7)    // Enable IRQ interrupt mask
#define SPSR_IRQ_I_MASK_DISABLE     BIT_1(7)    // Disable IRQ interrupt mask

// SError exception mask configuration
#define SPSR_SER_A_MASK_ENABLE      BIT_0(8)    // Enable SError exception mask
#define SPSR_SER_A_MASK_DISABLE     BIT_1(8)    // Disable SError exception mask

// spsr_el3 register configuration
#define SPSR_EL3_VAL               (SPSR_M_EL1h | SPSR_FIQ_F_MASK_DISABLE | SPSR_IRQ_I_MASK_DISABLE | SPSR_SER_A_MASK_DISABLE)

#endif /* _SYSREG_H_ */
