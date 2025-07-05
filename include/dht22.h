#ifndef DHT22_H
#define DHT22_H

#include <stdint.h>

// Error codes
#define DHT22_OK             0
#define DHT22_TIMEOUT_ERROR -1
#define DHT22_CHECKSUM_ERROR -2

// Function prototypes
extern void dht22_init(void); // Initialization function
extern int dht22_read(float *temperature, float *humidity); // Read function

#endif // DHT22_H
