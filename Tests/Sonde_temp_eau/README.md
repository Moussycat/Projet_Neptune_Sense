# Test Sonde de température eau (DS18B20 ou MCP9701)

## Matériel utilisé

#### Carte Arduino UNO

- Arduino UNO
- Arduino
- DS18B20

#### Carte STM32WL55 & carte finale

- STM32WL55
- Arduino
- MCP9701

## Configuration logiciel

#### Carte Arduino UNO

utilisation du logiciel Arduino

#### Carte STM32WL55 & carte finale

utilisation du logiciel Arduino avec STM32CubeProgrammer

## Pins

![Screenshot pinout](/Tests/Sonde_temp_eau/image_pinout_DS18B20.png)
![Screenshot pinout](/Tests/Sonde_temp_eau/image_pinout_MCP9701.png)

#### Carte Arduino UNO

| Arduino UNO Pin | DS18B20 Pin |
| :-------------: | :---------: |
|       GND       |     GND     |
|      3.3V       |     VCC     |
|       P4        |    VOUT     |

#### Carte STM32WL55

| STM32WL55 Pin | MCP9701 Pin |
| :-----------: | :---------: |
|      GND      |     GND     |
|      5V       |     VCC     |
|      PB1      |    VOUT     |

#### Carte finale

| Carte final Pin | DS18B20 Pin |
| :-------------: | :---------: |
|       GND       |     GND     |
|       5V        |     VCC     |
|       PA0       |    VOUT     |

## Les résultats attendus

#### Carte Arduino UNO, STM32WL55, carte finale

lorsque l'on branche le DS18B20 ou le MCP9701, on obtient une température constante

lorsque l'on met un doigt sur le DS18B20 ou le MCP9701, on voit une variation de la température (elle augmente).

lorsque l'on enleve le doigt sur le DS18B20 ou le MCP9701, on voit une variation de la température (elle diminue).

## Les résultats obtenus

#### Carte Arduino UNO

Lorsque l'on branche la carte arduino connecté au DS18B20, on observe qu'on obtient une valeur de température constante. Cela est bien le résultat attendu.

![Screenshot initial](/Tests/Sonde_temp_eau/image_mesure_initial.png)

Lorsque l'on branche la carte arduino connecté au DHT11, on observe qu'on obtient une valeur de température et humidité constante. Cela est bien le résultat attendu. Et la température varie bien quand on rajoute le doigt.

![Screenshot doigt](/Tests/Sonde_temp_eau/image_mesure_doigt.png)

#### Carte STM32WL55

On a utilisé un MCP9701 pour ce test.
Lorsque l'on met un doigt et on l'enlève , on observe bien un pic de température avec une augmentation quand le doigt est sur le capteur et une diminution de la valeur quand on l'enlève pour retourné à la valeur initial.

![Screenshot doigt](/Tests/Sonde_temp_eau/image_mesure_stm32.png)
