#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

// Define the LED pin
#define LED_PIN 13 // Replace 25 with your specific LED GPIO pin if different

// Function declarations
void led_init(void);
void led_on(void);
void led_off(void);

#endif // LED_H
