#include "mm.h"


.section "text.boot"

.globl _start
_start:
    mrs x0, mpidr_el1       // 1. Load the value of the MPIDR_EL1 register into x0
    and x0, x0, #0xFF       // 2. Mask the lower 8 bits of x0 (MPIDR_EL1 value) to isolate the core ID
    cbz x0, master          // 3. If x0 is zero (indicating the master core), branch to the label 'master'
    b proc_hang             // 4. If x0 is not zero (indicating a non-master core), branch to 'proc_hang'

master:
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
