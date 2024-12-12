#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Define the GPIO pins for the Trigger and Echo
#define TRIG_PIN 6 // GPIO pin for the Trigger
#define ECHO_PIN 7 // GPIO pin for the Echo  



// Function to initialize the ultrasonic sensor
void init_ultrasonic(void);

// Function to measure the distance (in cm) using the ultrasonic sensor
float measure_distance(void);

#endif