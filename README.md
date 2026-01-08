# Projet Barriere de Parking - Partie DataLogger

Module de journalisation des donnees liees au systeme.

## Description

Ce projet consiste a logger les donnees des capteurs lies au systeme de Barriere de Parking. Il utilise une carte SD pour stocker les informations avec differents niveaux de priorite (INFO, WARN, ERROR).

## Pour Commencer

### Pre-requis

* Arduino IDE
* Windows 10/11 ou MacOS

### Installation

1. Telecharger le dossier du projet.
2. S'assurer que les bibliotheques `SD.h` et `SPI.h` sont installees dans l'IDE Arduino.

### Execution

1. Connecter le module de carte SD a l'Arduino (voir schema de cablage).
2. Ouvrir le fichier `ParkingBarrierDemo.ino` dans le dossier `examples`.
3. Compiler et televerser le programme.
4. Ouvrir le moniteur serie (115200 bauds).
5. Le code initialise la carte SD et commence a logger les donnees.

## Auteurs

* **Claverie Dimitri** - dimitri.claverie@limayrac.fr
* **Peux Axel** - axel.peux@limayrac.fr

## Historique des versions

* 0.2
    * Corrections de bugs divers et optimisations
    * Compatibilite multi-plateforme (Mac/Windows)
* 0.1
    * Version initiale