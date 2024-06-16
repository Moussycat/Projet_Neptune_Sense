# Test Ecran TFT

## Matériel utilisé

#### Carte ESP32 & carte finale

- ESP32 WROOM WIFI
- Arduino IDE
- Ecran TFT

## Configuration logiciel

#### Carte ESP32 & carte finale

Utilisation du logiciel Arduino IDE pour envoyer le code.

## Pins

![Screenshot pinout](/Tests/Ecran_TFT_SD/ecran_tft.jpg)

#### Carte ESP32 & carte Finale

| ESP32 PIN | Ecran TFT |
| :-------: | :-------: |
|   3,3V    |    VCC    |
|    GND    |    GND    |
|    D15    |    CS     |
|    D4     |   RESET   |
|    D2     |    DC     |
|    D23    |   MOSI    |
|    D18    |    SCK    |
|   3,3V    |    LED    |
|    D19    |   MISO    |

## Les résultats attendus

#### Carte ESP32, carte finale

On envoie des données d'affichage sur l'écran. On doit obtenir sur l'écran les données envoyées.

## Les résultats obtenus

On obtient bien le bon affichage par rapport au code envoyé.
![Screenshot affichage](/Tests/Ecran_TFT_SD/test_.jpg)

En orange se trouve la trame SCK (D18) et en vert la trame CS (D15).
![Oscillo_trame](/Tests/Ecran_TFT_SD/oscillo_trame.png)

En vert nous observons la trame MOSI (D23)
![Oscillo_trame_MOSI](/Tests/Ecran_TFT_SD/oscillo_trame_MOSI.png)
