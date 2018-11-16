#ifndef DEBUG_H
#define DEBUG_H

//##################### DEBUG ######################
//#define DEBUG_MOTORS      1
//#define DEBUG_SERVOS      1
//#define DEBUG_RADIO       1
//#define DEBUG_COMPASS     1
//#define DEBUG_PID         1
//##################################################

//#################### PIN MAP #####################

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

//The following pins should be changed

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

//Magnetometer
#define SDA                 20
#define SCL                 21

//Radio
#define RADIO_SIG_I         8

#endif
//##################################################

//#################### TIMERS ######################
#define MOTOR_DELAY         1
#define PID_DELAY           1
#define RADIO_DELAY         1
//##################################################

//################# COMMUNICATION ##################
#define SERIAL_BAUDRATE 115200
//##################################################

//################# PLATFORM SETTINGS ##############
//States
#define IDLE 0
#define MANUAL 1
#define AUTOMATIC 2
#define MISSION 3
#define RADIO 4
#define START_STATE IDLE
//##################################################

//################# PID VALUES #####################

#define KP_ROT 0.05
#define KI_ROT 0
#define KD_ROT 0.01

//##################################################



#endif