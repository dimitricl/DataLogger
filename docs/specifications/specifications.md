# CAHIER DES CHARGES - MODULE DATALOGGER
## Systeme de Barriere de Parking - Partie Gestion des Logs

---

## 1. OBJECTIFS

Creer un module de journalisation (logging) pour enregistrer les evenements du systeme de barriere de parking sur une carte SD. Le module doit gerer automatiquement l'espace disque et archiver les donnees avec des niveaux de priorite.

---

## 2. FONCTIONNALITES PRINCIPALES

### 2.1 Initialisation
- Interface SD via protocole SPI
- Pin CS configurable
- Verification de la disponibilite de la carte SD
- Signalisation de l'etat (OK/ERREUR)

### 2.2 Journalisation
- Trois niveaux de log : INFO, WARN, ERROR
- Horodatage automatique (HH:MM:SS)
- Formatage standardise des messages
- Affichage en temps reel sur le port serie

### 2.3 Gestion de l'espace disque
- Limite de taille par fichier : 1 Mo
- Rotation automatique des fichiers
- Pas de perte de donnees lors du changement de fichier

---

## 3. COMPORTEMENT DU SYSTEME

### 3.1 Demarrage
1. Initialisation serie (115200 bauds)
2. Tentative de connexion a la carte SD
3. Affichage du resultat
4. Pause de 1 seconde
5. Demarrage du systeme

### 3.2 En fonctionnement
1. Lecture capteur (chaque 2 secondes)
2. Enregistrement de la valeur dans le log
3. Controle des seuils
4. Generation d'alertes si necessaire

### 3.3 Rotation de fichiers
- Verification de la taille avant chaque ecriture
- Si taille > 1 Mo : creation de nouveau fichier