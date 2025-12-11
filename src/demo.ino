#include "DataLogger.h"

DataLogger logger("system.log", 5);

void setup() {
    Serial.begin(115200);
    delay(1000);

    if (!logger.begin()) {
        Serial.println("Impossible d'initialiser la SD !");
        while (true);
    }

    logger.log("Système démarré", INFO);
}

void loop() {
    int sensorValue = analogRead(A0);

    logger.log("Valeur capteur : " + String(sensorValue), INFO);

    if (sensorValue > 900) {
        logger.log("Seuil critique dépassé !", WARN);
    }

    if (sensorValue < 10) {
        logger.log("Erreur : capteur déconnecté ?", ERROR);
    }

    delay(2000);
}
