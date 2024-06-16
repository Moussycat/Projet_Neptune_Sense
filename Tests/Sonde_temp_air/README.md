# Test DHT11

## Matériel utilisé

#### Carte Arduino UNO

- Arduino UNO
- Arduino
- DHT11 (capteur de temperature et d'humidité)

#### Carte STM32WL55 & carte finale

- STM32WL55
- Arduino
- DHT11 (capteur de température et d'humidité)

## Configuration logiciel

#### Carte Arduino UNO

utilisation du logiciel Arduino

#### Carte STM32WL55 & carte finale

utilisation du logiciel Arduino avec STM32CubeProgrammer

## Pins

![Screenshot pinout](/Tests/Sonde_temp_air/image_pinout_DHT11.png)

#### Carte Arduino UNO

| Arduino UNO Pin | DHT11 Pin |
| :-------------: | :-------: |
|       GND       |    GND    |
|      3.3V       |    VCC    |
|      Pin 2      |   Data    |

#### Carte STM32WL55 & carte finale

| STM32WL55 Pin | DHT11 Pin |
| :-----------: | :-------: |
|      GND      |    GND    |
|      5V       |    VCC    |
|      PA9      |   Data    |

## Les résultats attendus

#### Carte Arduino UNO, STM32WL55, carte finale

lorsque l'on branche le DHT11, on obtient une température constante et un taux d'humitidé

lorsque l'on met un doigt sur le DHT11, on voit une variation de la température (elle augmente).

lorsque l'on enleve le doigt sur le DHT11, on voit une variation de la température (elle diminue).

## Les résultats obtenus

#### Carte Arduino UNO

Lorsque l'on branche la carte arduino connecté au DHT11, on observe qu'on obtient une valeur de température et humidité constante. Cela est bien le résultat attendu.

![Screenshot initial](/Tests/Sonde_temp_air/image_mesure_initial.png)

Lorsque l'on met un doigt et on l'enlève , on observe bien un pic de température avec une augmentation quand le doigt est sur le capteur et une diminution de la valeur quand on l'enlève pour retourné à la valeur initial.

![Screenshot doigt](/Tests/Sonde_temp_air/image_mesure_doigt.png)

#### Carte STM32WL55

Lorsque l'on branche la carte arduino connecté au DHT11, on observe qu'on obtient une valeur de température et humidité constante. Cela est bien le résultat attendu. Et la température varie bien quand on rajoute le doigt.

![Screenshot doigt](/Tests/Sonde_temp_air/image_mesure_stm32.png)

#### Carte finale
