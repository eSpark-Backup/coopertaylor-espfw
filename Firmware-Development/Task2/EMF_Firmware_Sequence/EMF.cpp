#include "EMF.hpp"

void EMFDetector::setUp() 
{
  initializeHardware();
  initializeLDC1614();
}

bool EMFDetector::isEMFThresholdExceeded()
{
  if (checkDeviceId()) 
  {
    u32 ChannelData = readChannelData();
     return handleEMFDetection(ChannelData); 
  } 
  else 
  {
    Serial.println("The IIC communication fails, please reset the sensor!");
    return false;
  }
}

void EMFDetector::initializeHardware() 
{
  Wire.setPins(SDA_, SCL_);

  // pinMode(INT, INPUT);
}

void EMFDetector::initializeLDC1614() 
{
  ldc.LDC1614_init();
  if (ldc.LDC1614_single_channel_config(GETCHANNEL, INDUCTANCE, CAPACITANCE)) 
  {
    Serial.println("Can't detect sensor!");
    while (1) delay(100);
  }
}

bool EMFDetector::checkDeviceId() {
  u16 value = 0;
  ldc.IIC_read_16bit(LDC1614_READ_DEVICE_ID, &value);
  return value == 0x3055;
}

u32 EMFDetector::readChannelData() 
{
  u32 ChannelData = 0;
  delay(100);
  if (ldc.LDC1614_get_channel_result(GETCHANNEL, &ChannelData) == 0) 
  {
    return ChannelData;
  }
  return 0;  // Return 0 if there's an error
}

bool EMFDetector::handleEMFDetection(u32 ChannelData) 
{
  Serial.printf("EMF Level (Channel %d): %d\r\n", 4 - GETCHANNEL, ChannelData);

  if (ChannelData > EMF_THRESHOLD) 
  {
    Serial.println("Dangerous EMF level detected!");
    return true;
  } 
  else 
  {
    return false;
  }
}


