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

    motorTimer = Timer();
    PIDTimer = Timer();
    radioTimer = Timer();
}

void Platform::begin()
{
    DebugSerial->begin(DEBUG_SERIAL_BAUDRATE);
    
    Serial1.begin(MAIN_SERIAL_BAUDRATE);
    //MainSerial.setStream(&Serial1);
    //MainSerial.setPacketHandler(&processPacketFromSender);

    DebugSerial->println("Initializing Walle...");
    delay(100);

    motorTimer.setTimer(MOTOR_DELAY);
    delay(200);
    PIDTimer.setTimer(PID_DELAY);
    delay(200);
    radioTimer.setTimer(RADIO_DELAY);
    delay(200);

    /* Initialise the sensor */
    if (!compass.begin())
    {
        /* There was a problem detecting the HMC5883 ... check your connections */
            DebugSerial->println("Ooops, no HMC5883 detected ... Check your wiring!");
        while (1);
    }
    if (rotationPID.err())
    {
            DebugSerial->println("There was a configuration error with the rotationPID");
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

//Allways read serial input
MainSerial.update();

    switch(_mode){
        case IDLE:
            DebugSerial->println("State = Idle");
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
                //DebugSerial->println("Motor");
            }
            if(PIDTimer.check()){
                //run PID loop
                //DebugSerial->println("PID");
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
                DebugSerial->println("Error, this state does not exist. Going back to idle.");
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

#ifdef DEBUG_MOTORS         DebugSerial->print("Mapped: ");         DebugSerial->print(_y);     DebugSerial->print(", ");        DebugSerial->println(_x);       DebugSerial->print("Radius and angle: ");         DebugSerial->print(r);        DebugSerial->print(", ");      DebugSerial->println(t);        DebugSerial->print("Left: ");          DebugSerial->print(left);          DebugSerial->print(", ");       DebugSerial->print("Right: ");       DebugSerial->println(right);
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
    /* Display the results (magnetic vector values are in micro-Tesla (uT)) */          DebugSerial->print("X: ");          DebugSerial->print(event.magnetic.x);       DebugSerial->print("  ");         DebugSerial->print("Y: ");      DebugSerial->print(event.magnetic.y);        DebugSerial->print("  ");       DebugSerial->print("Z: ");         DebugSerial->print(event.magnetic.z);        DebugSerial->print("  ");    DebugSerial->println("uT");          DebugSerial->print("Heading (degrees): ");      DebugSerial->println(headingDegrees);
#endif

    _heading = headingDegrees;
    return headingDegrees;
}

void Platform::displaySensorDetails()
{
    sensor_t sensor;
    compass.getSensor(&sensor);         DebugSerial->println("------------------------------------");           DebugSerial->print("Sensor:       ");       DebugSerial->println(sensor.name);       DebugSerial->print("Driver Ver:   ");         DebugSerial->println(sensor.version);         DebugSerial->print("Unique ID:    ");          DebugSerial->println(sensor.sensor_id);         DebugSerial->print("Max Value:    ");       DebugSerial->print(sensor.max_value);     DebugSerial->println(" uT");       DebugSerial->print("Min Value:    ");         DebugSerial->print(sensor.min_value);         DebugSerial->println(" uT");           DebugSerial->print("Resolution:   ");       DebugSerial->print(sensor.resolution);          DebugSerial->println(" uT");           DebugSerial->println("------------------------------------");       DebugSerial->println("");
    delay(500);
}

void Platform::rotateTo(int setPoint)
{
    float output = rotationPID.calculate(setPoint, getHeading());

    CUTOFF1(output);
    _x = output;
            DebugSerial->println(output);
}

void Platform::processPacketFromSender(const uint8_t* buffer, size_t size)
{

}