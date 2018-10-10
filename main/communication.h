#ifndef COMMUNICATION_H
#define COMMUNICATION_H
//*************INKLUDERINGAR*********************************************
#include "Arduino.h"
//*************INSTaLLNINGAR*********************************************
#define startCommand '!' //det tecken som initierar lasning av kommando
//*************GLOBALA VARIABLER*****************************************
extern volatile uint8_t rxBuffer[]; //Buffer dar senast mottagna datan ligger
extern char rxCommand[];
extern volatile uint8_t rxCtr; // haller reda pa var i buffern vi ar
extern volatile bool rxFlag; //true om vi fatt ett nytt varde i buffern
//*************FUNKTIONER************************************************
void setupCommunication();
void rxProcess();

#endif
