#pragma once

#include <DFRobot_DS1307.h>
#define SCL_PIN 19
#define SDA_PIN 20
class DS1307Manager 
{
public:
    DS1307Manager();
    void setUp(uint16_t initialTime[7]);
    void getTime(char* timeArray);

private:
    DFRobot_DS1307 DS1307;
    void setTime(uint16_t timeArray[7]);
    void start();

};


