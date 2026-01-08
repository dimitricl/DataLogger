/**
 * DataLogger.h
 * * Module de journalisation pour systeme de barriere de parking
 * Gere l'enregistrement des donnees sur carte SD avec rotation de fichiers
 * * Auteurs : Claverie Dimitri, Peux Axel
 * Version : 0.2
 */

#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

/**
 * Niveaux de priorite des messages de log
 */
enum LogLevel {
    INFO,    ///< Information normale
    WARN,    ///< Avertissement
    ERROR    ///< Erreur critique
};

/**
 * Classe DataLogger
 * * Gere la journalisation des evenements systeme sur carte SD
 */
class DataLogger {
public:
    /**
     * Constructeur
     * * @param filename Nom du fichier de log (ex: "system.log")
     * @param csPin Numero de la broche CS (Chip Select) pour la SD
     */
    DataLogger(const char* filename, uint8_t csPin);

    /**
     * Initialise la connexion a la carte SD via SPI
     * * @return true si succes, false si echec
     */
    bool begin();

    /**
     * Enregistre un message dans le fichier de log
     * * @param message Texte a enregistrer
     * @param level Niveau de priorite (INFO, WARN, ou ERROR)
     */
    void log(const String& message, LogLevel level);

    /**
     * Verifie si la SD est initialisee et prete
     * * @return true si prete, false sinon
     */
    bool isReady() const;

    /**
     * Retourne le nombre de fichiers crees lors des rotations
     * * @return Index du fichier courant
     */
    int getFileIndex() const { return _fileIndex; }

    /**
     * Retourne le nom du fichier actuellement utilise
     * * @return Pointeur vers le nom du fichier
     */
    const char* getFilename() const { return _filename; }

private:
    char* _filename;           ///< Nom du fichier de log
    uint8_t _csPin;            ///< Broche CS pour la SD
    bool _ready;               ///< Etat de la SD
    int _fileIndex;            ///< Compteur pour rotation de fichiers

    /**
     * Genere une chaine formatee du temps ecoule
     */
    String getTimestamp();

    /**
     * Convertit l'enum LogLevel en String
     */
    String levelToString(LogLevel level);

    /**
     * Gere la rotation des fichiers si la taille depasse la limite
     */
    void rotateFileIfNeeded();
};

#endif