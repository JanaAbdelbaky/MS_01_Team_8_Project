#include "pico/stdlib.h"
#include "LD.h"
#include "led.h"
#include "motor.h"
#include "sound.h"
#include "ultrasonic.h"
#include "stdio.h"

// Define GPIO pins
#define BUZZER_PIN 19 // GPIO pin for the buzzer
#define OBJECT_DETECTION_THRESHOLD 10

// Function to initialize the buzzer
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

// Interrupt handler for sound detection
void sound_interrupt_handler(uint gpio, uint32_t events) {
    if (gpio == SOUND_DETECTOR_PIN) {
        printf("Sound detected on pin %d\n", gpio);
        buzzer_on();
        sleep_ms(100); // Keep buzzer on for 100ms
        buzzer_off();
    }
}

// Interrupt handler for ultrasonic detection
void ultrasonic_interrupt_handler(uint gpio, uint32_t events) {
    if (gpio == ECHO_PIN) {
        float distance = measure_distance();
        printf("Measured Distance: %.2f cm\n", distance);

        if (distance <= OBJECT_DETECTION_THRESHOLD) {
            // Stop the motors if an object is detected within the threshold
            motor_control(0, false);
        } else {
            // Resume motor movement (e.g., forward at moderate speed)
            motor_control(128, true); // Forward with speed 128 (50% duty cycle)
        }
    }
}

int main() {
    stdio_init_all();

    // Initialize modules
    init_ultrasonic();
    motor_init();
    buzzer_init();
    sound_detector_init();

    // Set up interrupts
    gpio_set_irq_enabled_with_callback(SOUND_DETECTOR_PIN, GPIO_IRQ_EDGE_RISE, true, sound_interrupt_handler);
    gpio_set_irq_enabled_with_callback(ECHO_PIN, GPIO_IRQ_EDGE_RISE, true, ultrasonic_interrupt_handler);

    while (true) {
        // Main loop can perform other tasks or simply wait
        tight_loop_contents(); // Efficient idle waiting

        motor_control(128, true); // Forward with speed 128 (50% duty cycle)
    }

    return 0;
}
