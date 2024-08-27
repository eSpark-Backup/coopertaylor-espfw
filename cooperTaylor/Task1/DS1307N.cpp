#include "DS1307N.hpp"
#include <Arduino.h>
#include <Wire.h> 

DS1307Manager::DS1307Manager() {}

void DS1307Manager::setUp(uint16_t initialTime[7]) 
{
   Wire.setPins(SDA_PIN, SCL_PIN);
    // Initialize the RTC communication
    while (!DS1307.begin()) 
    {
        Serial.println("Communication with device failed, please check connection");
        delay(3000);
    }

    Serial.println("Begin ok!");

    // Set the initial time and SQW pin mode
    DS1307.setTime(initialTime);
    start();
    DS1307.setSqwPinMode(DS1307.eSquareWave_1Hz);
}

void DS1307Manager::getTime(char* timeArray) 
{
    uint16_t localTimeArray[7] = {0};  // Avoid shadowing the parameter

    DS1307.getTime(localTimeArray);

    sprintf(timeArray, "Time: %d/%d/%d-%d %d:%d:%d\r\n",
            localTimeArray[6], localTimeArray[5], localTimeArray[4], localTimeArray[3],
            localTimeArray[2], localTimeArray[1], localTimeArray[0]);

    Serial.print(timeArray);
}

void DS1307Manager::setTime(uint16_t timeArray[7])
{
    DS1307.setTime(timeArray);
}

void DS1307Manager::start() {
    DS1307.start();
}


