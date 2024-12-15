#include "sound.h"

void sound_detector_init(void) {
    gpio_init(SOUND_DETECTOR_PIN);   // Initialize the GPIO pin
    gpio_set_dir(SOUND_DETECTOR_PIN, GPIO_IN); // Set the pin as input
    //gpio_pull_up(SOUND_DETECTOR_PIN); // Enable pull-up resistor

    // Configure interrupt for the sound detector pin
    //gpio_set_irq_enabled_with_callback(SOUND_DETECTOR_PIN, GPIO_IRQ_EDGE_RISE, true, sound_interrupt_handler);
}


bool is_sound_detected(void) {
    return gpio_get(SOUND_DETECTOR_PIN) == 1; // Return true if sound detected (LOW)
} 

// void sound_interrupt_handler(uint gpio, uint32_t events) {
//     if (gpio == SOUND_DETECTOR_PIN) {
//         buzzer_on();    // Turn on the buzzer
//         sleep_ms(500);  // Keep the buzzer on for 500ms
//         buzzer_off();   // Turn off the buzzer
//     }
// }