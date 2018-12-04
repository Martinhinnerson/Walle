#ifndef DEBUG_H
#define DEBUG_H

// =============================================================================
// Debug
// =============================================================================
//#define DEBUG_MOTORS      1
//#define DEBUG_SERVOS      1
//#define DEBUG_RADIO       1
//#define DEBUG_COMPASS     1
//#define DEBUG_PID         1

// =============================================================================
// Pin map
// =============================================================================

// If Arduino UNO is used
#if defined (__AVR_ATmega328P__) // Arduino UNO

//Motor1
#define PWM_PIN_1           3
#define DIR1_PIN_1          2
#define DIR2_PIN_1          4
#define HALL_PIN_1          A1

//Motor2
#define PWM_PIN_2           6
#define DIR1_PIN_2          7
#define DIR2_PIN_2          5
#define HALL_PIN_2          A0

//Radio
#define RADIO_SIG_I         8

// If Arduino MEGA is used
#elif defined (__AVR_ATmega2560__) //Arduino MEGA

//TODO: The following pins should be changed depending on what we use for the MEGA
//Note that pin 2-13 is PWM pins and should probably not be used for pins that won't need PWM

//Motor1
#define PWM_PIN_1           4
#define DIR1_PIN_1          5
#define DIR2_PIN_1          6
#define HALL_PIN_1          A1

//Motor2
#define PWM_PIN_2           8
#define DIR1_PIN_2          9
#define DIR2_PIN_2          10
#define HALL_PIN_2          A0

//Magnetometer
#define SDA                 20
#define SCL                 21

//Radio
#define RADIO_SIG_I         11

//Stepper Motor
#define STEPPER_PIN_1       26
#define STEPPER_PIN_2       24
#define STEPPER_PIN_3       32
#define STEPPER_PIN_4       30
#define STEPPER_ENABLE      22
#define STEPPER_ENABLE_2    28

#endif

// =============================================================================
// Timers
// =============================================================================
#define MOTOR_DELAY         100
#define PID_DELAY           100
#define RADIO_DELAY         100

// =============================================================================
// Communication
// =============================================================================
#define DEBUG_SERIAL_BAUDRATE   9600
#define MAIN_SERIAL_BAUDRATE    9600

#define MAX_INPUT_SIZE          30
#define SERIAL_SPLIT_CHAR       '|'

#define COMMAND                 0
#define SENSORVAL               1

// =============================================================================
// Platform settings
// =============================================================================

#define IDLE        0
#define MANUAL      1
#define AUTOMATIC   2
#define MISSION     3
#define RADIO       4
#define STEPPER     5
#define START_STATE STEPPER

// =============================================================================
// PID values
// =============================================================================
#define KP_ROT 0.05
#define KI_ROT 0
#define KD_ROT 0.01

// =============================================================================
// Stepper settings
// =============================================================================
#define STEPPER_SPEED       100
#define STEPPER_ACCEL       10

#define STEPS_PER_REV       200

// =============================================================================
// Motor settings
// =============================================================================
#define MOTOR_DEADBAND      0.05
#define PWM_MIN             50
#define PWM_MAX             255

#endif