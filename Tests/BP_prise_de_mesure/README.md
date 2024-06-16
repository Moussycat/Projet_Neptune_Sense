# Test Bouton prise de mesure

## Matériel utilisé

- Bouton poussoir

#### Carte STM32 & carte finale

- STM32WL
- STM32 IDE

## Pins

#### Carte STM32WL55

| STM32 PIN | Bouton poussoir |
| :-------: | :-------------: |
|   PA11    |        1        |
|    5V     |        2        |

#### Carte finale

| Carte finale PIN | Bouton poussoir |
| :--------------: | :-------------: |
|       PB10       |        1        |
|        5V        |        2        |

## Les résultats attendus

#### Carte STM32, carte finale

Lors de l'appui sur le bouton, on réalise une prise de mesure en manuel pour forcer la prise d'information.

## Les résultats obtenus

On prend bien les informations uniquement lorsque l'on appuie sur le bouton poussoir
