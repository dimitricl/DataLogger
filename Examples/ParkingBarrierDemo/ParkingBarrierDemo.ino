/**
 * ParkingBarrierDemo.ino
 * * Demonstration complete du module DataLogger
 * Simule un systeme de barriere de parking avec capteurs
 * * Auteurs : Claverie Dimitri, Peux Axel
 * Version : 0.2
 */

#include "DataLogger.h"

// Creation de l'instance du logger
// Fichier : "system.log"
// Broche CS : 5
DataLogger logger("system.log", 5);

// Variables pour la gestion des capteurs
const int SENSOR_PIN = A0;           // Capteur position barriere
const int SENSOR_TEMP_PIN = A1;      // Capteur temperature
const int SEUIL_CRITIQUE = 900;      // Seuil d'alerte haute
const int SEUIL_MIN = 10;            // Seuil erreur capteur
const unsigned long INTERVAL_LOG = 2000; // Intervalle entre les logs (ms)

unsigned long lastLogTime = 0;       // Horodatage du dernier log
int lastSensorValue = -1;            // Valeur precedente pour detecter changements

/**
 * Configuration initiale de l'Arduino
 */
void setup() {
    // Initialisation du port serie
    Serial.begin(115200);
    
    delay(1000);

    Serial.println("--- Demarrage du systeme Barriere ---");

    // Initialisation du logger
    if (logger.begin()) {
        logger.log("Systeme demarre", INFO);
    } else {
        Serial.println("ERREUR CRITIQUE : Impossible d'initialiser la carte SD");
    }
}

/**
 * Boucle principale
 */
void loop() {
    unsigned long currentTime = millis();

    // Lecture des capteurs simules (ou reels si connectes)
    int sensorValue = analogRead(SENSOR_PIN);
    
    // Log periodique (toutes les 2 secondes)
    if (currentTime - lastLogTime >= INTERVAL_LOG) {
        lastLogTime = currentTime;

        // Log d'information standard
        String msg = "Position barriere : " + String(sensorValue);
        logger.log(msg, INFO);

        // Verification des seuils
        if (sensorValue > SEUIL_CRITIQUE) {
            logger.log("ALERTE : Position anormale detectee !", WARN);
        }

        if (sensorValue < SEUIL_MIN) {
            logger.log("ERREUR : Capteur deconnecte ou defaillant", ERROR);
        }
    }

    // Affichage de diagnostic sur le port serie
    // Serial.print("Etat SD : ");
    // Serial.println(logger.isReady() ? "OK" : "ERREUR");
    
    delay(100); // Petite pause pour la stabilite
}