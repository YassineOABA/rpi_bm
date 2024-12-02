#ifndef _MM_H_
#define _MM_H_

#define PAGE_SHIFT      12   // 4KB pages
#define TABLE_SHIFT     10  // Typically 10 for 64-bit ARMv8-A (could be 9 for 32-bit mode)
#define SECTION_SHIFT   (PAGE_SHIFT + TABLE_SHIFT)  // 12 + 10 = 22 for larger sections (or 21 for 2MB)

#define PAGE_SIZE       (1 << PAGE_SHIFT)         // 4KB
#define SECTION_SIZE    (1 << SECTION_SHIFT)   // 2MB or larger sections (may be 2MB or 16MB depending on configuration)

#define LOW_MEMORY      (2 * SECTION_SIZE)   // Typically 4MB for 2MB sections

#ifndef __ASSEMBLER__

#include <stdint.h>

extern void memzero(uint64_t src,  uint32_t n);

#endif

#endif /* _MM_H_ */