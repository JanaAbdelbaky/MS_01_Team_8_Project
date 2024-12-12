#ifndef MOTOR_H
#define MOTOR_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Motor control pin definitions (Update these based on your wiring)
#define MOTOR1_PWM_PIN 1  // PWM pin for Motor 1 speed
#define MOTOR1_DIR_PIN1 3  // Direction pin for Motor 1
#define MOTOR1_DIR_PIN2 4

#define MOTOR2_PWM_PIN 2  // PWM pin for Motor 2 speed
#define MOTOR2_DIR_PIN1 8  // Direction pin for Motor 2
#define MOTOR2_DIR_PIN2 9

// Function prototypes
void motor_init(void);
void motor_control(uint16_t speed, bool forward);
//void motor_set_speed(uint motor, float speed); // Set speed (-1.0 to 1.0)
void motor_stop();

#endif 