# Project Barrière de Parking - Partie DataLogger

Logger les données lier au système.

## Description

Ce projet consiste à Logger les données des capteurs lier au système de Barrière de Parking. 

## Getting Started

### Dependencies

* Arduino 
* Windows 10/ Windoows 11
* MacOS 

### Installing

* mettre le code dans un dossier.
* installer les dépendances : SD.h et SPI.h

### Executing program

* Connecter le lecteur de carte SD au arduino.
* Faire les branchement avec le schème de cablage.
* Lancer le programme.
* Le code initialise la carte SD.
* Affiche un code d'erreur si la carte SD ne peux être initialiser.
* Logs des données de test dans un fichier TXT.
* Quand le fichier fait 1Mo cela créer un nouveau fichier.
* Arreter le code.
* Débrancher la carte.
* Connecter ensuite la Carte SD a un ordinateur et regarder le fichier créer. 
  
```

```

## Help

Problème Possible 
```
Probable que la carte s'ignitialise pas au premier lancement. 
```

## Authors

Contributors names and contact info

 Claverie Dimitri  
 [@dimitricl](dimitri.claverie@limayrac.fr)
 Peux Axel
 [@](axel.peux@limayrac.fr)

## Version History

* 0.2
    * Various bug fixes and optimizations
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release

## Acknowledgments

Inspiration, code snippets, etc.
* []()
