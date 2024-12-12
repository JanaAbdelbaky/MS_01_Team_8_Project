#ifndef LD_H
#define LD_H

#include "pico/stdlib.h"


#define LDR_gpio_PIN 17




// Function to initialize the ADC for the LDR module
void ldr_init(void);

// Function to read the light intensity as a voltage
bool is_light_detected(void) ;

//void check_light_and_control_led(void);


#endif
