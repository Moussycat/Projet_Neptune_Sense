# Test Sonde TDS

## Matériel utilisé

#### Carte ESP32

- ESP32
- Arduino
- TDS Meter (qualité d'eau)

#### Carte STM32WL55 & carte finale

- STM32WL55
- Arduino
- TDS Meter (qualité d'eau)

## Configuration logiciel

#### Carte ESP32

Sur Arduino, installez les board ESP32

#### Carte STM32WL55 & Carte finale

Sur Arduino, installez les board STM32 .
Installer aussi le logiciel STM32CubeProgrammer

## Pins

#### Carte ESP32

|    ESP 32 Pin     | TDS Pin |
| :---------------: | :-----: |
|        GND        |   GND   |
|       3.3V        |   VCC   |
| GPIO 27 (ADC pin) |  Data   |

#### Carte STM32WL55

| STM32WL55 Pin | TDS Pin |
| :-----------: | :-----: |
|      GND      |   GND   |
|      3V3      |   VCC   |
|      PB2      |  Data   |

#### Carte finale (pas prévu sur la PCB)

| Carte final Pin | TDS Pin |
| :-------------: | :-----: |
|       GND       |   GND   |
|       3V3       |   VCC   |
|       PB3       |  Data   |

## Les résultats attendus

#### Carte ESP32, STM32WL55, carte finale

> [!IMPORTANT]
> Pour les tests suivants de l'ESP32, l'eau était à une température élevée ( >> 25°C)

Lorsque l'on ne plonge pas la sonde, la valeur doit être de 0ppm et 0,0V.

Lorsque l'on plonge au maximum la sonde, la valeur doit être maximal selon la température de l'eau et de sa qualité.

Lorsque l'on fait varier la hauteur du niveau d'eau sur les deux broche métaliques, la valeur de ppm et de tension doit varier.

## Les résultats obtenus

#### Carte ESP32

Lorsque l'on ne plonge pas la sonde, la valeur de ppm est à 0 ppm et la valeur de la conversion de la valeur de la tension en valeur tds on obtient 0V

![Screenshot Test 0V](/Tests/Sonde_TDS_meter/picture_0V.png)

Lorsque l'on plonge totalement la sonde dans l'eau, on obtient la valeur maximum pour l'eau mesurée.
![Screenshot Test max](/Tests/Sonde_TDS_meter/picture_max.png)

Lorsque l'on fait varier le niveau de l'eau, on obtient bien une variation des valeurs.

![Screenshot Test variation](/Tests/Sonde_TDS_meter/picture_measurment.png)

#### Carte STM32WL55

Lorsque l'on plonge totalement la sonde dans l'eau, on obtient la valeur maximum pour l'eau mesurée et quand on l'enlève, on observe bien un changement de valeur qui se rapproche de la valeur de 0 ppm.

![Screenshot Test variation](/Tests/Sonde_TDS_meter/picture_measurment_STM32.png)
