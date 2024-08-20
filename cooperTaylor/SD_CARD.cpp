#include "SD_CARD.hpp"

SDCardHandler::SDCardHandler(int csPin, int sclkPin, int misoPin, int mosiPin)
    : _csPin(csPin), _sclkPin(sclkPin), _misoPin(misoPin), _mosiPin(mosiPin) {}

void SDCardHandler::setUp() 
{

    SPI.begin(_sclkPin, _misoPin, _mosiPin, _csPin);

    Serial.print("Initializing SD card...");

    if (!SD.begin(_csPin)) 
    {
        Serial.println("initialization failed!");
        while (1);
    }
    Serial.println("initialization done.");
}

void SDCardHandler::store(const String& data) 
{
    // Open the file for writing:
    _myFile = SD.open("test.txt", FILE_APPEND);

    if (_myFile) 
    {
        Serial.print("Writing to test.txt...");
        _myFile.println(data);
        _myFile.close();
        Serial.println("done.");
    } 
    else 
    {
        Serial.println("error opening test.txt for writing");
    }

    // Re-open the file for reading:
    _myFile = SD.open("test.txt");
    if (_myFile) 
    {
        Serial.println("test.txt:");

        // Read from the file until there's nothing else in it:
        while (_myFile.available()) 
        {
            Serial.write(_myFile.read());
        }
        _myFile.close();
    } 
    else 
    {
        Serial.println("error opening test.txt for reading");
    }
}