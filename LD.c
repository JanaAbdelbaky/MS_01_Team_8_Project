#include "LD.h"

void ldr_init(void) {
    gpio_init(LDR_gpio_PIN);   
    gpio_set_dir(LDR_gpio_PIN, GPIO_IN); 
          
}

bool is_light_detected(void) {
    return gpio_get(LDR_gpio_PIN) == 0; 
}


