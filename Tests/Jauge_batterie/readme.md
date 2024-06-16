# Test Jauge de batterie

## Matériel utilisé

- Jauge de batterie
- Batterie
-

#### Carte ESP32

- ESP32 WROOM
- IDE Arduino
-

#### Carte STM32 & carte finale

- STM32WL
- IDE ARduino

#### ATTENTION : Bien changer la capacité en mAh de la batterie dans le code ici par exemple 1050mAh :

![MAH](/Tests/Jauge_batterie/MAH.png)

### Port I2C :

- GND: Broche d'alimentation, à connecter au système GND
- VCC: Broche d'alimentation, connectée à l'alimentation 5V ou 3,3V de ce module.
- SDA : Broche de signal, données série I2C
- SCL: Broche de signal, horloge série I2C

![Port I2C](/Tests/Jauge_batterie/I2C.png)

### Port OUT :

- Sortie d'alimentation, connexion à la charge ou au chargeur.
- +: Puissance de sortie Électrode positive
- -: Puissance de sortie de l'électrode négative

![Port OUT](/Tests/Jauge_batterie/OUT.png)

### Port IN :

- Entrée d'alimentation, alimentation de la sortie
- - : Entrée d'alimentation Électrode positive
- - : Électrode négative de l'entrée d'alimentation

![Port IN](/Tests/Jauge_batterie/IN.png)

### Port BATTERIE :

- Entrée batterie, supporte une batterie Li-PO de 3,7-4,2v,
- Jst2.0(2 pin-2.0mm), alimentation de la sortie.

- - : Entrée de la batterie Electrode positive
- - : Électrode négative de l'entrée de la batterie

![Port Battery](/Tests/Jauge_batterie/BATTERY.png)

## Configuration

Voici le montage utilisé pour faire le test à la différence que la batterie est remplacée par une alimentation. Au niveau du code nous avons configuré pour une batterie de 1050mAh pour l'exemple.

![SETUP](/Tests/Jauge_batterie/SETUP.png)

## Les résultats attendus

Nous devons recevoir sur le terminal le pourcentage de batterie depuis que le compteur de coulomb est alimenté.
Nous nous sommes basés sur le test de [SEEED STUDIO](https://wiki.seeedstudio.com/Grove-Coulomb_Counter_3.3V_to_5V-LTC2941)

## Les résultats obtenus

Ici on récupère bien les données, bien évidemment la capacité n'est pas récaliste puisqu'on utilise pas une vraie batterie.

![Test Jauge](/Tests/Jauge_batterie/TEST_Jauge.png)

#### Trame SCL :

![Test Jauge](/Tests/Jauge_batterie/SCL.png)

#### Trame SDA :

![Test Jauge](/Tests/Jauge_batterie/SDA.png)
