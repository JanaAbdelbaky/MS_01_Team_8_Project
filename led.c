#include "led.h"

// Initialize the LED pin
void led_init(void) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

// Turn the LED on
void led_on(void) {
    gpio_put(LED_PIN, 1);
}

// Turn the LED off
void led_off(void) {
    gpio_put(LED_PIN, 0);
}
