#include "motor.h"

void motor_init(void) {
    // Initialize Motor 1 Direction Pins
    gpio_init(MOTOR1_DIR_PIN1);
    gpio_set_dir(MOTOR1_DIR_PIN1, GPIO_OUT); // Set direction pin as output
    gpio_init(MOTOR1_DIR_PIN2);
    gpio_set_dir(MOTOR1_DIR_PIN2, GPIO_OUT); // Set direction pin as output 

    // Initialize Motor 2 Direction Pins
    gpio_init(MOTOR2_DIR_PIN1);
    gpio_set_dir(MOTOR2_DIR_PIN1, GPIO_OUT); // Set direction pin as output
    gpio_init(MOTOR2_DIR_PIN2);
    gpio_set_dir(MOTOR2_DIR_PIN2, GPIO_OUT); // Set direction pin as output  

    // Initialize PWM for Motor 1 and Motor 2
    gpio_set_function(MOTOR1_PWM_PIN, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR2_PWM_PIN, GPIO_FUNC_PWM);

    // Get slice number for PWM pins
    uint slice_num1 = pwm_gpio_to_slice_num(MOTOR1_PWM_PIN);
    uint slice_num2 = pwm_gpio_to_slice_num(MOTOR2_PWM_PIN); 

    // Set PWM range (0 to 255 for 8-bit resolution)
    pwm_set_wrap(slice_num1, 255);
    pwm_set_wrap(slice_num2, 255);

    // Set PWM clock divider for speed control
    pwm_set_clkdiv(slice_num1, 4.0f); // Adjust as needed
    pwm_set_clkdiv(slice_num2, 4.0f);  

    // Enable PWM output for both motors
    pwm_set_enabled(slice_num1, true);
    pwm_set_enabled(slice_num2, true);

    // Add debugging: print to check motor initialization
    //printf("Motor pins initialized\n");
}


void motor_control(uint16_t speed, bool forward) {
    if (speed > 255) speed = 255;  // Cap speed to 255

    if (forward) {
        // Move forward
        gpio_put(MOTOR1_DIR_PIN1, 1);
        gpio_put(MOTOR1_DIR_PIN2, 0);

        gpio_put(MOTOR2_DIR_PIN1, 1);
        gpio_put(MOTOR2_DIR_PIN2, 0);
    } else {
        // Reverse direction
        gpio_put(MOTOR1_DIR_PIN1, 0);
        gpio_put(MOTOR1_DIR_PIN2, 0);

        gpio_put(MOTOR2_DIR_PIN1, 0);
        gpio_put(MOTOR2_DIR_PIN2, 0);
    }

    // Set the PWM duty cycle based on the speed
    pwm_set_gpio_level(MOTOR1_PWM_PIN, speed);
    pwm_set_gpio_level(MOTOR2_PWM_PIN, speed);

    // Add debugging to confirm motor control
    //printf("Motor speed: %d, Forward: %d\n", speed, forward);
}


// void motor_set_speed(uint motor, float speed) {
//     uint pwm_pin, dir_pin1,dir_pin2;

//     // Determine motor pins
//     if (motor == 1) {
//         pwm_pin = MOTOR1_PWM_PIN;
//         dir_pin1 = MOTOR1_DIR_PIN1;
//         dir_pin2 = MOTOR1_DIR_PIN2;
//     } else if (motor == 2) {
//         pwm_pin = MOTOR2_PWM_PIN;
//         dir_pin1 = MOTOR2_DIR_PIN1;
//         dir_pin2 = MOTOR2_DIR_PIN2;
//     } else {
//         return; // Invalid motor number
//     }

//     // Set direction based on speed
//     if (speed < 0) {
//         gpio_put(dir_pin1, 1);
//         gpio_put(dir_pin2,0); // Reverse direction
//         speed = -speed;       // Make speed positive
//     } else {
//         gpio_put(dir_pin1, 0);
//         gpio_put(dir_pin2,1);
//          // Forward direction
//     }

//     // Set PWM duty cycle (0 to 255)
//     uint slice_num = pwm_gpio_to_slice_num(pwm_pin);
//     pwm_set_gpio_level(pwm_pin, speed); // Scale speed (0-1) to 0-255
// }

void motor_stop() {
        gpio_put(MOTOR1_DIR_PIN1, 0);
        gpio_put(MOTOR1_DIR_PIN2, 0);

        gpio_put(MOTOR2_DIR_PIN1, 0);
        gpio_put(MOTOR2_DIR_PIN2, 0);
}
