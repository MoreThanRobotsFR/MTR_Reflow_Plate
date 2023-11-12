# Documentation de l'API

## Introduction
Cette API vous permet de contrôler la température d'une plaque de refusion. Elle fournit des points de terminaison pour récupérer la température actuelle, définir la température souhaitée, démarrer et arrêter le processus de refusion, et configurer les paramètres de chaque zone de refusion.

## Points de terminaison

### Récupérer la température actuelle
- Méthode : `GET`
- Point de terminaison : `/readTemperature`
- Réponse : La température actuelle en degrés Celsius

### Récupérer la température de consigne
- Méthode : `GET`
- Point de terminaison : `/readSetPoint`
- Réponse : La température de consigne souhaitée en degrés Celsius

### Démarrer le processus de refusion
- Méthode : `GET`
- Point de terminaison : `/start`
- Réponse : Aucune

### Arrêter le processus de refusion
- Méthode : `GET`
- Point de terminaison : `/stop`
- Réponse : Aucune

### Définir le mode manuel
- Méthode : `POST`
- Point de terminaison : `/manu`
- Paramètres de la requête :
  - `manuMode` : le mode souhaité (0 pour automatique, 2 pour manuel)
- Réponse : Aucune

### Définir la température manuelle
- Méthode : `POST`
- Point de terminaison : `/manuSetTemperature`
- Paramètres de la requête :
  - `manuTemperature` : la température souhaitée en degrés Celsius
- Réponse : Aucune

### Définir les paramètres de refusion
- Méthode : `POST`
- Point de terminaison : `/params`
- Paramètres de la requête :
  - `temps_zone_preheating` : la durée de la zone de préchauffage en secondes
  - `temperature_zone_preheating` : la température de la zone de préchauffage en degrés Celsius
  - `temps_zone_recirculation` : la durée de la zone de recirculation en secondes
  - `temperature_zone_recirculation` : la température de la zone de recirculation en degrés Celsius
  - `temps_zone_reflow` : la durée de la zone de refusion en secondes
  - `temperature_zone_reflow` : la température de la zone de refusion en degrés Celsius
  - `temps_zone_cooling` : la durée de la zone de refroidissement en secondes
  - `temperature_zone_cooling` : la température de la zone de refroidissement en degrés Celsius
- Réponse : Aucune

### Récupérer les paramètres de refusion
- Méthode : `GET`
- Point de terminaison : `/getParams`
- Réponse : Les paramètres de refusion actuels sous la forme d'un objet JSON avec les propriétés suivantes :
  - `temps_zone_preheating` : la durée de la zone de préchauffage en secondes
  - `temperature_zone_preheating` : la température de la zone de préchauffage en degrés Celsius
  - `temps_zone_recirculation` : la durée de la zone de recirculation en secondes
  - `temperature_zone_recirculation` : la température de la zone de recirculation en degrés Celsius
  - `temps_zone_reflow` : la durée de la zone de refusion en secondes
  - `temperature_zone_reflow` : la température de la zone de refusion en degrés Celsius
  - `temperature_zone_cooling` : la température de la zone de refroidissement en degrés Celsius

## Explication des modes

### Mode automatique
En mode automatique, le processus de refusion suit un profil de température prédéfini qui comprend quatre zones : préchauffage, recirculation, refusion et refroidissement. La durée et la température de chaque zone peuvent être configurées à l'aide du point de terminaison `/params`.

Pour démarrer le processus de refusion en mode automatique, envoyez une requête GET au point de terminaison `/start`. Le processus de refusion s'exécutera conformément aux paramètres configurés jusqu'à ce qu'il atteigne la zone de refroidissement. À la fin de la zone de refroidissement, le processus s'arrêtera automatiquement.

Pour arrêter le processus de refusion, envoyez une requête GET au point de terminaison `/stop`.

### Mode manuel
En mode manuel, vous pouvez définir une température souhaitée pour la plaque de refusion. La plaque de refusion chauffera ou refroidira jusqu'à atteindre la température souhaitée.

Pour activer le mode manuel, envoyez une requête POST au point de terminaison `/manu` avec le paramètre `manuMode` défini sur 2. Cela activera le mode manuel.

Pour définir la température souhaitée en mode manuel, envoyez une requête POST au point de terminaison `/manuSetTemperature` avec le paramètre `manuTemperature` défini sur la température souhaitée en degrés Celsius.

Pour commencer à chauffer ou à refroidir la plaque de refusion en mode manuel, envoyez une requête GET au point de terminaison `/manuStart`.

Pour arrêter le processus de chauffage ou de refroidissement en mode manuel, envoyez une requête GET au point de terminaison `/manuStop`.

## Gestion des erreurs
En cas d'erreur, le serveur répondra avec un code d'état HTTP approprié et un message d'erreur dans le corps de la réponse.

Codes d'erreur possibles :
- 400 : Requête incorrecte - La requête est invalide ou des paramètres obligatoires sont manquants.
- 404 : Non trouvé - La ressource ou le point de terminaison demandé n'existe pas.
- 500 : Erreur interne du serveur - Une erreur inattendue s'est produite sur le serveur.