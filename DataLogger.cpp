/**
 * DataLogger.cpp
 * 
 * Implémentation du module DataLogger
 * Gère l'enregistrement des données sur carte SD avec rotation automatique
 */

#include "DataLogger.h"

// Limite de taille par fichier (1 Mo = 1024 * 1024 octets)
#define MAX_LOG_SIZE (1024UL * 1024UL)

/**
 * Constructeur du DataLogger
 * Initialise les paramètres mais ne connecte pas la SD
 * (utiliser begin() pour initialiser)
 */
DataLogger::DataLogger(const char* filename, uint8_t csPin) {
    _filename = strdup(filename);  // Allocation mémoire pour le nom du fichier
    _csPin = csPin;                // Sauvegarde la broche CS
    _ready = false;                // SD pas encore initialisée
    _fileIndex = 0;                // Pas de rotation encore
}

/**
 * Initialise la connexion à la carte SD via SPI
 * 
 * Processus :
 * 1. Affiche un message de diagnostic
 * 2. Tente de démarrer la communication SD
 * 3. Met à jour l'état interne
 * 4. Affiche le résultat
 */
bool DataLogger::begin() {
    Serial.print("Initialisation de la carte SD... ");

    // Tentative de démarrage de la SD avec la broche CS spécifiée
    if (!SD.begin(_csPin)) {
        Serial.println("Échec ❌");
        _ready = false;
        return false;
    }

    Serial.println("OK ✅");
    _ready = true;
    return true;
}

/**
 * Enregistre un message dans le fichier de log
 * 
 * Processus :
 * 1. Vérifie que la SD est prête
 * 2. Ouvre le fichier en mode ajout
 * 3. Vérifie la taille et crée un nouveau fichier si nécessaire
 * 4. Formate le message avec horodatage et niveau
 * 5. Écrit dans le fichier
 * 6. Affiche sur le port série
 */
void DataLogger::log(const String& message, LogLevel level) {
    // Vérification que la SD est initialisée
    if (!_ready) {
        Serial.println("⚠️ SD non initialisée !");
        return;
    }

    // Ouverture du fichier en mode ajout (FILE_WRITE)
    File file = SD.open(_filename, FILE_WRITE);
    if (!file) {
        Serial.println("❌ Impossible d'ouvrir le fichier !");
        return;
    }

    // Vérification de la taille du fichier (rotation si nécessaire)
    if (file.size() > MAX_LOG_SIZE) {
        file.close();
        Serial.println("⚠️ Taille max atteinte → nouveau fichier");

        // Génération du nouveau nom de fichier
        // Exemple : data_0.log → data_1.log → data_2.log
        _fileIndex++;
        char newName[32];
        snprintf(newName, sizeof(newName), "data_%d.log", _fileIndex);
        _filename = strdup(newName);

        // Ouverture du nouveau fichier
        file = SD.open(_filename, FILE_WRITE);
        if (!file) {
            Serial.println("❌ Impossible de créer le nouveau fichier !");
            return;
        }
    }

    // Construction de la ligne de log avec format standardisé
    // Format : "HH:MM:SS [NIVEAU] message"
    String line = getTimestamp() + " [" + levelToString(level) + "] " + message + "\n";

    // Écriture dans le fichier sur SD
    file.print(line);
    file.close();

    // Affichage en temps réel sur le port série
    Serial.println(line);
}

/**
 * Retourne l'état de la SD
 */
bool DataLogger::isReady() const {
    return _ready;
}

/**
 * Convertit un niveau de log en chaîne de caractères
 * 
 * @param level Niveau (INFO, WARN, ERROR)
 * @return Chaîne correspondante
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
 * Génère l'horodatage au format HH:MM:SS
 * 
 * Basé sur millis() depuis le démarrage de l'Arduino
 * 
 * @return Chaîne formatée "HH:MM:SS"
 */
String DataLogger::getTimestamp() {
    unsigned long ms = millis();           // Millisecondes depuis le démarrage
    unsigned long sec = ms / 1000;         // Conversion en secondes
    unsigned long min = sec / 60;          // Conversion en minutes
    unsigned long hr = min / 60;           // Conversion en heures

    // Formatage dans un buffer avec modulo pour tenir sur 24 heures
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02lu:%02lu:%02lu",
             hr % 24,      // Heures (0-23)
             min % 60,     // Minutes (0-59)
             sec % 60);    // Secondes (0-59)

    return String(buffer);
}
