# CAHIER DES CHARGES - MODULE DATALOGGER
## Système de Barrière de Parking - Partie Gestion des Logs

---

## 1. OBJECTIFS

Créer un module de journalisation (logging) pour enregistrer les événements du système de barrière de parking sur une carte SD. Le module doit gérer automatiquement l'espace disque et archiver les données avec des niveaux de priorité.

---

## 2. FONCTIONNALITÉS PRINCIPALES

### 2.1 Initialisation
- Interface SD via protocole SPI
- Pin CS configurable
- Vérification de la disponibilité de la carte SD
- Signalisation de l'état (OK/ERREUR)

### 2.2 Journalisation
- Trois niveaux de log : INFO, WARN, ERROR
- Horodatage automatique (HH:MM:SS)
- Formatage standardisé des messages
- Affichage en temps réel sur le port série

### 2.3 Gestion de l'espace disque
- Limite de taille par fichier : 1 Mo
- Rotation automatique des fichiers (data_0.log, data_1.log, etc.)
- Pas de perte de données lors du changement de fichier

### 2.4 Fiabilité
- Gestion des erreurs d'ouverture de fichier
- État prêt vérifiable avant utilisation
- Fermeture correcte des fichiers après chaque écriture

---

## 3. INTERFACES ÉLECTRIQUES

### 3.1 Connexions SD Shield
| Broche Arduino | Broche SD Shield | Fonction |
|---|---|---|
| 5V | VCC | Alimentation +5V |
| GND | GND | Masse |
| Pin 5 (configurable) | CS | Chip Select |
| MOSI (Pin 11) | MOSI | Données vers SD |
| MISO (Pin 12) | MISO | Données depuis SD |
| SCK (Pin 13) | SCK | Horloge SPI |

### 3.2 Capteurs de données (exemple)
| Broche Arduino | Capteur | Type | Utilisation |
|---|---|---|---|
| A0 | Capteur position | Analogique | Détection barrière |
| A1 | Capteur température | Analogique | Surveillance thermique |

---

## 4. SPÉCIFICATIONS TECHNIQUES

### 4.1 Matériel requis
- Arduino Uno/Mega/Nano compatible
- Carte SD (Fat32, max 32 Go)
- SD Shield avec support SPI
- Câblage (breadboard, fils)

### 4.2 Logiciel requis
- Arduino IDE 1.8.x ou supérieur
- Librairies : SD.h, SPI.h (incluses par défaut)

### 4.3 Performance
- Temps d'initialisation : < 2 secondes
- Latence d'écriture : < 100 ms
- Fréquence d'écriture : jusqu'à 2 fois par seconde

---

## 5. COMPORTEMENT DU SYSTÈME

### 5.1 Démarrage
1. Initialisation série (115200 bauds)
2. Tentative de connexion à la carte SD
3. Affichage du résultat (OK ✅ / Échec ❌)
4. Pause de 1 seconde
5. Démarrage du système

### 5.2 En fonctionnement
1. Lecture capteur (chaque 2 secondes)
2. Enregistrement de la valeur dans le log
3. Contrôle des seuils
4. Génération d'alertes si nécessaire

### 5.3 Rotation de fichiers
- Vérification de la taille avant chaque écriture
- Si taille > 1 Mo : création de nouveau fichier
- Incrémentation automatique de l'index

---

## 6. FORMAT DES MESSAGES

```
HH:MM:SS [NIVEAU] Message utilisateur
```

Exemple :
```
00:00:12 [INFO] Système démarré
00:00:14 [INFO] Valeur capteur : 512
00:01:03 [WARN] Seuil critique dépassé !
00:02:45 [ERROR] Erreur : capteur déconnecté ?
```

---

## 7. FICHIERS LIVRABLES

| Fichier | Description |
|---|---|
| DataLogger.h | Déclaration de classe et interfaces publiques |
| DataLogger.cpp | Implémentation du module |
| demo.ino | Exemple d'utilisation complet |
| schéma_connexions.pdf | Schéma électrique du montage |
| recette_test.h + .cpp | Tests et validation du module |

---

## 8. CRITÈRES D'ACCEPTATION

- ✅ Module compile sans erreur
- ✅ Carte SD s'initialise correctement
- ✅ Les logs s'écrivent dans le fichier
- ✅ Horodatage correct
- ✅ Rotation de fichier à 1 Mo
- ✅ Pas de perte de données
- ✅ Messages affichés en serial
- ✅ Gestion d'erreurs complète
