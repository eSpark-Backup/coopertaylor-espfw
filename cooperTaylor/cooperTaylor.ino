#include "DS1307N.hpp"
#include "SD_CARD.hpp"

#define TIME_INTERVAL 10000 // Time interval in milliseconds
#define BATTERY_ADC_PIN 3

#define CS_PIN   7
#define SCLK_PIN 8
#define MISO_PIN 9
#define MOSI_PIN 10

unsigned long previousMillis = 0;

char timeBuffer[100];  
DS1307Manager rtcManager; 
SDCardHandler sdCardHandler(CS_PIN, SCLK_PIN, MISO_PIN, MOSI_PIN);

void setup() 
{
    Serial.begin(115200); 
    pinMode(BATTERY_ADC_PIN, INPUT);
    sdCardHandler.setUp();
       // Define the initial time (example: {sec, min, hour, day of week, date, month, year})
    uint16_t initialTime[7] = {0, 1, 12, 6, 9, 9, 2024}; // Example time: 12:01:00 on 9th Sept 2024
    rtcManager.setUp(initialTime);
}

void loop() 
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= TIME_INTERVAL)
    {
        rtcManager.getTime(timeBuffer);  // Pass the renamed variable
        
        // put your main code here, to run repeatedly:
        float adcBatteryVoltage = analogRead(BATTERY_ADC_PIN) * (3.3/4095.0);
        Serial.print("Battery Level : ");
        Serial.println(adcBatteryVoltage);
        
        char sdData[50];
        snprintf(sdData, sizeof(sdData), "Battery Voltage Level: %d, Unix Time: %lu", adcBatteryVoltage, timeBuffer);
        Serial.println(sdData);

        sdCardHandler.store(sdData);
        previousMillis = currentMillis;
    }
}