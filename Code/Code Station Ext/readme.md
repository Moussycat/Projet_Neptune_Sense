# Code Station extérieure

## Configuration

Logiciel `Aduino IDE 2.3.2`

Librairie `ArduinoJson.h`, `STM32LoRaWAN.h`, `DHT.h`, `LTC2941.h`, `Arduino.h`, `OneWire.h`,`DallasTemperature.h`,

Carte utilisée `STM32WL55JC1` par ST Microelectronics. Pour pouvoir utiliser l'IDE Arduino, suivez les instructions de [stm32duino](https://github.com/stm32duino/Arduino_Core_STM32?tab=readme-ov-file).

> [!WARNING]  
> Si vous devez modifier vos PATH, soyez vigilent à ne pas supprimer des éléments déjà présents. Si c'est le cas, surtout n'éteignez pas votre ordinateur et essayé de suivre cette [aide](https://superuser.com/questions/523688/how-to-restore-the-path-environment-variable-i-deleted)

## But du code

Récupérer les données des différents capteurs et les mettre dans un JSON qui doit s'envoyer ensuite en Lora à la gateway de l'ESEO.

## Pins

#### Carte STM32WL55JC1

| STM32 | TEMP EAU | TEMP EXT | MODULE PH | JAUGE BATTERIE |
| :---: | :------: | :------: | :-------: | :------------: |
|  GND  |   GND    |   GND    |    GND    |      GND       |
|  PA0  |  T_EAU   |          |           |                |
|  PA9  |          |  T_AIR   |           |                |
|  PB4  |          |          |   P_OUT   |                |
| PB15  |          |          |           |      SDA       |
| PA15  |          |          |           |      SCL       |

## Différentes parties du code

### Connexions a la gatway dans le setup et envoi des packets en JSON

![Screen RECEPTION_TRAME_COMPLETE](/Tests/Lora_WAN/RECEPTION_TRAME_COMPLETE.png)

### Fonction pour la sonde de température d'eau, la sonde de pH, la sonde TDS

![informations sous JSON](résultat.png)

## Résultats obtenus

Nous pouvons nous connecter au serveur MQTT et nous arrivons à encapsuler les informations de nos capteurs en JSON
