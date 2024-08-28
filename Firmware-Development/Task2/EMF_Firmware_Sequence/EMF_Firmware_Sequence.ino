
#include "EMF.hpp"
// Create an instance of the EMFDetector class
#define BUZZER 2 
EMFDetector emfDetector;

void setup() 
{
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  Serial.begin(115200);
  Serial.println("RAK12029 EMF Detection TEST");
  emfDetector.setUp();
}

void loop() 
{    
    if(emfDetector.isEMFThresholdExceeded())
       digitalWrite(BUZZER, HIGH);
    else
       digitalWrite(BUZZER, LOW);
}
