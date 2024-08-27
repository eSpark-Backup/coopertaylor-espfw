#pragma Once
#include <SPI.h>
#include <SD.h>

class SDCardHandler 
{
public:
    SDCardHandler(int csPin, int sclkPin, int misoPin, int mosiPin);
    void setUp();
    void store(const String& data);

private:
    int _csPin;
    int _sclkPin;
    int _misoPin;
    int _mosiPin;
    File _myFile;
};