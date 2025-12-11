/**
 * demo.ino
 * 
 * Démonstration complète du module DataLogger
 * Simule un système de barrière de parking avec capteurs
 * 
 * Auteurs : Claverie Dimitri, Peux Axel
 * Version : 0.2
 */

#include "DataLogger.h"

// Création de l'instance du logger
// Fichier : "system.log"
// Broche CS : 5
DataLogger logger("system.log", 5);

// Variables pour la gestion des capteurs
const int SENSOR_PIN = A0;           // Capteur position barrière
const int SENSOR_TEMP_PIN = A1;      // Capteur température
const int SEUIL_CRITIQUE = 900;      // Seuil d'alerte haute
const int SEUIL_MIN = 10;            // Seuil erreur capteur
const unsigned long INTERVAL_LOG = 2000; // Intervalle entre les logs (ms)

unsigned long lastLogTime = 0;       // Horodatage du dernier log
int lastSensorValue = -1;            // Valeur précédente pour détecter changements

/**
 * Configuration initiale de l'Arduino
 * 
 * Étapes :
 * 1. Initialisation du port série
 * 2. Tentative de connexion à la SD
 * 3. Enregistrement du démarrage
 */
void setup() {
    // Initialisation du port série pour le monitoring en direct
    // Vitesse : 115200 bauds (standard Arduino)
    Serial.begin(115200);
    
    // Pause pour laisser le temps à la connexion de s'établir
    delay(1000);

    Serial.println("\n=== DÉMARRAGE SYSTÈME ===");
    Serial.println("Barrière de Parking - Module DataLogger v0.2\n");

    // Initialisation du logger
    if (!logger.begin()) {
        Serial.println("❌ Impossible d'initialiser la SD !");
        Serial.println("⚠️  Vérifiez :");
        Serial.println("   - La carte SD est-elle insérée ?");
        Serial.println("   - Les connexions SPI sont-elles correctes ?");
        Serial.println("   - La broche CS est-elle sur la pin 5 ?");
        
        // Arrêt du système (boucle infinie)
        while (true) {
            delay(500);
        }
    }

    // Enregistrement du démarrage
    logger.log("=== SYSTÈME DÉMARRÉ ===", INFO);
    logger.log("Barrière de Parking - v0.2", INFO);
    logger.log("Module DataLogger activé", INFO);
    
    delay(500);
}

/**
 * Boucle principale du système
 * 
 * Tâches :
 * 1. Lecture des capteurs (analogique)
 * 2. Enregistrement des données
 * 3. Vérification des seuils d'alerte
 * 4. Génération des logs d'erreur
 */
void loop() {
    // Vérification de l'intervalle de log
    // Ceci évite de surcharger la carte SD
    if (millis() - lastLogTime < INTERVAL_LOG) {
        delay(100);  // Petit délai pour ne pas bloquer le microcontrôleur
        return;
    }
    
    lastLogTime = millis();

    // ============================================
    // LECTURE DU CAPTEUR POSITION (A0)
    // ============================================
    int sensorValue = analogRead(SENSOR_PIN);
    
    // Enregistrement de la valeur
    logger.log("Valeur capteur position : " + String(sensorValue), INFO);

    // ============================================
    // LECTURE DU CAPTEUR TEMPÉRATURE (A1)
    // ============================================
    int tempValue = analogRead(SENSOR_TEMP_PIN);
    logger.log("Température : " + String(tempValue) + " (brut)", INFO);

    // ============================================
    // VÉRIFICATION DES SEUILS
    // ============================================
    
    // Alerte : seuil critique dépassé
    if (sensorValue > SEUIL_CRITIQUE) {
        logger.log("⚠️  ALERTE : Seuil critique dépassé ! (" + 
                   String(sensorValue) + " > " + String(SEUIL_CRITIQUE) + ")", 
                   WARN);
    }

    // Erreur : capteur déconnecté ou défaillant
    if (sensorValue < SEUIL_MIN) {
        logger.log("❌ ERREUR : Capteur position peut être déconnecté ! " +
                   String("Valeur: ") + String(sensorValue), 
                   ERROR);
    }

    // Alerte température
    if (tempValue > 800) {
        logger.log("⚠️  ATTENTION : Température élevée détectée", WARN);
    }

    // ============================================
    // SIMULATION D'ÉVÉNEMENTS (optionnel)
    // ============================================
    // Permet de tester le système sans vrai capteur
    /*
    static int testCounter = 0;
    testCounter++;
    
    if (testCounter == 10) {  // Tous les 20 secondes (10 x 2sec)
        logger.log("Barrière levée", INFO);
    }
    if (testCounter == 15) {
        logger.log("Barrière baissée", INFO);
    }
    if (testCounter >= 20) {
        testCounter = 0;
    }
    */

    // Affichage de diagnostic sur le port série
    Serial.print("État SD : ");
    Serial.println(logger.isReady() ? "✅ OK" : "❌ ERREUR");
}

// ============================================
// NOTES D'UTILISATION
// ============================================
/*
 * SCHÉMA DE CÂBLAGE (VOIR DOCUMENT SÉPARÉ)
 * 
 * Connexions Arduino -> SD Shield :
 * - 5V      -> VCC
 * - GND     -> GND
 * - Pin 5   -> CS (Chip Select)
 * - Pin 11  -> MOSI
 * - Pin 12  -> MISO
 * - Pin 13  -> SCK
 * 
 * Capteurs :
 * - A0 -> Capteur position (0-1023)
 * - A1 -> Capteur température (0-1023)
 * - GND -> Masse commune
 * 
 * FICHIERS GÉNÉRÉS
 * 
 * La première exécution crée "system.log" sur la carte SD.
 * Après 1 Mo, un nouveau fichier "data_1.log" est créé.
 * 
 * Format du fichier :
 * 00:00:12 [INFO] = Système démarré
 * 00:00:14 [INFO] Valeur capteur : 512
 * 00:01:03 [WARN] Seuil critique dépassé !
 * 
 * DIAGNOSTIC
 * 
 * - Serial Monitor à 115200 bauds
 * - Messages en temps réel affichés
 * - Vérifier la présence de la carte SD
 * - Vérifier l'alimentation 5V du shield
 */
