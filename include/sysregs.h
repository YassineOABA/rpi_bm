#ifndef _SYSREG_H_
#define _SYSREG_H_

#define BIT_0(x)                    (0 << x)
#define BIT_1(x)                    (1 << x)

#define SHIFT(v, p)                 ((v) << (p))



// Enable, Disable FPEN
#define CPACR_FPEN_DISABLE          SHIFT(3,20)
#define CPACR_FPEN_ENABLE           SHIFT(0,20)

// cpacr_el1 register conf
#define CPACR_EL1_VAL               (CPACR_FPEN_DISABLE)




// MMU Enable, Disable (bit 0)
#define SCTLR_MMU_DISABLE           BIT_0(0)
#define SCTLR_MMU_ENABLE            BIT_1(0)

// Data cache Enable, Disable (bit 2)
#define SCTLR_DATA_C_DISABLE        BIT_0(2)
#define SCTLR_DATA_C_ENABLE         BIT_1(2)

// Instruction cache Enable, Disable (bit 12)
#define SCTLR_INSTR_I_DISABLE       BIT_0(12)
#define SCTLR_INSTR_I_ENABLE        BIT_1(12)

// Endiannese conf for EL0
#define SCTLR_E0E_LITTLE            BIT_0(24)
#define SCTLR_E0E_BIG               BIT_1(24)

// Endiannese conf for EL1
#define SCTLR_E1E_LITTLE            BIT_0(25)
#define SCTLR_E1E_BIG               BIT_1(25)

// sctlr_el1 register config
#define SCTLR_EL1_VAL               (SCTLR_MMU_DISABLE | SCTLR_DATA_C_DISABLE | SCTLR_INSTR_I_DISABLE |  SCTLR_E1E_LITTLE)




// Enable Arch64
#define HCR_EL1_ARCH_32             BIT_0(31)
#define HCR_EL1_ARCH_64             BIT_1(31)

// hcr_el2 register conf
#define HCR_EL2_VAL                 (HCR_EL1_ARCH_64)




// Enable, Disable non secure bit
#define SCR_NS_DISABLE              BIT_0(0)
#define SCR_NS_ENABLE               BIT_1(0)

// Configure RW
#define SCR_RW_ARCH32               BIT_0(10)
#define SCR_RW_ARCH64               BIT_1(10)

// scr_el3 register conf
#define SCR_EL3_VAL                 (SCR_NS_ENABLE | SCR_RW_ARCH64)




// Select SP
#define SPSR_M_EL1h                 SHIFT(5,0)

// FIQ interrupt mask
#define SPSR_FIQ_F_MASK_ENABLE      BIT_0(6)
#define SPSR_FIQ_F_MASK_DISABLE     BIT_1(6)

// IRQ interrupt mask
#define SPSR_IRQ_I_MASK_ENABLE      BIT_0(7)
#define SPSR_IRQ_I_MASK_DISABLE     BIT_1(7)

// SError exception mask
#define SPSR_SER_A_MASK_ENABLE      BIT_0(8)
#define SPSR_SER_A_MASK_DISABLE     BIT_1(8)

// spsr_el3 register conf 
#define SPSR_EL3_VAL               (SPSR_M_EL1h | SPSR_FIQ_F_MASK_DISABLE | SPSR_IRQ_I_MASK_DISABLE | SPSR_SER_A_MASK_DISABLE)

#endif /* _SYSREG_H_ */