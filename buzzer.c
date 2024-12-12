#include "buzzer.h"

// Initialize the buzzer pin
void buzzer_init(void) {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0); // Ensure the buzzer is off initially
    

}

// Turn the buzzer on
void buzzer_on(void) {
    gpio_put(BUZZER_PIN, 1);
}

// Turn the buzzer off
void buzzer_off(void) {
    gpio_put(BUZZER_PIN, 0);
}
