# MTR Reflow Plate

## Description du projet
Le projet MTR Reflow Plate est un contrôleur de température pour une plaque de refusion. Il permet de réguler la température de la plaque et de suivre les différentes zones de température lors du processus de refusion.

## Plateforme matériel
La plateforme matérielle utilisée est l'ESP32 DevKit V1, un microcontrôleur à base de WiFi et Bluetooth intégré. Elle est utilisée en combinaison avec un capteur de température MAX31865 et un corps chauffant.

## Installation du firmware
Le code du firmware se trouve dans le répertoire "fireware".

### Prérequis
- La version du logiciel Arduino IDE utilisée doit être compatible avec l'ESP32.
- Les bibliothèques suivantes doivent être installées via le gestionnaire de bibliothèques d'Arduino :
  - Wire
  - SPI
  - AutoPID
  - Adafruit_MAX31865
  - ESPAsyncWebServer
  - SPIFFS

### Configuration du matériel
1. Connectez le capteur de température MAX31865 à l'ESP32 comme suit :
   - CS du MAX31865 à la broche 5 de l'ESP32
   - MOSI du MAX31865 à la broche 23 de l'ESP32
   - MISO du MAX31865 à la broche 19 de l'ESP32
   - CLK du MAX31865 à la broche 18 de l'ESP32
2. Connectez le corps chauffant à la broche 4 de l'ESP32.

### Téléchargement et configuration du firmware
1. Téléchargez le code source du firmware depuis le répertoire "fireware".
2. Ouvrez le fichier "MTR_Reflow_Plate/fireware/src/main.cpp" dans l'IDE Arduino.
3. Modifiez les paramètres de température et de durée des différentes zones selon vos besoins.
4. Si vous souhaitez personnaliser le nom du réseau et le mot de passe WiFi, modifiez les variables ssid et password dans le fichier "MTR_Reflow_Plate/fireware/src/main.cpp".
5. Compilez le code et téléchargez-le sur votre ESP32.

## Utilisation de l'interface utilisateur
Lorsque le firmware est correctement chargé sur l'ESP32, vous pouvez accéder à l'interface utilisateur depuis un navigateur Web en entrant l'adresse IP attribuée à l'ESP32.

L'interface utilisateur dispose de plusieurs fonctionnalités :
- **Temperature**: Affiche la valeur actuelle de la température.
- **SET Params**: Permet de définir les paramètres de température et de durée des différentes zones.
- **START**: Démarre le processus de refusion selon les paramètres définis.
- **STOP**: Arrête le processus de refusion.
- **MANU**: Permet de passer en mode de contrôle manuel de la température.
- **Chart**: Affiche un graphique des températures mesurées.

## Exemple de code pour l'utilisation de l'API REST
Il est possible de contrôler la refusion en utilisant l'API REST fournie par l'ESP32.

Voici quelques exemples d'utilisation de l'API REST :
- Récupérer la température actuelle :
  ```
  GET /readTemperature
  ```
- Récupérer la consigne de température actuelle :
  ```
  GET /readSetPoint
  ```
- Définir les paramètres de température et de durée des différentes zones :
  ```
  POST /params
  Content-Type: application/x-www-form-urlencoded
  
  temps_zone_preheating=100000&temperature_zone_preheating=80&temps_zone_recirculation=100000&temperature_zone_recirculation=120&temps_zone_reflow=10000&temperature_zone_reflow=183&temperature_zone_cooling=23
  ```
Pour plus d'informations sur l'utilisation de l'API REST, veuillez consulter le fichier [fireware/MTR_Reflow_Plate/data/README.md](./fireware/MTR_Reflow_Plate/data/README.md).

## Documentation de l'interface web

### Introduction
L'interface web de la plaque de refusion MTR permet de visualiser la température actuelle, de contrôler le mode de fonctionnement (automatique ou manuel) et de configurer les paramètres de refusion. Cette documentation présente les pages principales de l'interface : index.html, manu.html et chart.html.

### index.html
La page index.html est la page d'accueil de l'interface web de la plaque de refusion MTR. Elle permet de visualiser la température actuelle, de configurer les paramètres de refusion et de contrôler le démarrage et l'arrêt du processus de refusion. La page comprend les sections suivantes :

- **Température actuelle** : Affiche la température actuelle de la plaque de refusion en degrés Celsius.
- **Configuration des paramètres** : Permet de définir les temps et les températures de chaque zone de refusion (préchauffage, recirculation, refusion et refroidissement).
- **Boutons de contrôle** : Permettent de démarrer ou d'arrêter le processus de refusion, ainsi que de passer en mode manuel.
- **Affichage des paramètres** : Affiche les paramètres de refusion actuels.

<p align="center">
<img src="./images/index.png" alt="index.html" width="500"/>
</p>

### manu.html
La page manu.html permet de contrôler la plaque de refusion en mode manuel. Elle affiche la température actuelle et permet de définir une température manuelle. La page comprend les sections suivantes :

- **Température actuelle** : Affiche la température actuelle de la plaque de refusion en degrés Celsius.
- **Définition de la température manuelle** : Permet de définir une température manuelle pour la plaque de refusion.
- **Boutons de contrôle** : Permettent de démarrer ou d'arrêter le chauffage ou le refroidissement de la plaque de refusion.

<p align="center">
<img src="./images/manu.png" alt="manu.html" width="500"/>
</p>

### chart.html
La page chart.html affiche un graphique en temps réel de la température de la plaque de refusion. Le graphique est mis à jour automatiquement toutes les quelques secondes et affiche la température actuelle ainsi que la température de consigne. La page comprend les sections suivantes :

- **Graphique de température** : Affiche le graphique en temps réel de la température de la plaque de refusion et de la température de consigne.

<p align="center">
<img src="./images/chart.png" alt="chart.html" width="800"/>
</p>

### Conclusion
L'interface web de la plaque de refusion MTR offre une visualisation claire de la température actuelle de la plaque, ainsi que des fonctionnalités de contrôle et de configuration pour le processus de refusion. Les pages index.html, manu.html et chart.html fournissent une interface conviviale pour interagir avec la plaque de refusion et surveiller le processus de refusion en temps réel.

## Auteur
Ce projet a été développé par Ciciliano Altmann pour MTR (MoreThanRobots).

## Licence
Ce projet est distribué sous licence MIT. Veuillez consulter le fichier "LICENSE" pour plus d'informations.