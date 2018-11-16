#include <Arduino.h>
#include "platform.h"

//Constructor
Platform::Platform()
{
    _speed = 0;
    _direction = 0;
    _heading = 0;
    _x = 0;
    _y = 0;
    _mode = START_STATE;

    rotationPID = PID(KP_ROT, KI_ROT, KD_ROT); //Kp Ki Kd

    rightMotor = Motor::Motor(PWM_PIN_1, DIR1_PIN_1, DIR2_PIN_1, HALL_PIN_1, 1);
    leftMotor = Motor::Motor(PWM_PIN_2, DIR1_PIN_2, DIR2_PIN_2, HALL_PIN_2, 0);
    radioInput = Radio::Radio();
    compass = Adafruit_HMC5883_Unified(12345);

    //motorTimer.setTimer(MOTOR_DELAY);
    //PIDTimer.setTimer(PID_DELAY);
    //radioTimer.setTimer(RADIO_DELAY);
}

void Platform::begin()
{
    //DebugSerial->begin(SERIAL_BAUDRATE);

    //DebugSerial->println("Initializing Walle...");
    //delay(100);

    /* Initialise the sensor */
    if (!compass.begin())
    {
        /* There was a problem detecting the HMC5883 ... check your connections */
        Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
        while (1);
    }
    if (rotationPID.err())
    {
        Serial.println("There was a configuration error with the rotationPID");
        while (1);
    }
    
    CPPM.begin();
    
}

/*
 * run()
 * 
 * This function is the main function of the platform and it should be run in loop()
 * Every loop it checks if a timer has passed and if it has it runs its corresponding functions
 * We can also add things without timers that should run all the time. (16Mhz)
 * 
 * Here we also have the state machine controlling the different modes of the platform
 * 
 * Inputs: none
 * Outputs: none
 */
void Platform::run(){

    switch(_mode){
        case IDLE:
            Serial.println("State = Idle");
            delay(1000);

        break;
        case MANUAL:
            if(motorTimer.check()){
                mapToMotors();
                runMotors();
            }
        break;
        case AUTOMATIC:

            if(motorTimer.check()){
                mapToMotors();
                runMotors();
            }
            if(PIDTimer.check()){
                //run PID loop
            }

        break;
        case MISSION:

        break;
        case RADIO:
            
            if(radioTimer.check()){
                readFromRadio();
            }
            if(motorTimer.check()){
                mapToMotors();
                runMotors();
            }

        break;
        default:
            Serial.println("Error, this state does not exist. Going back to idle.");
            _mode = IDLE;
        break;
    }

}

void Platform::setSpeed(double speed)
{
    _speed = speed;
}
double Platform::getSpeed()
{
    return _speed;
}
void Platform::setDirection(int direction)
{
    _direction = direction;
}
int Platform::getDirection()
{
    return _direction;
}

void Platform::setMode(int mode){
    _mode = mode;
}

int Platform::getMode(){
    return _mode;
}

//Run the motors with their set speed
void Platform::runMotors()
{
    rightMotor.runMotor();
    leftMotor.runMotor();
}

//Read the values from the radio reciever and store them to _x, _y
void Platform::readFromRadio()
{
    radioInput.updateRadio();
    //Map to -1, 1
    _x = double(map(radioInput.getJoysticX(), -514, 514, -100, 100)) / 100;
    _y = double(map(radioInput.getJoysticY(), -514, 514, -100, 100)) / 100;
}

//Map x and y to the motors
void Platform::mapToMotors()
{
    //Convert to polar
    double r = hypot(_y, _x);
    double t = atan2(_y, _x);

    //rotate by 45 degrees
    t -= 3.14 / 4;

    //convert back to cartesian
    double left = r * cos(t);
    double right = r * sin(t);

    //rescale the new coordinates
    left = left * sqrt(2);
    right = right * sqrt(2);

    //Clamp to -1/+1
    left = max(-1, min(left, 1));
    right = max(-1, min(right, 1));

    leftMotor.setSpeed(left);
    rightMotor.setSpeed(right);

#ifdef DEBUG_MOTORS
    Serial.print("Mapped: ");
    Serial.print(_y);
    Serial.print(", ");
    Serial.println(_x);
    Serial.print("Radius and angle: ");
    Serial.print(r);
    Serial.print(", ");
    Serial.println(t);
    Serial.print("Left: ");
    Serial.print(left);
    Serial.print(", ");
    Serial.print("Right: ");
    Serial.println(right);
#endif
}

int Platform::getHeading()
{
    /* Get a new sensor event */
    sensors_event_t event;
    compass.getEvent(&event);

    // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
    // Calculate heading when the magnetometer is level, then correct for signs of axis.
    float heading = atan2(event.magnetic.y, event.magnetic.x);

    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
    float declinationAngle = 0.089;
    heading += declinationAngle;

    // Correct for when signs are reversed.
    if (heading < 0)
        heading += 2 * PI;

    // Check for wrap due to addition of declination.
    if (heading > 2 * PI)
        heading -= 2 * PI;

    // Convert radians to degrees for readability.
    int headingDegrees = heading * 180 / M_PI;

#ifdef DEBUG_COMPASS
    /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
    Serial.print("X: ");
    Serial.print(event.magnetic.x);
    Serial.print("  ");
    Serial.print("Y: ");
    Serial.print(event.magnetic.y);
    Serial.print("  ");
    Serial.print("Z: ");
    Serial.print(event.magnetic.z);
    Serial.print("  ");
    Serial.println("uT");
    Serial.print("Heading (degrees): ");
    Serial.println(headingDegrees);
#endif

    _heading = headingDegrees;
    return headingDegrees;
}

void Platform::displaySensorDetails()
{
    sensor_t sensor;
    compass.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print("Sensor:       ");
    Serial.println(sensor.name);
    Serial.print("Driver Ver:   ");
    Serial.println(sensor.version);
    Serial.print("Unique ID:    ");
    Serial.println(sensor.sensor_id);
    Serial.print("Max Value:    ");
    Serial.print(sensor.max_value);
    Serial.println(" uT");
    Serial.print("Min Value:    ");
    Serial.print(sensor.min_value);
    Serial.println(" uT");
    Serial.print("Resolution:   ");
    Serial.print(sensor.resolution);
    Serial.println(" uT");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
}

void Platform::rotateTo(int setPoint)
{
    float output = rotationPID.calculate(setPoint, getHeading());

    CUTOFF1(output);
    _x = output;

    Serial.println(output);
}