#include "dht22.h"
#include "gpio.h"     // Replace with your platform's GPIO library
#include "timer.h"    // Replace with your platform's delay/timer library
#include "uart_printf.h" // For debugging messages

#define DHT22_PIN          6  // Adjust based on your configuration
#define DHT22_MAX_TIMINGS  100
#define MAX_RETRIES        3

/**
 * @brief Initializes the DHT22 sensor module.
 * 
 * This function configures the GPIO pin connected to the DHT22 sensor as an
 * input/output pin. It should be called once during system initialization.
 */
void dht22_init(void)
{
    // Configure the GPIO pin as output initially to send the start signal
    gpio_set_pin_function(DHT22_PIN, GPIO_OUTPUT);
    gpio_pull_up_down(DHT22_PIN, GPIO_PUD_UP);
    gpio_set_pin(DHT22_PIN); // Set the pin high (idle state)

    // Optionally, add a delay to stabilize the sensor after power-up
    delay_micro_s(2000000); // Wait for the DHT22 to stabilize (recommended 2 seconds)
}

/**
 * @brief Reads temperature and humidity from the DHT22 sensor.
 * 
 * This function communicates with the DHT22 sensor to retrieve temperature
 * and humidity values. It handles the sensor's communication protocol,
 * including sending the start signal, reading the response, and verifying
 * the checksum.
 * 
 * @param[out] temperature Pointer to store the temperature value.
 * @param[out] humidity Pointer to store the humidity value.
 * 
 * @return int Status code (DHT22_OK, DHT22_TIMEOUT_ERROR, DHT22_CHECKSUM_ERROR).
 */
int dht22_read(float *temperature, float *humidity)
{
    uint8_t data[5] = {0};
    uint32_t last_state = 1;
    uint32_t count = 0;

    for (int attempt = 0; attempt < MAX_RETRIES; attempt++) {
        // Pull the line low to send start signal
        gpio_set_pin_function(DHT22_PIN, GPIO_OUTPUT);
        gpio_clear_pin(DHT22_PIN);
        delay_micro_s(18000); // Keep the line low for at least 18ms

        // Pull the line high and wait briefly
        gpio_set_pin(DHT22_PIN);
        delay_micro_s(30);

        // Set the pin to input mode to read the response
        gpio_set_pin_function(DHT22_PIN, GPIO_INPUT);

        // Read the response signal and data
        for (uint32_t i = 0; i < DHT22_MAX_TIMINGS; i++) {
            count = 0;
            while (gpio_read_pin(DHT22_PIN) == last_state) {
                count++;
                delay_micro_s(1);
                if (count > 255) {
                    uart_printf("Timing error at index %d, Count %d, Last State %d\n", i, count, last_state);
                    return DHT22_TIMEOUT_ERROR;
                }
            }
            last_state = gpio_read_pin(DHT22_PIN);

            // Skip the first 3 transitions (response signal)
            if ((i >= 4) && (i % 2 == 0)) {
                data[(i - 4) / 16] <<= 1;
                if (count > 50) {
                    data[(i - 4) / 16] |= 1;
                }
            }
        }

        // Verify the checksum
        uint8_t checksum = data[0] + data[1] + data[2] + data[3];
        if (checksum != data[4]) {
            uart_printf("Checksum error: Expected %d, Got %d\n", checksum, data[4]);
            continue; // Retry on checksum error
        }

        // Convert data to temperature and humidity
        *humidity = ((data[0] << 8) | data[1]) / 10.0;
        *temperature = ((data[2] & 0x7F) << 8 | data[3]) / 10.0;
        if (data[2] & 0x80) {
            *temperature *= -1.0; // Negative temperature
        }

        return DHT22_OK; // Success
    }

    return DHT22_TIMEOUT_ERROR; // Failed after retries
}
