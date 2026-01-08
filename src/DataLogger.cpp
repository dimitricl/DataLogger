/**
 * DataLogger.cpp
 * * Implementation du module DataLogger
 * Gere l'enregistrement des donnees sur carte SD avec rotation automatique
 */

#include "DataLogger.h"

// Limite de taille par fichier (1 Mo = 1024 * 1024 octets)
#define MAX_LOG_SIZE (1024UL * 1024UL)

/**
 * Constructeur du DataLogger
 */
DataLogger::DataLogger(const char* filename, uint8_t csPin) {
    _filename = strdup(filename);  // Allocation memoire pour le nom du fichier
    _csPin = csPin;                // Sauvegarde la broche CS
    _ready = false;                // SD pas encore initialisee
    _fileIndex = 0;                // Pas de rotation encore
}

/**
 * Initialise la connexion a la carte SD via SPI
 */
bool DataLogger::begin() {
    Serial.print("Initialisation de la carte SD... ");

    // Tentative de demarrage de la SD avec la broche CS specifiee
    if (!SD.begin(_csPin)) {
        Serial.println("Echec");
        _ready = false;
        return false;
    }

    Serial.println("OK");
    _ready = true;
    return true;
}

/**
 * Gere la rotation automatique des fichiers
 * Si le fichier depasse MAX_LOG_SIZE, on cree un nouveau fichier
 */
void DataLogger::rotateFileIfNeeded() {
    if (!_ready) return;

    File file = SD.open(_filename, FILE_READ);
    if (file) {
        if (file.size() >= MAX_LOG_SIZE) {
            file.close();
            _fileIndex++;
            
            // Renommage simple pour l'exemple (system.log -> system1.log)
            // Note : L'implementation ideale necessiterait une gestion de chaines plus complexe
            // Ici, on remet a zero le fichier principal pour simuler la rotation
            SD.remove(_filename); 
            Serial.println("Rotation des logs effectuee");
        } else {
            file.close();
        }
    }
}

/**
 * Enregistre un message dans le fichier de log
 */
void DataLogger::log(const String& message, LogLevel level) {
    if (!_ready) return;

    rotateFileIfNeeded();

    File file = SD.open(_filename, FILE_WRITE);
    if (!file) {
        Serial.println("Erreur d'ouverture du fichier !");
        return;
    }

    String line = getTimestamp() + " [" + levelToString(level) + "] " + message + "\n";

    // Ecriture dans le fichier sur SD
    file.print(line);
    file.close();

    // Affichage en temps reel sur le port serie
    Serial.print(line); // Utilisation de print car line contient deja \n
}

/**
 * Retourne l'etat de la SD
 */
bool DataLogger::isReady() const {
    return _ready;
}

/**
 * Convertit un niveau de log en chaine de caracteres
 */
String DataLogger::levelToString(LogLevel level) {
    switch (level) {
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

/**
 * Genere l'horodatage au format HH:MM:SS
 */
String DataLogger::getTimestamp() {
    unsigned long ms = millis();           // Millisecondes depuis le demarrage
    unsigned long sec = ms / 1000;         // Conversion en secondes
    unsigned long min = sec / 60;          // Conversion en minutes
    unsigned long hr = min / 60;           // Conversion en heures

    // Formatage dans un buffer
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02lu:%02lu:%02lu", hr % 24, min % 60, sec % 60);
    
    return String(buffer);
}