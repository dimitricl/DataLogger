# RECETTE DE TEST - MODULE DATALOGGER
## Validation fonctionnelle et d'integration

**Projet :** Barriere de Parking - Gestion des logs  
**Module :** DataLogger v0.2  

---

## 1. PREPARATION DE L'ENVIRONNEMENT

### 1.1 Materiel a preparer
- [ ] Arduino Uno (ou compatible)
- [ ] SD Shield + cables SPI
- [ ] Carte SD formatee en FAT32 (max 32 Go)

### 1.2 Configuration logicielle
- [ ] Arduino IDE ouvert
- [ ] Librairies SD.h et SPI.h verifiees
- [ ] Port serie detecte
- [ ] Vitesse de transmission : 115200 bauds

---

## 2. TESTS DE VALIDATION FINALE

### Checklist d'acceptation

- [ ] Compilation sans erreur
- [ ] Initialisation SD correcte
- [ ] Horodatage fonctionnel
- [ ] Trois niveaux de log operationnels
- [ ] Fichier cree et persistant
- [ ] Rotation automatique a 1 Mo
- [ ] Capteurs lus correctement
- [ ] Seuils detectes et alertes generees
- [ ] Gestion d'erreurs robuste

### Remarques finales

Code compile et teste. Prets pour deploiement.