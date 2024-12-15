#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "motor.h"
#include "ultrasonic.h"
#include "LD.h"
#include "sound.h"
#include "led.h"
#include "stdio.h"

// Obstacle detection threshold in cm
#define OBSTACLE_DISTANCE_THRESHOLD 20.0
#define BUZZER_PIN 19

volatile float distance = 0.0; // Shared variable for distance

void car_task(void *pvParameters);
void distance_task(void *pvParameters);
void ldr_task(void *pvParameters);
void sound_task(void *pvParameters); 

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


int main() {
    stdio_init_all();

    // Initialize peripherals
    motor_init();
    init_ultrasonic();
    ldr_init();
    buzzer_init();
    sound_detector_init();
    led_init();

    // Create FreeRTOS tasks
    xTaskCreate(distance_task, "DistanceTask", 256, NULL, 1, NULL);
    xTaskCreate(car_task, "CarTask", 256, NULL, 1, NULL);
    xTaskCreate(ldr_task, "LDRTask", 256, NULL, 1, NULL);
    xTaskCreate(sound_task, "SoundTask", 256, NULL, 1, NULL);

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    while (1) {}
    return 0;
}

// Task to read distance and update shared variable
void distance_task(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(100); // Update every 100ms

    while (true) {
        distance = measure_distance();
        printf("Measured distance: %.2f cm\n", distance);
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}

// Task to control the car based on distance
void car_task(void *pvParameters) {
    while (true) {
        if (distance < OBSTACLE_DISTANCE_THRESHOLD && distance > 0) {
            // Stop and rotate the car if an obstacle is detected
         motor_control(200, false);
            printf("Obstacle detected! Stopping...\n");

        } else {
            // Move forward
            motor_control(200, true); // Forward at speed 200
            printf("Moving forward...\n");
        }

        vTaskDelay(pdMS_TO_TICKS(100)); // Update every 100ms
    }
}

void ldr_task(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(100);

    while (true) {
        if (is_light_detected()) {
           led_off(); 
        } else {
             led_on();
        }

        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}

void sound_task(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(100);

    while (true) {
        if (is_sound_detected()) {
            buzzer_on();
            printf("Sound detected: Buzzer ON\n");
            vTaskDelay(pdMS_TO_TICKS(100));
            buzzer_off();
            printf("Buzzer OFF\n");
        }

        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}