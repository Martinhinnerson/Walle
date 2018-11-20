

//========================================================================================
/*                                                                                      *
 *                                        Walle-e                                       *
 *                                                                                      *
 *                      Created by Martin Hinnerson and Tim Fornell                     *
 *                                                                                      */
//========================================================================================



// =============================================================================
// Libraries
// =============================================================================
#include <Arduino.h>

// =============================================================================
// Headers
// =============================================================================
#include "platform.h"
#include "settings.h"

// =============================================================================
// Globals
// =============================================================================
Platform walle; // instansiate the platform with the default constructor

// =============================================================================
// Setup
// =============================================================================
void setup()
{
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Initializing Walle...");
  delay(100);
  walle.begin();
  delay(1000);
  Serial.println("Walle initialized.");
}

// =============================================================================
// Main loop
// =============================================================================
void loop()
{
  walle.run();
}
