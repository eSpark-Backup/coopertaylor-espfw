#pragma once

#include "RAK12029_LDC1614.h"  // Assuming this library is for the LDC1614

#define INDUCTANCE   13.000
#define CAPACITANCE  100.0
#define GETCHANNEL   LDC1614_CHANNEL_0 //LDC1614_CHANNEL_(0~3)

#define SCL_  4
#define SDA_  5
#define INT   6 

#define EMF_THRESHOLD 100000  // Example threshold value for dangerous EMF detection

class EMFDetector 
{
public:

    void setUp();
    bool isEMFThresholdExceeded();
private:

    RAK12029_LDC1614_Inductive ldc;
    void initializeHardware();
    void initializeLDC1614();
    bool checkDeviceId();
    u32 readChannelData();
    bool handleEMFDetection(u32 ChannelData);  
};