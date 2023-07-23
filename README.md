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
- Activer le mode manuel :
  ```
  POST /manu
  Content-Type: application/x-www-form-urlencoded
  
  manuMode=1
  ```
- Définir la température de consigne en mode manuel :
  ```
  POST /manuSetTemperature
  Content-Type: application/x-www-form-urlencoded
  
  manuTemperature=150
  ```

## Auteur
Ce projet a été développé par Ciciliano Altmann pour MTR (MoreThanRobots).

## Licence
Ce projet est distribué sous licence MIT. Veuillez consulter le fichier "LICENSE" pour plus d'informations.