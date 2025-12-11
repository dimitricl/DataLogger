/**
 * DataLogger.h
 * 
 * Module de journalisation pour système de barrière de parking
 * Gère l'enregistrement des données sur carte SD avec rotation de fichiers
 * 
 * Auteurs : Claverie Dimitri, Peux Axel
 * Version : 0.2
 */

#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

/**
 * Niveaux de priorité des messages de log
 */
enum LogLevel {
    INFO,    ///< Information normale
    WARN,    ///< Avertissement
    ERROR    ///< Erreur critique
};

/**
 * Classe DataLogger
 * 
 * Gère la journalisation des événements système sur carte SD
 * 
 * Exemple d'utilisation :
 * @code
 * DataLogger logger("system.log", 5);  // Fichier: system.log, CS pin: 5
 * 
 * if (logger.begin()) {
 *     logger.log("Système démarré", INFO);
 *     logger.log("Attention: seuil élevé", WARN);
 *     logger.log("Erreur critique détectée", ERROR);
 * } else {
 *     Serial.println("Impossible d'initialiser la SD");
 * }
 * @endcode
 */
class DataLogger {
public:
    /**
     * Constructeur
     * 
     * @param filename Nom du fichier de log (ex: "system.log")
     * @param csPin Numéro de la broche CS (Chip Select) pour la SD
     * 
     * Exemple :
     * DataLogger logger("data.log", 5);  // Pin 5 comme CS
     */
    DataLogger(const char* filename, uint8_t csPin);

    /**
     * Initialise la connexion à la carte SD
     * 
     * @return true si succès, false si la SD n'est pas détectée
     * 
     * Exemple :
     * if (!logger.begin()) {
     *     Serial.println("Erreur : carte SD non détectée");
     * }
     */
    bool begin();

    /**
     * Enregistre un message dans le fichier de log
     * 
     * @param message Le message à enregistrer (String ou const char*)
     * @param level Niveau de priorité (INFO, WARN, ou ERROR)
     * 
     * Le message sera formaté comme :
     * HH:MM:SS [NIVEAU] message\n
     * 
     * Exemple :
     * int sensorValue = analogRead(A0);
     * logger.log("Valeur capteur : " + String(sensorValue), INFO);
     * logger.log("Seuil dépassé !", WARN);
     */
    void log(const String& message, LogLevel level);

    /**
     * Vérifie si la SD est initialisée et prête
     * 
     * @return true si prête, false sinon
     * 
     * Exemple :
     * if (logger.isReady()) {
     *     logger.log("SD OK", INFO);
     * }
     */
    bool isReady() const;

    /**
     * Retourne le nombre de fichiers créés lors des rotations
     * 
     * @return Index du fichier courant
     */
    int getFileIndex() const { return _fileIndex; }

    /**
     * Retourne le nom du fichier actuellement utilisé
     * 
     * @return Pointeur vers le nom du fichier
     */
    const char* getFilename() const { return _filename; }

private:
    char* _filename;           ///< Nom du fichier de log
    uint8_t _csPin;            ///< Broche CS pour la SD
    bool _ready;               ///< État de la SD
    int _fileIndex;            ///< Compteur pour rotation de fichiers

    /**
     * Génère une chaîne formatée du temps écoulé
     * Format : "HH:MM:SS"
     */
    String getTimestamp();

    /**
     * Convertit un LogLevel en chaîne de caractères
     */
    String levelToString(LogLevel level);
};

#endif // DATALOGGER_H
