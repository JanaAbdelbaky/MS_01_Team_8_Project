#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

// Define the buzzer pin
#define BUZZER_PIN 19 // Replace 15 with the GPIO pin connected to the buzzer

// Function declarations
void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);

#endif // BUZZER_H
