#include <Arduino.h>
#include "communication.h"

void setupCommunication()
{
  Serial.begin(9600);
}

void rxProcess()
{
  rxCtr--;
	switch(rxBuffer[rxCtr]) //Om kommandot vi fick in va...
	{
    default:
      break;
  }
}
