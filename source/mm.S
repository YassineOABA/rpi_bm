.globl memzero
memzero:
    str xzr, [x0], #8    // 1. Store zero into memory, increment address by 8 bytes
    subs x1, x1, #8      // 2. Subtract 8 from x1 and set flags
    b.gt memzero         // 3. If x1 > 0, branch back to memzero
    ret                  // 4. Return from function