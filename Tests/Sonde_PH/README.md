# Test Sonde de Ph

## Matériel utilisé

#### Carte Arduino UNO

- Arduino UNO
- Arduino
- Sonde de Ph

#### Carte STM32WL55 & carte finale

- STM32WL55
- Arduino
- Sonde de Ph

## Configuration logiciel

#### Carte Arduino UNO

utilisation du logiciel Arduino

#### Carte STM32WL55 & carte finale

utilisation du logiciel Arduino avec STM32CubeProgrammer

## Pins

#### Carte Arduino UNO

| Arduino UNO Pin | Sonde de Ph Pin |
| :-------------: | :-------------: |
|       GND       |       GND       |
|       5V        |       VCC       |
|       A0        |      Data       |

#### Carte STM32WL55 & carte finale

| STM32WL55 Pin | Sonde de Ph Pin |
| :-----------: | :-------------: |
|      GND      |       GND       |
|      5V       |       VCC       |
|      PB4      |      Data       |

## Les résultats attendus

#### Carte Arduino UNO, STM32WL55, carte finale

Lorsque l'on plonge la sonde dans de l'eau du robinet, la valeur doit être à 7.

## Les résultats obtenus

#### Carte Arduino UNO

Voici le montage que l'on a utilisé pour tester la sonde PH avec une arduino UNO.

![Screenshot Test variation](/Tests/Sonde_PH/picture_instalation_Arduino.jpg)

Les resultats obtenues lors de ce test sont des valeurs de pH proche de la valeur attendue.

![Screenshot Test variation](/Tests/Sonde_PH/picture_measurment_Arduino.jpg)

### Carte STM32WL55

Voici le montage que l'on a utilisé pour tester la sonde PH avec une nucleo WL55JC1.

![Screenshot Test variation](/Tests/Sonde_PH/picture_instalation_STM32.jpg)

Les resultats obtenues lors de ce test sont des valeurs de pH proche de la valeur attendue.

![Screenshot Test variation](/Tests/Sonde_PH/picture_measurment_STM32.png)

### Carte finale

Nous n'avons pas eu le temps de terminé la verification de l'envoi des bonnes infos au microcontrolleurs
