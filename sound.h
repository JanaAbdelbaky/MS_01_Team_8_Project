#ifndef SOUND_DETECTOR_H
#define SOUND_DETECTOR_H
#include "hardware/gpio.h"

#include "pico/stdlib.h"

// GPIO pin connected to the sound detector's digital output
#define SOUND_DETECTOR_PIN 18 // Change to the GPIO pin you're using
#define BUZZER_PIN 19  

// Function to initialize the sound detector
void sound_detector_init(void);

// Function to check if sound is detected
bool is_sound_detected(void);  

//void sound_interrupt_handler(uint gpio, uint32_t events);




#endif

