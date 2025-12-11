#include "DataLogger.h"

#define MAX_LOG_SIZE (1024UL * 1024UL)

DataLogger::DataLogger(const char* filename, uint8_t csPin) {
    _filename = strdup(filename);
    _csPin = csPin;
    _ready = false;
}

bool DataLogger::begin() {
    Serial.print("Initialisation de la carte SD... ");

    if (!SD.begin(_csPin)) {
        Serial.println("Échec ❌");
        _ready = false;
        return false;
    }

    Serial.println("OK ✅");
    _ready = true;
    return true;
}

void DataLogger::log(const String& message, LogLevel level) {
    if (!_ready) {
        Serial.println("⚠️ SD non initialisée !");
        return;
    }

    File file = SD.open(_filename, FILE_WRITE);
    if (!file) {
        Serial.println("❌ Impossible d’ouvrir le fichier !");
        return;
    }

    if (file.size() > MAX_LOG_SIZE) {
        file.close();
        Serial.println("⚠️ Taille max atteinte → nouveau fichier");

        _fileIndex++;
        char newName[32];
        snprintf(newName, sizeof(newName), "data_%d.log", _fileIndex);
        _filename = strdup(newName);

        file = SD.open(_filename, FILE_WRITE);
        if (!file) {
            Serial.println("❌ Impossible de créer le nouveau fichier !");
            return;
        }
    }

    String line = getTimestamp() + " [" + levelToString(level) + "] " + message + "\n";

    file.print(line);
    file.close();

    Serial.println(line);
}

bool DataLogger::isReady() const {
    return _ready;
}

String DataLogger::levelToString(LogLevel level) {
    switch (level) {
        case INFO: return "INFO";
        case WARN: return "WARN";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

String DataLogger::getTimestamp() {
    unsigned long ms = millis();
    unsigned long sec = ms / 1000;
    unsigned long min = sec / 60;
    unsigned long hr = min / 60;

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02lu:%02lu:%02lu",
             hr % 24, min % 60, sec % 60);

    return String(buffer);
}
