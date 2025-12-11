#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

enum LogLevel {
    INFO,
    WARN,
    ERROR
};

class DataLogger {
public:
    DataLogger(const char* filename, uint8_t csPin);

    bool begin();
    void log(const String& message, LogLevel level);
    bool isReady() const;

private:
    char* _filename;
    uint8_t _csPin;
    bool _ready;
    int _fileIndex = 0;

    String getTimestamp();
    String levelToString(LogLevel level);
};

#endif
