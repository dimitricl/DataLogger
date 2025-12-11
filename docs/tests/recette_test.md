# 📋 RECETTE DE TEST - MODULE DATALOGGER
## Validation fonctionnelle et d'intégration

**Projet :** Barrière de Parking - Gestion des logs  
**Module :** DataLogger v0.2  
**Date :** Décembre 2024  
**Testeur :** [Nom]  
**Date de test :** [Date]  

---

## 1. PRÉPARATION DE L'ENVIRONNEMENT

### 1.1 Matériel à préparer
- [ ] Arduino Uno (ou compatible)
- [ ] SD Shield + câbles SPI
- [ ] Carte SD formatée en FAT32 (max 32 Go)
- [ ] Câble USB pour alimentation et programmation
- [ ] Capteur analogique (ou résistance variable)
- [ ] Breadboard et fils de connexion
- [ ] Ordinateur avec Arduino IDE 1.8+

### 1.2 Configuration logicielle
- [ ] Arduino IDE ouvert
- [ ] Librairies SD.h et SPI.h vérifiées (incluses par défaut)
- [ ] Port série détecté (Tools → Port)
- [ ] Carte Arduino sélectionnée (Tools → Board)
- [ ] Vitesse de transmission : 115200 bauds

### 1.3 Placement des fichiers
```
MonProjet/
├── DataLogger.h
├── DataLogger.cpp
├── demo.ino
└── recette_test.md
```

**Résultat :** ✅ Environnement opérationnel

---

## 2. TESTS DE COMPILATION

### Test 2.1 : Compilation sans erreur

**Procédure :**
1. Ouvrir demo.ino dans Arduino IDE
2. Cliquer sur "Vérifier" (Sketch → Verify)
3. Attendre la fin de la compilation

**Résultat attendu :**
```
Vérification terminée
Taille du sketch: XX bytes (XX% de 30720 bytes)
```

- [ ] **PASS** : Compilation réussie sans erreur
- [ ] **FAIL** : Erreurs détectées → Consulter la console Arduino

**Erreurs communes :**
- `'DataLogger' was not declared in this scope` → Vérifier #include "DataLogger.h"
- `SD.h: No such file or directory` → Installer les librairies manquantes

---

## 3. TESTS MATÉRIELS (PRÉ-UPLOAD)

### Test 3.1 : Câblage SD Shield

**Procédure :**
1. Arduino débranché de l'USB
2. Vérifier chaque connexion avec la table :

| Broche Arduino | SD Shield | État |
|---|---|---|
| 5V | VCC | ✅ |
| GND | GND | ✅ |
| Pin 5 | CS | ✅ |
| Pin 11 | MOSI | ✅ |
| Pin 12 | MISO | ✅ |
| Pin 13 | SCK | ✅ |

3. Vérifier que la carte SD est bien insérée dans le slot
4. Vérifier l'alimentation 5V stable (multimètre : 4.8-5.2V)

- [ ] **PASS** : Tous les branchements vérifiés
- [ ] **FAIL** : Branchement incorrect → Rectifier

---

## 4. TESTS FONCTIONNELS (POST-UPLOAD)

### Test 4.1 : Initialisation système

**Procédure :**
1. Connecter Arduino en USB
2. Ouvrir Serial Monitor (115200 bauds)
3. Attendre 2 secondes

**Résultat attendu :**
```
=== DÉMARRAGE SYSTÈME ===
Barrière de Parking - Module DataLogger v0.2

Initialisation de la carte SD... OK ✅
```

- [ ] **PASS** : Message "OK ✅" affiché
- [ ] **FAIL** : Message "Échec ❌" → Vérifier SD + câblage
- [ ] **FAIL** : Aucun message → Vérifier baud rate et port série

**Diagnostic en cas d'échec :**
- Carte SD non détectée → Formater en FAT32 et réessayer
- Broche CS incorrecte → Vérifier pin 5 et DataLogger.ino (ligne 3)
- Alimentation insuffisante → Vérifier 5V avec multimètre

---

### Test 4.2 : Enregistrement des logs (démarrage)

**Procédure :**
1. Laisser tourner 5 secondes après initialisation
2. Vérifier la sortie série

**Résultat attendu :**
```
00:00:00 [INFO] === SYSTÈME DÉMARRÉ ===
00:00:00 [INFO] Barrière de Parking - v0.2
00:00:00 [INFO] Module DataLogger activé
00:00:02 [INFO] Valeur capteur position : 512
```

- [ ] **PASS** : Messages enregistrés avec horodatage
- [ ] **FAIL** : "⚠️ SD non initialisée !" → Remonter à 4.1
- [ ] **FAIL** : "❌ Impossible d'ouvrir le fichier !" → Vérifier carte SD

---

### Test 4.3 : Horodatage correct

**Procédure :**
1. Noter l'heure du premier message (ex: 00:00:12)
2. Laisser tourner 10 secondes
3. Vérifier que les horodatages progressent

**Résultat attendu :**
```
00:00:12 [INFO] Valeur capteur : 512
00:00:14 [INFO] Valeur capteur : 518
00:00:16 [INFO] Valeur capteur : 515
...
00:00:22 [INFO] Valeur capteur : 520
```

- [ ] **PASS** : Horodatages croissants par pas de 2 secondes
- [ ] **FAIL** : Horodatages fixes ou décroissants → Problème getTimestamp()

---

### Test 4.4 : Lecture du capteur A0

**Procédure :**
1. Connecter un capteur analogique ou une résistance variable à A0
2. Observer les valeurs affichées (3 lectures)
3. Faire varier manuellement la résistance

**Résultat attendu :**
```
00:00:14 [INFO] Valeur capteur position : 512
00:00:16 [INFO] Valeur capteur position : 450
00:00:18 [INFO] Valeur capteur position : 600
```

- [ ] **PASS** : Valeurs varient entre 0 et 1023
- [ ] **FAIL** : Valeur fixe 0 ou 1023 → Vérifier câblage capteur
- [ ] **FAIL** : Valeurs aberrantes (>1023) → Vérifier GND

---

### Test 4.5 : Niveaux de log

**Procédure :**
1. Modifier demo.ino pour tester les trois niveaux :

```cpp
logger.log("Test INFO", INFO);
logger.log("Test WARN", WARN);
logger.log("Test ERROR", ERROR);
```

2. Téléverser et observer la sortie

**Résultat attendu :**
```
00:00:12 [INFO] Test INFO
00:00:12 [WARN] Test WARN
00:00:12 [ERROR] Test ERROR
```

- [ ] **PASS** : Les trois niveaux s'affichent correctement
- [ ] **FAIL** : "UNKNOWN" au lieu du niveau → Vérifier levelToString()

---

### Test 4.6 : Détection de seuils

**Procédure :**
1. Augmenter progressivement la tension sur A0
2. Dépasser le seuil 900 pour déclencher une alerte
3. Descendre sous 10 pour simuler une erreur

**Résultat attendu :**
```
00:00:30 [INFO] Valeur capteur position : 910
00:00:30 [WARN] ⚠️  ALERTE : Seuil critique dépassé ! (910 > 900)
00:01:12 [INFO] Valeur capteur position : 5
00:01:12 [ERROR] ❌ ERREUR : Capteur position peut être déconnecté ! Valeur: 5
```

- [ ] **PASS** : Alerte et erreur générées correctement
- [ ] **FAIL** : Seuils non détectés → Vérifier demo.ino lignes 75-85

---

## 5. TESTS D'INTÉGRATION (FICHIER SD)

### Test 5.1 : Création du fichier log

**Procédure :**
1. Arrêter le programme (débrancher Arduino)
2. Retirer la carte SD
3. Connecter la carte SD à un ordinateur
4. Ouvrir l'explorateur de fichiers

**Résultat attendu :**
```
Carte SD /
├── system.log  (250 Ko approx)
└── [autres fichiers...]
```

- [ ] **PASS** : Fichier "system.log" présent
- [ ] **FAIL** : Aucun fichier → Vérifier l'initialisation SD
- [ ] **FAIL** : Fichier vide → Problème d'écriture

---

### Test 5.2 : Format du fichier log

**Procédure :**
1. Ouvrir "system.log" avec un éditeur texte (Notepad, VS Code)
2. Vérifier les 10 premières lignes

**Résultat attendu :**
```
00:00:00 [INFO] === SYSTÈME DÉMARRÉ ===
00:00:00 [INFO] Barrière de Parking - v0.2
00:00:00 [INFO] Module DataLogger activé
00:00:02 [INFO] Valeur capteur position : 512
00:00:02 [INFO] Température : 345 (brut)
00:00:04 [INFO] Valeur capteur position : 516
00:00:04 [INFO] Température : 344 (brut)
...
```

- [ ] **PASS** : Format correct "HH:MM:SS [NIVEAU] message"
- [ ] **FAIL** : Format incorrect → Vérifier getTimestamp() et levelToString()
- [ ] **FAIL** : Caractères spéciaux mal affichés → Vérifier encodage UTF-8

---

### Test 5.3 : Persistance des données

**Procédure :**
1. Laisser tourner le système 30 secondes
2. Faire une première sauvegarde du fichier
3. Relancer le programme 30 secondes
4. Comparer les deux sauvegardes

**Résultat attendu :**
```
Fichier log après 60 secondes de test :
- ~30 lignes (1 toutes les 2 secondes)
- Pas de doublons
- Chronologie respectée
```

- [ ] **PASS** : Données persistantes et chronologiques
- [ ] **FAIL** : Données perdues au redémarrage → Problème fichier
- [ ] **FAIL** : Doublons → Problème ouverture/fermeture fichier

---

### Test 5.4 : Rotation de fichiers (1 Mo)

**Procédure :**
1. Créer un test long (1 heure) avec très haute fréquence :

```cpp
// Dans loop(), changer delay(2000) à delay(10)
delay(10);  // Environ 100 logs/seconde
```

2. Laisser tourner jusqu'à atteindre ~1 Mo
3. Vérifier la création d'un nouveau fichier

**Résultat attendu :**
```
Logs :
⚠️ Taille max atteinte → nouveau fichier

Fichiers sur SD :
├── system.log     (1 Mo) 
└── data_1.log     (xx Ko en cours)
```

- [ ] **PASS** : Nouveau fichier créé automatiquement
- [ ] **FAIL** : Pas de rotation → Vérifier MAX_LOG_SIZE
- [ ] **FAIL** : Perte de logs → Vérifier gestion fichier

---

## 6. TESTS DE ROBUSTESSE

### Test 6.1 : Sans carte SD insérée

**Procédure :**
1. Retirer la carte SD
2. Téléverser le code
3. Observer la sortie série

**Résultat attendu :**
```
Initialisation de la carte SD... Échec ❌
❌ Impossible d'initialiser la SD !
```

- [ ] **PASS** : Message d'erreur clair
- [ ] **FAIL** : Crash ou boucle infinie → Améliorer gestion erreurs

---

### Test 6.2 : Redémarrages multiples

**Procédure :**
1. Redémarrer l'Arduino 5 fois (appui sur reset ou débrancher/rebrancher USB)
2. Vérifier que le fichier n'est pas corrompu à chaque redémarrage

**Résultat attendu :**
```
Après 5 redémarrages :
- Le fichier se maintient à 1 Mo max
- Pas de fichiers corrompus
- Numérotation cohérente (data_1, data_2, ...)
```

- [ ] **PASS** : Système robuste aux redémarrages
- [ ] **FAIL** : Fichier corrompu → Problème gestion FAT32

---

### Test 6.3 : Déconnexion USB pendant l'écriture

**Procédure :**
1. Lancer le code normalement
2. Après 10 secondes, débrancher le câble USB brutalement
3. Attendre 5 secondes
4. Rebrancher et vérifier l'état

**Résultat attendu :**
```
- Pas de crash Arduino
- Fichier lisible (pas de corruption critique)
```

- [ ] **PASS** : Coupure supportée sans corruption
- [ ] **FAIL** : Fichier corrompu → Améliorer fermeture fichier

---

## 7. TESTS DE PERFORMANCE

### Test 7.1 : Latence d'écriture

**Procédure :**
1. Activer les timestamps dans le code
2. Mesurer le délai entre appel de log() et affichage série

```cpp
unsigned long before = micros();
logger.log("Test latence", INFO);
unsigned long after = micros();
Serial.println("Latence : " + String(after - before) + " µs");
```

**Résultat attendu :** < 100 ms

- [ ] **PASS** : Latence < 100 ms
- [ ] **WARN** : Latence 100-500 ms (acceptable)
- [ ] **FAIL** : Latence > 500 ms → Optimiser SD.open()

---

### Test 7.2 : Consommation mémoire

**Procédure :**
1. Consulter la console Arduino IDE lors de la compilation
2. Vérifier le ratio utilisé/disponible

**Résultat attendu :**
```
Taille du sketch: 8500 bytes (28% de 30720 bytes)
```

- [ ] **PASS** : < 70% de la mémoire utilisée
- [ ] **WARN** : 70-90% → Optimiser si possible
- [ ] **FAIL** : > 90% → Réduire la taille du code

---

## 8. VALIDATION FINALE

### Checklist d'acceptation

- [ ] ✅ Compilation sans erreur
- [ ] ✅ Initialisation SD correcte
- [ ] ✅ Horodatage fonctionnel
- [ ] ✅ Trois niveaux de log opérationnels
- [ ] ✅ Fichier créé et persistant
- [ ] ✅ Rotation automatique à 1 Mo
- [ ] ✅ Capteurs lus correctement
- [ ] ✅ Seuils détectés et alertes générées
- [ ] ✅ Gestion d'erreurs robuste
- [ ] ✅ Performance acceptable

### Signature de validation

| Rôle | Nom | Signature | Date |
|---|---|---|---|
| **Testeur** | | | |
| **Validateur** | | | |
| **Responsable Projet** | | | |

### Remarques finales

```
_____________________________________________
_____________________________________________
_____________________________________________
```

---

## DOCUMENTATION UTILE

- Brochage Arduino : https://www.arduino.cc/en/Reference/AnalogRead
- Protocole SPI : https://fr.wikipedia.org/wiki/Serial_Peripheral_Interface
- FAT32 sur SD : https://www.arduino.cc/en/Reference/SD
- Débogage : Utiliser Serial.println() et Serial Monitor
