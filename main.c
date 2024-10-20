

#include <stdio.h>
#include "pico/stdlib.h"

// Define the pin numbers for the LEDs
const uint RED_LED_PIN = 14;    // Pin for Red LED
const uint GREEN_LED_PIN = 15;  // Pin for Green LED
const uint BLUE_LED_PIN = 13;   // Pin for Blue LED

void setup() {
    // Initialize the LED pins
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    
    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
    
    // Initialize chosen serial port
    stdio_init_all();
}

void loop() {
    // Step 1: Wait for the first 5 seconds with all LEDs off
    gpio_put(RED_LED_PIN, false);
    gpio_put(GREEN_LED_PIN, false);
    gpio_put(BLUE_LED_PIN, false);
    sleep_ms(5000); // Delay for 5 seconds

    // Step 2: Sequence to turn on each LED for 1 second
    // Turn on Red LED
    gpio_put(RED_LED_PIN, true);
    sleep_ms(1000); // Wait for 1 second
    gpio_put(RED_LED_PIN, false);

    // Turn on Green LED
    gpio_put(GREEN_LED_PIN, true);
    sleep_ms(1000); // Wait for 1 second
    gpio_put(GREEN_LED_PIN, false);

    // Turn on Blue LED
    gpio_put(BLUE_LED_PIN, true);
    sleep_ms(1000); // Wait for 1 second
    gpio_put(BLUE_LED_PIN, false);

    // Step 3: Turn on all LEDs together for 2 seconds
    gpio_put(RED_LED_PIN, true);
    gpio_put(GREEN_LED_PIN, true);
    gpio_put(BLUE_LED_PIN, true);
    sleep_ms(2000); // Wait for 2 seconds

    // Turn off all LEDs
    gpio_put(RED_LED_PIN, false);
    gpio_put(GREEN_LED_PIN, false);
    gpio_put(BLUE_LED_PIN, false);
}

int main() {
    setup(); // Call setup function to initialize LEDs

    // Loop continuously
    while (true) {
        loop(); // Execute the LED control sequence
    }
}