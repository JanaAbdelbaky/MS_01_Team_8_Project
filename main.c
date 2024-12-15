#include <FreeRTOS.h>
#include <task.h>
#include "LD.h"
#include "led.h"
#include "motor.h"
#include "sound.h"
#include "ultrasonic.h"
#include "buzzer.h"

// Task priorities
#define ULTRASONIC_TASK_PRIORITY 2
#define LIGHT_TASK_PRIORITY 2
#define SOUND_TASK_PRIORITY 2

// Task stack sizes
#define TASK_STACK_SIZE 256

// Task prototypes
void ultrasonic_task(void *pvParameters);
void light_task(void *pvParameters);
void sound_task(void *pvParameters);

int main() {
    // Initialize all peripherals
    ldr_init();
    led_init();
    motor_init();
    sound_detector_init();
    init_ultrasonic();
    buzzer_init();

    // Create tasks
    xTaskCreate(ultrasonic_task, "Ultrasonic Task", TASK_STACK_SIZE, NULL, ULTRASONIC_TASK_PRIORITY, NULL);
    xTaskCreate(light_task, "Light Task", TASK_STACK_SIZE, NULL, LIGHT_TASK_PRIORITY, NULL);
    xTaskCreate(sound_task, "Sound Task", TASK_STACK_SIZE, NULL, SOUND_TASK_PRIORITY, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // The program should never reach here
    while (1) {
        // Infinite loop as a failsafe
    }

    return 0;
}

// Ultrasonic task
void ultrasonic_task(void *pvParameters) {
    while (1) {
        float distance = measure_distance();
        if (distance < 10.0) { // Adjust threshold as needed
            motor_control(50, false); // Move backward with speed 50
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Check every 100ms
    }
}

// Light task
void light_task(void *pvParameters) {
    while (1) {
        if (is_light_detected()) {
            led_off(); // Turn off LED if light is detected
        } else {
            led_on(); // Turn on LED if no light is detected
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Check every 100ms
    }
}

// Sound task
void sound_task(void *pvParameters) {
    while (1) {
        if (is_sound_detected()) {
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(100));
            buzzer_off();

        } else {
            buzzer_off(); // Turn off buzzer if no sound is detected
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Check every 100ms
    }
}
