// #include <Arduino.h>
// #include "radio.h"

// #include "jm_CPPM.h"

// Radio::Radio()
// {
//   _joystick_x = 0;
//   _joystick_y = 0;
//   _joystick_rot = 0;
// }
// void Radio::setJoysticInputs(int x, int y)
// {
//   _joystick_x = x;
//   _joystick_y = y;
// }
// int Radio::getJoysticX()
// {
//   return _joystick_x;
// }
// int Radio::getJoysticY()
// {
//   return _joystick_y;
// }

// void Radio::updateRadio(void)
// {
//   if (CPPM.synchronized())
//   {
//     _joystick_y = CPPM.read_us(CPPM_THRO) - 1500;
//     _joystick_x = CPPM.read_us(CPPM_ELEV) - 1500;
//     _joystick_rot = CPPM.read_us(CPPM_AILE) - 1500;

// #ifdef DEBUG_RADIO
//     Serial.println(_joystick_y);
//     Serial.println(_joystick_x);
//     Serial.println(_joystick_rot);
// #endif
//   }
// }

// void Radio::test_cppm()
// {
//   if (CPPM.synchronized())
//   {
//     int aile = CPPM.read_us(CPPM_AILE) - 1500; // aile
//     int elev = CPPM.read_us(CPPM_ELEV) - 1500; // elevator
//     int thro = CPPM.read_us(CPPM_THRO) - 1500; // throttle
//     int rudd = CPPM.read_us(CPPM_RUDD) - 1500; // rudder
//     int gear = CPPM.read_us(CPPM_GEAR) - 1500; // gear
//     int aux1 = CPPM.read_us(CPPM_AUX1) - 1500; // flap

// #if 0
//       Serial.print(aile); Serial.print(", ");
//       Serial.print(elev); Serial.print(", ");
//       Serial.print(thro); Serial.print(", ");
//       Serial.print(rudd); Serial.print(", ");
//       Serial.print(gear); Serial.print(", ");
//       Serial.print(aux1); Serial.print("\n");
// #else
//     for (int i = 0; i < (CPPM_MSERVO + 2); i++)
//     {
//       Serial.print('\t');
//       Serial.print(CPPM._sync2s[i] / 2); // width of synch pulses
//     }
//     Serial.println();
//     for (int i = 0; i < (CPPM_MSERVO + 2); i++)
//     {
//       Serial.print('\t');
//       Serial.print(CPPM._puls3s[i] / 2); // width of servo pulses
//     }
//     Serial.println();
// #endif

//     Serial.flush();

//     delay(100);

//     CPPM.received();
//   }
//   else
//   {
//     // if not synchronized, do something...
//   }
// }