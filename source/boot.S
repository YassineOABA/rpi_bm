/**
 * @file        boot.S
 * @brief       Bootloader assembly code.
 * @description This file contains the assembly code for the bootloader, responsible for 
 *              initializing the system and transitioning control to the kernel.
 * 
 * @version     1.0
 * @date        2024-12-06
 */





#include "mm.h"
#include "sysregs.h"

.section ".text.boot"

.globl _start
_start:
    mrs x0, mpidr_el1       // 1. Load the value of the MPIDR_EL1 register into x0
    and x0, x0, #0xFF       // 2. Mask the lower 8 bits of x0 (MPIDR_EL1 value) to isolate the core ID
    cbz x0, master          // 3. If x0 is zero (indicating the master core), branch to the label 'master'
    b proc_hang             // 4. If x0 is not zero (indicating a non-master core), branch to 'proc_hang'

master:
    ldr x0, =CPACR_EL1_VAL  // Load the value for configuring coprocessor access (e.g., SIMD, FP)
    msr cpacr_el1, x0       // Write the configuration to CPACR_EL1 (EL1 Coprocessor Access Control Register)

    ldr x0, =SCTLR_EL1_VAL  // Load the configuration value for System Control Register at EL1
    msr sctlr_el1, x0       // Write the value into SCTLR_EL1 (controls memory system settings like MMU, caches, etc.)

    ldr x0, =HCR_EL2_VAL    // Load the configuration value for HCR_EL2
    msr hcr_el2, x0         // Write the value into HCR_EL2 (Hypervisor Configuration Register for EL2 settings)

    ldr x0, =SCR_EL3_VAL    // Load the configuration value for SCR_EL3
    msr scr_el3, x0         // Write the value into SCR_EL3 (Secure Configuration Register for EL3 settings)

    ldr x0, =SPSR_EL3_VAL   // Load the configuration value for SPSR_EL3
    msr spsr_el3, x0        // Write the value into SPSR_EL3 (Saved Program Status Register for EL3)

    adr x0, el1_secure       // Load the address of the EL1 entry point into x0
    msr elr_el3, x0         // Write the EL1 entry point address into ELR_EL3 (Exception Link Register at EL3)

    eret                    // Execute the Exception Return instruction to transition to EL1                


el1_secure:
    adr x0, bss_begin       // 1. Load address of bss_begin into x0
    adr x1, bss_end         // 2. Load address of bss_end into x1
    sub x1, x1, x0          // 3. Calculate the size of the .bss section (bss_end - bss_begin)
    bl memzero              // 4. Call the memzero function to clear the .bss section

    mov sp, #LOW_MEMORY     // 5. Set the stack pointer (sp) to LOW_MEMORY address
    bl kernel_main          // 6. Branch to kernel_main (start the main kernel logic)
    b proc_hang             // 7. Infinite loop to hang the processor


proc_hang:
    wfe                     // Wait for an interrupt or event (low-power state)
    b proc_hang             // Loop back and keep waiting for the next event
