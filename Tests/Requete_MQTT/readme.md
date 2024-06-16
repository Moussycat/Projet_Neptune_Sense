# Test Requête MQTT

## Matériel utilisé

#### Carte ESP32

- ESP32 WROOM WIFI
- Arduino IDE

#### Carte finale

##### station de base

- ESP32 WROOM
- Arduino IDE

## Configuration logiciel

#### Carte Arduino UNO & carte finale

Utilisation du logiciel Arduino IDE, ne pas oublier d'ajouter le ssid et mot de passe dans le code pour ajouter un réseau WiFi.

## Les résultats attendus

#### Carte ESP32 & carte finale

1- Le code doit scruter tous les réseaux enregistrés dans le code et se connecter au réseau disponible.

2- Envoi d'un message via un MQTT broker public. Lorsque j'envoie un message, l'ESP32 doit recevoir le message et l'afficher.

## Les résultats obtenus

> [!WARNING]
> Pour utiliser votre Iphone comme point d'accès, n'oubliez pas de cocher la case "Maximiser la compatibilité". Sans cette activation, la connexion ne pourra se faire.

#### Carte ESP32

1- Connexion entre un point d'accès téléphone et box internet réussi.

![Screen Wifi OK](/Tests/Requete_MQTT/WiFi_OK.png)

2- Le message est bien affiché.

![Screen MQTT broker](/Tests/Requete_MQTT/MQTT_broker.png)

#### Carte finale
