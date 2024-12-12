#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define TRIG_PIN 15 // GPIO pin for the Trigger
#define ECHO_PIN 14 // GPIO pin for the Echo

void init_ultrasonic() {
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_put(TRIG_PIN, 0);

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}

float measure_distance() {
    // Trigger a 10us pulse on the TRIG_PIN
    gpio_put(TRIG_PIN, 1);
    sleep_us(10);
    gpio_put(TRIG_PIN, 0);

    // Wait for the Echo pin to go HIGH
    while (gpio_get(ECHO_PIN) == 0)
        tight_loop_contents();

    // Record the start time
    uint64_t start_time = time_us_64();

    // Wait for the Echo pin to go LOW
    while (gpio_get(ECHO_PIN) == 1)
        tight_loop_contents();

    // Record the end time
    uint64_t end_time = time_us_64();

    // Calculate pulse duration
    uint64_t pulse_duration = end_time - start_time;

    // Convert to distance in cm (speed of sound = 34300 cm/s)
    float distance = (pulse_duration / 2.0) * 0.0343;

    return distance;
}
